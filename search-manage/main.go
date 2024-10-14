package main

import (
	"fmt"

	"github.com/gin-gonic/gin"
	"github.com/sirupsen/logrus"
)

var logger = logrus.New()

var par2VecGrpcURL_ string = "192.168.0.20:50052"

func main() {
	fmt.Println("*********************************************")
	fmt.Println(" Similarity Search Management Server")
	fmt.Println("*********************************************")

	// For Rest API
	router := gin.New()
	router.Use(gin.Logger())

	basePath := "/recommend/"

	router.POST(basePath+"/par2vec", convertParToVec)

	// Create, delete and update a search index
	//router.GET(basePath+"/index", getSearchIndex)
	//router.POST(basePath+"/index", createSearchIndex)
	//router.DELETE(basePath+"/index", deleteSearchIndex)
	//router.PUT(basePath+"/index", updateSearchIndex)

	// Add, delete and update an element
	//router.GET(basePath+"/index/elements", getElementsOfIndex)
	//router.POST(basePath+"/index/elements", addElementsToIndex)
	//router.DELETE(basePath+"/index/elements", deleteElementsFromIndex)
	//router.PUT(basePath+"/index/elements", updateElementsOfIndex)

	// Search similar elements
	//router.POST(basePath+"/index/search", searchNeighbors)
	//router.POST(basePath+"/index/findSimilarity", computeSimilarity)

	router.Run(":8090")
}
