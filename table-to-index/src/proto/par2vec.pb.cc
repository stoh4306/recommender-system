// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: par2vec.proto

#include "par2vec.pb.h"

#include <algorithm>
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/extension_set.h"
#include "google/protobuf/wire_format_lite.h"
#include "google/protobuf/descriptor.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/reflection_ops.h"
#include "google/protobuf/wire_format.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"
PROTOBUF_PRAGMA_INIT_SEG
namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = ::PROTOBUF_NAMESPACE_ID::internal;
namespace par2vec {
template <typename>
PROTOBUF_CONSTEXPR HelloRequest::HelloRequest(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.hello_)*/ {
    &::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized {}
  }

  , /*decltype(_impl_._cached_size_)*/{}} {}
struct HelloRequestDefaultTypeInternal {
  PROTOBUF_CONSTEXPR HelloRequestDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~HelloRequestDefaultTypeInternal() {}
  union {
    HelloRequest _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 HelloRequestDefaultTypeInternal _HelloRequest_default_instance_;
template <typename>
PROTOBUF_CONSTEXPR HelloReply::HelloReply(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.reply_)*/ {
    &::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized {}
  }

  , /*decltype(_impl_._cached_size_)*/{}} {}
struct HelloReplyDefaultTypeInternal {
  PROTOBUF_CONSTEXPR HelloReplyDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~HelloReplyDefaultTypeInternal() {}
  union {
    HelloReply _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 HelloReplyDefaultTypeInternal _HelloReply_default_instance_;
template <typename>
PROTOBUF_CONSTEXPR Par2VecRequest::Par2VecRequest(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.paragraph_)*/ {
    &::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized {}
  }

  , /*decltype(_impl_._cached_size_)*/{}} {}
struct Par2VecRequestDefaultTypeInternal {
  PROTOBUF_CONSTEXPR Par2VecRequestDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~Par2VecRequestDefaultTypeInternal() {}
  union {
    Par2VecRequest _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 Par2VecRequestDefaultTypeInternal _Par2VecRequest_default_instance_;
template <typename>
PROTOBUF_CONSTEXPR DefaultReply::DefaultReply(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.fvec_)*/ {}

  , /*decltype(_impl_.dim_)*/ 0u

  , /*decltype(_impl_._cached_size_)*/{}} {}
struct DefaultReplyDefaultTypeInternal {
  PROTOBUF_CONSTEXPR DefaultReplyDefaultTypeInternal() : _instance(::_pbi::ConstantInitialized{}) {}
  ~DefaultReplyDefaultTypeInternal() {}
  union {
    DefaultReply _instance;
  };
};

PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT
    PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 DefaultReplyDefaultTypeInternal _DefaultReply_default_instance_;
}  // namespace par2vec
static ::_pb::Metadata file_level_metadata_par2vec_2eproto[4];
static constexpr const ::_pb::EnumDescriptor**
    file_level_enum_descriptors_par2vec_2eproto = nullptr;
static constexpr const ::_pb::ServiceDescriptor**
    file_level_service_descriptors_par2vec_2eproto = nullptr;
const ::uint32_t TableStruct_par2vec_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(
    protodesc_cold) = {
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::par2vec::HelloRequest, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::par2vec::HelloRequest, _impl_.hello_),
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::par2vec::HelloReply, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::par2vec::HelloReply, _impl_.reply_),
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::par2vec::Par2VecRequest, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::par2vec::Par2VecRequest, _impl_.paragraph_),
    ~0u,  // no _has_bits_
    PROTOBUF_FIELD_OFFSET(::par2vec::DefaultReply, _internal_metadata_),
    ~0u,  // no _extensions_
    ~0u,  // no _oneof_case_
    ~0u,  // no _weak_field_map_
    ~0u,  // no _inlined_string_donated_
    ~0u,  // no _split_
    ~0u,  // no sizeof(Split)
    PROTOBUF_FIELD_OFFSET(::par2vec::DefaultReply, _impl_.dim_),
    PROTOBUF_FIELD_OFFSET(::par2vec::DefaultReply, _impl_.fvec_),
};

