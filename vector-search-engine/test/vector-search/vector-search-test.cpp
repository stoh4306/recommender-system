#include <iostream>
#include <random>

#include "vector-search.h"
#include <faiss/IndexFlat.h>
#include <faiss/index_io.h>

std::list<m2m::Index>::iterator find(std::list<m2m::Index>& a, std::string indexName) {
    std::list<m2m::Index>::iterator it = a.begin();
    for( ; it!=a.end(); ++it) {
        if (it->name == indexName) {
            break;
        }
    }
    return it;
}

void simple_container_test() {
    // Test for index container
    std::list<m2m::Index> indexArray;
    m2m::Index index[1];
    index[0].name = "project";
    index[0].dim = 384;
    indexArray.push_back(index[0]);

    std::cout << &(*find(indexArray, "project")) << std::endl;
    std::cout << &(*find(indexArray, "free")) << ", " << &(*indexArray.end()) << std::endl;

    // 
    m2m::IndexContainer ic;
    std::cout << ic.add(index[0]) << std::endl;

    std::cout << ic.hasIndex("project") << std::endl;
    std::cout << ic.hasIndex("free") << std::endl;
}

void printSearchResult(unsigned long k, unsigned long nq, int64_t* I, float* D) {
    // Get search result
    std::ostringstream searchResult;
    searchResult << "I=\n";
    for (unsigned long i = 0; i < nq; ++i) {
        for (unsigned long j = 0; j < k; ++j) {
            searchResult << I[i * k + j] << " ";
        }
        searchResult << "\n";
    }
    searchResult << "D=\n";
    for (unsigned long i = 0; i < nq; ++i) {
        for (unsigned long j = 0; j < k; ++j) {
            searchResult << D[i * k + j] << " ";
        }
        searchResult << "\n";
    }
    std::cout << "search result=" << searchResult.str() << std::endl;
}

void create_index_test() {
    std::mt19937 rng;
    std::uniform_real_distribution<> distrib;

    unsigned long dim = 348;
    unsigned long nb = 1000;

    float* xb = new float[dim * nb];
    for (size_t i = 0; i < nb; ++i) {
        for (unsigned int j = 0; j < dim; ++j) {
            xb[dim * i + j] = (float)distrib(rng);
            //std::cout << xq[dim * i + j] << " ";
        }
        xb[dim * i] += i / 1000;
        //std::cout << std::endl;
    }

    // Create index with a vector collection
    faiss::IndexFlatL2* index = new faiss::IndexFlatL2(dim);
    index->add(nb, xb);

    // Save the index to disk
    std::string indexFilePath = "./test-index.dat";
    faiss::write_index(index, indexFilePath.c_str());

    // Delete the index
    delete index;
    index = nullptr;

    delete[] xb;
}

void load_index_search_test() {
    // Load index from disk
    std::string indexFilePath = "./test-index.dat";
    faiss::IndexFlatL2* index = (faiss::IndexFlatL2*) faiss::read_index(indexFilePath.c_str());

    unsigned long dim = 348;
    
    // Query vectors
    unsigned long nq = 2;
    unsigned long k = 4;

    std::mt19937 rng;
    std::uniform_real_distribution<> distrib;

    float* xq = new float[dim * nq];
    for (size_t i = 0; i < nq; ++i) {
        for (unsigned int j = 0; j < dim; ++j) {
            xq[dim * i + j] = (float)distrib(rng);
            //std::cout << xq[dim * i + j] << " ";
        }
        xq[dim * i] += i / 1000;
        //std::cout << std::endl;
    }

    int64_t* I = new int64_t[k * nq];
    float* D = new float[k * nq];

    index->search(nq, xq, k, D, I);

    printSearchResult(k, nq, I, D);

    delete[] D;
    delete[] I;
    delete[] xq;
}

void load_index_add_to_container_test() {
    // Load index from disk
    std::string indexFilePath = "./test-index.dat";
    faiss::IndexFlatL2* findex = (faiss::IndexFlatL2*) faiss::read_index(indexFilePath.c_str());

    std::cout << findex->d << std::endl;
    std::cout << findex->ntotal << std::endl;
    std::cout << findex->get_xb() << std::endl;
    
    m2m::Index index;
    index.name = "test-data";
    index.dim = findex->d;
    index.ntotal = findex->ntotal;
    index.type = m2m::FLATL2;
    index.vecData = findex->get_xb();
    index.dataFilePath = indexFilePath;
    index.indexPtr = findex;
    index.nprobe = 1;
    index.useGpu = false;

    m2m::IndexContainer ic;
    ic.add(index);


    delete findex;
}

