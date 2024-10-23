cmake_minimum_required(VERSION 3.6)
project(vector-search-engine)

find_package(OpenMP REQUIRED)
find_package(faiss REQUIRED)
#find_package(CUDAToolkit REQUIRED)
find_package(MKL REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
    /usr/local/mysql/connector-c++-8.0.33/include/ # mysql-connector
#    ${CUDAToolkit_INCLUDE_DIRS}
)

link_directories(
    /usr/local/mysql/connector-c++-8.0.33/lib64 # mysql-connector
)

add_library(vector-search 
    ${PROJECT_SOURCE_DIR}/src/vector-search.cpp
)

#message(STATUS "PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}")

add_executable(test-vector-search
    ${PROJECT_SOURCE_DIR}/test/vector-search/vector-search-test.cpp
    #/home/stoh/Codes/recommender-system/vector-search-engine/test/vector-search/vector-search-test.cpp
)
target_link_libraries(test-vector-search 
    vector-search 
    faiss
    mkl_intel_lp64 mkl_intel_thread mkl_core
    OpenMP::OpenMP_CXX
    iomp5 
    pthread
    mysqlcppconn
)