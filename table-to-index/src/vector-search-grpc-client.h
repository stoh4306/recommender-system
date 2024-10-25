#pragma once

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "./proto/vecsearch.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

using vecsearchgrpc::CreateIndexRequest;
using vecsearchgrpc::DefaultRequest;
//using vecsearchgrpc::DefaultReply;
using vecsearchgrpc::SearchRequest;
using vecsearchgrpc::SearchReply;
using vecsearchgrpc::VectorSearchGrpc;

class VectorSearchGrpcClient {
public:
    VectorSearchGrpcClient(std::shared_ptr<Channel> channel) 
        : stub_(VectorSearchGrpc::NewStub(channel)) {
    }

    void createIndex(std::string indexName, unsigned long dim, unsigned long nb, float* v) {
        ClientContext context;

        // Make a CreateIndexRequest
        CreateIndexRequest request;
        request.set_indexname(indexName);
        request.set_numvectors(nb);
        request.set_dim(dim);
        for(unsigned long i = 0; i < nb*dim; ++i) {
            request.add_vecdata(v[i]);
        }
        std::cout << "num vectors = " << request.mutable_vecdata()->size() / dim << std::endl;
        vecsearchgrpc::DefaultReply response;
        Status stat = stub_->createIndex(&context, request, &response);
        if (stat.ok()) {
            std::cout << "gRPC call createIndex : SUCCESS" << std::endl;
        } else {
            std::cout << "gRPC call create index : FAILURE" << std::endl;
            std::cout << stat.error_code() << ", " << stat.error_message() << "," << stat.error_details() << std::endl;
        }

        std::cout << "Response:" << response.status() << ",\n" << response.message() << std::endl;
    }

    void deleteIndex(std::string indexName) {
        ClientContext context;

        DefaultRequest request;
        request.set_indexname(indexName);

        vecsearchgrpc::DefaultReply response;
        Status stat = stub_->deleteIndex(&context, request, &response);
        if (!stat.ok()) {
            std::cout << "- [ERROR] Failed to delete index : " << indexName << std::endl;
            std::cout << stat.error_code() << ", " << stat.error_message() << "," << stat.error_details() << std::endl;
        }
        std::cout << "- Response : " << response.status() << ", " << response.message() << std::endl;
    }

    void loadIndex(std::string indexName) {
        ClientContext context;

        DefaultRequest request;
        request.set_indexname(indexName);

        vecsearchgrpc::DefaultReply response;
        Status stat = stub_->loadIndex(&context, request, &response);
        if (!stat.ok()) {
            std::cout << "- [ERROR] Failed to load index : " << indexName << std::endl;
            std::cout << stat.error_code() << ", " << stat.error_message() << "," << stat.error_details() << std::endl;
        }

        std::cout << "Response:" << response.status() << ",\n" << response.message() << std::endl;
    }

    void unloadIndex(std::string indexName) {
        std::cout << "- Call grpc unloadIndex()" << std::endl;

        ClientContext context;

        DefaultRequest request;
        request.set_indexname(indexName);

        vecsearchgrpc::DefaultReply response;
        Status stat = stub_->unloadIndex(&context, request, &response);
        if (!stat.ok()) {
            std::cout << "- [ERROR] Failed to unload index : " << indexName << std::endl;
            std::cout << stat.error_code() << ", " << stat.error_message() << "," << stat.error_details() << std::endl;
        }

        std::cout << "- Response:" << response.status() << ",\n" << response.message() << std::endl;
    }

    void searchIndex(std::string indexName, 
        unsigned int dim, unsigned int nq, const float* xq, unsigned int k) {
        ClientContext context;

        SearchRequest request;
        request.set_indexname(indexName);
        request.set_dim(dim);
        request.set_numqueryvectors(nq);
        request.set_numneighbors(k);
        for(unsigned long i = 0; i < nq*dim; ++i) {
            request.add_vecdata(xq[i]);
        }

        SearchReply response;
        Status stat = stub_->searchNeighbors(&context, request, &response);
        if (!stat.ok()) {
            std::cout << "- [ERROR] Failed to search index : " << indexName << std::endl;
            std::cout << stat.error_code() << ", " << stat.error_message() << "," << stat.error_details() << std::endl;
            return;
        }
        
        // Get search result
        uint32_t r_nq = response.numqueryvectors();
        uint32_t r_k = response.numneighbors();
        const long* I = response.i().data();
        const float* D = response.d().data();

        std::ostringstream searchResult;
        searchResult << "I=\n";
        for (unsigned long i = 0; i < nq; ++i) {
            for (unsigned long j = 0; j < k; ++j) {
                searchResult << I[i * k + j] << " ";
            }
            searchResult << "\n";
        }
        searchResult << "D=\n";
        for (unsigned long i = 0; i < nq; ++i) {
            for (unsigned long j = 0; j < k; ++j) {
                searchResult << D[i * k + j] << " ";
            }
            searchResult << "\n";
        }
        std::cout << "search result=" << searchResult.str() << std::endl;
    }
private:
    std::unique_ptr<VectorSearchGrpc::Stub> stub_;
};