int vector_search_test_() {
    m2m::VectorSearch vecSearch;
    std::string indexFilePath = "./test-index.dat";
    void* indexPtr = nullptr;
    std::string err;
    int result = vecSearch.loadIndexFromDisk(indexFilePath, indexPtr, err);
    if (result != 0) {
        std::cout << "[ERROR] " << err << std::endl;
        return 1;
    } else {
        std::cout << "- Successfully loaded the index : " << indexFilePath << ", " << indexPtr << std::endl;
    }

    faiss::IndexFlatL2* findex = (faiss::IndexFlatL2*) indexPtr;
    std::cout << findex->d << ", " << findex->ntotal << ", " << findex->get_xb() << std::endl;
    
    std::string indexName = "test-index-3";
    if (vecSearch.addIndexToContainer(indexName, indexPtr, indexFilePath, false, err) > 0) {
        std::cout << "[ERROR] " << err << std::endl;
        return 1;
    } else {
        std::cout << "- Successfully added the index to container : " << indexName << std::endl;
    }

    // Add the same data again with a different name
    result = vecSearch.loadIndexFromDisk(indexFilePath, indexPtr, err);
    if (result != 0) {
        std::cout << "[ERROR] " << err << std::endl;
        return 1;
    } else {
        std::cout << "- Successfully loaded the index : " << indexFilePath << ", " << indexPtr << std::endl;
    }
    indexName = "test-index-2";
    if (vecSearch.addIndexToContainer(indexName, indexPtr, indexFilePath, false, err) > 0) {
        std::cout << "[ERROR] " << err << std::endl;
        return 1;
    } else {
        std::cout << "- Successfully added the index to container : " << indexName << std::endl;
    }
    std::cout << "- current container size = " << vecSearch.numIndices() << std::endl;
    vecSearch.indexContainer()->printIndexList();


    // Search 
    unsigned long dim = 348;
    
    // Query vectors
    unsigned long nq = 2;
    unsigned long k = 4;

    std::mt19937 rng;
    std::uniform_real_distribution<> distrib;

    float* xq = new float[dim * nq];
    for (size_t i = 0; i < nq; ++i) {
        for (unsigned int j = 0; j < dim; ++j) {
            xq[dim * i + j] = (float)distrib(rng);
            //std::cout << xq[dim * i + j] << " ";
        }
        xq[dim * i] += i / 1000;
        //std::cout << std::endl;
    }

    int64_t* I = new int64_t[k * nq];
    float* D = new float[k * nq];
    if (vecSearch.searchNeighbors("test-index-2", dim, 2, xq, k, I, D, err) == 0) {
        printSearchResult(k, nq, I, D); 
    } else {
        std::cout << err << std::endl;
    }

    // Set database
    std::string dbUrl = "192.168.0.5:3306";
    vecSearch.setDatabase(dbUrl, "recommder", "grida", "MM22mm01#");
    
    if (vecSearch.storeIndexToDB("test-index-3", err)!=0) {
        std::cout << "[ERROR] " << err << std::endl;
    }
    if (vecSearch.removeIndexFromDB("test-index-100", err) !=0) {
        std::cout << "[ERROR] " << err << std::endl;
    }

    err = "";
    return 0;
}

int main(int argc, char** argv) {
    std::cout << "TEST" << std::endl;

    //simple_container_test();
    //create_index_test();
    //load_index_search_test();
    //load_index_add_to_container_test();

    //vector_search_test_();

    m2m::VectorSearch vecSearch;

    // Set database
    std::string dbUrl = "192.168.0.5:3306";
    vecSearch.setDatabase(dbUrl, "recommder", "grida", "MM22mm01#");

    std::string err;

    //vecSearch.removeIndexFromDB("test-index-2", err);

    if (vecSearch.loadIndexFromDB("test-index-3", err)  != 0 ) {
        std::cout << "[ERROR] " << err << std::endl;
    }

    if (vecSearch.saveIndexInContainerToDisk("test-index-3", err, "test-index-3.dat") != 0) {
        std::cout << "[ERROR] " << err << std::endl;
    }

    /*
    // Search 
    unsigned long dim = 348;
    
    // Query vectors
    unsigned long nq = 2;
    unsigned long k = 4;

    std::mt19937 rng;
    std::uniform_real_distribution<> distrib;

    float* xq = new float[dim * nq];
    for (size_t i = 0; i < nq; ++i) {
        for (unsigned int j = 0; j < dim; ++j) {
            xq[dim * i + j] = (float)distrib(rng);
            //std::cout << xq[dim * i + j] << " ";
        }
        xq[dim * i] += i / 1000;
        //std::cout << std::endl;
    }

    int64_t* I = new int64_t[k * nq];
    float* D = new float[k * nq];
    if (vecSearch.searchNeighbors("test-index-3", dim, 2, xq, k, I, D, err) == 0) {
        printSearchResult(k, nq, I, D); 
    } else {
        std::cout << err << std::endl;
    }//*/

    return 0;
}