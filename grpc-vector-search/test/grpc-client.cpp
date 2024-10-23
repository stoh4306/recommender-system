#include <iostream>
#include <random>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "../src/proto/vecsearch.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

using vecsearchgrpc::CreateIndexRequest;
using vecsearchgrpc::DefaultRequest;
using vecsearchgrpc::DefaultReply;
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

        DefaultReply response;
        stub_->createIndex(&context, request, &response);

        std::cout << "Response:" << response.status() << ",\n" << response.message() << std::endl;
    }

    void loadIndex(std::string indexName) {
        ClientContext context;

        DefaultRequest request;
        request.set_indexname(indexName);

        DefaultReply response;
        stub_->loadIndex(&context, request, &response);

        std::cout << "Response:" << response.status() << ",\n" << response.message() << std::endl;
    }
private:
    std::unique_ptr<VectorSearchGrpc::Stub> stub_;
};

void createVectors(unsigned long nb, unsigned long dim, float*& v) {
    std::mt19937 rng;
    std::uniform_real_distribution<> distrib;

    float* xb = new float[dim * nb];
    for (size_t i = 0; i < nb; ++i) {
        for (unsigned int j = 0; j < dim; ++j) {
            xb[dim * i + j] = (float)distrib(rng);
            //std::cout << xq[dim * i + j] << " ";
        }
        xb[dim * i] += i / 1000;
        //std::cout << std::endl;
    }

    v = xb;
}

int main(int argc, char** argv) {
    // Create a client instance
    VectorSearchGrpcClient client(
        grpc::CreateChannel("192.168.0.20:50053", grpc::InsecureChannelCredentials()));

    // Generate vectors to make an index
    unsigned long nb, dim;
    nb = 100000;
    dim = 348;
    
    float* xb;

    createVectors(nb, dim, xb);
    
    client.createIndex("index-1", dim, nb, xb);
    client.loadIndex("index");
    
    return 0;
}