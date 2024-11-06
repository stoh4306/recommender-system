package main

import (
	"database/sql"
	"net/http"
	"strconv"

	"github.com/gin-gonic/gin"
)

type Freelancer struct {
	Name         string `json:"name"`
	Introduction string `json:"introduction"`
	Skills       string `json:"skills"`
}

type FreelancerList struct {
	Freelancers []Freelancer `json:"freelancers"`
}

type SearchProjectResponse = SearchFreelancerResponse

func getFreelancerIntroduction(id uint32) (string, error) {
	// Connect to DB
	db, err := sql.Open("mysql", dsn)
	if err != nil {
		logger.Errorf("Error opening database connection: %v", err)
		return "", err
	}
	defer db.Close()

	if err := db.Ping(); err != nil {
		logger.Errorf("Error pinging database: %v", err)
		return "", err
	}
	logger.Infoln("Successfully connected to the database")

	table := "freelancer"
	col := "introduction"
	query := "SELECT " + col + " FROM " + table + " WHERE id = ?"

	intro := ""
	err = db.QueryRow(query, id).Scan(&intro)
	if err != nil {
		logger.Errorf("Error retrieving database: %v", err)
		return "", err
	}

	return intro, nil
}

func getProjects(ids []int64) ([]string, error) {
	// Connect to DB
	db, err := sql.Open("mysql", dsn)
	if err != nil {
		logger.Errorf("Error opening database connection: %v", err)
		return nil, err
	}
	defer db.Close()

	if err := db.Ping(); err != nil {
		logger.Errorf("Error pinging database: %v", err)
		return nil, err
	}
	logger.Infoln("Successfully connected to the database")

	// Query to find project_id from vector_id
	table := "vec_to_project"
	col := "project_id"
	query := "SELECT " + col + " FROM " + table + " WHERE vector_id = ?"

	// Query to find project name from project id
	table2 := "project"
	col2 := "title"
	query_2 := "SELECT " + col2 + " FROM " + table2 + " WHERE id = ?"

	proj_id := uint64(0)
	projlist := make([]string, len(ids))

	for i, vid := range ids {
		db.QueryRow(query, vid).Scan(&proj_id)
		logger.Infof("vid=%v, proj_id=%v", vid, proj_id)
		db.QueryRow(query_2, proj_id).Scan(&projlist[i])
	}

	return projlist, nil
}

func findProjectsCloseToFreelancer(c *gin.Context) {
	free_id, err := strconv.Atoi(c.Param("id"))
	if err != nil {
		logger.Errorf("Missing freelancer ID: %v", err)
		c.IndentedJSON(http.StatusBadRequest,
			gin.H{"Status": "Failure", "Message": err})
		return
	}

	free_intro, err := getFreelancerIntroduction(uint32(free_id))
	if err != nil {
		c.IndentedJSON(http.StatusInternalServerError, gin.H{"status": "Failure", "message": err.Error()})
		return
	}

	logger.Infof("freelancer introduction for id=%v: %v", free_id, free_intro)
	fvec, err := par2vec(free_intro)
	if err != nil {
		c.IndentedJSON(http.StatusInternalServerError,
			gin.H{"status": "Failure", "message": err})
		return
	}

	indexName := "project_collection"
	k := uint32(5)
	I, D, err := searchIndex(indexName, 1, uint32(len(fvec)), k, &fvec)
	if err != nil {
		c.IndentedJSON(http.StatusInternalServerError,
			gin.H{"status": "Failure", "message": err})
		return
	}
	logger.Infof("I=%v", I)

	projlist, err := getProjects(I)
	if err != nil {
		c.IndentedJSON(http.StatusInternalServerError,
			gin.H{"status": "Failure", "message": err})
		return
	}

	var response SearchProjectResponse
	response.Status = "Success"
	response.Message = "Found " + strconv.Itoa(int(k)) + "neighbors"
	response.NumQueryVectors = 1
	response.NumNeighbors = k
	response.Name = projlist
	response.D = D

	c.IndentedJSON(http.StatusOK, response)
}

func addFreelancersToDB(free *[]Freelancer) error {
	if len(*free) == 0 {
		return nil
	}

	// Connect to DB
	dsn := "grida:MM22mm01#" + "@tcp(192.168.0.5:3306)/" + "recommender"

	db, err := sql.Open("mysql", dsn)
	if err != nil {
		logger.Errorf("Error opening database connection: %v", err)
	}
	defer db.Close()

	if err := db.Ping(); err != nil {
		logger.Errorf("Error pinging database: %v", err)
	}
	logger.Infoln("Successfully connected to the database")

	// Add data to freelancer table
	query := "INSERT INTO freelancer (name, introduction, skills) VALUES (?, ?, ?)"

	free_ids := make([]uint64, len(*free))

	for i, p := range *free {
		r, err := db.Exec(query, p.Name, p.Introduction, p.Skills)
		if err != nil {
			logger.Errorf("Error inserting data: %v", err)
			return err
		}
		tvalue, err := r.LastInsertId()

		if err != nil {
			logger.Errorf("Error retrieving id for the last inserted data: %v", err)
			return err
		}
		free_ids[i] = uint64(tvalue)
	}

	// Update table : vec_to_freelancer
	indexName := "freelancer_collection"
	query = "SELECT num_vectors FROM search_index WHERE name = ?"
	var numVectors uint64
	err = db.QueryRow(query, indexName).Scan(&numVectors)
	if err != nil {
		logger.Errorf("Error retrieving column data: %v", err)
		return err
	}

	logger.Infof("Num-vectors in %v : %v", indexName, numVectors)

	// vec_to_project
	query = "INSERT INTO vec_to_freelancer (vector_id, freelancer_id) VALUES (?, ?)"
	vi := numVectors
	for i := 0; i < len(*free); i++ {
		_, err := db.Exec(query, vi, free_ids[i])
		if err != nil {
			logger.Errorf("Error inserting data: %v", err)
			return err
		}
		vi++
	}
	numVectors = numVectors + uint64(len(*free))

	// Update search structure
	fvec := make([]float32, 0)
	for _, p := range *free {
		tfv, err := par2vec(p.Introduction)
		if err != nil {
			logger.Errorf("Error converting to feature vector: %v", err)
			return err
		}
		fvec = append(fvec, tfv...)
	}

	nb := uint64(len(*free))
	dim := uint64(len(fvec)) / nb
	err = addVectors(indexName, uint32(dim), nb, &fvec)
	if err != nil {
		logger.Errorf("Error adding vectors: %v", err)
		return err
	}

	// Finally, update search_index
	query = "UPDATE search_index SET num_vectors = ? WHERE name = ?"

	_, err = db.Exec(query, numVectors, indexName)
	if err != nil {
		logger.Errorf("Error updating num_vectors: %v", err)
		return err
	}

	return nil
}

func addFreelancers(c *gin.Context) {
	var freeList FreelancerList
	c.BindJSON(&freeList)

	var response VsDefaultResponse
	err := addFreelancersToDB(&freeList.Freelancers)
	if err != nil {

		response.Status = "Failure"
		response.Message = err.Error()

		c.IndentedJSON(http.StatusOK, response)
		return
	}

	response.Status = "Success"
	response.Message = "added " + strconv.Itoa(len(freeList.Freelancers)) + "freelancers"
	c.IndentedJSON(http.StatusOK, response)
}
