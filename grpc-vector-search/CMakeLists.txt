cmake_minimum_required(VERSION 3.8)

project(grpc-vector-search)

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

message("- PROJECT_SOURCE_DIR = " ${PROJECT_SOURCE_DIR})
message("- CMAKE_CURRENT_BINARY_DIR = " ${CMAKE_CURRENT_BINARY_DIR})
message("- _PROTOBUF_PROTOC = " ${_PROTOBUF_PROTOC})
message("- _GRPC_CPP_PLUGIN_EXECUTABLE = " ${_GRPC_CPP_PLUGIN_EXECUTABLE})
message("- GRPC_LIBRARIES = " ${GRPC_LIBS})

#Proto file
get_filename_component(vecsearch_proto "${PROJECT_SOURCE_DIR}/../protos/vecsearch.proto" ABSOLUTE)
get_filename_component(vecsearch_proto_path "${vecsearch_proto}" PATH)
message("- proto-file = " ${vecsearch_proto})
message("- proto-path = " ${vecsearch_proto_path})

# Generated sources
set(vecsearch_proto_srcs "${PROJECT_SOURCE_DIR}/src/proto/vecsearch.pb.cc")
set(vecsearch_proto_hdrs "${PROJECT_SOURCE_DIR}/src/proto/vecsearch.pb.h")
set(vecsearch_grpc_srcs  "${PROJECT_SOURCE_DIR}/src/proto/vecsearch.grpc.pb.cc")
set(vecsearch_grpc_hdrs  "${PROJECT_SOURCE_DIR}/src/proto/vecsearch.grpc.pb.h")
get_filename_component(vecsearch_proto_grpc_out "${vecsearch_proto_srcs}" PATH)
message("- proto-out-path : " ${vecsearch_proto_grpc_out})

add_custom_command(
      OUTPUT "${vecsearch_proto_srcs}" "${vecsearch_proto_hdrs}" "${vecsearch_grpc_srcs}" "${vecsearch_grpc_hdrs}"
      COMMAND "/usr/local/bin/protoc" #${_PROTOBUF_PROTOC} 
      ARGS --grpc_out "${vecsearch_proto_grpc_out}"
        --cpp_out "${vecsearch_proto_grpc_out}"
        -I "${vecsearch_proto_path}"
        --plugin=protoc-gen-grpc="/usr/local/bin/grpc_cpp_plugin" #${_GRPC_CPP_PLUGIN_EXECUTABLE}
        "${vecsearch_proto}"
      DEPENDS "${vecsearch_proto}")

# Include generated *.pb.h files
include_directories( 
    #/usr/local/include
    ${vecsearch_proto_grpc_out}
    ${PROJECT_SOURCE_DIR}/../vector-search-engine/src
    ${PROJECT_SOURCE_DIR}/src
    /usr/local/mysql/connector-c++-8.0.33/include/ # mysql-connector
    )

link_directories(
    /usr/local/mysql/connector-c++-8.0.33/lib64 # mysql-connector
    ${PROJECT_SOURCE_DIR}/../vector-search-engine/build
)

# Proto lib
add_library(vecsearch_grpc_proto
  ${vecsearch_grpc_srcs}
  ${vecsearch_grpc_hdrs}
  ${vecsearch_proto_srcs}
  ${vecsearch_proto_hdrs}
  )
target_link_libraries(vecsearch_grpc_proto #gRPC::grpc++)
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF} )

# Project target
add_executable(server 
            src/main-server.cpp
            src/vector-search-grpc.cpp)

target_link_libraries(server
    vecsearch_grpc_proto
    #gRPC::grpc++ gRPC::grpc++_reflection gRPC::grpc++_alts
#    absl::flags absl::flags_parse 
#    #absl_log_internal_check_op absl_log_internal_conditions absl_log_internal_format absl_log_internal_globals absl_log_internal_log_sink_set 
#    #absl_log_internal_message absl_log_internal_nullguard absl_log_internal_proto absl_log_severity absl_log_sink #grpc++_reflection grpc++ grpc #grpc++_reflection 
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    
    vector-search 
    faiss
    mkl_intel_lp64 mkl_intel_thread mkl_core
    OpenMP::OpenMP_CXX
    iomp5 
    pthread
    mysqlcppconn
)

#add_executable(client client.cpp)
#target_link_libraries(client 
#    vecsearch_grpc_proto
#    ${GRPC_LIB_FILES})