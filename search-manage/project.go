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

type SearchFreelancerResponse struct {
	Status          string    `json:"status"`
	Message         string    `json:"message"`
	NumQueryVectors uint32    `json:"numQueryVectors"`
	NumNeighbors    uint32    `json:"numNeighbors"`
	Name            []string  `json:"name"`
	D               []float32 `json:"D"`
}

func getProjectDescription(id uint32) (string, error) {
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

	proj_table := "project"
	query := "SELECT description FROM " + proj_table + " WHERE id = ?"

	descr := ""
	err = db.QueryRow(query, id).Scan(&descr)
	if err != nil {
		logger.Errorf("Error retrieving database: %v", err)
		return "", err
	}

	return descr, nil
}

func getFreelancers(ids []int64) ([]string, error) {
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

	table := "vec_to_freelancer"
	query := "SELECT freelancer_id FROM " + table + " WHERE vector_id = ?"

	free_id := uint64(0)
	freelist := make([]string, len(ids))

	query_2 := "SELECT name FROM freelancer WHERE id = ?"
	for i, vid := range ids {
		db.QueryRow(query, vid).Scan(&free_id)
		db.QueryRow(query_2, free_id).Scan(&freelist[i])
	}

	return freelist, nil
}

// Find freelancers  godoc
// @Summary      Find freelancers
// @Description  Find freelancers clost to a given project
// @Tags         Search
// @Accept       json
// @Produce      json
// @Param		 id 	path   int true  "Project Id"
// @Success      200  {object}  SearchFreelancerResponse "Found freelancers close to the input project"
// @Failure		 400  {object}  VsDefaultResponse "Project ID missing in the path"
// @Failure 	 500  {object}  VsDefaultResponse "Internal server error"
// @Router       /projects/{id}/find/freelancers [get]
func findFreelancersCloseToProject(c *gin.Context) {
	proj_id, err := strconv.Atoi(c.Param("id"))
	if err != nil {
		logger.Errorf("Missing project ID: %v", err)
		c.IndentedJSON(http.StatusBadRequest,
			gin.H{"Status": "Failure", "Message": err})
		return
	}

	proj_descr, err := getProjectDescription(uint32(proj_id))
	if err != nil {
		c.IndentedJSON(http.StatusInternalServerError, gin.H{"status": "Failure", "message": err.Error()})
		return
	}

	logger.Infof("project description for id=%v: %v", proj_id, proj_descr)
	fvec, err := par2vec(proj_descr, true)
	if err != nil {
		c.IndentedJSON(http.StatusInternalServerError,
			gin.H{"status": "Failure", "message": err})
		return
	}

	indexName := "freelancer_collection"
	k := uint32(5)
	I, D, err := searchIndex(indexName, 1, uint32(len(fvec)), k, &fvec)
	if err != nil {
		c.IndentedJSON(http.StatusInternalServerError,
			gin.H{"status": "Failure", "message": err})
		return
	}

	freelist, err := getFreelancers(I)

	var response SearchFreelancerResponse
	response.Status = "Success"
	response.Message = "Found " + strconv.Itoa(int(k)) + "neighbors"
	response.NumQueryVectors = 1
	response.NumNeighbors = k
	response.Name = freelist
	response.D = D

	c.IndentedJSON(http.StatusOK, response)
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
		tfv, err := par2vec(p.Description, true)
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
