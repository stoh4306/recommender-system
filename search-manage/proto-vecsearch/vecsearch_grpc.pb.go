// Code generated by protoc-gen-go-grpc. DO NOT EDIT.
// versions:
// - protoc-gen-go-grpc v1.3.0
// - protoc             v4.23.4
// source: vecsearch.proto

package vecsearchgrpc

import (
	context "context"
	grpc "google.golang.org/grpc"
	codes "google.golang.org/grpc/codes"
	status "google.golang.org/grpc/status"
)

// This is a compile-time assertion to ensure that this generated file
// is compatible with the grpc package it is being compiled against.
// Requires gRPC-Go v1.32.0 or later.
const _ = grpc.SupportPackageIsVersion7

const (
	VectorSearchGrpc_ListLoadedIndex_FullMethodName       = "/vecsearchgrpc.VectorSearchGrpc/listLoadedIndex"
	VectorSearchGrpc_GetIndexFromContainer_FullMethodName = "/vecsearchgrpc.VectorSearchGrpc/getIndexFromContainer"
	VectorSearchGrpc_CreateIndex_FullMethodName           = "/vecsearchgrpc.VectorSearchGrpc/createIndex"
	VectorSearchGrpc_DeleteIndex_FullMethodName           = "/vecsearchgrpc.VectorSearchGrpc/deleteIndex"
	VectorSearchGrpc_AddVectors_FullMethodName            = "/vecsearchgrpc.VectorSearchGrpc/addVectors"
	VectorSearchGrpc_LoadIndex_FullMethodName             = "/vecsearchgrpc.VectorSearchGrpc/loadIndex"
	VectorSearchGrpc_UnloadIndex_FullMethodName           = "/vecsearchgrpc.VectorSearchGrpc/unloadIndex"
	VectorSearchGrpc_SearchNeighbors_FullMethodName       = "/vecsearchgrpc.VectorSearchGrpc/searchNeighbors"
)

// VectorSearchGrpcClient is the client API for VectorSearchGrpc service.
//
// For semantics around ctx use and closing/ending streaming RPCs, please refer to https://pkg.go.dev/google.golang.org/grpc/?tab=doc#ClientConn.NewStream.
type VectorSearchGrpcClient interface {
	ListLoadedIndex(ctx context.Context, in *EmptyRequest, opts ...grpc.CallOption) (*IndexList, error)
	GetIndexFromContainer(ctx context.Context, in *DefaultRequest, opts ...grpc.CallOption) (*IndexInfo, error)
	CreateIndex(ctx context.Context, in *CreateIndexRequest, opts ...grpc.CallOption) (*DefaultReply, error)
	DeleteIndex(ctx context.Context, in *DefaultRequest, opts ...grpc.CallOption) (*DefaultReply, error)
	AddVectors(ctx context.Context, in *CreateIndexRequest, opts ...grpc.CallOption) (*DefaultReply, error)
	LoadIndex(ctx context.Context, in *DefaultRequest, opts ...grpc.CallOption) (*DefaultReply, error)
	UnloadIndex(ctx context.Context, in *DefaultRequest, opts ...grpc.CallOption) (*DefaultReply, error)
	SearchNeighbors(ctx context.Context, in *SearchRequest, opts ...grpc.CallOption) (*SearchReply, error)
}

type vectorSearchGrpcClient struct {
	cc grpc.ClientConnInterface
}

func NewVectorSearchGrpcClient(cc grpc.ClientConnInterface) VectorSearchGrpcClient {
	return &vectorSearchGrpcClient{cc}
}

