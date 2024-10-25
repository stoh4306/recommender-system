#pragma once

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "./proto/par2vec.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

using namespace par2vec;
using par2vec::Par2VecRequest;
using par2vec::HelloRequest;
using par2vec::HelloReply;

class Par2VecGrpcClient {
public:
    Par2VecGrpcClient(std::shared_ptr<Channel> channel) 
        : stub_(Par2Vec::NewStub(channel)) {
    }

    void hello(std::string greetings) {
        ClientContext context;

        HelloRequest request;
        request.set_hello(greetings);

        HelloReply response;
        Status stat = stub_->hello(&context, request, &response);
        if (stat.ok()) {
            std::cout << "- [RESPONSE] " << response.reply() << std::endl;
        } else {
            std::cout << "- [ERROR] Failed to call hello() :";
            std::cout << stat.error_code() << ", " << stat.error_message() << ",  " << stat.error_details() << std::endl;
        }
    }

    void par2vec(std::string par, uint32_t& dim, std::vector<float>& tv) {
        ClientContext context;

        Par2VecRequest request;
        request.set_paragraph(par);

        par2vec::DefaultReply response;
        Status stat = stub_->convertParToVec(&context, request, &response);
        if (stat.ok()) {
            std::cout << "- [RESPONSE] dim=" << response.dim() << ", " 
                << response.fvec().data()[0] << "..." << response.fvec().data()[response.dim()-1] << std::endl;
            tv = std::vector<float>(response.fvec().begin(), response.fvec().end());
            dim = response.dim();
            assert(dim == (uint32_t)tv.size());
            
            //std::cout << "- [RESPONSE] " << "dim=" << response.dim() << ",\n";
            //uint32_t d = response.dim();
            //const float* v = response.fvec().data();
            //for (uint32_t i = 0; i < d; ++i) {
            //    std::cout << v[i] << ", ";
            //}
            //std::cout << std::endl;
        } else {
            std::cout << "- [ERROR] Failed to call convertPar2Vec() :";
            std::cout << stat.error_code() << ", " << stat.error_message() << ",  " << stat.error_details() << std::endl;
        }
    }
private:
    std::unique_ptr<Par2Vec::Stub> stub_;
};