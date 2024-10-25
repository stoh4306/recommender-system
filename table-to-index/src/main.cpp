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

#include <mysql/jdbc.h>

const std::string DB_URL = "tcp://192.168.0.5:3306";
const std::string DB_USER = "grida";
const std::string DB_PASSWORD = "MM22mm01#";
const std::string DB_SCHEMA= "recommder";

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

void test() {
    grpc_hello("Hi, this is seungtaik!");
    par2vec_client->par2vec("Hi, this is Seungtaik");
    
    //grpc_loadIndex("index-1");
    std::thread t1(grpc_loadIndex, "index-1");
    t1.join();
}

struct Project {
    uint64_t id;
    std::string title;
    std::string description;
    std::string skills;
};

std::vector<Project> projectList;

int readProjectListFromDB(std::vector<Project>& projectList, std::string& err) {
    const std::string TABLE_NAME = "project";
    try {
        sql::mysql::MySQL_Driver * driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> con(
            driver->connect(DB_URL, DB_USER, DB_PASSWORD)
        );
        con->setSchema(DB_SCHEMA);

        std::unique_ptr<sql::PreparedStatement> pstmt(
            con->prepareStatement("SELECT * FROM " + TABLE_NAME)
        );
        
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        Project proj;
        while (res->next()) {
            proj.id = res->getUInt64("id");
            proj.title = res->getString("title");
            proj.description = res->getString("description");
            proj.skills = res->getString("skills");

            projectList.push_back(proj);
        }
        std::cout << "- Successfully read project data from DB" << std::endl;

    } catch (sql::SQLException& e) {
        std::ostringstream ss;
        ss << "SQLException: " << e.what()  
                  << " (MySQL error code: " << e.getErrorCode()
                  << ", SQLState: " << e.getSQLState() << " )";
        err = ss.str();
        return 2;
    } catch (std::exception& e) {
        std::ostringstream ss;
        ss << "Standard exception: " << e.what();
        err = ss.str();
        return 3;
    }

    err = "";
    return 0;
}

void printProject(const Project& proj) {
    std::cout << "- PROJECT" << "\n"
              << "  id : " << proj.id << "\n" 
              << "  title : " << proj.title << "\n" 
              << "  descr : " << proj.description << "\n"
              << "  skill : " << proj.skills << std::endl;
}

int main(int argc, char** argv) {
    // Preparation: two grpc clients to call par2vec and grpc-vector-search
    make_clients();

    // 1. Read project data from DB
    std::string err;
    projectList.resize(0);
    readProjectListFromDB(projectList, err);
    std::cout << "- # of project = " << projectList.size() << std::endl;
    if (projectList.size() > 0) {
        printProject(projectList[0]);
        printProject(projectList[projectList.size()-1]);
    }

    // 2. For each project, 
    // 2.1 convert description to vector
    // 2.2 add a pair (vector_id, project_id) to the project_index table
    // 2.3 add the vector to a temp vector array
    // 3. Create a faiss index from the temp vector array
    // 4. Save the faiss index data to disk
    // 5. Add the faiss index to the search_index table

    delete par2vec_client; par2vec_client = nullptr;
    delete vecsearch_client; vecsearch_client = nullptr;
    
    return 0;
}