static const ::_pbi::MigrationSchema
    schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
        { 0, -1, -1, sizeof(::par2vec::HelloRequest)},
        { 9, -1, -1, sizeof(::par2vec::HelloReply)},
        { 18, -1, -1, sizeof(::par2vec::Par2VecRequest)},
        { 27, -1, -1, sizeof(::par2vec::DefaultReply)},
};

static const ::_pb::Message* const file_default_instances[] = {
    &::par2vec::_HelloRequest_default_instance_._instance,
    &::par2vec::_HelloReply_default_instance_._instance,
    &::par2vec::_Par2VecRequest_default_instance_._instance,
    &::par2vec::_DefaultReply_default_instance_._instance,
};
const char descriptor_table_protodef_par2vec_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
    "\n\rpar2vec.proto\022\007par2vec\"\035\n\014HelloRequest"
    "\022\r\n\005hello\030\001 \001(\t\"\033\n\nHelloReply\022\r\n\005reply\030\001"
    " \001(\t\"#\n\016Par2VecRequest\022\021\n\tparagraph\030\001 \001("
    "\t\")\n\014DefaultReply\022\013\n\003dim\030\001 \001(\r\022\014\n\004fVec\030\002"
    " \003(\0022\205\001\n\007Par2Vec\0225\n\005hello\022\025.par2vec.Hell"
    "oRequest\032\023.par2vec.HelloReply\"\000\022C\n\017conve"
    "rtParToVec\022\027.par2vec.Par2VecRequest\032\025.pa"
    "r2vec.DefaultReply\"\000B\027Z\025./recommender/pa"
    "r2vecb\006proto3"
};
static ::absl::once_flag descriptor_table_par2vec_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_par2vec_2eproto = {
    false,
    false,
    333,
    descriptor_table_protodef_par2vec_2eproto,
    "par2vec.proto",
    &descriptor_table_par2vec_2eproto_once,
    nullptr,
    0,
    4,
    schemas,
    file_default_instances,
    TableStruct_par2vec_2eproto::offsets,
    file_level_metadata_par2vec_2eproto,
    file_level_enum_descriptors_par2vec_2eproto,
    file_level_service_descriptors_par2vec_2eproto,
};

// This function exists to be marked as weak.
// It can significantly speed up compilation by breaking up LLVM's SCC
// in the .pb.cc translation units. Large translation units see a
// reduction of more than 35% of walltime for optimized builds. Without
// the weak attribute all the messages in the file, including all the
// vtables and everything they use become part of the same SCC through
// a cycle like:
// GetMetadata -> descriptor table -> default instances ->
//   vtables -> GetMetadata
// By adding a weak function here we break the connection from the
// individual vtables back into the descriptor table.
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_par2vec_2eproto_getter() {
  return &descriptor_table_par2vec_2eproto;
}
// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2
static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_par2vec_2eproto(&descriptor_table_par2vec_2eproto);
namespace par2vec {
// ===================================================================

class HelloRequest::_Internal {
 public:
};

HelloRequest::HelloRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:par2vec.HelloRequest)
}
HelloRequest::HelloRequest(const HelloRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  HelloRequest* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.hello_) {}

    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.hello_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.hello_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_hello().empty()) {
    _this->_impl_.hello_.Set(from._internal_hello(), _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:par2vec.HelloRequest)
}

inline void HelloRequest::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_.hello_) {}

    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.hello_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.hello_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

HelloRequest::~HelloRequest() {
  // @@protoc_insertion_point(destructor:par2vec.HelloRequest)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void HelloRequest::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.hello_.Destroy();
}

