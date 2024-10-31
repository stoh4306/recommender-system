package main

import (
	"context"
	"fmt"
	"net/http"
	pb "recommender/proto"
	"time"

	"github.com/gin-gonic/gin"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials/insecure"
)

type Par2VecRequest struct {
	Paragraph string `json:"paragraph"`
}
type Par2VecResponse struct {
	Dim  int       `json:"dim"`
	FVec []float32 `json:"fvec"`
}
type SimpleResponse struct {
	Message string `json:"message"`
}

/*func par2vec_grpc(client pb.Par2VecClient, ctx context.Context, paragraph string) ([]float32, error) {
	r, err := client.ConvertParToVec(ctx, &pb.Par2VecRequest{Paragraph: paragraph})
	if err != nil {
		logger.Errorf("could not convert: %v", err)
		return r.GetFVec(), err
	}
	return r.GetFVec(), nil
}

func convertParToVec(c *gin.Context) {
	connPar2vec, err := grpc.NewClient(par2VecGrpcURL_, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		fmt.Printf("Failed to connect gRPC server: %v", par2VecGrpcURL_)
		return
	}
	defer connPar2vec.Close()

	client := pb.NewPar2VecClient(connPar2vec)

	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	// Convert paragraph to feature vector
	//paragraph := c.Param("par")
	var req Par2VecRequest
	c.BindJSON(&req)
	logger.Infof("paragraph= %v", req.Paragraph)
	fvec, err := par2vec_grpc(client, ctx, req.Paragraph)
	if err != nil {
		c.IndentedJSON(http.StatusInternalServerError,
			SimpleResponse{"Failed to compute feature vector from input paragraph"})
		return
	}
	//
	// Set response from feature vector
	var response Par2VecResponse
	response.Dim = len(fvec)
	response.FVec = fvec
	logger.Infof("dim=%v, fv=%v...%v", len(fvec), fvec[0], fvec[len(fvec)-1])
	c.JSON(http.StatusOK, response)
}
*/

func par2vec(paragraph string) ([]float32, error) {
	connPar2vec, err := grpc.NewClient(par2VecGrpcURL_, grpc.WithTransportCredentials(insecure.NewCredentials()))
	if err != nil {
		fmt.Printf("Failed to connect gRPC server: %v", par2VecGrpcURL_)
		return nil, err
	}
	defer connPar2vec.Close()

	client := pb.NewPar2VecClient(connPar2vec)

	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()

	// Convert paragraph to feature vector
	//logger.Infof("paragraph= %v", paragraph)

	r, err := client.ConvertParToVec(ctx, &pb.Par2VecRequest{Paragraph: paragraph})
	if err != nil {
		logger.Errorf("could not convert: %v", err)
		return nil, nil
	}

	return r.GetFVec(), nil
}

func convertParToVec(c *gin.Context) {
	var req Par2VecRequest
	c.BindJSON(&req)
	logger.Infof("paragraph= %v", req.Paragraph)
	fvec, err := par2vec(req.Paragraph)
	if err != nil {
		c.IndentedJSON(http.StatusInternalServerError,
			SimpleResponse{"Failed to compute feature vector from input paragraph"})
		return
	}

	// Set response from feature vector
	var response Par2VecResponse
	response.Dim = len(fvec)
	response.FVec = fvec
	logger.Infof("dim=%v, fv=%v...%v", len(fvec), fvec[0], fvec[len(fvec)-1])
	c.JSON(http.StatusOK, response)
}
