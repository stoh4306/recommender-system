package main

import (
	"fmt"
	"net/http"
	"recommender/docs"

	"github.com/gin-gonic/gin"
	"github.com/sirupsen/logrus"

	swaggerFiles "github.com/swaggo/files"
	ginSwagger "github.com/swaggo/gin-swagger"
)

var logger = logrus.New()

var par2VecGrpcURL_ string = "192.168.0.5:50052"
var vecSearchGrpcURL_ string = "192.168.0.5:50053"

// Connect to DB
var dsn string = "grida:MM22mm01#" + "@tcp(192.168.0.5:3306)/" + "recommender"

func setupSwagger(r *gin.Engine) {
	r.GET("/", func(c *gin.Context) {
		c.Redirect(http.StatusFound, "/swagger/index.html")
	})

	r.GET("/swagger/*any", ginSwagger.WrapHandler(swaggerFiles.Handler))
}

func main() {
	fmt.Println("*********************************************")
	fmt.Println(" Similarity Search Management Server")
	fmt.Println("*********************************************")

	// Set swagger info
	docs.SwaggerInfo.Title = "Recommender API"
	docs.SwaggerInfo.Description = "This is a recommender backend server"
	docs.SwaggerInfo.Version = "1.0"
	docs.SwaggerInfo.Host = "localhost:8090"
	docs.SwaggerInfo.BasePath = "/recommend"
	docs.SwaggerInfo.Schemes = []string{"http", "https"}

	// For Rest API
	router := gin.New()
	router.Use(gin.Logger())

	// For swagger
	setupSwagger(router)

	basePath := "/recommend/"

	router.POST(basePath+"/par2vec", convertParToVec)

	// Create, get and delete a search index
	//router.GET(basePath+"/index/:name", retrieveSearchIndex)
	router.POST(basePath+"/index", createSearchIndex)
	router.DELETE(basePath+"/index", deleteSearchIndex)
	router.GET(basePath+"/index/getList", getSearchIndexList)
	router.GET(basePath+"/index/getListUnloaded", getSearchIndexListUnloaded)

	// Load, unload index
	router.POST(basePath+"/index/load", loadSearchIndex)
	router.POST(basePath+"/index/unload", unloadSearchIndex)

	// Search similar elements
	router.POST(basePath+"/index/search", searchNeighbors)

	// Projects
	router.GET(basePath+"/projects/:id", retrieveProjectData)
	router.POST(basePath+"/projects/add", addProjects)
	router.GET(basePath+"/projects/:id/find/freelancers", findFreelancersCloseToProject)
	router.GET(basePath+"/projects/getDataWithVid/:vid", getProjectDataWithVecId)

	// Freelancers
	router.GET(basePath+"/freelancers/:id", retrieveFreelancerData)
	router.POST(basePath+"/freelancers/add", addFreelancers)
	router.GET(basePath+"/freelancers/:id/find/projects", findProjectsCloseToFreelancer)
	router.GET(basePath+"/freelancers/getDataWithVid/:vid", getFreelancerDataWithVecId)

	router.Run("0.0.0.0:8090")
}