void HelloRequest::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void HelloRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:par2vec.HelloRequest)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.hello_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* HelloRequest::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string hello = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_hello();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "par2vec.HelloRequest.hello"));
        } else {
          goto handle_unusual;
        }
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::uint8_t* HelloRequest::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:par2vec.HelloRequest)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string hello = 1;
  if (!this->_internal_hello().empty()) {
    const std::string& _s = this->_internal_hello();
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE, "par2vec.HelloRequest.hello");
    target = stream->WriteStringMaybeAliased(1, _s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:par2vec.HelloRequest)
  return target;
}

::size_t HelloRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:par2vec.HelloRequest)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string hello = 1;
  if (!this->_internal_hello().empty()) {
    total_size += 1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
                                    this->_internal_hello());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData HelloRequest::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    HelloRequest::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*HelloRequest::GetClassData() const { return &_class_data_; }


void HelloRequest::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<HelloRequest*>(&to_msg);
  auto& from = static_cast<const HelloRequest&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:par2vec.HelloRequest)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_hello().empty()) {
    _this->_internal_set_hello(from._internal_hello());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void HelloRequest::CopyFrom(const HelloRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:par2vec.HelloRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool HelloRequest::IsInitialized() const {
  return true;
}

void HelloRequest::InternalSwap(HelloRequest* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.hello_, lhs_arena,
                                       &other->_impl_.hello_, rhs_arena);
}

::PROTOBUF_NAMESPACE_ID::Metadata HelloRequest::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_par2vec_2eproto_getter, &descriptor_table_par2vec_2eproto_once,
      file_level_metadata_par2vec_2eproto[0]);
}
// ===================================================================

class HelloReply::_Internal {
 public:
};

HelloReply::HelloReply(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:par2vec.HelloReply)
}
HelloReply::HelloReply(const HelloReply& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  HelloReply* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.reply_) {}

    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.reply_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.reply_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_reply().empty()) {
    _this->_impl_.reply_.Set(from._internal_reply(), _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:par2vec.HelloReply)
}

inline void HelloReply::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_.reply_) {}

    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.reply_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.reply_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

HelloReply::~HelloReply() {
  // @@protoc_insertion_point(destructor:par2vec.HelloReply)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void HelloReply::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.reply_.Destroy();
}

void HelloReply::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void HelloReply::Clear() {
// @@protoc_insertion_point(message_clear_start:par2vec.HelloReply)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.reply_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* HelloReply::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string reply = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_reply();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "par2vec.HelloReply.reply"));
        } else {
          goto handle_unusual;
        }
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::uint8_t* HelloReply::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:par2vec.HelloReply)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string reply = 1;
  if (!this->_internal_reply().empty()) {
    const std::string& _s = this->_internal_reply();
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE, "par2vec.HelloReply.reply");
    target = stream->WriteStringMaybeAliased(1, _s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:par2vec.HelloReply)
  return target;
}

::size_t HelloReply::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:par2vec.HelloReply)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string reply = 1;
  if (!this->_internal_reply().empty()) {
    total_size += 1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
                                    this->_internal_reply());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData HelloReply::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    HelloReply::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*HelloReply::GetClassData() const { return &_class_data_; }


void HelloReply::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<HelloReply*>(&to_msg);
  auto& from = static_cast<const HelloReply&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:par2vec.HelloReply)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_reply().empty()) {
    _this->_internal_set_reply(from._internal_reply());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void HelloReply::CopyFrom(const HelloReply& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:par2vec.HelloReply)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool HelloReply::IsInitialized() const {
  return true;
}

void HelloReply::InternalSwap(HelloReply* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.reply_, lhs_arena,
                                       &other->_impl_.reply_, rhs_arena);
}

::PROTOBUF_NAMESPACE_ID::Metadata HelloReply::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_par2vec_2eproto_getter, &descriptor_table_par2vec_2eproto_once,
      file_level_metadata_par2vec_2eproto[1]);
}
// ===================================================================

class Par2VecRequest::_Internal {
 public:
};

