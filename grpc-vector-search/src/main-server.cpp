#include <iostream>
#include <string>

#include "vector-search-grpc.h"


void RunServer(uint16_t port) {
    std::string server_address = "0.0.0.0:"+std::to_string(port);

    VectorSearchGrpcImpl service;
    if (service.setDatabase("192.168.0.5:3306", "recommender", "grida", "MM22mm01#") != 0) {
        std::cerr << "[ERROR] Cannot start the gRPC server because of connection failure to database " << std::endl;
        return;
    }
    service.setIndexFilePathBase("/home/stoh/Codes/recommender-system/data/");

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;
    builder.SetMaxReceiveMessageSize(1024 * 1024 * 1024);  // 1 GB
    builder.SetMaxSendMessageSize(1024 * 1024 * 1024);     // 1 GB

    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char** argv) {
    uint16_t port = 50053;
    RunServer(port);

    return 0;
}