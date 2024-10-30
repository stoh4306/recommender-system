#include "vector-search-grpc.h"

#include <chrono>

Status VectorSearchGrpcImpl::listLoadedIndex(ServerContext* context, const EmptyRequest* request, IndexList* reply) {
    std::cout << "- ListLoadedIndex() called..." << std::endl;

    std::vector<std::string> indexName;
    std::vector<unsigned long> numVectors;
    std::vector<unsigned int> dim;

    vecSearch_.getListOfIndicesInContainer(indexName, numVectors, dim);

    for(size_t i = 0; i < indexName.size(); ++i) {
        reply->add_indexname(indexName[i]);
        reply->add_numvectors(numVectors[i]);
        reply->add_dim(dim[i]);
    }

    std::cout << "- ListLoadedIndex() successfully executed" << std::endl;
    return Status::OK;
}

Status VectorSearchGrpcImpl::getIndexFromContainer(ServerContext* context, const DefaultRequest* request, IndexInfo* reply) {
    std::cout << "- GetIndexFromContainer() called..." << std::endl;

    std::string indexName = request->indexname();

    void* indexPtr = vecSearch_.indexPtr(indexName);
    if (vecSearch_.indexPtr(indexName) == nullptr) {
        reply->set_indexname(indexName);
        reply->set_datafilepath("");
        return Status(grpc::StatusCode::INTERNAL,  "Failed to getIndexFromContainer() : unable to find the index in the container");
    }

    std::string dataFilePath = vecSearch_.indexContainer()->getIndexFilePath(indexName);
    reply->set_indexname(indexName);
    reply->set_datafilepath(dataFilePath);

    std::cout << "- GetIndexFromContainer() successfully executed" << std::endl;
    
    return Status::OK;
}

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

    // Check if the inpute request is valid
    bool isInMemory = false, isInDB = false;
    if (vecSearch_.checkExistenceOfIndex(indexName, isInMemory, isInDB, err) != 0) {
        reply->set_status("Failure");
        reply->set_message("Unable to connecto DB");
        return Status(grpc::StatusCode::INTERNAL,  err);
    }

    if (indexName == "") {
        reply->set_status("Failure");
        reply->set_message("No index name");
        return Status(grpc::StatusCode::INVALID_ARGUMENT,  "Missing index name");
    }

    if (isInMemory || isInDB) {
        reply->set_status("Failure");
        reply->set_message("The index with the same name already exists");
        return Status(grpc::StatusCode::INVALID_ARGUMENT,  "The index with the same name already exists. Use a different name");
    }


    if (xb.size() != dim*nb) {
        reply->set_status("Failure");
        reply->set_message("Inconsistency among dim, numVectors and vecData");

        return Status(grpc::StatusCode::INVALID_ARGUMENT,  "Check dim, numVectors and the size of vecData");
    }


    // Add index to container
    int result = vecSearch_.addIndexToContainer(indexName, dim, nb, xb.data(), dataFileName, false, err);
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

        // Remove the previously added index from the container
        std::string tmpErr;
        vecSearch_.deleteIndexFromContainer(indexName, tmpErr);

        return Status(grpc::StatusCode::INTERNAL,  "Failed to createIndex() : unable to save the index to disk");
    }
    //std::cout << "- CreateIndex() : saved index to disk" << std::endl;
        

    // Store the index to DB
    result = vecSearch_.storeIndexToDB(indexName, err);
    if (result!=0) {
        reply->set_status("Failure");
        reply->set_message("Failed to store the index to DB");

        std::string tmpErr;
        // Delete the data file stored in disk in the previous step
        vecSearch_.deleteIndexDataFile(indexName, tmpErr);

        // Remove the previously added index from the container
        vecSearch_.deleteIndexFromContainer(indexName, tmpErr);
        
        return Status(grpc::StatusCode::INTERNAL,  "Failed to createIndex() : unable to store the index to DB");
    }
    std::cout << "- CreateIndex() successfully executed" << std::endl;

    reply->set_status("Success");
    reply->set_message("Created an index : " + indexName);

    return Status::OK;
}