func (c *vectorSearchGrpcClient) ListLoadedIndex(ctx context.Context, in *EmptyRequest, opts ...grpc.CallOption) (*IndexList, error) {
	out := new(IndexList)
	err := c.cc.Invoke(ctx, VectorSearchGrpc_ListLoadedIndex_FullMethodName, in, out, opts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

func (c *vectorSearchGrpcClient) GetIndexFromContainer(ctx context.Context, in *DefaultRequest, opts ...grpc.CallOption) (*IndexInfo, error) {
	out := new(IndexInfo)
	err := c.cc.Invoke(ctx, VectorSearchGrpc_GetIndexFromContainer_FullMethodName, in, out, opts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

func (c *vectorSearchGrpcClient) CreateIndex(ctx context.Context, in *CreateIndexRequest, opts ...grpc.CallOption) (*DefaultReply, error) {
	out := new(DefaultReply)
	err := c.cc.Invoke(ctx, VectorSearchGrpc_CreateIndex_FullMethodName, in, out, opts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

func (c *vectorSearchGrpcClient) DeleteIndex(ctx context.Context, in *DefaultRequest, opts ...grpc.CallOption) (*DefaultReply, error) {
	out := new(DefaultReply)
	err := c.cc.Invoke(ctx, VectorSearchGrpc_DeleteIndex_FullMethodName, in, out, opts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

func (c *vectorSearchGrpcClient) AddVectors(ctx context.Context, in *CreateIndexRequest, opts ...grpc.CallOption) (*DefaultReply, error) {
	out := new(DefaultReply)
	err := c.cc.Invoke(ctx, VectorSearchGrpc_AddVectors_FullMethodName, in, out, opts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

func (c *vectorSearchGrpcClient) LoadIndex(ctx context.Context, in *DefaultRequest, opts ...grpc.CallOption) (*DefaultReply, error) {
	out := new(DefaultReply)
	err := c.cc.Invoke(ctx, VectorSearchGrpc_LoadIndex_FullMethodName, in, out, opts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

func (c *vectorSearchGrpcClient) UnloadIndex(ctx context.Context, in *DefaultRequest, opts ...grpc.CallOption) (*DefaultReply, error) {
	out := new(DefaultReply)
	err := c.cc.Invoke(ctx, VectorSearchGrpc_UnloadIndex_FullMethodName, in, out, opts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

func (c *vectorSearchGrpcClient) SearchNeighbors(ctx context.Context, in *SearchRequest, opts ...grpc.CallOption) (*SearchReply, error) {
	out := new(SearchReply)
	err := c.cc.Invoke(ctx, VectorSearchGrpc_SearchNeighbors_FullMethodName, in, out, opts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

// VectorSearchGrpcServer is the server API for VectorSearchGrpc service.
// All implementations must embed UnimplementedVectorSearchGrpcServer
// for forward compatibility
type VectorSearchGrpcServer interface {
	ListLoadedIndex(context.Context, *EmptyRequest) (*IndexList, error)
	GetIndexFromContainer(context.Context, *DefaultRequest) (*IndexInfo, error)
	CreateIndex(context.Context, *CreateIndexRequest) (*DefaultReply, error)
	DeleteIndex(context.Context, *DefaultRequest) (*DefaultReply, error)
	AddVectors(context.Context, *CreateIndexRequest) (*DefaultReply, error)
	LoadIndex(context.Context, *DefaultRequest) (*DefaultReply, error)
	UnloadIndex(context.Context, *DefaultRequest) (*DefaultReply, error)
	SearchNeighbors(context.Context, *SearchRequest) (*SearchReply, error)
	mustEmbedUnimplementedVectorSearchGrpcServer()
}

// UnimplementedVectorSearchGrpcServer must be embedded to have forward compatible implementations.
type UnimplementedVectorSearchGrpcServer struct {
}

func (UnimplementedVectorSearchGrpcServer) ListLoadedIndex(context.Context, *EmptyRequest) (*IndexList, error) {
	return nil, status.Errorf(codes.Unimplemented, "method ListLoadedIndex not implemented")
}
func (UnimplementedVectorSearchGrpcServer) GetIndexFromContainer(context.Context, *DefaultRequest) (*IndexInfo, error) {
	return nil, status.Errorf(codes.Unimplemented, "method GetIndexFromContainer not implemented")
}
func (UnimplementedVectorSearchGrpcServer) CreateIndex(context.Context, *CreateIndexRequest) (*DefaultReply, error) {
	return nil, status.Errorf(codes.Unimplemented, "method CreateIndex not implemented")
}
func (UnimplementedVectorSearchGrpcServer) DeleteIndex(context.Context, *DefaultRequest) (*DefaultReply, error) {
	return nil, status.Errorf(codes.Unimplemented, "method DeleteIndex not implemented")
}
func (UnimplementedVectorSearchGrpcServer) AddVectors(context.Context, *CreateIndexRequest) (*DefaultReply, error) {
	return nil, status.Errorf(codes.Unimplemented, "method AddVectors not implemented")
}
func (UnimplementedVectorSearchGrpcServer) LoadIndex(context.Context, *DefaultRequest) (*DefaultReply, error) {
	return nil, status.Errorf(codes.Unimplemented, "method LoadIndex not implemented")
}
func (UnimplementedVectorSearchGrpcServer) UnloadIndex(context.Context, *DefaultRequest) (*DefaultReply, error) {
	return nil, status.Errorf(codes.Unimplemented, "method UnloadIndex not implemented")
}
func (UnimplementedVectorSearchGrpcServer) SearchNeighbors(context.Context, *SearchRequest) (*SearchReply, error) {
	return nil, status.Errorf(codes.Unimplemented, "method SearchNeighbors not implemented")
}
func (UnimplementedVectorSearchGrpcServer) mustEmbedUnimplementedVectorSearchGrpcServer() {}

// UnsafeVectorSearchGrpcServer may be embedded to opt out of forward compatibility for this service.
// Use of this interface is not recommended, as added methods to VectorSearchGrpcServer will
// result in compilation errors.
type UnsafeVectorSearchGrpcServer interface {
	mustEmbedUnimplementedVectorSearchGrpcServer()
}

func RegisterVectorSearchGrpcServer(s grpc.ServiceRegistrar, srv VectorSearchGrpcServer) {
	s.RegisterService(&VectorSearchGrpc_ServiceDesc, srv)
}

func _VectorSearchGrpc_ListLoadedIndex_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(EmptyRequest)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(VectorSearchGrpcServer).ListLoadedIndex(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: VectorSearchGrpc_ListLoadedIndex_FullMethodName,
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(VectorSearchGrpcServer).ListLoadedIndex(ctx, req.(*EmptyRequest))
	}
	return interceptor(ctx, in, info, handler)
}

func _VectorSearchGrpc_GetIndexFromContainer_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(DefaultRequest)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(VectorSearchGrpcServer).GetIndexFromContainer(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: VectorSearchGrpc_GetIndexFromContainer_FullMethodName,
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(VectorSearchGrpcServer).GetIndexFromContainer(ctx, req.(*DefaultRequest))
	}
	return interceptor(ctx, in, info, handler)
}

func _VectorSearchGrpc_CreateIndex_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(CreateIndexRequest)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(VectorSearchGrpcServer).CreateIndex(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: VectorSearchGrpc_CreateIndex_FullMethodName,
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(VectorSearchGrpcServer).CreateIndex(ctx, req.(*CreateIndexRequest))
	}
	return interceptor(ctx, in, info, handler)
}

func _VectorSearchGrpc_DeleteIndex_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(DefaultRequest)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(VectorSearchGrpcServer).DeleteIndex(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: VectorSearchGrpc_DeleteIndex_FullMethodName,
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(VectorSearchGrpcServer).DeleteIndex(ctx, req.(*DefaultRequest))
	}
	return interceptor(ctx, in, info, handler)
}

func _VectorSearchGrpc_AddVectors_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(CreateIndexRequest)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(VectorSearchGrpcServer).AddVectors(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: VectorSearchGrpc_AddVectors_FullMethodName,
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(VectorSearchGrpcServer).AddVectors(ctx, req.(*CreateIndexRequest))
	}
	return interceptor(ctx, in, info, handler)
}

func _VectorSearchGrpc_LoadIndex_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(DefaultRequest)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(VectorSearchGrpcServer).LoadIndex(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: VectorSearchGrpc_LoadIndex_FullMethodName,
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(VectorSearchGrpcServer).LoadIndex(ctx, req.(*DefaultRequest))
	}
	return interceptor(ctx, in, info, handler)
}

func _VectorSearchGrpc_UnloadIndex_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(DefaultRequest)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(VectorSearchGrpcServer).UnloadIndex(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: VectorSearchGrpc_UnloadIndex_FullMethodName,
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(VectorSearchGrpcServer).UnloadIndex(ctx, req.(*DefaultRequest))
	}
	return interceptor(ctx, in, info, handler)
}

func _VectorSearchGrpc_SearchNeighbors_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(SearchRequest)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(VectorSearchGrpcServer).SearchNeighbors(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: VectorSearchGrpc_SearchNeighbors_FullMethodName,
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(VectorSearchGrpcServer).SearchNeighbors(ctx, req.(*SearchRequest))
	}
	return interceptor(ctx, in, info, handler)
}

// VectorSearchGrpc_ServiceDesc is the grpc.ServiceDesc for VectorSearchGrpc service.
// It's only intended for direct use with grpc.RegisterService,
// and not to be introspected or modified (even as a copy)
var VectorSearchGrpc_ServiceDesc = grpc.ServiceDesc{
	ServiceName: "vecsearchgrpc.VectorSearchGrpc",
	HandlerType: (*VectorSearchGrpcServer)(nil),
	Methods: []grpc.MethodDesc{
		{
			MethodName: "listLoadedIndex",
			Handler:    _VectorSearchGrpc_ListLoadedIndex_Handler,
		},
		{
			MethodName: "getIndexFromContainer",
			Handler:    _VectorSearchGrpc_GetIndexFromContainer_Handler,
		},
		{
			MethodName: "createIndex",
			Handler:    _VectorSearchGrpc_CreateIndex_Handler,
		},
		{
			MethodName: "deleteIndex",
			Handler:    _VectorSearchGrpc_DeleteIndex_Handler,
		},
		{
			MethodName: "addVectors",
			Handler:    _VectorSearchGrpc_AddVectors_Handler,
		},
		{
			MethodName: "loadIndex",
			Handler:    _VectorSearchGrpc_LoadIndex_Handler,
		},
		{
			MethodName: "unloadIndex",
			Handler:    _VectorSearchGrpc_UnloadIndex_Handler,
		},
		{
			MethodName: "searchNeighbors",
			Handler:    _VectorSearchGrpc_SearchNeighbors_Handler,
		},
	},
	Streams:  []grpc.StreamDesc{},
	Metadata: "vecsearch.proto",
}
