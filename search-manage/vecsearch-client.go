package main

import (
	"context"
	"fmt"
	"net/http"
	pb "recommender/proto-vecsearch"
	"strconv"
	"time"

	"github.com/gin-gonic/gin"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

type VsVectors struct {
	NumVectors uint64    `json:"numVectors"`
	Dim        uint32    `json:"dim"`
	VecData    []float32 `json:"vecData"`
}

type VsIndexList struct {
	IndexName  []string `json:"indexName"`
	NumVectors []uint64 `json:"numVectors"`
	Dim        []uint32 `json:"dim"`
}

type VsCreateIndexRequest struct {
	IndexName  string    `json:"indexName"`
	NumVectors uint64    `json:"numVectors"`
	Dim        uint32    `json:"dim"`
	VecData    []float32 `json:"vecData"`
}

type VsAddVectorsRequest = VsCreateIndexRequest

type VsDefaultRequest struct {
	IndexName string `json:"indexName"`
}

type VsDefaultResponse struct {
	Status  string `json:"status"`
	Message string `json:"message"`
}

type VsSearchRequest struct {
	IndexName       string    `json:"indexName"`
	NumQueryVectors uint32    `json:"numQueryVectors"`
	Dim             uint32    `json:"dim"`
	VecData         []float32 `json:"vecData"`
	NumNeighbors    uint32    `json:"numNeighbors"`
}

type VsSearchResponse struct {
	Status          string    `json:"status"`
	Message         string    `json:"message"`
	NumQueryVectors uint32    `json:"numQueryVectors"`
	NumNeighbors    uint32    `json:"numNeighbors"`
	I               []int64   `json:"I"`
	D               []float32 `json:"D"`
}

func searchIndex(indexName string, nq uint32, dim uint32, k uint32, xq *[]float32) ([]int64, []float32, error) {
	// Make a connection to the grpc server
	connVecSearchGrpc, err := grpc.NewClient(vecSearchGrpcURL_, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		logger.Errorf("Failed to connect gRPC server: %v", vecSearchGrpcURL_)
		return nil, nil, err
	}
	defer connVecSearchGrpc.Close()

	client := pb.NewVectorSearchGrpcClient(connVecSearchGrpc)

	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	_, err = client.GetIndexFromContainer(ctx, &pb.DefaultRequest{IndexName: indexName})
	if err != nil {
		logger.Errorf("Request index not found in memory. Try to load index first")
		return nil, nil, err
	}

	var request pb.SearchRequest
	request.IndexName = indexName
	request.NumQueryVectors = nq
	request.Dim = dim
	request.NumNeighbors = k
	request.VecData = *xq

	response, err := client.SearchNeighbors(ctx, &request)
	if err != nil {
		return nil, nil, err
	}

	return response.I, response.D, nil
}

// Search neighbors  godoc
// @Summary      Find neighbor items for a given feature vector
// @Description  Find neighbor items for a given feature vector
// @Tags         Index
// @Accept       json
// @Produce      json
// @Param		 Request body VsSearchRequest true "Search request"
// @Success      200  {object}  VsSearchResponse "Found neighbors close to the input feature vector"
// @Failure		 400  {object}  VsSearchResponse ""
// @Failure 	 500  {object}  VsSearchResponse "Internal server error"
// @Router       /index/search [post]
func searchNeighbors(c *gin.Context) {
	var req VsSearchRequest
	c.BindJSON(&req)

	var response VsSearchResponse

	// Check if input parameters are  valid
	if req.IndexName == "" {
		response.Status = "Failure"
		response.Message = "Name parameter is required"
		c.JSON(http.StatusBadRequest, response)
		return
	} else if req.Dim == 0 {
		response.Status = "Failure"
		response.Message = "Dim should be a positive integer"
		c.JSON(http.StatusBadRequest, response)
		return
	} else if req.NumNeighbors == 0 {
		response.Status = "Failure"
		response.Message = "NumNeighbors should be a positive integer"
		c.JSON(http.StatusBadRequest, response)
		return
	} else if req.NumQueryVectors == 0 {
		response.Status = "Failure"
		response.Message = "Number of query vectors should be positive integer"
		c.JSON(http.StatusBadRequest, response)
		return
	} else if uint32(len(req.VecData)) != req.Dim*req.NumQueryVectors {
		response.Status = "Failure"
		response.Message = "Query vector array size is incorrect"
		c.JSON(http.StatusBadRequest, response)
		return
	}

	// Now, try to search neighbors
	I, D, err := searchIndex(req.IndexName, req.NumQueryVectors, req.Dim, req.NumNeighbors, &req.VecData)
	if err != nil {
		response.Status = "Failure"
		response.Message = "Unable to search neighbors : " + err.Error()
		c.JSON(http.StatusInternalServerError, response)
		return
	}

	//
	response.Status = "Success"
	response.Message = "Found " + strconv.Itoa(int(req.NumNeighbors)) + " neighbors"
	response.NumNeighbors = req.NumNeighbors
	response.NumQueryVectors = req.NumQueryVectors
	response.I = I
	response.D = D
	c.IndentedJSON(http.StatusOK, response)
}

func getListOfLoadedIndex(client pb.VectorSearchGrpcClient, ctx context.Context,
	indexName *[]string, numVectors *[]uint64, dim *[]uint32) error {
	var empty_resquest pb.EmptyRequest

	response, err := client.ListLoadedIndex(ctx, &empty_resquest)

	if err != nil {
		logger.Infof("Failed to get the list of indices loaded to memory: %v", err.Error())
		return err
	}

	*indexName = append(*indexName, response.GetIndexName()...)
	*numVectors = append(*numVectors, response.GetNumVectors()...)
	*dim = append(*dim, response.GetDim()...)

	return nil
}

// Get a list of loaded indices godoc
// @Summary      Get a list of all loadded indices
// @Description  Get a list of all loaded indices
// @Tags         Index
// @Accept       json
// @Produce      json
// @Success      200  {object}  VsIndexList ""
// @Failure 	 500  {object}	VsDefaultResponse "Internal server error"
// @Router       /index/getList [get]
func getSearchIndexList(c *gin.Context) {
	// Make a connection to the grpc server
	connVecSearchGrpc, err := grpc.NewClient(vecSearchGrpcURL_, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		fmt.Printf("Failed to connect gRPC server: %v", vecSearchGrpcURL_)
		return
	}
	defer connVecSearchGrpc.Close()

	client := pb.NewVectorSearchGrpcClient(connVecSearchGrpc)

	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	// Get the list of indices in the container
	indexName := []string{}
	numVectors := []uint64{}
	dim := []uint32{}

	err = getListOfLoadedIndex(client, ctx, &indexName, &numVectors, &dim)

	if err != nil {
		var response VsDefaultResponse
		response.Status = "Failure"
		response.Message = "Unable to get the list of the loaded search indices"
		c.JSON(http.StatusInternalServerError, response)
		return
	}

	var success_response VsIndexList
	success_response.IndexName = indexName
	success_response.NumVectors = numVectors
	success_response.Dim = dim
	c.JSON(http.StatusOK, success_response)
}

func getIndexFromContainer(client pb.VectorSearchGrpcClient, ctx context.Context, indexName string) error {

	var grpc_req pb.DefaultRequest
	grpc_req.IndexName = indexName

	_, err := client.GetIndexFromContainer(ctx, &grpc_req)
	if err != nil {
		logger.Infof("Failed to find the index in the container : %v", indexName)
		return err

	}
	logger.Infof("Found the index in the container: %v", indexName)
	return nil
}

func loadIndex(indexName string) (string, error) {
	// Make a connection to the grpc server
	connVecSearchGrpc, err := grpc.NewClient(vecSearchGrpcURL_, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		logger.Errorf("Failed to connect gRPC server: %v", vecSearchGrpcURL_)
		return "", err
	}
	defer connVecSearchGrpc.Close()

	client := pb.NewVectorSearchGrpcClient(connVecSearchGrpc)

	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	var grpc_req pb.DefaultRequest
	grpc_req.IndexName = indexName

	// Check if the index is already loaded
	_, err = client.GetIndexFromContainer(ctx, &grpc_req)
	if err == nil {
		tmpMesg := fmt.Sprintf("The index already loaded: %v", indexName)
		logger.Infof(tmpMesg)
		return tmpMesg, nil
	}

	// Load index to memory
	_, err = client.LoadIndex(ctx, &grpc_req)
	if err != nil {
		logger.Infof("Failed to load the index in the container : %v, %v", indexName, err.Error())
		return "", err
	}
	logger.Infof("Loaded the index to memory : %v", indexName)
	return "", nil
}

// Load index godoc
// @Summary      Load index
// @Description  Load index from DB to memory
// @Tags         Index
// @Accept       json
// @Produce      json
// @Param        Request   body VsDefaultRequest  true  "Default request"
// @Success      200  {object}  VsDefaultResponse "Loaded index"
// @Failure		 400  {object}  VsDefaultResponse "Name parameter required"
// @Failure 	 500  {object}  VsDefaultResponse "Internal server error"
// @Router       /index/load [post]
func loadSearchIndex(c *gin.Context) {
	var req VsDefaultRequest
	c.BindJSON(&req)

	var response VsDefaultResponse
	// Return if the index name is empty
	if req.IndexName == "" {
		response.Status = "Failure"
		response.Message = "Name parameter is required"
		c.JSON(http.StatusBadRequest, response)
		return
	}

	// Load the index from DB to memory
	mesg, err := loadIndex(req.IndexName)
	if err != nil {
		response.Status = "Failure"
		response.Message = err.Error()
		c.JSON(http.StatusInternalServerError, response)
		return
	}

	//
	response.Status = "Success"
	if mesg != "" {
		response.Message = mesg
	} else {
		response.Message = "Loaded index : " + req.IndexName
	}
	c.IndentedJSON(http.StatusOK, response)
}

func unloadIndex(indexName string) (string, error) {
	// Make a connection to the grpc server
	connVecSearchGrpc, err := grpc.NewClient(vecSearchGrpcURL_, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		logger.Errorf("Failed to connect gRPC server: %v", vecSearchGrpcURL_)
		return "", err
	}
	defer connVecSearchGrpc.Close()

	client := pb.NewVectorSearchGrpcClient(connVecSearchGrpc)

	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	var grpc_req pb.DefaultRequest
	grpc_req.IndexName = indexName
	_, err = client.GetIndexFromContainer(ctx, &grpc_req)
	if err != nil {
		mesg := fmt.Sprintf("The index not found in memory: %v", indexName)
		logger.Infof(mesg)
		return mesg, nil
	}

	_, err = client.UnloadIndex(ctx, &grpc_req)
	if err != nil {
		logger.Errorf("Failed to unload index: %v", err)
		return "", err
	}
	logger.Infof("Successfully unloaded index: %v", indexName)
	return "", nil
}

// Unload index godoc
// @Summary      Unload index
// @Description  Unload index from memory
// @Tags         Index
// @Accept       json
// @Produce      json
// @Param        Request   body VsDefaultRequest  true  "Default request"
// @Success      200  {object}  VsDefaultResponse "Unloaded index"
// @Failure		 400  {object}  VsDefaultResponse "Name parameter required"
// @Failure 	 500  {object}  VsDefaultResponse "Internal server error"
// @Router       /index/unload [post]
func unloadSearchIndex(c *gin.Context) {
	var req VsDefaultRequest
	c.BindJSON(&req)

	var response VsDefaultResponse

	// Return if the index name is empty
	if req.IndexName == "" {
		response.Status = "Failure"
		response.Message = "Name parameter is required"
		c.JSON(http.StatusBadRequest, response)
		return
	}

	// Now, try to unload index from memory(container)
	mesg, err := unloadIndex(req.IndexName)
	if err != nil {
		response.Status = "Failure"
		response.Message = err.Error()
		c.JSON(http.StatusInternalServerError, response)
		return
	}

	//
	response.Status = "Success"
	if mesg != "" {
		response.Message = mesg
	} else {
		response.Message = "Unloaded an index : " + req.IndexName
	}
	c.IndentedJSON(http.StatusOK, response)
}

func createIndex(client pb.VectorSearchGrpcClient, ctx context.Context,
	indexName string, dim uint32, nb uint64, xb []float32) error {

	var request pb.CreateIndexRequest
	request.IndexName = indexName
	request.NumVectors = nb
	request.Dim = dim
	request.VecData = xb

	_, err := client.CreateIndex(ctx, &request)
	if err != nil {
		logger.Errorf("could not create: %v", err)
		return err
	}
	logger.Infof("- Successfully created index : %v", indexName)
	return nil
}

func createSearchIndex(c *gin.Context) {
	connVecSearchGrpc, err := grpc.NewClient(vecSearchGrpcURL_, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		fmt.Printf("Failed to connect gRPC server: %v", vecSearchGrpcURL_)
		return
	}
	defer connVecSearchGrpc.Close()

	client := pb.NewVectorSearchGrpcClient(connVecSearchGrpc)

	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	// Create an index
	var req VsCreateIndexRequest
	c.BindJSON(&req)

	var response VsDefaultResponse

	if req.IndexName == "" {
		response.Status = "Failure"
		response.Message = "No index name"
		c.IndentedJSON(http.StatusBadRequest, response)
		return
	}

	err = createIndex(client, ctx, req.IndexName, req.Dim, req.NumVectors, req.VecData)

	if err != nil {
		response.Status = "Failure"
		response.Message = "Unable to create index : " + req.IndexName + ", " + err.Error()
		c.IndentedJSON(http.StatusInternalServerError, response)
		return
	}
	//
	// Set response from feature vector

	response.Status = "Success"
	response.Message = "Created an index : " + req.IndexName
	c.IndentedJSON(http.StatusOK, response)
}

func deleteIndex(client pb.VectorSearchGrpcClient, ctx context.Context, indexName string) (*pb.DefaultReply, error) {
	var request pb.DefaultRequest
	request.IndexName = indexName

	response, err := client.DeleteIndex(ctx, &request)
	if err != nil {
		logger.Errorf("could not delete the index: %v, %v", indexName, err)
		return response, err
	}
	logger.Infof("- Successfully deleted index : %v", indexName)
	return response, nil
}

func deleteSearchIndex(c *gin.Context) {
	connVecSearchGrpc, err := grpc.NewClient(vecSearchGrpcURL_, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		fmt.Printf("Failed to connect gRPC server: %v", vecSearchGrpcURL_)
		return
	}
	defer connVecSearchGrpc.Close()

	client := pb.NewVectorSearchGrpcClient(connVecSearchGrpc)

	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	// Delete index from both container and DB
	var req VsDefaultRequest
	c.BindJSON(&req)
	grpc_response, err := deleteIndex(client, ctx, req.IndexName)

	var response VsDefaultResponse
	if err != nil {
		response.Status = "Failure"
		response.Message = "Unable to delete index : " + req.IndexName + ", " + err.Error()
		c.IndentedJSON(http.StatusInternalServerError, response)
		return
	}
	//
	// Set response from feature vector

	response.Status = "Success"
	response.Message = grpc_response.Message
	c.IndentedJSON(http.StatusOK, response)
}

/* func addVectors(client pb.VectorSearchGrpcClient, ctx context.Context,
	indexName string, dim uint32, nb uint64, xb []float32) error {

	var request pb.CreateIndexRequest
	request.IndexName = indexName
	request.NumVectors = nb
	request.Dim = dim
	request.VecData = xb

	_, err := client.AddVectors(ctx, &request)
	if err != nil {
		logger.Errorf("could not add vectors: %v", err)
		return err
	}
	logger.Infof("- Successfully add vectors to index : %v", indexName)
	return nil
}

func addElementsToIndex(c *gin.Context) {
	connVecSearchGrpc, err := grpc.NewClient(vecSearchGrpcURL_, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		fmt.Printf("Failed to connect gRPC server: %v", vecSearchGrpcURL_)
		return
	}
	defer connVecSearchGrpc.Close()

	client := pb.NewVectorSearchGrpcClient(connVecSearchGrpc)

	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	// Create an index
	var req VsAddVectorsRequest
	c.BindJSON(&req)

	var response VsDefaultResponse

	if req.IndexName == "" {
		response.Status = "Failure"
		response.Message = "No index name"
		c.IndentedJSON(http.StatusBadRequest, response)
		return
	}

	err = addVectors(client, ctx, req.IndexName, req.Dim, req.NumVectors, req.VecData)

	if err != nil {
		response.Status = "Failure"
		response.Message = "Unable to add vectors to index : " + req.IndexName + ", " + err.Error()
		c.IndentedJSON(http.StatusInternalServerError, response)
		return
	}
	//
	// Set response from feature vector

	response.Status = "Success"
	response.Message = "Added vectors to index : " + req.IndexName
	c.IndentedJSON(http.StatusOK, response)
} */

func addVectors(indexName string, dim uint32, nb uint64, xb *[]float32) error {
	connVecSearchGrpc, err := grpc.NewClient(vecSearchGrpcURL_, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		fmt.Printf("Failed to connect gRPC server: %v", vecSearchGrpcURL_)
		return err
	}
	defer connVecSearchGrpc.Close()

	client := pb.NewVectorSearchGrpcClient(connVecSearchGrpc)

	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	var request pb.CreateIndexRequest
	request.IndexName = indexName
	request.NumVectors = nb
	request.Dim = dim
	request.VecData = *xb

	_, err = client.AddVectors(ctx, &request)
	if err != nil {
		logger.Errorf("could not add vectors: %v", err)
		return err
	}
	logger.Infof("- Successfully add vectors to index : %v", indexName)
	return nil
}

/*
func addElementsToIndex(c *gin.Context) {
	// Create an index
	var req VsAddVectorsRequest
	c.BindJSON(&req)

	var response VsDefaultResponse

	if req.IndexName == "" {
		response.Status = "Failure"
		response.Message = "No index name"
		c.IndentedJSON(http.StatusBadRequest, response)
		return
	}

	err := addVectors(req.IndexName, req.Dim, req.NumVectors, &req.VecData)

	if err != nil {
		response.Status = "Failure"
		response.Message = "Unable to add vectors to index : " + req.IndexName + ", " + err.Error()
		c.IndentedJSON(http.StatusInternalServerError, response)
		return
	}

	// Set response from feature vector

	response.Status = "Success"
	response.Message = "Added vectors to index : " + req.IndexName
	c.IndentedJSON(http.StatusOK, response)
}
*/

/*func retrieveSearchIndex(c * gin.Context) {
	// Create a grpc connection
	connVecSearchGrpc, err := grpc.NewClient(vecSearchGrpcURL_, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		fmt.Printf("Failed to connect gRPC server: %v", vecSearchGrpcURL_)
		return
	}
	defer connVecSearchGrpc.Close()

	client := pb.NewVectorSearchGrpcClient(connVecSearchGrpc)

	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	// Get index information
	var req VsDefaultRequest
	c.BindJSON(&req)
	err = Index(client, ctx, req.IndexName)

	var response VsDefaultResponse
	if err != nil {
		response.Status = "Failure"
		response.Message = "Unable to delete index : " + req.IndexName + ", " + err.Error()
		c.IndentedJSON(http.StatusInternalServerError, response)
		return
	}
	//
	// Set response from feature vector

	response.Status = "Success"
	response.Message = "Delete the index : " + req.IndexName
	c.IndentedJSON(http.StatusOK, response)
}//*/
