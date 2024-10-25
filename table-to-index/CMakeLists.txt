cmake_minimum_required(VERSION 3.8)

project(table-to-index)

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

#--------------------
# vecsearch.proto
#--------------------
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

#--------------------
# par2vec.proto
#--------------------
get_filename_component(par2vec_proto "${PROJECT_SOURCE_DIR}/../protos/par2vec.proto" ABSOLUTE)
get_filename_component(par2vec_proto_path "${par2vec_proto}" PATH)
message("- proto-file = " ${par2vec_proto})
message("- proto-path = " ${par2vec_proto_path})

# Generated sources
set(par2vec_proto_srcs "${PROJECT_SOURCE_DIR}/src/proto/par2vec.pb.cc")
set(par2vec_proto_hdrs "${PROJECT_SOURCE_DIR}/src/proto/par2vec.pb.h")
set(par2vec_grpc_srcs  "${PROJECT_SOURCE_DIR}/src/proto/par2vec.grpc.pb.cc")
set(par2vec_grpc_hdrs  "${PROJECT_SOURCE_DIR}/src/proto/par2vec.grpc.pb.h")
get_filename_component(par2vec_proto_grpc_out "${par2vec_proto_srcs}" PATH)
message("- proto-out-path : " ${par2vec_proto_grpc_out})

add_custom_command(
      OUTPUT "${par2vec_proto_srcs}" "${par2vec_proto_hdrs}" "${par2vec_grpc_srcs}" "${par2vec_grpc_hdrs}"
      COMMAND "/usr/local/bin/protoc" #${_PROTOBUF_PROTOC} 
      ARGS --grpc_out "${par2vec_proto_grpc_out}"
        --cpp_out "${par2vec_proto_grpc_out}"
        -I "${par2vec_proto_path}"
        --plugin=protoc-gen-grpc="/usr/local/bin/grpc_cpp_plugin" #${_GRPC_CPP_PLUGIN_EXECUTABLE}
        "${par2vec_proto}"
      DEPENDS "${par2vec_proto}")
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

  # Proto lib
add_library(par2vec_grpc_proto
${par2vec_grpc_srcs}
${par2vec_grpc_hdrs}
${par2vec_proto_srcs}
${par2vec_proto_hdrs}
)
target_link_libraries(par2vec_grpc_proto #gRPC::grpc++)
${_REFLECTION}
${_GRPC_GRPCPP}
${_PROTOBUF_LIBPROTOBUF} )
include_directories(
    src/
    src/proto
    /usr/local/mysql/connector-c++-8.0.33/include/ # mysql-connector
)

link_directories(
    /usr/local/mysql/connector-c++-8.0.33/lib64 # mysql-connector
)

add_executable(table-to-index 
            src/main.cpp)

target_link_libraries(table-to-index 
    vecsearch_grpc_proto
    par2vec_grpc_proto
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF}
    mysqlcppconn
)
