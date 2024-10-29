package main

import (
	"fmt"

	"github.com/gin-gonic/gin"
	"github.com/sirupsen/logrus"
)

var logger = logrus.New()

var par2VecGrpcURL_ string = "192.168.0.20:50052"
var vecSearchGrpcURL_ string = "192.168.0.20:50053"

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
	//router.DELETE(basePath+"/index", deleteSearchIndex)
	router.GET(basePath+"/index/getList", getSearchIndexList)

	// Load index from DB to memory
	router.POST(basePath+"/index/load", loadSearchIndex)
	//router.POST(basePath+"/index/unload", unloadSearchIndex)

	// Add, delete and update an element
	//router.GET(basePath+"/index/elements", getElementsOfIndex)
	//router.POST(basePath+"/index/elements", addElementsToIndex)
	//router.DELETE(basePath+"/index/elements", deleteElementsFromIndex)
	//router.PUT(basePath+"/index/elements", updateElementsOfIndex)

	// Search similar elements
	router.POST(basePath+"/index/elements/search", searchNeighbors)

	router.Run("0.0.0.0:8090")
}
