// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: par2vec.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_par2vec_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_par2vec_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION < 4023000
#error "This file was generated by a newer version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please update"
#error "your headers."
#endif  // PROTOBUF_VERSION

#if 4023004 < PROTOBUF_MIN_PROTOC_VERSION
#error "This file was generated by an older version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please"
#error "regenerate this file with a newer version of protoc."
#endif  // PROTOBUF_MIN_PROTOC_VERSION
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_par2vec_2eproto

PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_par2vec_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable
    descriptor_table_par2vec_2eproto;
namespace par2vec {
class DefaultReply;
struct DefaultReplyDefaultTypeInternal;
extern DefaultReplyDefaultTypeInternal _DefaultReply_default_instance_;
class HelloReply;
struct HelloReplyDefaultTypeInternal;
extern HelloReplyDefaultTypeInternal _HelloReply_default_instance_;
class HelloRequest;
struct HelloRequestDefaultTypeInternal;
extern HelloRequestDefaultTypeInternal _HelloRequest_default_instance_;
class Par2VecRequest;
struct Par2VecRequestDefaultTypeInternal;
extern Par2VecRequestDefaultTypeInternal _Par2VecRequest_default_instance_;
}  // namespace par2vec
PROTOBUF_NAMESPACE_OPEN
template <>
::par2vec::DefaultReply* Arena::CreateMaybeMessage<::par2vec::DefaultReply>(Arena*);
template <>
::par2vec::HelloReply* Arena::CreateMaybeMessage<::par2vec::HelloReply>(Arena*);
template <>
::par2vec::HelloRequest* Arena::CreateMaybeMessage<::par2vec::HelloRequest>(Arena*);
template <>
::par2vec::Par2VecRequest* Arena::CreateMaybeMessage<::par2vec::Par2VecRequest>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

