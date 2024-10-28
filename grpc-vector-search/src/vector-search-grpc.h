#pragma once

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "./proto/vecsearch.grpc.pb.h"

#include "vector-search.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using namespace vecsearchgrpc;
using vecsearchgrpc::CreateIndexRequest;
using vecsearchgrpc::DefaultRequest;
using vecsearchgrpc::DefaultReply;
using vecsearchgrpc::SearchRequest;
using vecsearchgrpc::SearchReply;
using vecsearchgrpc::IndexInfo;

class VectorSearchGrpcImpl final : public VectorSearchGrpc::Service {
public:
    Status getIndexFromContainer(ServerContext* context, const DefaultRequest* request, IndexInfo* reply) override;
    Status createIndex(ServerContext* context, const CreateIndexRequest* request, DefaultReply* reply) override;
    Status deleteIndex(ServerContext* context, const DefaultRequest* request, DefaultReply* reply) override;

    Status loadIndex(ServerContext* context, const DefaultRequest* request, DefaultReply* reply) override;
    Status unloadIndex(ServerContext* context, const DefaultRequest* request, DefaultReply* reply) override;

    Status searchNeighbors(ServerContext* context, const SearchRequest* request, SearchReply* reply) override;

    int setDatabase(std::string dbUrl, std::string table, std::string dbUser, std::string dbPassword);
    void setIndexFilePathBase(std::string basePath);

    VectorSearchGrpcImpl();
    ~VectorSearchGrpcImpl();

private:
    m2m::VectorSearch vecSearch_;
};