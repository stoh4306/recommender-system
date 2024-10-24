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
        std::cout << "num vectors = " << request.mutable_vecdata()->size() / dim << std::endl;
        DefaultReply response;
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

        DefaultReply response;
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

        DefaultReply response;
        stub_->loadIndex(&context, request, &response);

        std::cout << "Response:" << response.status() << ",\n" << response.message() << std::endl;
    }

    void unloadIndex(std::string indexName) {
        ClientContext context;

        DefaultRequest request;
        request.set_indexname(indexName);

        DefaultReply response;
        stub_->unloadIndex(&context, request, &response);

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
    grpc::ChannelArguments channel_args;
    channel_args.SetMaxSendMessageSize(1024 * 1024 * 1024);
    channel_args.SetMaxReceiveMessageSize(1024 * 1024 * 1024);
    auto channel = grpc::CreateCustomChannel(  "192.168.0.20:50053", 
                                grpc::InsecureChannelCredentials(),
                                channel_args);
    VectorSearchGrpcClient client(channel);

    // Generate vectors to make an index
    unsigned long nb, dim;
    nb = 100000;
    dim = 348;
    
    float* xb;

    createVectors(nb, dim, xb);
    
    client.createIndex("index-1", dim, nb, xb);
    client.deleteIndex("index-1");
    //client.loadIndex("index");
    //client.unloadIndex("index-1");
    
    return 0;
}