namespace par2vec {

// ===================================================================


// -------------------------------------------------------------------

class HelloRequest final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:par2vec.HelloRequest) */ {
 public:
  inline HelloRequest() : HelloRequest(nullptr) {}
  ~HelloRequest() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR HelloRequest(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  HelloRequest(const HelloRequest& from);
  HelloRequest(HelloRequest&& from) noexcept
    : HelloRequest() {
    *this = ::std::move(from);
  }

  inline HelloRequest& operator=(const HelloRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline HelloRequest& operator=(HelloRequest&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const HelloRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const HelloRequest* internal_default_instance() {
    return reinterpret_cast<const HelloRequest*>(
               &_HelloRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(HelloRequest& a, HelloRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(HelloRequest* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(HelloRequest* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  HelloRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<HelloRequest>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const HelloRequest& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const HelloRequest& from) {
    HelloRequest::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(HelloRequest* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "par2vec.HelloRequest";
  }
  protected:
  explicit HelloRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kHelloFieldNumber = 1,
  };
  // string hello = 1;
  void clear_hello() ;
  const std::string& hello() const;




  template <typename Arg_ = const std::string&, typename... Args_>
  void set_hello(Arg_&& arg, Args_... args);
  std::string* mutable_hello();
  PROTOBUF_NODISCARD std::string* release_hello();
  void set_allocated_hello(std::string* ptr);

  private:
  const std::string& _internal_hello() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_hello(
      const std::string& value);
  std::string* _internal_mutable_hello();

  public:
  // @@protoc_insertion_point(class_scope:par2vec.HelloRequest)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr hello_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_par2vec_2eproto;
};// -------------------------------------------------------------------

class HelloReply final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:par2vec.HelloReply) */ {
 public:
  inline HelloReply() : HelloReply(nullptr) {}
  ~HelloReply() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR HelloReply(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  HelloReply(const HelloReply& from);
  HelloReply(HelloReply&& from) noexcept
    : HelloReply() {
    *this = ::std::move(from);
  }

  inline HelloReply& operator=(const HelloReply& from) {
    CopyFrom(from);
    return *this;
  }
  inline HelloReply& operator=(HelloReply&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const HelloReply& default_instance() {
    return *internal_default_instance();
  }
  static inline const HelloReply* internal_default_instance() {
    return reinterpret_cast<const HelloReply*>(
               &_HelloReply_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(HelloReply& a, HelloReply& b) {
    a.Swap(&b);
  }
  inline void Swap(HelloReply* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(HelloReply* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  HelloReply* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<HelloReply>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const HelloReply& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const HelloReply& from) {
    HelloReply::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(HelloReply* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "par2vec.HelloReply";
  }
  protected:
  explicit HelloReply(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kReplyFieldNumber = 1,
  };
  // string reply = 1;
  void clear_reply() ;
  const std::string& reply() const;




  template <typename Arg_ = const std::string&, typename... Args_>
  void set_reply(Arg_&& arg, Args_... args);
  std::string* mutable_reply();
  PROTOBUF_NODISCARD std::string* release_reply();
  void set_allocated_reply(std::string* ptr);

  private:
  const std::string& _internal_reply() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_reply(
      const std::string& value);
  std::string* _internal_mutable_reply();

  public:
  // @@protoc_insertion_point(class_scope:par2vec.HelloReply)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr reply_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_par2vec_2eproto;
};// -------------------------------------------------------------------

class Par2VecRequest final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:par2vec.Par2VecRequest) */ {
 public:
  inline Par2VecRequest() : Par2VecRequest(nullptr) {}
  ~Par2VecRequest() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR Par2VecRequest(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  Par2VecRequest(const Par2VecRequest& from);
  Par2VecRequest(Par2VecRequest&& from) noexcept
    : Par2VecRequest() {
    *this = ::std::move(from);
  }

  inline Par2VecRequest& operator=(const Par2VecRequest& from) {
    CopyFrom(from);
    return *this;
  }
  inline Par2VecRequest& operator=(Par2VecRequest&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Par2VecRequest& default_instance() {
    return *internal_default_instance();
  }
  static inline const Par2VecRequest* internal_default_instance() {
    return reinterpret_cast<const Par2VecRequest*>(
               &_Par2VecRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(Par2VecRequest& a, Par2VecRequest& b) {
    a.Swap(&b);
  }
  inline void Swap(Par2VecRequest* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Par2VecRequest* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Par2VecRequest* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Par2VecRequest>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const Par2VecRequest& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const Par2VecRequest& from) {
    Par2VecRequest::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(Par2VecRequest* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "par2vec.Par2VecRequest";
  }
  protected:
  explicit Par2VecRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kParagraphFieldNumber = 1,
  };
  // string paragraph = 1;
  void clear_paragraph() ;
  const std::string& paragraph() const;




  template <typename Arg_ = const std::string&, typename... Args_>
  void set_paragraph(Arg_&& arg, Args_... args);
  std::string* mutable_paragraph();
  PROTOBUF_NODISCARD std::string* release_paragraph();
  void set_allocated_paragraph(std::string* ptr);

  private:
  const std::string& _internal_paragraph() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_paragraph(
      const std::string& value);
  std::string* _internal_mutable_paragraph();

  public:
  // @@protoc_insertion_point(class_scope:par2vec.Par2VecRequest)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr paragraph_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_par2vec_2eproto;
};// -------------------------------------------------------------------

class DefaultReply final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:par2vec.DefaultReply) */ {
 public:
  inline DefaultReply() : DefaultReply(nullptr) {}
  ~DefaultReply() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR DefaultReply(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  DefaultReply(const DefaultReply& from);
  DefaultReply(DefaultReply&& from) noexcept
    : DefaultReply() {
    *this = ::std::move(from);
  }

  inline DefaultReply& operator=(const DefaultReply& from) {
    CopyFrom(from);
    return *this;
  }
  inline DefaultReply& operator=(DefaultReply&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance);
  }
  inline ::PROTOBUF_NAMESPACE_ID::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const DefaultReply& default_instance() {
    return *internal_default_instance();
  }
  static inline const DefaultReply* internal_default_instance() {
    return reinterpret_cast<const DefaultReply*>(
               &_DefaultReply_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    3;

  friend void swap(DefaultReply& a, DefaultReply& b) {
    a.Swap(&b);
  }
  inline void Swap(DefaultReply* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(DefaultReply* other) {
    if (other == this) return;
    ABSL_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  DefaultReply* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<DefaultReply>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const DefaultReply& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const DefaultReply& from) {
    DefaultReply::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(DefaultReply* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "par2vec.DefaultReply";
  }
  protected:
  explicit DefaultReply(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kFVecFieldNumber = 2,
    kDimFieldNumber = 1,
  };
  // repeated float fVec = 2;
  int fvec_size() const;
  private:
  int _internal_fvec_size() const;

  public:
  void clear_fvec() ;
  float fvec(int index) const;
  void set_fvec(int index, float value);
  void add_fvec(float value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField<float>& fvec() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField<float>* mutable_fvec();

  private:
  float _internal_fvec(int index) const;
  void _internal_add_fvec(float value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField<float>& _internal_fvec() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField<float>* _internal_mutable_fvec();

  public:
  // uint32 dim = 1;
  void clear_dim() ;
  ::uint32_t dim() const;
  void set_dim(::uint32_t value);

  private:
  ::uint32_t _internal_dim() const;
  void _internal_set_dim(::uint32_t value);

  public:
  // @@protoc_insertion_point(class_scope:par2vec.DefaultReply)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    ::PROTOBUF_NAMESPACE_ID::RepeatedField<float> fvec_;
    ::uint32_t dim_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_par2vec_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// HelloRequest

// string hello = 1;
inline void HelloRequest::clear_hello() {
  _impl_.hello_.ClearToEmpty();
}
inline const std::string& HelloRequest::hello() const {
  // @@protoc_insertion_point(field_get:par2vec.HelloRequest.hello)
  return _internal_hello();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void HelloRequest::set_hello(Arg_&& arg,
                                                     Args_... args) {
  ;
  _impl_.hello_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:par2vec.HelloRequest.hello)
}
inline std::string* HelloRequest::mutable_hello() {
  std::string* _s = _internal_mutable_hello();
  // @@protoc_insertion_point(field_mutable:par2vec.HelloRequest.hello)
  return _s;
}
inline const std::string& HelloRequest::_internal_hello() const {
  return _impl_.hello_.Get();
}
inline void HelloRequest::_internal_set_hello(const std::string& value) {
  ;


  _impl_.hello_.Set(value, GetArenaForAllocation());
}
inline std::string* HelloRequest::_internal_mutable_hello() {
  ;
  return _impl_.hello_.Mutable( GetArenaForAllocation());
}
inline std::string* HelloRequest::release_hello() {
  // @@protoc_insertion_point(field_release:par2vec.HelloRequest.hello)
  return _impl_.hello_.Release();
}
inline void HelloRequest::set_allocated_hello(std::string* value) {
  _impl_.hello_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.hello_.IsDefault()) {
          _impl_.hello_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:par2vec.HelloRequest.hello)
}

// -------------------------------------------------------------------

// HelloReply

// string reply = 1;
inline void HelloReply::clear_reply() {
  _impl_.reply_.ClearToEmpty();
}
inline const std::string& HelloReply::reply() const {
  // @@protoc_insertion_point(field_get:par2vec.HelloReply.reply)
  return _internal_reply();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void HelloReply::set_reply(Arg_&& arg,
                                                     Args_... args) {
  ;
  _impl_.reply_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:par2vec.HelloReply.reply)
}
inline std::string* HelloReply::mutable_reply() {
  std::string* _s = _internal_mutable_reply();
  // @@protoc_insertion_point(field_mutable:par2vec.HelloReply.reply)
  return _s;
}
inline const std::string& HelloReply::_internal_reply() const {
  return _impl_.reply_.Get();
}
inline void HelloReply::_internal_set_reply(const std::string& value) {
  ;


  _impl_.reply_.Set(value, GetArenaForAllocation());
}
inline std::string* HelloReply::_internal_mutable_reply() {
  ;
  return _impl_.reply_.Mutable( GetArenaForAllocation());
}
inline std::string* HelloReply::release_reply() {
  // @@protoc_insertion_point(field_release:par2vec.HelloReply.reply)
  return _impl_.reply_.Release();
}
inline void HelloReply::set_allocated_reply(std::string* value) {
  _impl_.reply_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.reply_.IsDefault()) {
          _impl_.reply_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:par2vec.HelloReply.reply)
}

// -------------------------------------------------------------------

// Par2VecRequest

// string paragraph = 1;
inline void Par2VecRequest::clear_paragraph() {
  _impl_.paragraph_.ClearToEmpty();
}
inline const std::string& Par2VecRequest::paragraph() const {
  // @@protoc_insertion_point(field_get:par2vec.Par2VecRequest.paragraph)
  return _internal_paragraph();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void Par2VecRequest::set_paragraph(Arg_&& arg,
                                                     Args_... args) {
  ;
  _impl_.paragraph_.Set(static_cast<Arg_&&>(arg), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:par2vec.Par2VecRequest.paragraph)
}
inline std::string* Par2VecRequest::mutable_paragraph() {
  std::string* _s = _internal_mutable_paragraph();
  // @@protoc_insertion_point(field_mutable:par2vec.Par2VecRequest.paragraph)
  return _s;
}
inline const std::string& Par2VecRequest::_internal_paragraph() const {
  return _impl_.paragraph_.Get();
}
inline void Par2VecRequest::_internal_set_paragraph(const std::string& value) {
  ;


  _impl_.paragraph_.Set(value, GetArenaForAllocation());
}
inline std::string* Par2VecRequest::_internal_mutable_paragraph() {
  ;
  return _impl_.paragraph_.Mutable( GetArenaForAllocation());
}
inline std::string* Par2VecRequest::release_paragraph() {
  // @@protoc_insertion_point(field_release:par2vec.Par2VecRequest.paragraph)
  return _impl_.paragraph_.Release();
}
inline void Par2VecRequest::set_allocated_paragraph(std::string* value) {
  _impl_.paragraph_.SetAllocated(value, GetArenaForAllocation());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.paragraph_.IsDefault()) {
          _impl_.paragraph_.Set("", GetArenaForAllocation());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:par2vec.Par2VecRequest.paragraph)
}

// -------------------------------------------------------------------

// DefaultReply

// uint32 dim = 1;
inline void DefaultReply::clear_dim() {
  _impl_.dim_ = 0u;
}
inline ::uint32_t DefaultReply::dim() const {
  // @@protoc_insertion_point(field_get:par2vec.DefaultReply.dim)
  return _internal_dim();
}
inline void DefaultReply::set_dim(::uint32_t value) {
  _internal_set_dim(value);
  // @@protoc_insertion_point(field_set:par2vec.DefaultReply.dim)
}
inline ::uint32_t DefaultReply::_internal_dim() const {
  return _impl_.dim_;
}
inline void DefaultReply::_internal_set_dim(::uint32_t value) {
  ;
  _impl_.dim_ = value;
}

// repeated float fVec = 2;
inline int DefaultReply::_internal_fvec_size() const {
  return _impl_.fvec_.size();
}
inline int DefaultReply::fvec_size() const {
  return _internal_fvec_size();
}
inline void DefaultReply::clear_fvec() {
  _internal_mutable_fvec()->Clear();
}
inline float DefaultReply::fvec(int index) const {
  // @@protoc_insertion_point(field_get:par2vec.DefaultReply.fVec)
  return _internal_fvec(index);
}
inline void DefaultReply::set_fvec(int index, float value) {
  _internal_mutable_fvec()->Set(index, value);
  // @@protoc_insertion_point(field_set:par2vec.DefaultReply.fVec)
}
inline void DefaultReply::add_fvec(float value) {
  _internal_add_fvec(value);
  // @@protoc_insertion_point(field_add:par2vec.DefaultReply.fVec)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField<float>& DefaultReply::fvec() const {
  // @@protoc_insertion_point(field_list:par2vec.DefaultReply.fVec)
  return _internal_fvec();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField<float>* DefaultReply::mutable_fvec() {
  // @@protoc_insertion_point(field_mutable_list:par2vec.DefaultReply.fVec)
  return _internal_mutable_fvec();
}

inline float DefaultReply::_internal_fvec(int index) const {
  return _internal_fvec().Get(index);
}
inline void DefaultReply::_internal_add_fvec(float value) {
  _internal_mutable_fvec()->Add(value);
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField<float>& DefaultReply::_internal_fvec() const {
  return _impl_.fvec_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField<float>* DefaultReply::_internal_mutable_fvec() {
  return &_impl_.fvec_;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace par2vec


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_par2vec_2eproto_2epb_2eh