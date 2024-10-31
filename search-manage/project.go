package main

import (
	"database/sql"
	"net/http"
	"strconv"

	"github.com/gin-gonic/gin"
	_ "github.com/go-sql-driver/mysql"
)

type Project struct {
	Title       string `json:"title"`
	Description string `json:"description"`
	Skills      string `json:"skills"`
}

type ProjectList struct {
	Projects []Project `json:"projects"`
}

func addProjectsToDB(proj *[]Project) error {
	if len(*proj) == 0 {
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

	// Add data to project table
	query := "INSERT INTO project (title, description, skills) VALUES (?, ?, ?)"

	proj_ids := make([]uint64, len(*proj))

	for i, p := range *proj {
		r, err := db.Exec(query, p.Title, p.Description, p.Skills)
		if err != nil {
			logger.Errorf("Error inserting data: %v", err)
			return err
		}
		tvalue, err := r.LastInsertId()

		if err != nil {
			logger.Errorf("Error retrieving id for the last inserted data: %v", err)
			return err
		}
		proj_ids[i] = uint64(tvalue)
	}

	// Update table : vec_to_project
	indexName := "project_collection"
	query = "SELECT num_vectors FROM search_index WHERE name = ?"
	var numVectors uint64
	err = db.QueryRow(query, indexName).Scan(&numVectors)
	if err != nil {
		logger.Errorf("Error retrieving column data: %v", err)
		return err
	}

	logger.Infof("Num-vectors in %v : %v", indexName, numVectors)

	// vec_to_project
	query = "INSERT INTO vec_to_project (vector_id, project_id) VALUES (?, ?)"
	vi := numVectors
	for i := 0; i < len(*proj); i++ {
		_, err := db.Exec(query, vi, proj_ids[i])
		if err != nil {
			logger.Errorf("Error inserting data: %v", err)
			return err
		}
		vi++
	}
	numVectors = numVectors + uint64(len(*proj))

	// Update search structure
	fvec := make([]float32, 0)
	for _, p := range *proj {
		tfv, err := par2vec(p.Description)
		if err != nil {
			logger.Errorf("Error converting to feature vector: %v", err)
			return err
		}
		fvec = append(fvec, tfv...)
	}

	nb := uint64(len(*proj))
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

func addProjects(c *gin.Context) {
	var projList ProjectList

	c.BindJSON(&projList)

	var response VsDefaultResponse
	err := addProjectsToDB(&projList.Projects)
	if err != nil {

		response.Status = "Failure"
		response.Message = err.Error()

		c.IndentedJSON(http.StatusOK, response)
		return
	}

	response.Status = "Success"
	response.Message = "added " + strconv.Itoa(len(projList.Projects)) + "projects"
	c.IndentedJSON(http.StatusOK, response)
}
