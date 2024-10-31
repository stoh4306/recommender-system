// Code generated by protoc-gen-go. DO NOT EDIT.
// versions:
// 	protoc-gen-go v1.31.0
// 	protoc        v4.23.4
// source: vecsearch.proto

package vecsearchgrpc

import (
	protoreflect "google.golang.org/protobuf/reflect/protoreflect"
	protoimpl "google.golang.org/protobuf/runtime/protoimpl"
	reflect "reflect"
	sync "sync"
)

const (
	// Verify that this generated code is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(20 - protoimpl.MinVersion)
	// Verify that runtime/protoimpl is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(protoimpl.MaxVersion - 20)
)

type EmptyRequest struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields
}

func (x *EmptyRequest) Reset() {
	*x = EmptyRequest{}
	if protoimpl.UnsafeEnabled {
		mi := &file_vecsearch_proto_msgTypes[0]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *EmptyRequest) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*EmptyRequest) ProtoMessage() {}

func (x *EmptyRequest) ProtoReflect() protoreflect.Message {
	mi := &file_vecsearch_proto_msgTypes[0]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use EmptyRequest.ProtoReflect.Descriptor instead.
func (*EmptyRequest) Descriptor() ([]byte, []int) {
	return file_vecsearch_proto_rawDescGZIP(), []int{0}
}

type IndexList struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	IndexName  []string `protobuf:"bytes,1,rep,name=indexName,proto3" json:"indexName,omitempty"`
	NumVectors []uint64 `protobuf:"varint,2,rep,packed,name=numVectors,proto3" json:"numVectors,omitempty"`
	Dim        []uint32 `protobuf:"varint,3,rep,packed,name=dim,proto3" json:"dim,omitempty"`
}

func (x *IndexList) Reset() {
	*x = IndexList{}
	if protoimpl.UnsafeEnabled {
		mi := &file_vecsearch_proto_msgTypes[1]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *IndexList) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*IndexList) ProtoMessage() {}

func (x *IndexList) ProtoReflect() protoreflect.Message {
	mi := &file_vecsearch_proto_msgTypes[1]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use IndexList.ProtoReflect.Descriptor instead.
func (*IndexList) Descriptor() ([]byte, []int) {
	return file_vecsearch_proto_rawDescGZIP(), []int{1}
}

func (x *IndexList) GetIndexName() []string {
	if x != nil {
		return x.IndexName
	}
	return nil
}

func (x *IndexList) GetNumVectors() []uint64 {
	if x != nil {
		return x.NumVectors
	}
	return nil
}

func (x *IndexList) GetDim() []uint32 {
	if x != nil {
		return x.Dim
	}
	return nil
}

type IndexInfo struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	IndexName    string `protobuf:"bytes,1,opt,name=indexName,proto3" json:"indexName,omitempty"`
	DataFilePath string `protobuf:"bytes,2,opt,name=dataFilePath,proto3" json:"dataFilePath,omitempty"`
}

func (x *IndexInfo) Reset() {
	*x = IndexInfo{}
	if protoimpl.UnsafeEnabled {
		mi := &file_vecsearch_proto_msgTypes[2]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *IndexInfo) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*IndexInfo) ProtoMessage() {}

func (x *IndexInfo) ProtoReflect() protoreflect.Message {
	mi := &file_vecsearch_proto_msgTypes[2]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use IndexInfo.ProtoReflect.Descriptor instead.
func (*IndexInfo) Descriptor() ([]byte, []int) {
	return file_vecsearch_proto_rawDescGZIP(), []int{2}
}

func (x *IndexInfo) GetIndexName() string {
	if x != nil {
		return x.IndexName
	}
	return ""
}

func (x *IndexInfo) GetDataFilePath() string {
	if x != nil {
		return x.DataFilePath
	}
	return ""
}

type CreateIndexRequest struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	IndexName  string    `protobuf:"bytes,1,opt,name=indexName,proto3" json:"indexName,omitempty"`
	NumVectors uint64    `protobuf:"varint,2,opt,name=numVectors,proto3" json:"numVectors,omitempty"`
	Dim        uint32    `protobuf:"varint,3,opt,name=dim,proto3" json:"dim,omitempty"`
	VecData    []float32 `protobuf:"fixed32,4,rep,packed,name=vecData,proto3" json:"vecData,omitempty"`
}