Par2VecRequest::Par2VecRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:par2vec.Par2VecRequest)
}
Par2VecRequest::Par2VecRequest(const Par2VecRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  Par2VecRequest* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.paragraph_) {}

    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.paragraph_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.paragraph_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_paragraph().empty()) {
    _this->_impl_.paragraph_.Set(from._internal_paragraph(), _this->GetArenaForAllocation());
  }
  // @@protoc_insertion_point(copy_constructor:par2vec.Par2VecRequest)
}

inline void Par2VecRequest::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_.paragraph_) {}

    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.paragraph_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        _impl_.paragraph_.Set("", GetArenaForAllocation());
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

Par2VecRequest::~Par2VecRequest() {
  // @@protoc_insertion_point(destructor:par2vec.Par2VecRequest)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Par2VecRequest::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.paragraph_.Destroy();
}

void Par2VecRequest::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void Par2VecRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:par2vec.Par2VecRequest)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.paragraph_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Par2VecRequest::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string paragraph = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_paragraph();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "par2vec.Par2VecRequest.paragraph"));
        } else {
          goto handle_unusual;
        }
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::uint8_t* Par2VecRequest::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:par2vec.Par2VecRequest)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string paragraph = 1;
  if (!this->_internal_paragraph().empty()) {
    const std::string& _s = this->_internal_paragraph();
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
        _s.data(), static_cast<int>(_s.length()), ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE, "par2vec.Par2VecRequest.paragraph");
    target = stream->WriteStringMaybeAliased(1, _s, target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:par2vec.Par2VecRequest)
  return target;
}

::size_t Par2VecRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:par2vec.Par2VecRequest)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string paragraph = 1;
  if (!this->_internal_paragraph().empty()) {
    total_size += 1 + ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
                                    this->_internal_paragraph());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Par2VecRequest::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    Par2VecRequest::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Par2VecRequest::GetClassData() const { return &_class_data_; }


void Par2VecRequest::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<Par2VecRequest*>(&to_msg);
  auto& from = static_cast<const Par2VecRequest&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:par2vec.Par2VecRequest)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_paragraph().empty()) {
    _this->_internal_set_paragraph(from._internal_paragraph());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Par2VecRequest::CopyFrom(const Par2VecRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:par2vec.Par2VecRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Par2VecRequest::IsInitialized() const {
  return true;
}

void Par2VecRequest::InternalSwap(Par2VecRequest* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::_pbi::ArenaStringPtr::InternalSwap(&_impl_.paragraph_, lhs_arena,
                                       &other->_impl_.paragraph_, rhs_arena);
}

::PROTOBUF_NAMESPACE_ID::Metadata Par2VecRequest::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_par2vec_2eproto_getter, &descriptor_table_par2vec_2eproto_once,
      file_level_metadata_par2vec_2eproto[2]);
}
// ===================================================================

class DefaultReply::_Internal {
 public:
};

DefaultReply::DefaultReply(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor(arena);
  // @@protoc_insertion_point(arena_constructor:par2vec.DefaultReply)
}
DefaultReply::DefaultReply(const DefaultReply& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  DefaultReply* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.fvec_) { from._impl_.fvec_ }

    , decltype(_impl_.dim_) {}

    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _this->_impl_.dim_ = from._impl_.dim_;
  // @@protoc_insertion_point(copy_constructor:par2vec.DefaultReply)
}

inline void DefaultReply::SharedCtor(::_pb::Arena* arena) {
  (void)arena;
  new (&_impl_) Impl_{
      decltype(_impl_.fvec_) { arena }

    , decltype(_impl_.dim_) { 0u }

    , /*decltype(_impl_._cached_size_)*/{}
  };
}

DefaultReply::~DefaultReply() {
  // @@protoc_insertion_point(destructor:par2vec.DefaultReply)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void DefaultReply::SharedDtor() {
  ABSL_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.fvec_.~RepeatedField();
}

