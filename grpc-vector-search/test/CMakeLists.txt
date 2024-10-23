cmake_minimum_required(VERSION 3.8)

project(vector-search-grpc-client)

find_package(Threads REQUIRED)

find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")
set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")
set(_GRPC_GRPCPP gRPC::grpc++)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

find_package(OpenMP REQUIRED)
#find_package(CUDAToolkit REQUIRED)
#message(STATUS "CUDA Libs dir : ${CUDA_TOOLKIT_ROOT_DIR}")

find_package(faiss REQUIRED)
find_package(MKL REQUIRED)

include_directories(
    ${PROJECT_SOURCE_DIR}/../src/proto
)

link_directories(
    ${PROJECT_SOURCE_DIR}/../build/
)

add_executable(client 
            grpc-client.cpp)

target_link_libraries(client 
    vecsearch_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
)