func (x *CreateIndexRequest) Reset() {
	*x = CreateIndexRequest{}
	if protoimpl.UnsafeEnabled {
		mi := &file_vecsearch_proto_msgTypes[3]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *CreateIndexRequest) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*CreateIndexRequest) ProtoMessage() {}

func (x *CreateIndexRequest) ProtoReflect() protoreflect.Message {
	mi := &file_vecsearch_proto_msgTypes[3]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use CreateIndexRequest.ProtoReflect.Descriptor instead.
func (*CreateIndexRequest) Descriptor() ([]byte, []int) {
	return file_vecsearch_proto_rawDescGZIP(), []int{3}
}

func (x *CreateIndexRequest) GetIndexName() string {
	if x != nil {
		return x.IndexName
	}
	return ""
}

func (x *CreateIndexRequest) GetNumVectors() uint64 {
	if x != nil {
		return x.NumVectors
	}
	return 0
}

func (x *CreateIndexRequest) GetDim() uint32 {
	if x != nil {
		return x.Dim
	}
	return 0
}

func (x *CreateIndexRequest) GetVecData() []float32 {
	if x != nil {
		return x.VecData
	}
	return nil
}

type SearchRequest struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	IndexName       string    `protobuf:"bytes,1,opt,name=indexName,proto3" json:"indexName,omitempty"`
	NumQueryVectors uint32    `protobuf:"varint,2,opt,name=numQueryVectors,proto3" json:"numQueryVectors,omitempty"`
	Dim             uint32    `protobuf:"varint,3,opt,name=dim,proto3" json:"dim,omitempty"`
	VecData         []float32 `protobuf:"fixed32,4,rep,packed,name=vecData,proto3" json:"vecData,omitempty"`
	NumNeighbors    uint32    `protobuf:"varint,5,opt,name=numNeighbors,proto3" json:"numNeighbors,omitempty"`
}

func (x *SearchRequest) Reset() {
	*x = SearchRequest{}
	if protoimpl.UnsafeEnabled {
		mi := &file_vecsearch_proto_msgTypes[4]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *SearchRequest) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*SearchRequest) ProtoMessage() {}

func (x *SearchRequest) ProtoReflect() protoreflect.Message {
	mi := &file_vecsearch_proto_msgTypes[4]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use SearchRequest.ProtoReflect.Descriptor instead.
func (*SearchRequest) Descriptor() ([]byte, []int) {
	return file_vecsearch_proto_rawDescGZIP(), []int{4}
}

func (x *SearchRequest) GetIndexName() string {
	if x != nil {
		return x.IndexName
	}
	return ""
}

func (x *SearchRequest) GetNumQueryVectors() uint32 {
	if x != nil {
		return x.NumQueryVectors
	}
	return 0
}

func (x *SearchRequest) GetDim() uint32 {
	if x != nil {
		return x.Dim
	}
	return 0
}

func (x *SearchRequest) GetVecData() []float32 {
	if x != nil {
		return x.VecData
	}
	return nil
}

func (x *SearchRequest) GetNumNeighbors() uint32 {
	if x != nil {
		return x.NumNeighbors
	}
	return 0
}

type SearchReply struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Status          string    `protobuf:"bytes,1,opt,name=status,proto3" json:"status,omitempty"`
	Message         string    `protobuf:"bytes,2,opt,name=message,proto3" json:"message,omitempty"`
	NumQueryVectors uint32    `protobuf:"varint,3,opt,name=numQueryVectors,proto3" json:"numQueryVectors,omitempty"`
	NumNeighbors    uint32    `protobuf:"varint,4,opt,name=numNeighbors,proto3" json:"numNeighbors,omitempty"`
	I               []int64   `protobuf:"varint,5,rep,packed,name=I,proto3" json:"I,omitempty"`
	D               []float32 `protobuf:"fixed32,6,rep,packed,name=D,proto3" json:"D,omitempty"`
}

func (x *SearchReply) Reset() {
	*x = SearchReply{}
	if protoimpl.UnsafeEnabled {
		mi := &file_vecsearch_proto_msgTypes[5]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *SearchReply) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*SearchReply) ProtoMessage() {}

