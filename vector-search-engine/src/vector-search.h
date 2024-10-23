#pragma once

#include <string>
#include <list>

namespace m2m {
enum IndexType  {FLATL2, IVFFLAT};

struct Index {
    std::string name;
    bool        useGpu;
    IndexType   type;
    u_int32_t   dim;
    u_int32_t   ntotal;
    float*      vecData;
    void*       indexPtr;
    void*       quantizerPtr;
    u_int32_t   nprobe;
    
    std::string dataFilePath;
};

//! Class for handling indices loaded to memory
class IndexContainer {
public:
    u_int64_t   size();
    std::list<Index>::iterator getIndexIterator(std::string indexName);
    bool        hasIndex(std::string indexName);
    //bool        isGpuIndex(std::string indexName);
    void*       getIndexPtr(std::string indexName);
    void*       getQuantizerPtr(std::string indexName);
    std::string getIndexFilePath(std::string indexName);
    
    u_int64_t add(Index newIndex);
    bool remove(std::string indexName);
    bool update(Index newIndex);

    void printIndexList();

    ~IndexContainer();
    IndexContainer();

private:
    std::list<Index>    indexArray_;
};

class VectorSearch {
public:
    int readVectorsFromFile(std::string filename, unsigned long& ntotal, unsigned long& dim, float*& data, std::string& err);
    int addIndexToContainer(std::string indexName, unsigned long dim, unsigned long ntotal, float* xb, std::string dataFileName, std::string& err);
    int addIndexToContainer(std::string indexName, void* indexPtr, std::string dataFileName, std::string& err);
    int saveIndexToDisk(void* indexPtr, std::string fileName, std::string& err);
    int saveIndexInContainerToDisk(std::string indexName, std::string& err, std::string filePath = "");
    int deleteIndexFromContainer(std::string indexName, std::string& err);
    int loadIndexFromDiskToContainer(std::string indexName, std::string indexFilePath, std::string& err);
    int loadIndexFromDisk(std::string indexFilePath, void*& indexPtr, std::string& err);
    unsigned        long numIndices();
    void*           indexPtr(std::string indexName);
    IndexContainer*  indexContainer();
    void setIndexDataPathBase(std::string path);

    int searchNeighbors(std::string indexName, unsigned long dim, unsigned long nq, std::string vectors, 
                        unsigned long k, long* I, float* D, std::string& err );
    int searchNeighbors(std::string indexName, unsigned long dim, unsigned long nq, float* xq, 
                        unsigned long k, long* I, float* D, std::string& err );

    int setDatabase(std::string url, std::string dbName_, std::string dbUserName, std::string dbPassword);
    int storeIndexToDB(std::string indexName, std::string& err);
    int removeIndexFromDB(std::string indexName, std::string& err);
    int loadIndexFromDB(std::string indexName, std::string& err);

    VectorSearch();
    ~VectorSearch();
private:
    IndexContainer indexContainer_;
    std::string    indexDataPathBase_;
    std::string dbUrl_, dbName_;
    std::string dbUserName_;
    std::string dbPassWord_;
};
}