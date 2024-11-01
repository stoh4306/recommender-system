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
