#include "vector-search-grpc.h"

Status VectorSearchGrpcImpl::createIndex(ServerContext* context, const CreateIndexRequest* request, DefaultReply* reply) {
        //TODO: Needs to implement
        return Status::OK;
}

Status VectorSearchGrpcImpl::deleteIndex(ServerContext* context, const DefaultRequest* request, DefaultReply* reply) {
    //TODO: Needs to implement
    return Status::OK;
}

Status VectorSearchGrpcImpl::loadIndex(ServerContext* context, const DefaultRequest* request, DefaultReply* reply) {
    //TODO: Needs to implement
    reply->set_status("Success");
    reply->set_message("This is a test.");
    
    return Status::OK;
}

Status VectorSearchGrpcImpl::unloadIndex(ServerContext* context, const DefaultRequest* request, DefaultReply* reply) {
    //TODO: Needs to implement
    return Status::OK;
}

Status VectorSearchGrpcImpl::searchNeighbors(ServerContext* context, const SearchRequest* request, SearchReply* reply) {
    //TODO: Needs to implement
    return Status::OK;
}

int VectorSearchGrpcImpl::setDatabase(std::string dbUrl, std::string table, std::string dbUser, std::string dbPassword) {
    return vecSearch_.setDatabase(dbUrl, table, dbUser, dbPassword);
}

VectorSearchGrpcImpl::VectorSearchGrpcImpl() {

}

VectorSearchGrpcImpl::~VectorSearchGrpcImpl() {

}