Status VectorSearchGrpcImpl::deleteIndex(ServerContext* context, const DefaultRequest* request, DefaultReply* reply) {
    std::cout << "- deleteIndex() called..." << std::endl;
    
    std::string indexName = request->indexname();
    
    int result[3];
    std::string err[3];

    // Check if the index is loaded
    bool isLoaded = vecSearch_.isLoadedIndex(indexName);

    if (isLoaded) {
        // First, delete the data file
        result[0] = vecSearch_.deleteIndexDataFile(indexName, err[0]);
    } else {
        result[0] = vecSearch_.deleteIndexDataFileWithDB(indexName, err[0]);
    }
    // Remove the index from DB 
    result[1] = vecSearch_.removeIndexFromDB(indexName, err[1]);

    // Delete the index from container
    result[2] = vecSearch_.deleteIndexFromContainer(indexName, err[2]);

    if ( result[0] != 0 || result[1] != 0 || result[2] != 0 ) 
    {
        reply->set_status("Success");

        std::string mesg;
        if (!err[0].empty()) mesg += "failed to delete data file (the file might not exist)";
        if (!err[1].empty()) {
            if (!mesg.empty()) mesg += ", ";
            mesg += "failed to delete from DB (the index might not exist in DB)";
        }
        if (!err[2].empty()) {
            if (!mesg.empty()) mesg += ", ";
            mesg += "failed to delete from memory (the index might be in a unloaded state)";
        }

        reply->set_message("WARNING : The index deleted, but " + mesg);
        std::cout << "Deleted index: " + indexName + ", but " +  mesg << std::endl;
        return Status::OK;
    }

    std::cout << "- deleteIndex() successfully executed" << std::endl;
    reply->set_status("Success");
    reply->set_message("Deleted index : " + indexName);
    return Status::OK;
}

Status VectorSearchGrpcImpl::loadIndex(ServerContext* context, const DefaultRequest* request, DefaultReply* reply) {
    std::cout << "- loadIndex() called..." << std::endl;

    std::string indexName = request->indexname();

    if (indexName == "") {
        reply->set_status("Failure");
        reply->set_message("No index name");
        std::cout << "Failed to load index: missing index name" << std::endl;
        return Status(grpc::StatusCode::INVALID_ARGUMENT, "No index name");
    }

    std::string err;
    int result = vecSearch_.loadIndexFromDB(indexName, err);
    if (result != 0) {
        reply->set_status("Failure");
        reply->set_message(err);
        std::cout << "Failed to load index: " + indexName + ", "+ err << std::endl;
        return Status(grpc::StatusCode::INTERNAL, err);
    }

    reply->set_status("Success");
    reply->set_message("Loaded the index : " + indexName);
    std::cout << "- Loaded the index : " + indexName << std::endl;

    return Status::OK;
}

Status VectorSearchGrpcImpl::unloadIndex(ServerContext* context, const DefaultRequest* request, DefaultReply* reply) {
    std::cout << "- unloadIndex() called..." << std::endl;

    std::string indexName = request->indexname();

    if (indexName == "") {
        reply->set_status("Failure");
        reply->set_message("No index name");
        std::cout << "Failed to unload index: missing index name" << std::endl;
        return Status(grpc::StatusCode::INVALID_ARGUMENT, "No index name");
    }

    std::string err;
    int result = vecSearch_.deleteIndexFromContainer(indexName, err);

    if (result != 0) {
        reply->set_status("Failure");
        reply->set_message("Failed to unload index: " + indexName + ", " + err);
        std::cout << "Failed to unload index: " + indexName + ", "+ err << std::endl;
        return Status(grpc::StatusCode::INTERNAL, err);
    }

    reply->set_status("Success");
    reply->set_message("Unloaded the index : " + indexName);
    std::cout << "- unloaded index : " + indexName << std::endl;

    return Status::OK;
}

Status VectorSearchGrpcImpl::searchNeighbors(ServerContext* context, const SearchRequest* request, SearchReply* reply) {
    std::cout << "- searchNeighbors() called..." << std::endl;
    
    std::string indexName = request->indexname();
    unsigned long d = request->dim();
    unsigned long nq = request->numqueryvectors();
    const float* xq = request->vecdata().data();
    unsigned long k = request->numneighbors();

    std::vector<long> I(nq*k);
    std::vector<float> D(nq*k);
    std::string err;

    int result = vecSearch_.searchNeighbors(indexName, d, nq, xq, k, I.data(), D.data(), err);
    if (result != 0) {
        reply->set_status("Failure");
        reply->set_message("Failed to search in the index : " + indexName + ", " + err);
        reply->set_numneighbors(k);
        reply->set_numqueryvectors(nq);
        
        std::cout << "Failed to search in the index: " + indexName + ", "+ err << std::endl;
        return Status(grpc::StatusCode::INTERNAL, err);
    }

    reply->set_status("Success");
    reply->set_message("Neighbor search in the index : " + indexName + ", " + err);
    reply->set_numneighbors(k);
    reply->set_numqueryvectors(nq);
    for(unsigned long i = 0; i < nq; ++i){
        for(unsigned long j = 0; j < k; ++j) {
            reply->add_i(I[i*k+j]);
            reply->add_d(D[i*k+j]);
        }
    }

    std::cout << "- Neighbor search successful : " << indexName << std::endl;
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