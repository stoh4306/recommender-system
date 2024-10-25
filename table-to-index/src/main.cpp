#include <iostream>
#include <iostream>
#include <random>
#include <sstream>
#include <thread>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "vector-search-grpc-client.h"
#include "par2vec-grpc-client.h"



VectorSearchGrpcClient* vecsearch_client = nullptr;
Par2VecGrpcClient* par2vec_client = nullptr;

void make_clients() {
    grpc::ChannelArguments channel_args[2];
    channel_args[0].SetMaxSendMessageSize(1024 * 1024 * 1024);
    channel_args[0].SetMaxReceiveMessageSize(1024 * 1024 * 1024);
    auto channel_1 = grpc::CreateCustomChannel(  "192.168.0.20:50053", 
                                grpc::InsecureChannelCredentials(),
                                channel_args[0]);
    vecsearch_client = new VectorSearchGrpcClient(channel_1);
    
    channel_args[1].SetMaxSendMessageSize(1024 * 1024 * 1024);
    channel_args[1].SetMaxReceiveMessageSize(1024 * 1024 * 1024);
    auto channel_2 = grpc::CreateCustomChannel(  "192.168.0.20:50052", 
                                grpc::InsecureChannelCredentials(),
                                channel_args[1]);
    par2vec_client = new Par2VecGrpcClient(channel_2);
}
void grpc_hello(std::string greetings) {
    par2vec_client->hello(greetings);
}

void grpc_loadIndex(std::string indexName) {
    vecsearch_client->loadIndex(indexName);
}

int main(int argc, char** argv) {
    // Preparation: two grpc clients to call par2vec and grpc-vector-search
    make_clients();

    grpc_hello("Hi, this is seungtaik!");
    par2vec_client->par2vec("Hi, this is Seungtaik");
    
    //grpc_loadIndex("index-1");
    std::thread t1(grpc_loadIndex, "index-1");

    t1.join();

    delete par2vec_client; par2vec_client = nullptr;
    delete vecsearch_client; vecsearch_client = nullptr;

    // 1. Read project data from DB
    // 2. For each project, 
    // 2.1 convert description to vector
    // 2.2 add a pair (vector_id, project_id) to the project_index table
    // 2.3 add the vector to a temp vector array
    // 3. Create a faiss index from the temp vector array
    // 4. Save the faiss index data to disk
    // 5. Add the faiss index to the search_index table
    
    return 0;
}