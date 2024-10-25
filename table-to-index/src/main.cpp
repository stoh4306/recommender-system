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
    uint32_t dim;
    std::vector<float> tv;
    par2vec_client->par2vec("Hi, this is Seungtaik", dim, tv);
    
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

struct Freelancer {
    uint64_t id;
    std::string name;
    std::string introduction;
    std::string skills;
};

std::vector<Freelancer> freelancerList;

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

void convertProjectsToVecs(std::string entity, uint32_t& dim, std::vector<float>& fvec) {
    if (entity=="description") {
        std::vector<float> tv;
        for(size_t i = 0; i < projectList.size(); ++i) {
            par2vec_client->par2vec(projectList[i].description, dim, tv);

            fvec.insert(fvec.end(), tv.begin(), tv.end());
        }
    }
}

int insertDataToVec2ProjectTable(std::string tableName, std::string& err) {
    try {
        sql::mysql::MySQL_Driver*  driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> conn(
            driver->connect(DB_URL, DB_USER, DB_PASSWORD)
        );

        conn->setSchema(DB_SCHEMA);

        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement(
                "INSERT INTO " + tableName + " (vector_id, project_id) VALUES (?, ?)"
            )
        );

        for(size_t i = 0; i < projectList.size(); ++i) {
            pstmt->setInt64(1, i);
            pstmt->setInt64(2, projectList[i].id);
            pstmt->executeUpdate();
        }
        std::cout << "Inserted " << projectList.size() << " rows in the vec_to_project table" << std::endl;

    } catch(sql::SQLException& e) {
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

int createIndex(std::string indexName, uint32_t dim, std::vector<float>& fvec, std::string err) {
    vecsearch_client->createIndex(indexName, dim, fvec.size()/dim, fvec.data());
    return 0;
}

void create_project_collection() {
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
    // 2.1 convert project descriptions to vectors
    uint32_t dim = 1;
    std::vector<float> fvec;
    convertProjectsToVecs("description", dim, fvec);
    std::cout << "- # fvec = " << fvec.size()/dim << ", dim=" << dim << std::endl;

    // 2.2 add a pair (vector_id, project_id) to the project_index table
    insertDataToVec2ProjectTable("vec_to_project", err);
    
    // 3. create index with fvec
    createIndex("project_collection", dim, fvec, err);
}

int readFreelancerListFromDB(std::string& err) {
    const std::string TABLE_NAME = "freelancer";
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
        Freelancer free;
        while (res->next()) {
            free.id = res->getUInt64("id");
            free.name = res->getString("name");
            free.introduction = res->getString("introduction");
            free.skills = res->getString("skills");

            freelancerList.push_back(free);
        }
        std::cout << "- Successfully read freelancer data from DB" << std::endl;

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

void printFreelancer(const Freelancer& free) {
    std::cout << "- FREELANCER" << "\n"
              << "  id : " << free.id << "\n" 
              << "  name  : " << free.name << "\n" 
              << "  intro : " << free.introduction << "\n"
              << "  skill : " << free.skills << std::endl;
}

void convertFreelancersToVecs(std::string entity, uint32_t& dim, std::vector<float>& fvec) {
    if (entity=="introduction") {
        std::vector<float> tv;
        for(size_t i = 0; i < freelancerList.size(); ++i) {
            par2vec_client->par2vec(freelancerList[i].introduction, dim, tv);

            fvec.insert(fvec.end(), tv.begin(), tv.end());
        }
    }
}

int insertDataToVec2FreelancerTable(std::string tableName, std::string& err) {
    try {
        sql::mysql::MySQL_Driver*  driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> conn(
            driver->connect(DB_URL, DB_USER, DB_PASSWORD)
        );

        conn->setSchema(DB_SCHEMA);

        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement(
                "INSERT INTO " + tableName + " (vector_id, freelancer_id) VALUES (?, ?)"
            )
        );

        for(size_t i = 0; i < freelancerList.size(); ++i) {
            pstmt->setInt64(1, i);
            pstmt->setInt64(2, freelancerList[i].id);
            pstmt->executeUpdate();
        }
        std::cout << "Inserted " << freelancerList.size() << " rows in the vec_to_freelancer table" << std::endl;

    } catch(sql::SQLException& e) {
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


void create_freelancer_collection() {
    // 1. Read freelancer data from DB
    std::string err;
    freelancerList.resize(0);
    readFreelancerListFromDB(err);
    std::cout << "- # of freelancer = " << freelancerList.size() << std::endl;
    if (freelancerList.size() > 0) {
        printFreelancer(freelancerList[0]);
        printFreelancer(freelancerList[freelancerList.size()-1]);
    }
 
    // 2.1 convert freelancer introduction to vectors
    uint32_t dim = 1;
    std::vector<float> fvec;
    convertFreelancersToVecs("introduction", dim, fvec);
    std::cout << "- # fvec = " << fvec.size()/dim << ", dim=" << dim << std::endl;

    // 2.2 add a pair (vector_id, freelancer_id) to the freelancer_index table
    insertDataToVec2FreelancerTable("vec_to_freelancer", err);
    
    // 3. create index with fvec
    createIndex("freelancer_collection", dim, fvec, err);
}

int main(int argc, char** argv) {
    //--------------------------------------------------------------
    // NOTE : To create collections for project and freelancer,
    //        uncomment the lines cotaining create_project_collection()
    //        and create_freelancer_collection().
    //--------------------------------------------------------------
    make_clients();
    test();

    // Create a project collection
    //create_project_collection();

    // Create a freelancer collection
    //create_freelancer_collection();

    delete par2vec_client; par2vec_client = nullptr;
    delete vecsearch_client; vecsearch_client = nullptr;
    
    return 0;
}