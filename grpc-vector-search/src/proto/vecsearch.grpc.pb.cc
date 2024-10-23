// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: vecsearch.proto

#include "vecsearch.pb.h"
#include "vecsearch.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace vecsearchgrpc {

static const char* VectorSearchGrpc_method_names[] = {
  "/vecsearchgrpc.VectorSearchGrpc/createIndex",
  "/vecsearchgrpc.VectorSearchGrpc/deleteIndex",
  "/vecsearchgrpc.VectorSearchGrpc/loadIndex",
  "/vecsearchgrpc.VectorSearchGrpc/unloadIndex",
  "/vecsearchgrpc.VectorSearchGrpc/searchNeighbors",
};

std::unique_ptr< VectorSearchGrpc::Stub> VectorSearchGrpc::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< VectorSearchGrpc::Stub> stub(new VectorSearchGrpc::Stub(channel, options));
  return stub;
}

VectorSearchGrpc::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_createIndex_(VectorSearchGrpc_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_deleteIndex_(VectorSearchGrpc_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_loadIndex_(VectorSearchGrpc_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_unloadIndex_(VectorSearchGrpc_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_searchNeighbors_(VectorSearchGrpc_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status VectorSearchGrpc::Stub::createIndex(::grpc::ClientContext* context, const ::vecsearchgrpc::CreateIndexRequest& request, ::vecsearchgrpc::DefaultReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::vecsearchgrpc::CreateIndexRequest, ::vecsearchgrpc::DefaultReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_createIndex_, context, request, response);
}

void VectorSearchGrpc::Stub::async::createIndex(::grpc::ClientContext* context, const ::vecsearchgrpc::CreateIndexRequest* request, ::vecsearchgrpc::DefaultReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::vecsearchgrpc::CreateIndexRequest, ::vecsearchgrpc::DefaultReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_createIndex_, context, request, response, std::move(f));
}

void VectorSearchGrpc::Stub::async::createIndex(::grpc::ClientContext* context, const ::vecsearchgrpc::CreateIndexRequest* request, ::vecsearchgrpc::DefaultReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_createIndex_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::vecsearchgrpc::DefaultReply>* VectorSearchGrpc::Stub::PrepareAsynccreateIndexRaw(::grpc::ClientContext* context, const ::vecsearchgrpc::CreateIndexRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::vecsearchgrpc::DefaultReply, ::vecsearchgrpc::CreateIndexRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_createIndex_, context, request);
}

::grpc::ClientAsyncResponseReader< ::vecsearchgrpc::DefaultReply>* VectorSearchGrpc::Stub::AsynccreateIndexRaw(::grpc::ClientContext* context, const ::vecsearchgrpc::CreateIndexRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsynccreateIndexRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status VectorSearchGrpc::Stub::deleteIndex(::grpc::ClientContext* context, const ::vecsearchgrpc::DefaultRequest& request, ::vecsearchgrpc::DefaultReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::vecsearchgrpc::DefaultRequest, ::vecsearchgrpc::DefaultReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_deleteIndex_, context, request, response);
}

void VectorSearchGrpc::Stub::async::deleteIndex(::grpc::ClientContext* context, const ::vecsearchgrpc::DefaultRequest* request, ::vecsearchgrpc::DefaultReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::vecsearchgrpc::DefaultRequest, ::vecsearchgrpc::DefaultReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_deleteIndex_, context, request, response, std::move(f));
}

void VectorSearchGrpc::Stub::async::deleteIndex(::grpc::ClientContext* context, const ::vecsearchgrpc::DefaultRequest* request, ::vecsearchgrpc::DefaultReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_deleteIndex_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::vecsearchgrpc::DefaultReply>* VectorSearchGrpc::Stub::PrepareAsyncdeleteIndexRaw(::grpc::ClientContext* context, const ::vecsearchgrpc::DefaultRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::vecsearchgrpc::DefaultReply, ::vecsearchgrpc::DefaultRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_deleteIndex_, context, request);
}

::grpc::ClientAsyncResponseReader< ::vecsearchgrpc::DefaultReply>* VectorSearchGrpc::Stub::AsyncdeleteIndexRaw(::grpc::ClientContext* context, const ::vecsearchgrpc::DefaultRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncdeleteIndexRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status VectorSearchGrpc::Stub::loadIndex(::grpc::ClientContext* context, const ::vecsearchgrpc::DefaultRequest& request, ::vecsearchgrpc::DefaultReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::vecsearchgrpc::DefaultRequest, ::vecsearchgrpc::DefaultReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_loadIndex_, context, request, response);
}

void VectorSearchGrpc::Stub::async::loadIndex(::grpc::ClientContext* context, const ::vecsearchgrpc::DefaultRequest* request, ::vecsearchgrpc::DefaultReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::vecsearchgrpc::DefaultRequest, ::vecsearchgrpc::DefaultReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_loadIndex_, context, request, response, std::move(f));
}

void VectorSearchGrpc::Stub::async::loadIndex(::grpc::ClientContext* context, const ::vecsearchgrpc::DefaultRequest* request, ::vecsearchgrpc::DefaultReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_loadIndex_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::vecsearchgrpc::DefaultReply>* VectorSearchGrpc::Stub::PrepareAsyncloadIndexRaw(::grpc::ClientContext* context, const ::vecsearchgrpc::DefaultRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::vecsearchgrpc::DefaultReply, ::vecsearchgrpc::DefaultRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_loadIndex_, context, request);
}

::grpc::ClientAsyncResponseReader< ::vecsearchgrpc::DefaultReply>* VectorSearchGrpc::Stub::AsyncloadIndexRaw(::grpc::ClientContext* context, const ::vecsearchgrpc::DefaultRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncloadIndexRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status VectorSearchGrpc::Stub::unloadIndex(::grpc::ClientContext* context, const ::vecsearchgrpc::DefaultRequest& request, ::vecsearchgrpc::DefaultReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::vecsearchgrpc::DefaultRequest, ::vecsearchgrpc::DefaultReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_unloadIndex_, context, request, response);
}

void VectorSearchGrpc::Stub::async::unloadIndex(::grpc::ClientContext* context, const ::vecsearchgrpc::DefaultRequest* request, ::vecsearchgrpc::DefaultReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::vecsearchgrpc::DefaultRequest, ::vecsearchgrpc::DefaultReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_unloadIndex_, context, request, response, std::move(f));
}

