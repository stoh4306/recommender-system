#include "vector-search-grpc.h"

#include <chrono>

Status VectorSearchGrpcImpl::createIndex(ServerContext* context, const CreateIndexRequest* request, DefaultReply* reply) {
    std::cout << "- CreateIndex() called..." << std::endl;
    std::string indexName = request->indexname();
    unsigned long dim = request->dim();
    unsigned long nb = request->numvectors();
    //std::cout << indexName << ", " << dim << ", " << nb << std::endl;

    std::vector<float>  xb(request->vecdata().begin(), request->vecdata().end());
    std::string dataFileName = indexName;
    auto now = std::chrono::system_clock::now();
    auto seconds_since_epoch 
        = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    dataFileName += "_" + std::to_string(seconds_since_epoch)+".dat";
    //std::cout << dataFileName << std::endl;

    std::string err;

    // Add index to container
    int result = vecSearch_.addIndexToContainer(indexName, dim, nb, xb.data(), dataFileName, err);
    if (result != 0) {
        reply->set_status("Failure");
        reply->set_message("Failed to add the index to container");

        return Status(grpc::StatusCode::INTERNAL,  "Failed to createIndex() : unable to add the index to container");
    }
    //std::cout << "- CreateIndex() : added index to container" << std::endl;

    // Save index to disk
    result = vecSearch_.saveIndexInContainerToDisk(indexName, err);
    if (result != 0) {
        std::cout << "error code=" << result << ", " << err << std::endl;
        reply->set_status("Failure");
        reply->set_message("Failed to save the index to disk");

        return Status(grpc::StatusCode::INTERNAL,  "Failed to createIndex() : unable to save the index to disk");
    }
    //std::cout << "- CreateIndex() : saved index to disk" << std::endl;
        

    // Store the index to DB
    result = vecSearch_.storeIndexToDB(indexName, err);
    if (result!=0) {
        reply->set_status("Failure");
        reply->set_message("Failed to store the index to DB");
        return Status(grpc::StatusCode::INTERNAL,  "Failed to createIndex() : unable to store the index to DB");
    }
    std::cout << "- CreateIndex() successfully executed" << std::endl;

    reply->set_status("Success");
    reply->set_message("Created an index : " + indexName);

    return Status::OK;
}

Status VectorSearchGrpcImpl::deleteIndex(ServerContext* context, const DefaultRequest* request, DefaultReply* reply) {
    //TODO: Needs to implement
    return Status::OK;
}

Status VectorSearchGrpcImpl::loadIndex(ServerContext* context, const DefaultRequest* request, DefaultReply* reply) {
    //TODO: Needs to implement
    std::cout << "Executing loadIndex() rpc..." << std::endl;
    reply->set_status("Success");
    reply->set_message("This is a test for loadIndex.");
    std::cout << "done" << std::endl;

    return Status::OK;
}

Status VectorSearchGrpcImpl::unloadIndex(ServerContext* context, const DefaultRequest* request, DefaultReply* reply) {
    //TODO: Needs to implement
    reply->set_status("Success");
    reply->set_message("This is a test for unloadIndex.");
    return Status::OK;
}

Status VectorSearchGrpcImpl::searchNeighbors(ServerContext* context, const SearchRequest* request, SearchReply* reply) {
    //TODO: Needs to implement
    return Status::OK;
}

int VectorSearchGrpcImpl::setDatabase(std::string dbUrl, std::string table, std::string dbUser, std::string dbPassword) {
    return vecSearch_.setDatabase(dbUrl, table, dbUser, dbPassword);
}

void VectorSearchGrpcImpl::setIndexFilePathBase(std::string basePath) {
    vecSearch_.setIndexDataPathBase(basePath);
}

VectorSearchGrpcImpl::VectorSearchGrpcImpl() {

}

VectorSearchGrpcImpl::~VectorSearchGrpcImpl() {

}