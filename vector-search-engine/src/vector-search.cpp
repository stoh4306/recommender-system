#include <vector-search.h>

#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>

#include <mysql/jdbc.h>

#include <faiss/IndexFlat.h>
#include <faiss/index_io.h>

namespace m2m {

int VectorSearch::searchNeighbors(std::string indexName, unsigned long dim, unsigned long nq, std::string vectors, 
                        unsigned long k, long* I, float* D, std::string& err ) {
    if (!indexContainer_.hasIndex(indexName)) {
        err = "Can't find the index : " + indexName;
        return 1;
    }

    faiss::IndexFlatL2* findex = (faiss::IndexFlatL2*) indexContainer_.getIndexPtr(indexName);

    // Convert string to vectors
    unsigned long tnq = (unsigned long)nq;
    unsigned long tdim = (unsigned long)dim;
    float* xq = new float[dim * tnq];
    float* txq = xq;
    std::stringstream ss(vectors); 
    for (unsigned int i = 0; i < tnq; ++i)
    {
        for (unsigned int j = 0; j < tdim; ++j)
        {
            ss >> *txq;
            txq++;
        }
    }
    ss.clear();

    std::cout << "- Searching...";
    auto stime = std::chrono::high_resolution_clock::now();

    findex->search(nq, xq, k, D, I);
    
    auto ftime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(ftime-stime);
    std::cout << "done... time=" << duration.count() << " msec" << std::endl;

    err = "";
    return 0;
}
int VectorSearch::searchNeighbors(std::string indexName, unsigned long dim, unsigned long nq, float* xq, 

                        unsigned long k, long* I, float* D, std::string& err ) {
    if (!indexContainer_.hasIndex(indexName)) {
        err = "Can't find the index : " + indexName;
        return 1;
    }

    faiss::IndexFlatL2* findex = (faiss::IndexFlatL2*) indexContainer_.getIndexPtr(indexName);

    std::cout << "- Searching...";
    auto stime = std::chrono::high_resolution_clock::now();

    findex->search(nq, xq, k, D, I);
    
    auto ftime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(ftime-stime);
    std::cout << "done... time=" << duration.count() << " msec" << std::endl;

    err = "";
    return 0;
}

void pythonListToArray(std::string inStr, unsigned int dim, float* arr) {
    std::string arrInStr;
    arrInStr.reserve(inStr.length());

    for (char& c : inStr) {
        if ( c != '[' && c != ']' && c!= ',' ) {
            arrInStr.push_back(c);
        }
    }
    //std::cout << inStr << "\n->" << arrInStr << std::endl;

    std::istringstream ss(arrInStr);
    float * tmpPtr = arr;
    for ( unsigned int i = 0; i < dim; ++i) {
        ss >> *(tmpPtr++);
    }
    //std::cout << arr[0] << ", " << arr[dim-1] << std::endl;
}

int VectorSearch::readVectorsFromFile(std::string filename, unsigned long& ntotal, unsigned long& dim, float*& data, std::string& err) {
    std::ifstream inFile(filename);

    if (!inFile.is_open())
    {
        err = "Failed to open file : " + filename;
        return 1;
    } 

    inFile >> ntotal >> dim;
    //std::cout << ntotal << " " << dim << std::endl;

    data = new float[ntotal * dim];
    if (data==nullptr)
    {
        err = "Failed to allocate memory for vector data";
        return 2;
    }

    float* arrPtr = data;

    std::string line;
    std::getline(inFile, line, '\n');

    unsigned int i = 0;

    while (!inFile.eof()) {
        std::getline(inFile, line, '\n');
        if(line.empty()) break;

        //std::cout << i++ << " : ";
        pythonListToArray(line, dim, arrPtr);

        arrPtr += dim;
    }

    inFile.close();

    err = "";
    return 0;
}

int VectorSearch::addIndexToContainer(std::string indexName, unsigned long dim, unsigned long ntotal, float* xb, 
                                    std::string dataFileName, std::string& err) {
    if (indexContainer_.hasIndex(indexName))
    {
        err = "There already exists an index with the same name : " + indexName;
        return 1;
    }

    // Create index structure
    // NOTE : Index and base vector data will be deleted by the destructor
    faiss::IndexFlatL2* findex = new faiss::IndexFlatL2(dim); 
    findex->add(ntotal, xb);

    // Add index to container
    Index newIndex;
    newIndex.name = indexName;
    newIndex.useGpu = false;
    newIndex.type = FLATL2;
    newIndex.dim = dim;
    newIndex.ntotal = ntotal;
    newIndex.vecData = findex->get_xb();
    newIndex.indexPtr = findex;
    newIndex.quantizerPtr = nullptr; // NOTE : Quantizer deletion is not necessary (index type= FlatL2)
    newIndex.dataFilePath = indexDataPathBase_ + "/" + dataFileName;

    indexContainer_.add(newIndex);

    err = "";
    return 0;
}

int VectorSearch::addIndexToContainer(std::string indexName, void* indexPtr, std::string dataFileName, std::string& err) {
    if (indexContainer_.hasIndex(indexName))
    {
        err = "There already exists an index with the same name : " + indexName;
        return 1;
    }

    // Add an index to container with the index name and the index pointer
    faiss::IndexFlatL2* findex = (faiss::IndexFlatL2*) indexPtr;

    Index newIndex;
    newIndex.name = indexName;
    newIndex.useGpu = false;
    newIndex.type = FLATL2;
    newIndex.dim = findex->d;
    newIndex.ntotal = findex->ntotal;
    newIndex.vecData = findex->get_xb();
    newIndex.indexPtr = findex;
    newIndex.quantizerPtr = nullptr; // NOTE : Quantizer deletion is not necessary (index type= FlatL2)
    newIndex.dataFilePath = indexDataPathBase_ + "/" + dataFileName; 

    indexContainer_.add(newIndex);

    err = "";
    return 0;
}

int VectorSearch::saveIndexToDisk(void* indexPtr, std::string fileName, std::string& err) {
    if (indexPtr == nullptr) {
        err = "Can't save with the null index pointer";
        return 1;
    } 

    faiss::IndexFlatL2* findex = (faiss::IndexFlatL2*) indexPtr;

    std::string fileFullPath = indexDataPathBase_ + "/" + fileName;

    faiss::write_index(findex, fileFullPath.c_str());

    err = "";
    return 0;
}

int VectorSearch::saveIndexInContainerToDisk(std::string indexName, std::string& err, std::string fileName) {
    if (!indexContainer_.hasIndex(indexName)) {
        err = "Can't find the index in the container: " + indexName;
        std::cout << err << std::endl;
        return 1;
    }

    std::list<Index>::iterator it = indexContainer_.getIndexIterator(indexName);

    std::string indexFilePath = indexDataPathBase_ + "/" + fileName;

    if (fileName=="") indexFilePath = it->dataFilePath;

    faiss::write_index((faiss::IndexFlatL2*)it->indexPtr, indexFilePath.c_str());
    
    err = "";
    return 0;
}

int VectorSearch::deleteIndexFromContainer(std::string indexName, std::string& err) {
    if (!indexContainer_.hasIndex(indexName)) {
        err = "Can't find the index in the container: " + indexName;
        return 1;
    }

    if (!indexContainer_.remove(indexName)) {
        err = "Failed to remove index from the container: " + indexName;
        return 2;
    }

    err = "";
    return 0;
}

int VectorSearch::loadIndexFromDisk(std::string indexFilePath, void*& indexPtr, std::string& err) {
    // Check if the file exists
    std::ifstream inFile(indexFilePath.c_str());
    if (!inFile.is_open()) {
        err = "Can't open index file : " + indexFilePath;
        return 1;
    }

    indexPtr = (faiss::IndexFlatL2*)faiss::read_index(indexFilePath.c_str());

    err = "";
    return 0;
}

int VectorSearch::loadIndexFromDiskToContainer(std::string indexName, std::string indexFilePath, std::string& err) {
    if (indexContainer_.hasIndex(indexName)) {
        err = "There already exists an index with the same : " + indexName;
        return 1;
    }

    void* indexPtr = nullptr;
    if (loadIndexFromDisk(indexFilePath, indexPtr, err) > 0) {
        return 2;
    }

    if (addIndexToContainer(indexName, indexPtr, indexFilePath, err) > 0) {
        return 3;
    }

    return 0;
}

unsigned long  VectorSearch::numIndices() {
    return indexContainer_.size();
}

void* VectorSearch::indexPtr(std::string indexName) {
    return indexContainer_.getIndexPtr(indexName);
}

IndexContainer*    VectorSearch::indexContainer() {
    return &indexContainer_;
}

void VectorSearch::setIndexDataPathBase(std::string path) {
    indexDataPathBase_ = path;
    std::cout << "- Set IndexDataPathBase : " << path << std::endl;
}

int VectorSearch::loadIndexFromDB(std::string indexName, std::string& err) {
    std::string dataPath;
    try {
        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> con(
            driver->connect("tcp://"+dbUrl_, dbUserName_, dbPassWord_)
        );
        std::cout << "A connection made : mysql" << std::endl;

        // Connect to the database schema (e.g., test)
        con->setSchema("recommder");

        sql::PreparedStatement* pstmt_1(
            con->prepareStatement("SELECT * FROM search_index WHERE name = ? LIMIT 1")
        );
        pstmt_1->setString(1, indexName);
        sql::ResultSet* res = pstmt_1->executeQuery();
        if (res->next()) {
            dataPath = res->getString("data_path");
        } else {
            err = "Can't find an index in DB : " + indexName;
            return 1;
        }

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

    if (loadIndexFromDiskToContainer(indexName, dataPath, err) != 0) {
        err = "Failed to load index from DB to container : " + indexName + "(" + err +")";
        return 4;
    }

    err = "";
    return 0;
}

int VectorSearch::removeIndexFromDB(std::string indexName, std::string& err) {
    try {
        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> con(
            driver->connect("tcp://"+dbUrl_, dbUserName_, dbPassWord_)
        );
        std::cout << "A connection made : mysql" << std::endl;

        // Connect to the database schema (e.g., test)
        con->setSchema("recommder");

        sql::PreparedStatement* pstmt_1(
            con->prepareStatement("SELECT * FROM search_index WHERE name = ?  LIMIT 1")
        );
        pstmt_1->setString(1, indexName);

        std::unique_ptr<sql::ResultSet> res(pstmt_1->executeQuery());
        if (!res->next()) {
            err = "warning! can't find an index with name in DB: " + indexName;
            return 0;
        } 

        sql::PreparedStatement* pstmt2(
            con->prepareStatement("DELETE FROM search_index WHERE name = ?")
        );
        pstmt2->setString(1, indexName);
        int deleteCount = pstmt2->executeUpdate();

        std::cout << "Deleted " << deleteCount << " row(s) successfully." << std::endl;
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

int VectorSearch::storeIndexToDB(std::string indexName, std::string& err) {
    if (!indexContainer_.hasIndex(indexName)) {
        err = "Can't find index in the container: " + indexName;
        return 1;
    }

    std::list<Index>::iterator it = indexContainer_.getIndexIterator(indexName);
    
    //
    // At the moment, we assume that there is no indices with the input name.    
    // TODO: Drop the assumption
    //

    try {
        sql::mysql::MySQL_Driver *driver = sql::mysql::get_mysql_driver_instance();
        std::unique_ptr<sql::Connection> con(
            driver->connect("tcp://"+dbUrl_, dbUserName_, dbPassWord_)
        );
        std::cout << "A connection made : mysql" << std::endl;

        // Connect to the database schema (e.g., test)
        con->setSchema("recommder");

        sql::PreparedStatement* pstmt_1(
            con->prepareStatement("SELECT * FROM search_index WHERE name = ?  LIMIT 1")
        );
        pstmt_1->setString(1, indexName);

        std::unique_ptr<sql::ResultSet> res(pstmt_1->executeQuery());
        if (res->next()) {
            
            std::unique_ptr<sql::PreparedStatement> pstmt_2( 
                con->prepareStatement(
                    "UPDATE search_index SET data_path = ? WHERE name = ?"
                )
            );
            pstmt_2->setString(1, it->dataFilePath);
            pstmt_2->setString(2, indexName);

            pstmt_2->executeUpdate();

            std::cout << "Updated a row with name=" << indexName << " succesfully" << std::endl;

        } else {
            std::unique_ptr<sql::PreparedStatement> pstmt_2( 
                con->prepareStatement(
                    "INSERT INTO search_index (name, data_path) VALUES (?, ?)"
                )
            );
        
            pstmt_2->setString(1, indexName);
            pstmt_2->setString(2, it->dataFilePath);

            pstmt_2->executeUpdate();
            std::cout << "Inserted a row succesfully" << std::endl;
        }
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

int VectorSearch::setDatabase(std::string url, std::string dbName, std::string dbUserName, std::string dbPassword) {
    dbUrl_ = url;
    dbName_ = dbName;
    dbUserName_ = dbUserName;
    dbPassWord_ = dbPassword;

    return 0;
}

VectorSearch::VectorSearch() {
    indexDataPathBase_ = ".";
}

VectorSearch::~VectorSearch() {}

u_int64_t IndexContainer::size() {
    return indexArray_.size();
}

std::list<Index>::iterator IndexContainer::getIndexIterator(std::string indexName) {
    std::list<Index>::iterator it = indexArray_.begin();
    for (; it != indexArray_.end(); ++it) {
        if (it->name == indexName) {
            break;
        }
    }
    return it;
}

bool IndexContainer::hasIndex(std::string indexName) {
    if ( getIndexIterator(indexName) != indexArray_.end() )  {
        return true; 
    } else {
        return false;
    }
}

void* IndexContainer::getIndexPtr(std::string indexName) {
    std::list<Index>::iterator it = getIndexIterator(indexName);
    if ( it != indexArray_.end() )  {
        return it->indexPtr;
    } else {
        return nullptr;
    }
}

// TODO: Need to check if this works
void* IndexContainer::getQuantizerPtr(std::string indexName) {
    std::list<Index>::iterator it = getIndexIterator(indexName);
    if ( it != indexArray_.end() )  {
        return it->quantizerPtr;
    } else {
        return nullptr;
    }
}

std::string IndexContainer::getIndexFilePath(std::string indexName) {
    std::list<Index>::iterator it = getIndexIterator(indexName);
    if ( it != indexArray_.end() )  {
        return it->dataFilePath;
    } else {
        return std::string("");
    }
}

u_int64_t IndexContainer::add(Index newIndex) {
    indexArray_.push_back(newIndex);
    return indexArray_.size();
}

bool IndexContainer::remove(std::string indexName) {
    std::list<Index>::iterator it = getIndexIterator(indexName);
    if ( it != indexArray_.end() )  {
        if (it->indexPtr != nullptr) {
            faiss::IndexFlatL2* index = (faiss::IndexFlatL2*) it->indexPtr;
            delete index;

            it->indexPtr = nullptr;
            it->vecData = nullptr;
        }
        indexArray_.erase(it);
        return true;
    } else {
        return false;
    }
}

bool IndexContainer::update(Index newIndex) {
    std::list<Index>::iterator it = getIndexIterator(newIndex.name);
    if ( it != indexArray_.end() )  {
        *it = newIndex;
        return true;
    } else {
        return false;
    }
}

void IndexContainer::printIndexList() {
    std::list<Index>::iterator it = indexArray_.begin();
    int id = 0;
    std::cout << "*** index list : " << std::endl;
    for (; it != indexArray_.end(); ++it, ++id)
    {
        std::cout 
            << "- id : " << id << "\n"
            << "  name : " << it->name << "\n"
            << "  gpu  : " << it->useGpu << "\n"
            << "  indexType : " << it->type << "\n"
            << "  dim : " << it->dim << "\n"
            << "  ntotal : " << it->ntotal << "\n"
            << "  data   : " << it->vecData << "\n"
            << "  indexPtr : " << it->indexPtr << "\n"
            << "  quantizerPtr : " << it->quantizerPtr << "\n"
            << "  indexFile : " << it->dataFilePath << "\n";
    }
    std::cout << std::endl;
}

IndexContainer::IndexContainer() {
    indexArray_.resize(0);
}

IndexContainer::~IndexContainer() {
    //Deallocate index data
    std::list<Index>::iterator it = indexArray_.begin();
    for (; it != indexArray_.end(); ++it) {
        if (it->indexPtr != nullptr) {
            faiss::IndexFlatL2* index = (faiss::IndexFlatL2*) it->indexPtr;
            // CAUTION: Deallocate base vector data will cause a segmentation fault error.
            //          It seems that deallocating the base vector data proceeds in deallocating index data.
            it->vecData = nullptr;

            delete index;
            it->indexPtr = nullptr;
        }
    }
    indexArray_.resize(0);
}

/*Index::Index() {
    name = "";
    useGpu = false;
    type = FLATL2;
    dim = 0;
    ntotal = 0;
    vecData = nullptr;
    indexPtr = nullptr;
    quantizerPtr = nullptr;
    nprobe = 0;
    
    dataFilePath = "";
}//*/
}