func (x *SearchReply) ProtoReflect() protoreflect.Message {
	mi := &file_vecsearch_proto_msgTypes[5]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use SearchReply.ProtoReflect.Descriptor instead.
func (*SearchReply) Descriptor() ([]byte, []int) {
	return file_vecsearch_proto_rawDescGZIP(), []int{5}
}

func (x *SearchReply) GetStatus() string {
	if x != nil {
		return x.Status
	}
	return ""
}

func (x *SearchReply) GetMessage() string {
	if x != nil {
		return x.Message
	}
	return ""
}

func (x *SearchReply) GetNumQueryVectors() uint32 {
	if x != nil {
		return x.NumQueryVectors
	}
	return 0
}

func (x *SearchReply) GetNumNeighbors() uint32 {
	if x != nil {
		return x.NumNeighbors
	}
	return 0
}

func (x *SearchReply) GetI() []int64 {
	if x != nil {
		return x.I
	}
	return nil
}

func (x *SearchReply) GetD() []float32 {
	if x != nil {
		return x.D
	}
	return nil
}

type DefaultRequest struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	IndexName string `protobuf:"bytes,1,opt,name=indexName,proto3" json:"indexName,omitempty"`
}

func (x *DefaultRequest) Reset() {
	*x = DefaultRequest{}
	if protoimpl.UnsafeEnabled {
		mi := &file_vecsearch_proto_msgTypes[6]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *DefaultRequest) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*DefaultRequest) ProtoMessage() {}

func (x *DefaultRequest) ProtoReflect() protoreflect.Message {
	mi := &file_vecsearch_proto_msgTypes[6]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use DefaultRequest.ProtoReflect.Descriptor instead.
func (*DefaultRequest) Descriptor() ([]byte, []int) {
	return file_vecsearch_proto_rawDescGZIP(), []int{6}
}

func (x *DefaultRequest) GetIndexName() string {
	if x != nil {
		return x.IndexName
	}
	return ""
}

type DefaultReply struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Status  string `protobuf:"bytes,1,opt,name=status,proto3" json:"status,omitempty"`
	Message string `protobuf:"bytes,2,opt,name=message,proto3" json:"message,omitempty"`
}

func (x *DefaultReply) Reset() {
	*x = DefaultReply{}
	if protoimpl.UnsafeEnabled {
		mi := &file_vecsearch_proto_msgTypes[7]
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		ms.StoreMessageInfo(mi)
	}
}

func (x *DefaultReply) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*DefaultReply) ProtoMessage() {}

