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

// Find projects  godoc
// @Summary      Find projects
// @Description  Find freelancers clost to a given project
// @Tags         Search
// @Accept       json
// @Produce      json
// @Param		 id 	path   int true  "Freelancer Id"
// @Success      200  {object}  SearchProjectResponse "Found projects close to the input freelancer"
// @Failure		 400  {object}  VsDefaultResponse "Freelancer ID missing in the path"
// @Failure 	 500  {object}  VsDefaultResponse "Internal server error"
// @Router       /freelancers/{id}/find/projects [get]
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
	fvec, err := par2vec(free_intro, true)
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

func getFreelancerData(ids []uint64) ([]Freelancer, error) {
	freeData := []Freelancer{}

	// Connect to DB
	db, err := sql.Open("mysql", dsn)
	if err != nil {
		logger.Errorf("Error opening database connection: %v", err)
		return freeData, err
	}
	defer db.Close()

	if err := db.Ping(); err != nil {
		logger.Errorf("Error pinging database: %v", err)
		return freeData, err
	}
	logger.Infoln("Successfully connected to the database")

	table := "freelancer"
	query := "SELECT name, introduction, skills FROM " + table + " WHERE id = ?"

	for _, free_id := range ids {
		rows, err := db.Query(query, free_id)
		if err != nil {
			logger.Errorf("Error retrieving database: %v", err)
			return freeData, err
		}

		var name, intro, skills string
		for rows.Next() {
			err = rows.Scan(&name, &intro, &skills)
			if err != nil {
				logger.Errorf("Error retrieving database: %v", err)
				return freeData, err
			}

			freeData = append(freeData, Freelancer{Name: name, Introduction: intro, Skills: skills})
			break
		}
	}

	return freeData, nil
}

// Retrieve freelancer data  godoc
// @Summary      Retrieve freelancer data with project id
// @Description  Retrieve freelancer data with project id
// @Tags         Project/Freelancer
// @Accept       json
// @Produce      json
// @Param		 id 	path   int true  "Freelancer Id"
// @Success      200  {object}  FreelancerList "Retrieved project data"
// @Failure		 400  {object}  VsDefaultResponse "Freelancer ID missing in the path or is not a proper integer"
// @Failure 	 500  {object}  VsDefaultResponse "Internal server error"
// @Router       /freelancers/{id} [get]
func retrieveFreelancerData(c *gin.Context) {
	id, err := strconv.Atoi(c.Param("id"))
	if err != nil {
		c.IndentedJSON(http.StatusBadRequest, gin.H{
			"status":  "Failure",
			"message": "id parameter is missing or is not a proper integer",
		})
		return
	}

	ids := make([]uint64, 1)
	ids[0] = uint64(id)
	freelancerData, err := getFreelancerData(ids)
	if err != nil {
		c.IndentedJSON(http.StatusInternalServerError, gin.H{
			"status":  "Failure",
			"message": err.Error(),
		})
		return
	}

	c.IndentedJSON(http.StatusOK, FreelancerList{Freelancers: freelancerData})
}

func findFreelancerId(vid int) (uint64, error) {
	// Connect to DB
	db, err := sql.Open("mysql", dsn)
	if err != nil {
		logger.Errorf("Error opening database connection: %v", err)
		return 0, err
	}
	defer db.Close()

	if err := db.Ping(); err != nil {
		logger.Errorf("Error pinging database: %v", err)
		return 0, err
	}
	logger.Infoln("Successfully connected to the database")

	table := "vec_to_freelancer"
	query := "SELECT freelancer_id FROM " + table + " WHERE vector_id = ?"

	var fid uint64 = 0
	err = db.QueryRow(query, vid).Scan(&fid)
	if err != nil {
		logger.Errorf("Error retrieving database: %v", err)
		return 0, err
	}

	return uint64(fid), nil
}

// Retrieve freelancer data  godoc
// @Summary      Retrieve freelancer data with a vector id
// @Description  Retrieve freelancer data with a vector id
// @Tags         Project/Freelancer
// @Accept       json
// @Produce      json
// @Param		 vid 	path   int true  "Vector Id"
// @Success      200  {object}  FreelancerList "Retrieved freelancer data"
// @Failure		 400  {object}  VsDefaultResponse "Project ID missing in the path or is not a proper integer"
// @Failure 	 500  {object}  VsDefaultResponse "Internal server error"
// @Router       /freelancers/getDataWithVid/{vid} [get]
func getFreelancerDataWithVecId(c *gin.Context) {
	vid, err := strconv.Atoi(c.Param("vid"))
	if err != nil {
		mesg := "Vector index missing or invalid vector index"
		logger.Errorf(mesg)
		c.IndentedJSON(http.StatusBadRequest, gin.H{
			"status":  "Failure",
			"message": mesg,
		})
		return
	}

	fid := make([]uint64, 1)
	fid[0], err = findFreelancerId(vid)
	if err != nil {
		mesg := "Failed to find the freelancer id with the input"
		logger.Errorf(mesg)
		c.IndentedJSON(http.StatusBadRequest, gin.H{
			"status":  "Failure",
			"message": err,
		})
		return
	}

	free, err := getFreelancerData(fid)
	if err != nil {
		mesg := "Failed to retrieve the freelancer data with the freelancer id"
		logger.Errorf(mesg)
		c.IndentedJSON(http.StatusBadRequest, gin.H{
			"status":  "Failure",
			"message": err,
		})
		return
	}
	c.IndentedJSON(http.StatusOK, FreelancerList{Freelancers: free})
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
		tfv, err := par2vec(p.Introduction, true)
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