void VectorSearchGrpc::Stub::async::unloadIndex(::grpc::ClientContext* context, const ::vecsearchgrpc::DefaultRequest* request, ::vecsearchgrpc::DefaultReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_unloadIndex_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::vecsearchgrpc::DefaultReply>* VectorSearchGrpc::Stub::PrepareAsyncunloadIndexRaw(::grpc::ClientContext* context, const ::vecsearchgrpc::DefaultRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::vecsearchgrpc::DefaultReply, ::vecsearchgrpc::DefaultRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_unloadIndex_, context, request);
}

::grpc::ClientAsyncResponseReader< ::vecsearchgrpc::DefaultReply>* VectorSearchGrpc::Stub::AsyncunloadIndexRaw(::grpc::ClientContext* context, const ::vecsearchgrpc::DefaultRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncunloadIndexRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status VectorSearchGrpc::Stub::searchNeighbors(::grpc::ClientContext* context, const ::vecsearchgrpc::SearchRequest& request, ::vecsearchgrpc::SearchReply* response) {
  return ::grpc::internal::BlockingUnaryCall< ::vecsearchgrpc::SearchRequest, ::vecsearchgrpc::SearchReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_searchNeighbors_, context, request, response);
}

void VectorSearchGrpc::Stub::async::searchNeighbors(::grpc::ClientContext* context, const ::vecsearchgrpc::SearchRequest* request, ::vecsearchgrpc::SearchReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::vecsearchgrpc::SearchRequest, ::vecsearchgrpc::SearchReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_searchNeighbors_, context, request, response, std::move(f));
}