func (x *DefaultReply) ProtoReflect() protoreflect.Message {
	mi := &file_vecsearch_proto_msgTypes[7]
	if protoimpl.UnsafeEnabled && x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use DefaultReply.ProtoReflect.Descriptor instead.
func (*DefaultReply) Descriptor() ([]byte, []int) {
	return file_vecsearch_proto_rawDescGZIP(), []int{7}
}

func (x *DefaultReply) GetStatus() string {
	if x != nil {
		return x.Status
	}
	return ""
}

func (x *DefaultReply) GetMessage() string {
	if x != nil {
		return x.Message
	}
	return ""
}

var File_vecsearch_proto protoreflect.FileDescriptor

var file_vecsearch_proto_rawDesc = []byte{
	0x0a, 0x0f, 0x76, 0x65, 0x63, 0x73, 0x65, 0x61, 0x72, 0x63, 0x68, 0x2e, 0x70, 0x72, 0x6f, 0x74,
	0x6f, 0x12, 0x0d, 0x76, 0x65, 0x63, 0x73, 0x65, 0x61, 0x72, 0x63, 0x68, 0x67, 0x72, 0x70, 0x63,
	0x22, 0x0e, 0x0a, 0x0c, 0x45, 0x6d, 0x70, 0x74, 0x79, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74,
	0x22, 0x5b, 0x0a, 0x09, 0x49, 0x6e, 0x64, 0x65, 0x78, 0x4c, 0x69, 0x73, 0x74, 0x12, 0x1c, 0x0a,
	0x09, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x4e, 0x61, 0x6d, 0x65, 0x18, 0x01, 0x20, 0x03, 0x28, 0x09,
	0x52, 0x09, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x4e, 0x61, 0x6d, 0x65, 0x12, 0x1e, 0x0a, 0x0a, 0x6e,
	0x75, 0x6d, 0x56, 0x65, 0x63, 0x74, 0x6f, 0x72, 0x73, 0x18, 0x02, 0x20, 0x03, 0x28, 0x04, 0x52,
	0x0a, 0x6e, 0x75, 0x6d, 0x56, 0x65, 0x63, 0x74, 0x6f, 0x72, 0x73, 0x12, 0x10, 0x0a, 0x03, 0x64,
	0x69, 0x6d, 0x18, 0x03, 0x20, 0x03, 0x28, 0x0d, 0x52, 0x03, 0x64, 0x69, 0x6d, 0x22, 0x4d, 0x0a,
	0x09, 0x49, 0x6e, 0x64, 0x65, 0x78, 0x49, 0x6e, 0x66, 0x6f, 0x12, 0x1c, 0x0a, 0x09, 0x69, 0x6e,
	0x64, 0x65, 0x78, 0x4e, 0x61, 0x6d, 0x65, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x09, 0x69,
	0x6e, 0x64, 0x65, 0x78, 0x4e, 0x61, 0x6d, 0x65, 0x12, 0x22, 0x0a, 0x0c, 0x64, 0x61, 0x74, 0x61,
	0x46, 0x69, 0x6c, 0x65, 0x50, 0x61, 0x74, 0x68, 0x18, 0x02, 0x20, 0x01, 0x28, 0x09, 0x52, 0x0c,
	0x64, 0x61, 0x74, 0x61, 0x46, 0x69, 0x6c, 0x65, 0x50, 0x61, 0x74, 0x68, 0x22, 0x7e, 0x0a, 0x12,
	0x43, 0x72, 0x65, 0x61, 0x74, 0x65, 0x49, 0x6e, 0x64, 0x65, 0x78, 0x52, 0x65, 0x71, 0x75, 0x65,
	0x73, 0x74, 0x12, 0x1c, 0x0a, 0x09, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x4e, 0x61, 0x6d, 0x65, 0x18,
	0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x09, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x4e, 0x61, 0x6d, 0x65,
	0x12, 0x1e, 0x0a, 0x0a, 0x6e, 0x75, 0x6d, 0x56, 0x65, 0x63, 0x74, 0x6f, 0x72, 0x73, 0x18, 0x02,
	0x20, 0x01, 0x28, 0x04, 0x52, 0x0a, 0x6e, 0x75, 0x6d, 0x56, 0x65, 0x63, 0x74, 0x6f, 0x72, 0x73,
	0x12, 0x10, 0x0a, 0x03, 0x64, 0x69, 0x6d, 0x18, 0x03, 0x20, 0x01, 0x28, 0x0d, 0x52, 0x03, 0x64,
	0x69, 0x6d, 0x12, 0x18, 0x0a, 0x07, 0x76, 0x65, 0x63, 0x44, 0x61, 0x74, 0x61, 0x18, 0x04, 0x20,
	0x03, 0x28, 0x02, 0x52, 0x07, 0x76, 0x65, 0x63, 0x44, 0x61, 0x74, 0x61, 0x22, 0xa7, 0x01, 0x0a,
	0x0d, 0x53, 0x65, 0x61, 0x72, 0x63, 0x68, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x12, 0x1c,
	0x0a, 0x09, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x4e, 0x61, 0x6d, 0x65, 0x18, 0x01, 0x20, 0x01, 0x28,
	0x09, 0x52, 0x09, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x4e, 0x61, 0x6d, 0x65, 0x12, 0x28, 0x0a, 0x0f,
	0x6e, 0x75, 0x6d, 0x51, 0x75, 0x65, 0x72, 0x79, 0x56, 0x65, 0x63, 0x74, 0x6f, 0x72, 0x73, 0x18,
	0x02, 0x20, 0x01, 0x28, 0x0d, 0x52, 0x0f, 0x6e, 0x75, 0x6d, 0x51, 0x75, 0x65, 0x72, 0x79, 0x56,
	0x65, 0x63, 0x74, 0x6f, 0x72, 0x73, 0x12, 0x10, 0x0a, 0x03, 0x64, 0x69, 0x6d, 0x18, 0x03, 0x20,
	0x01, 0x28, 0x0d, 0x52, 0x03, 0x64, 0x69, 0x6d, 0x12, 0x18, 0x0a, 0x07, 0x76, 0x65, 0x63, 0x44,
	0x61, 0x74, 0x61, 0x18, 0x04, 0x20, 0x03, 0x28, 0x02, 0x52, 0x07, 0x76, 0x65, 0x63, 0x44, 0x61,
	0x74, 0x61, 0x12, 0x22, 0x0a, 0x0c, 0x6e, 0x75, 0x6d, 0x4e, 0x65, 0x69, 0x67, 0x68, 0x62, 0x6f,
	0x72, 0x73, 0x18, 0x05, 0x20, 0x01, 0x28, 0x0d, 0x52, 0x0c, 0x6e, 0x75, 0x6d, 0x4e, 0x65, 0x69,
	0x67, 0x68, 0x62, 0x6f, 0x72, 0x73, 0x22, 0xa9, 0x01, 0x0a, 0x0b, 0x53, 0x65, 0x61, 0x72, 0x63,
	0x68, 0x52, 0x65, 0x70, 0x6c, 0x79, 0x12, 0x16, 0x0a, 0x06, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73,
	0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x06, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x12, 0x18,
	0x0a, 0x07, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x18, 0x02, 0x20, 0x01, 0x28, 0x09, 0x52,
	0x07, 0x6d, 0x65, 0x73, 0x73, 0x61, 0x67, 0x65, 0x12, 0x28, 0x0a, 0x0f, 0x6e, 0x75, 0x6d, 0x51,
	0x75, 0x65, 0x72, 0x79, 0x56, 0x65, 0x63, 0x74, 0x6f, 0x72, 0x73, 0x18, 0x03, 0x20, 0x01, 0x28,
	0x0d, 0x52, 0x0f, 0x6e, 0x75, 0x6d, 0x51, 0x75, 0x65, 0x72, 0x79, 0x56, 0x65, 0x63, 0x74, 0x6f,
	0x72, 0x73, 0x12, 0x22, 0x0a, 0x0c, 0x6e, 0x75, 0x6d, 0x4e, 0x65, 0x69, 0x67, 0x68, 0x62, 0x6f,
	0x72, 0x73, 0x18, 0x04, 0x20, 0x01, 0x28, 0x0d, 0x52, 0x0c, 0x6e, 0x75, 0x6d, 0x4e, 0x65, 0x69,
	0x67, 0x68, 0x62, 0x6f, 0x72, 0x73, 0x12, 0x0c, 0x0a, 0x01, 0x49, 0x18, 0x05, 0x20, 0x03, 0x28,
	0x03, 0x52, 0x01, 0x49, 0x12, 0x0c, 0x0a, 0x01, 0x44, 0x18, 0x06, 0x20, 0x03, 0x28, 0x02, 0x52,
	0x01, 0x44, 0x22, 0x2e, 0x0a, 0x0e, 0x44, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74, 0x52, 0x65, 0x71,
	0x75, 0x65, 0x73, 0x74, 0x12, 0x1c, 0x0a, 0x09, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x4e, 0x61, 0x6d,
	0x65, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x09, 0x69, 0x6e, 0x64, 0x65, 0x78, 0x4e, 0x61,
	0x6d, 0x65, 0x22, 0x40, 0x0a, 0x0c, 0x44, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74, 0x52, 0x65, 0x70,
	0x6c, 0x79, 0x12, 0x16, 0x0a, 0x06, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x18, 0x01, 0x20, 0x01,
	0x28, 0x09, 0x52, 0x06, 0x73, 0x74, 0x61, 0x74, 0x75, 0x73, 0x12, 0x18, 0x0a, 0x07, 0x6d, 0x65,
	0x73, 0x73, 0x61, 0x67, 0x65, 0x18, 0x02, 0x20, 0x01, 0x28, 0x09, 0x52, 0x07, 0x6d, 0x65, 0x73,
	0x73, 0x61, 0x67, 0x65, 0x32, 0xf9, 0x04, 0x0a, 0x10, 0x56, 0x65, 0x63, 0x74, 0x6f, 0x72, 0x53,
	0x65, 0x61, 0x72, 0x63, 0x68, 0x47, 0x72, 0x70, 0x63, 0x12, 0x48, 0x0a, 0x0f, 0x6c, 0x69, 0x73,
	0x74, 0x4c, 0x6f, 0x61, 0x64, 0x65, 0x64, 0x49, 0x6e, 0x64, 0x65, 0x78, 0x12, 0x1b, 0x2e, 0x76,
	0x65, 0x63, 0x73, 0x65, 0x61, 0x72, 0x63, 0x68, 0x67, 0x72, 0x70, 0x63, 0x2e, 0x45, 0x6d, 0x70,
	0x74, 0x79, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x1a, 0x18, 0x2e, 0x76, 0x65, 0x63, 0x73,
	0x65, 0x61, 0x72, 0x63, 0x68, 0x67, 0x72, 0x70, 0x63, 0x2e, 0x49, 0x6e, 0x64, 0x65, 0x78, 0x4c,
	0x69, 0x73, 0x74, 0x12, 0x50, 0x0a, 0x15, 0x67, 0x65, 0x74, 0x49, 0x6e, 0x64, 0x65, 0x78, 0x46,
	0x72, 0x6f, 0x6d, 0x43, 0x6f, 0x6e, 0x74, 0x61, 0x69, 0x6e, 0x65, 0x72, 0x12, 0x1d, 0x2e, 0x76,
	0x65, 0x63, 0x73, 0x65, 0x61, 0x72, 0x63, 0x68, 0x67, 0x72, 0x70, 0x63, 0x2e, 0x44, 0x65, 0x66,
	0x61, 0x75, 0x6c, 0x74, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x1a, 0x18, 0x2e, 0x76, 0x65,
	0x63, 0x73, 0x65, 0x61, 0x72, 0x63, 0x68, 0x67, 0x72, 0x70, 0x63, 0x2e, 0x49, 0x6e, 0x64, 0x65,
	0x78, 0x49, 0x6e, 0x66, 0x6f, 0x12, 0x4d, 0x0a, 0x0b, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x49,
	0x6e, 0x64, 0x65, 0x78, 0x12, 0x21, 0x2e, 0x76, 0x65, 0x63, 0x73, 0x65, 0x61, 0x72, 0x63, 0x68,
	0x67, 0x72, 0x70, 0x63, 0x2e, 0x43, 0x72, 0x65, 0x61, 0x74, 0x65, 0x49, 0x6e, 0x64, 0x65, 0x78,
	0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x1a, 0x1b, 0x2e, 0x76, 0x65, 0x63, 0x73, 0x65, 0x61,
	0x72, 0x63, 0x68, 0x67, 0x72, 0x70, 0x63, 0x2e, 0x44, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74, 0x52,
	0x65, 0x70, 0x6c, 0x79, 0x12, 0x49, 0x0a, 0x0b, 0x64, 0x65, 0x6c, 0x65, 0x74, 0x65, 0x49, 0x6e,
	0x64, 0x65, 0x78, 0x12, 0x1d, 0x2e, 0x76, 0x65, 0x63, 0x73, 0x65, 0x61, 0x72, 0x63, 0x68, 0x67,
	0x72, 0x70, 0x63, 0x2e, 0x44, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74, 0x52, 0x65, 0x71, 0x75, 0x65,
	0x73, 0x74, 0x1a, 0x1b, 0x2e, 0x76, 0x65, 0x63, 0x73, 0x65, 0x61, 0x72, 0x63, 0x68, 0x67, 0x72,
	0x70, 0x63, 0x2e, 0x44, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74, 0x52, 0x65, 0x70, 0x6c, 0x79, 0x12,
	0x4c, 0x0a, 0x0a, 0x61, 0x64, 0x64, 0x56, 0x65, 0x63, 0x74, 0x6f, 0x72, 0x73, 0x12, 0x21, 0x2e,
	0x76, 0x65, 0x63, 0x73, 0x65, 0x61, 0x72, 0x63, 0x68, 0x67, 0x72, 0x70, 0x63, 0x2e, 0x43, 0x72,
	0x65, 0x61, 0x74, 0x65, 0x49, 0x6e, 0x64, 0x65, 0x78, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74,
	0x1a, 0x1b, 0x2e, 0x76, 0x65, 0x63, 0x73, 0x65, 0x61, 0x72, 0x63, 0x68, 0x67, 0x72, 0x70, 0x63,
	0x2e, 0x44, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74, 0x52, 0x65, 0x70, 0x6c, 0x79, 0x12, 0x47, 0x0a,
	0x09, 0x6c, 0x6f, 0x61, 0x64, 0x49, 0x6e, 0x64, 0x65, 0x78, 0x12, 0x1d, 0x2e, 0x76, 0x65, 0x63,
	0x73, 0x65, 0x61, 0x72, 0x63, 0x68, 0x67, 0x72, 0x70, 0x63, 0x2e, 0x44, 0x65, 0x66, 0x61, 0x75,
	0x6c, 0x74, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x1a, 0x1b, 0x2e, 0x76, 0x65, 0x63, 0x73,
	0x65, 0x61, 0x72, 0x63, 0x68, 0x67, 0x72, 0x70, 0x63, 0x2e, 0x44, 0x65, 0x66, 0x61, 0x75, 0x6c,
	0x74, 0x52, 0x65, 0x70, 0x6c, 0x79, 0x12, 0x49, 0x0a, 0x0b, 0x75, 0x6e, 0x6c, 0x6f, 0x61, 0x64,
	0x49, 0x6e, 0x64, 0x65, 0x78, 0x12, 0x1d, 0x2e, 0x76, 0x65, 0x63, 0x73, 0x65, 0x61, 0x72, 0x63,
	0x68, 0x67, 0x72, 0x70, 0x63, 0x2e, 0x44, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74, 0x52, 0x65, 0x71,
	0x75, 0x65, 0x73, 0x74, 0x1a, 0x1b, 0x2e, 0x76, 0x65, 0x63, 0x73, 0x65, 0x61, 0x72, 0x63, 0x68,
	0x67, 0x72, 0x70, 0x63, 0x2e, 0x44, 0x65, 0x66, 0x61, 0x75, 0x6c, 0x74, 0x52, 0x65, 0x70, 0x6c,
	0x79, 0x12, 0x4d, 0x0a, 0x0f, 0x73, 0x65, 0x61, 0x72, 0x63, 0x68, 0x4e, 0x65, 0x69, 0x67, 0x68,
	0x62, 0x6f, 0x72, 0x73, 0x12, 0x1c, 0x2e, 0x76, 0x65, 0x63, 0x73, 0x65, 0x61, 0x72, 0x63, 0x68,
	0x67, 0x72, 0x70, 0x63, 0x2e, 0x53, 0x65, 0x61, 0x72, 0x63, 0x68, 0x52, 0x65, 0x71, 0x75, 0x65,
	0x73, 0x74, 0x1a, 0x1a, 0x2e, 0x76, 0x65, 0x63, 0x73, 0x65, 0x61, 0x72, 0x63, 0x68, 0x67, 0x72,
	0x70, 0x63, 0x2e, 0x53, 0x65, 0x61, 0x72, 0x63, 0x68, 0x52, 0x65, 0x70, 0x6c, 0x79, 0x22, 0x00,
	0x42, 0x1d, 0x5a, 0x1b, 0x2e, 0x2f, 0x72, 0x65, 0x63, 0x6f, 0x6d, 0x6d, 0x65, 0x6e, 0x64, 0x65,
	0x72, 0x2f, 0x76, 0x65, 0x63, 0x73, 0x65, 0x61, 0x72, 0x63, 0x68, 0x67, 0x72, 0x70, 0x63, 0x62,
	0x06, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x33,
}

var (
	file_vecsearch_proto_rawDescOnce sync.Once
	file_vecsearch_proto_rawDescData = file_vecsearch_proto_rawDesc
)

func file_vecsearch_proto_rawDescGZIP() []byte {
	file_vecsearch_proto_rawDescOnce.Do(func() {
		file_vecsearch_proto_rawDescData = protoimpl.X.CompressGZIP(file_vecsearch_proto_rawDescData)
	})
	return file_vecsearch_proto_rawDescData
}

var file_vecsearch_proto_msgTypes = make([]protoimpl.MessageInfo, 8)
var file_vecsearch_proto_goTypes = []interface{}{
	(*EmptyRequest)(nil),       // 0: vecsearchgrpc.EmptyRequest
	(*IndexList)(nil),          // 1: vecsearchgrpc.IndexList
	(*IndexInfo)(nil),          // 2: vecsearchgrpc.IndexInfo
	(*CreateIndexRequest)(nil), // 3: vecsearchgrpc.CreateIndexRequest
	(*SearchRequest)(nil),      // 4: vecsearchgrpc.SearchRequest
	(*SearchReply)(nil),        // 5: vecsearchgrpc.SearchReply
	(*DefaultRequest)(nil),     // 6: vecsearchgrpc.DefaultRequest
	(*DefaultReply)(nil),       // 7: vecsearchgrpc.DefaultReply
}
var file_vecsearch_proto_depIdxs = []int32{
	0, // 0: vecsearchgrpc.VectorSearchGrpc.listLoadedIndex:input_type -> vecsearchgrpc.EmptyRequest
	6, // 1: vecsearchgrpc.VectorSearchGrpc.getIndexFromContainer:input_type -> vecsearchgrpc.DefaultRequest
	3, // 2: vecsearchgrpc.VectorSearchGrpc.createIndex:input_type -> vecsearchgrpc.CreateIndexRequest
	6, // 3: vecsearchgrpc.VectorSearchGrpc.deleteIndex:input_type -> vecsearchgrpc.DefaultRequest
	3, // 4: vecsearchgrpc.VectorSearchGrpc.addVectors:input_type -> vecsearchgrpc.CreateIndexRequest
	6, // 5: vecsearchgrpc.VectorSearchGrpc.loadIndex:input_type -> vecsearchgrpc.DefaultRequest
	6, // 6: vecsearchgrpc.VectorSearchGrpc.unloadIndex:input_type -> vecsearchgrpc.DefaultRequest
	4, // 7: vecsearchgrpc.VectorSearchGrpc.searchNeighbors:input_type -> vecsearchgrpc.SearchRequest
	1, // 8: vecsearchgrpc.VectorSearchGrpc.listLoadedIndex:output_type -> vecsearchgrpc.IndexList
	2, // 9: vecsearchgrpc.VectorSearchGrpc.getIndexFromContainer:output_type -> vecsearchgrpc.IndexInfo
	7, // 10: vecsearchgrpc.VectorSearchGrpc.createIndex:output_type -> vecsearchgrpc.DefaultReply
	7, // 11: vecsearchgrpc.VectorSearchGrpc.deleteIndex:output_type -> vecsearchgrpc.DefaultReply
	7, // 12: vecsearchgrpc.VectorSearchGrpc.addVectors:output_type -> vecsearchgrpc.DefaultReply
	7, // 13: vecsearchgrpc.VectorSearchGrpc.loadIndex:output_type -> vecsearchgrpc.DefaultReply
	7, // 14: vecsearchgrpc.VectorSearchGrpc.unloadIndex:output_type -> vecsearchgrpc.DefaultReply
	5, // 15: vecsearchgrpc.VectorSearchGrpc.searchNeighbors:output_type -> vecsearchgrpc.SearchReply
	8, // [8:16] is the sub-list for method output_type
	0, // [0:8] is the sub-list for method input_type
	0, // [0:0] is the sub-list for extension type_name
	0, // [0:0] is the sub-list for extension extendee
	0, // [0:0] is the sub-list for field type_name
}

func init() { file_vecsearch_proto_init() }
func file_vecsearch_proto_init() {
	if File_vecsearch_proto != nil {
		return
	}
	if !protoimpl.UnsafeEnabled {
		file_vecsearch_proto_msgTypes[0].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*EmptyRequest); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_vecsearch_proto_msgTypes[1].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*IndexList); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_vecsearch_proto_msgTypes[2].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*IndexInfo); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_vecsearch_proto_msgTypes[3].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*CreateIndexRequest); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_vecsearch_proto_msgTypes[4].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*SearchRequest); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_vecsearch_proto_msgTypes[5].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*SearchReply); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_vecsearch_proto_msgTypes[6].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*DefaultRequest); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
		file_vecsearch_proto_msgTypes[7].Exporter = func(v interface{}, i int) interface{} {
			switch v := v.(*DefaultReply); i {
			case 0:
				return &v.state
			case 1:
				return &v.sizeCache
			case 2:
				return &v.unknownFields
			default:
				return nil
			}
		}
	}
	type x struct{}
	out := protoimpl.TypeBuilder{
		File: protoimpl.DescBuilder{
			GoPackagePath: reflect.TypeOf(x{}).PkgPath(),
			RawDescriptor: file_vecsearch_proto_rawDesc,
			NumEnums:      0,
			NumMessages:   8,
			NumExtensions: 0,
			NumServices:   1,
		},
		GoTypes:           file_vecsearch_proto_goTypes,
		DependencyIndexes: file_vecsearch_proto_depIdxs,
		MessageInfos:      file_vecsearch_proto_msgTypes,
	}.Build()
	File_vecsearch_proto = out.File
	file_vecsearch_proto_rawDesc = nil
	file_vecsearch_proto_goTypes = nil
	file_vecsearch_proto_depIdxs = nil
}