void DefaultReply::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void DefaultReply::Clear() {
// @@protoc_insertion_point(message_clear_start:par2vec.DefaultReply)
  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _internal_mutable_fvec()->Clear();
  _impl_.dim_ = 0u;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* DefaultReply::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // uint32 dim = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 8)) {
          _impl_.dim_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else {
          goto handle_unusual;
        }
        continue;
      // repeated float fVec = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::uint8_t>(tag) == 18)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedFloatParser(_internal_mutable_fvec(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<::uint8_t>(tag) == 21) {
          _internal_add_fvec(::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr));
          ptr += sizeof(float);
        } else {
          goto handle_unusual;
        }
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

::uint8_t* DefaultReply::_InternalSerialize(
    ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:par2vec.DefaultReply)
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // uint32 dim = 1;
  if (this->_internal_dim() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteUInt32ToArray(
        1, this->_internal_dim(), target);
  }

  // repeated float fVec = 2;
  if (this->_internal_fvec_size() > 0) {
    target = stream->WriteFixedPacked(2, _internal_fvec(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:par2vec.DefaultReply)
  return target;
}

::size_t DefaultReply::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:par2vec.DefaultReply)
  ::size_t total_size = 0;

  ::uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated float fVec = 2;
  {
    std::size_t data_size = std::size_t{4} *
        ::_pbi::FromIntSize(this->_internal_fvec_size())
    ;
    std::size_t tag_size = data_size == 0
        ? 0
        : 1 + ::_pbi::WireFormatLite::Int32Size(
                            static_cast<int32_t>(data_size))
    ;
    total_size += tag_size + data_size;
  }

  // uint32 dim = 1;
  if (this->_internal_dim() != 0) {
    total_size += ::_pbi::WireFormatLite::UInt32SizePlusOne(
        this->_internal_dim());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData DefaultReply::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    DefaultReply::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*DefaultReply::GetClassData() const { return &_class_data_; }


void DefaultReply::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<DefaultReply*>(&to_msg);
  auto& from = static_cast<const DefaultReply&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:par2vec.DefaultReply)
  ABSL_DCHECK_NE(&from, _this);
  ::uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.fvec_.MergeFrom(from._impl_.fvec_);
  if (from._internal_dim() != 0) {
    _this->_internal_set_dim(from._internal_dim());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void DefaultReply::CopyFrom(const DefaultReply& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:par2vec.DefaultReply)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool DefaultReply::IsInitialized() const {
  return true;
}

void DefaultReply::InternalSwap(DefaultReply* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.fvec_.InternalSwap(&other->_impl_.fvec_);

  swap(_impl_.dim_, other->_impl_.dim_);
}

::PROTOBUF_NAMESPACE_ID::Metadata DefaultReply::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_par2vec_2eproto_getter, &descriptor_table_par2vec_2eproto_once,
      file_level_metadata_par2vec_2eproto[3]);
}
// @@protoc_insertion_point(namespace_scope)
}  // namespace par2vec
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::par2vec::HelloRequest*
Arena::CreateMaybeMessage< ::par2vec::HelloRequest >(Arena* arena) {
  return Arena::CreateMessageInternal< ::par2vec::HelloRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::par2vec::HelloReply*
Arena::CreateMaybeMessage< ::par2vec::HelloReply >(Arena* arena) {
  return Arena::CreateMessageInternal< ::par2vec::HelloReply >(arena);
}
template<> PROTOBUF_NOINLINE ::par2vec::Par2VecRequest*
Arena::CreateMaybeMessage< ::par2vec::Par2VecRequest >(Arena* arena) {
  return Arena::CreateMessageInternal< ::par2vec::Par2VecRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::par2vec::DefaultReply*
Arena::CreateMaybeMessage< ::par2vec::DefaultReply >(Arena* arena) {
  return Arena::CreateMessageInternal< ::par2vec::DefaultReply >(arena);
}
PROTOBUF_NAMESPACE_CLOSE
// @@protoc_insertion_point(global_scope)
#include "google/protobuf/port_undef.inc"