void VectorSearchGrpc::Stub::async::searchNeighbors(::grpc::ClientContext* context, const ::vecsearchgrpc::SearchRequest* request, ::vecsearchgrpc::SearchReply* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_searchNeighbors_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::vecsearchgrpc::SearchReply>* VectorSearchGrpc::Stub::PrepareAsyncsearchNeighborsRaw(::grpc::ClientContext* context, const ::vecsearchgrpc::SearchRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::vecsearchgrpc::SearchReply, ::vecsearchgrpc::SearchRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_searchNeighbors_, context, request);
}

::grpc::ClientAsyncResponseReader< ::vecsearchgrpc::SearchReply>* VectorSearchGrpc::Stub::AsyncsearchNeighborsRaw(::grpc::ClientContext* context, const ::vecsearchgrpc::SearchRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncsearchNeighborsRaw(context, request, cq);
  result->StartCall();
  return result;
}

VectorSearchGrpc::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VectorSearchGrpc_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VectorSearchGrpc::Service, ::vecsearchgrpc::CreateIndexRequest, ::vecsearchgrpc::DefaultReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VectorSearchGrpc::Service* service,
             ::grpc::ServerContext* ctx,
             const ::vecsearchgrpc::CreateIndexRequest* req,
             ::vecsearchgrpc::DefaultReply* resp) {
               return service->createIndex(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VectorSearchGrpc_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VectorSearchGrpc::Service, ::vecsearchgrpc::DefaultRequest, ::vecsearchgrpc::DefaultReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VectorSearchGrpc::Service* service,
             ::grpc::ServerContext* ctx,
             const ::vecsearchgrpc::DefaultRequest* req,
             ::vecsearchgrpc::DefaultReply* resp) {
               return service->deleteIndex(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VectorSearchGrpc_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VectorSearchGrpc::Service, ::vecsearchgrpc::DefaultRequest, ::vecsearchgrpc::DefaultReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VectorSearchGrpc::Service* service,
             ::grpc::ServerContext* ctx,
             const ::vecsearchgrpc::DefaultRequest* req,
             ::vecsearchgrpc::DefaultReply* resp) {
               return service->loadIndex(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VectorSearchGrpc_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VectorSearchGrpc::Service, ::vecsearchgrpc::DefaultRequest, ::vecsearchgrpc::DefaultReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VectorSearchGrpc::Service* service,
             ::grpc::ServerContext* ctx,
             const ::vecsearchgrpc::DefaultRequest* req,
             ::vecsearchgrpc::DefaultReply* resp) {
               return service->unloadIndex(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      VectorSearchGrpc_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< VectorSearchGrpc::Service, ::vecsearchgrpc::SearchRequest, ::vecsearchgrpc::SearchReply, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](VectorSearchGrpc::Service* service,
             ::grpc::ServerContext* ctx,
             const ::vecsearchgrpc::SearchRequest* req,
             ::vecsearchgrpc::SearchReply* resp) {
               return service->searchNeighbors(ctx, req, resp);
             }, this)));
}

VectorSearchGrpc::Service::~Service() {
}

::grpc::Status VectorSearchGrpc::Service::createIndex(::grpc::ServerContext* context, const ::vecsearchgrpc::CreateIndexRequest* request, ::vecsearchgrpc::DefaultReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status VectorSearchGrpc::Service::deleteIndex(::grpc::ServerContext* context, const ::vecsearchgrpc::DefaultRequest* request, ::vecsearchgrpc::DefaultReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status VectorSearchGrpc::Service::loadIndex(::grpc::ServerContext* context, const ::vecsearchgrpc::DefaultRequest* request, ::vecsearchgrpc::DefaultReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status VectorSearchGrpc::Service::unloadIndex(::grpc::ServerContext* context, const ::vecsearchgrpc::DefaultRequest* request, ::vecsearchgrpc::DefaultReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status VectorSearchGrpc::Service::searchNeighbors(::grpc::ServerContext* context, const ::vecsearchgrpc::SearchRequest* request, ::vecsearchgrpc::SearchReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace vecsearchgrpc

