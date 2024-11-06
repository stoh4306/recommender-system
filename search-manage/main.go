package main

import (
	"fmt"

	"github.com/gin-gonic/gin"
	"github.com/sirupsen/logrus"
)

var logger = logrus.New()

var par2VecGrpcURL_ string = "192.168.0.20:50052"
var vecSearchGrpcURL_ string = "192.168.0.20:50053"

// Connect to DB
var dsn string = "grida:MM22mm01#" + "@tcp(192.168.0.5:3306)/" + "recommender"

func main() {
	fmt.Println("*********************************************")
	fmt.Println(" Similarity Search Management Server")
	fmt.Println("*********************************************")

	// For Rest API
	router := gin.New()
	router.Use(gin.Logger())

	basePath := "/recommend/"

	router.POST(basePath+"/par2vec", convertParToVec)

	// Create, get and delete a search index
	//router.GET(basePath+"/index/:name", retrieveSearchIndex)
	router.POST(basePath+"/index", createSearchIndex)
	router.DELETE(basePath+"/index", deleteSearchIndex)
	router.GET(basePath+"/index/getList", getSearchIndexList)

	// Load, unload index
	router.POST(basePath+"/index/load", loadSearchIndex)
	router.POST(basePath+"/index/unload", unloadSearchIndex)

	// Search similar elements
	router.POST(basePath+"/index/search", searchNeighbors)

	// Projects
	router.POST(basePath+"/projects/add", addProjects)
	router.POST(basePath+"/projects/:id/find/freelancers", findFreelancersCloseToProject)

	// Freelancers
	router.POST(basePath+"/freelancers/add", addFreelancers)
	router.GET(basePath+"/freelancers/:id/find/projects", findProjectsCloseToFreelancer)

	router.Run("0.0.0.0:8090")
}
