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

func searchIndex(client pb.VectorSearchGrpcClient, ctx context.Context,
	restapi_req *VsSearchRequest) (VsSearchResponse, error) {
	var tmpSearchRequest pb.SearchRequest
	tmpSearchRequest.IndexName = restapi_req.IndexName
	tmpSearchRequest.NumQueryVectors = restapi_req.NumQueryVectors
	tmpSearchRequest.Dim = restapi_req.Dim
	tmpSearchRequest.NumNeighbors = restapi_req.NumNeighbors
	tmpSearchRequest.VecData = restapi_req.VecData

	var tmpSearchResponse VsSearchResponse

	searchResponse, err := client.SearchNeighbors(ctx, &tmpSearchRequest)
	if err != nil {
		tmpSearchResponse.Status = "Failure"
		tmpSearchResponse.Message = "Unable to find neighbors for the given query vectors"
		return tmpSearchResponse, err
	}

	tmpSearchResponse.Status = "Success"
	tmpSearchResponse.Message = "Found " + strconv.Itoa(int(searchResponse.NumNeighbors)) + " neighbors"
	tmpSearchResponse.NumNeighbors = searchResponse.GetNumNeighbors()
	tmpSearchResponse.NumQueryVectors = searchResponse.GetNumQueryVectors()
	tmpSearchResponse.I = searchResponse.GetI()
	tmpSearchResponse.D = searchResponse.GetD()

	return tmpSearchResponse, nil
}

func searchNeighbors(c *gin.Context) {
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

	// Load the index from DB to memory
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

	// Check if the index was loaded to memory => status=200
	err = getIndexFromContainer(client, ctx, req.IndexName)
	if err != nil {
		response.Status = "Failure"
		response.Message = "Needs to load the index first : " + req.IndexName
		c.JSON(http.StatusBadRequest, response)
		return
	}

	// Now, try to search neighbors
	response, err = searchIndex(client, ctx, &req)
	if err != nil {
		response.Status = "Failure"
		response.Message = "Unable to search neighbors : " + err.Error()
		c.JSON(http.StatusInternalServerError, response)
		return
	}

	//
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

func loadIndex(client pb.VectorSearchGrpcClient, ctx context.Context, indexName string) error {
	var grpc_req pb.DefaultRequest
	grpc_req.IndexName = indexName

	_, err := client.LoadIndex(ctx, &grpc_req)

	if err != nil {
		logger.Infof("Failed to load the index in the container : %v, %v", indexName, err.Error())
		return err
	}

	logger.Infof("Loaded the index to memory : %v", indexName)

	return nil
}

func loadSearchIndex(c *gin.Context) {
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

	// Load the index from DB to memory
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

	// Check if the index was loaded to memory => status=200
	err = getIndexFromContainer(client, ctx, req.IndexName)
	if err == nil {
		response.Status = "Success"
		response.Message = "The index was already loaded : " + req.IndexName
		c.JSON(http.StatusOK, response)
		return
	}

	// Now, try to load index from DB
	err = loadIndex(client, ctx, req.IndexName)
	if err != nil {
		response.Status = "Failure"
		response.Message = "Unable to load index : " + req.IndexName + ", " + err.Error()
		c.JSON(http.StatusInternalServerError, response)
		return
	}

	//
	response.Status = "Success"
	response.Message = "Loaded an index : " + req.IndexName
	c.IndentedJSON(http.StatusOK, response)
}

func unloadIndex(client pb.VectorSearchGrpcClient, ctx context.Context, indexName string) error {
	var grpc_req pb.DefaultRequest
	grpc_req.IndexName = indexName

	_, err := client.UnloadIndex(ctx, &grpc_req)

	if err != nil {
		logger.Infof("Failed to unload the index from the container : %v, %v", indexName, err.Error())
		return err
	}

	logger.Infof("Unloaded the index from memory : %v", indexName)

	return nil
}

func unloadSearchIndex(c *gin.Context) {
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

	// Load the index from DB to memory
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

	err = getIndexFromContainer(client, ctx, req.IndexName)
	if err != nil {
		response.Status = "Failure"
		response.Message = "Not found in the container: " + req.IndexName
		c.JSON(http.StatusBadRequest, response)
		return
	}

	// Now, try to unload index from memory(container)
	err = unloadIndex(client, ctx, req.IndexName)
	if err != nil {
		response.Status = "Failure"
		response.Message = "Unable to unload index : " + req.IndexName + ", " + err.Error()
		c.JSON(http.StatusInternalServerError, response)
		return
	}

	//
	response.Status = "Success"
	response.Message = "Unloaded an index : " + req.IndexName
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
		logger.Errorf("could not convert: %v", err)
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

	// Create index with the
	//paragraph := c.Param("par")
	var req VsCreateIndexRequest
	c.BindJSON(&req)
	//logger.Infof("paragraph= %v", req.Paragraph)
	err = createIndex(client, ctx, req.IndexName, req.Dim, req.NumVectors, req.VecData)

	var response VsDefaultResponse
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
