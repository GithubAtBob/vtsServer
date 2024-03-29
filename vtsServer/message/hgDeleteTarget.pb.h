// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hgDeleteTarget.proto

#ifndef PROTOBUF_hgDeleteTarget_2eproto__INCLUDED
#define PROTOBUF_hgDeleteTarget_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3001000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3001000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_hgDeleteTarget_2eproto();
void protobuf_InitDefaults_hgDeleteTarget_2eproto();
void protobuf_AssignDesc_hgDeleteTarget_2eproto();
void protobuf_ShutdownFile_hgDeleteTarget_2eproto();

class hgDeleteTarget;

enum DeleteTarget {
  DeleteAll = 0,
  DeleteSim = 1,
  DeleteLost = 2,
  DeleteTarget_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  DeleteTarget_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool DeleteTarget_IsValid(int value);
const DeleteTarget DeleteTarget_MIN = DeleteAll;
const DeleteTarget DeleteTarget_MAX = DeleteLost;
const int DeleteTarget_ARRAYSIZE = DeleteTarget_MAX + 1;

const ::google::protobuf::EnumDescriptor* DeleteTarget_descriptor();
inline const ::std::string& DeleteTarget_Name(DeleteTarget value) {
  return ::google::protobuf::internal::NameOfEnum(
    DeleteTarget_descriptor(), value);
}
inline bool DeleteTarget_Parse(
    const ::std::string& name, DeleteTarget* value) {
  return ::google::protobuf::internal::ParseNamedEnum<DeleteTarget>(
    DeleteTarget_descriptor(), name, value);
}
// ===================================================================

class hgDeleteTarget : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:hgDeleteTarget) */ {
 public:
  hgDeleteTarget();
  virtual ~hgDeleteTarget();

  hgDeleteTarget(const hgDeleteTarget& from);

  inline hgDeleteTarget& operator=(const hgDeleteTarget& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const hgDeleteTarget& default_instance();

  static const hgDeleteTarget* internal_default_instance();

  void Swap(hgDeleteTarget* other);

  // implements Message ----------------------------------------------

  inline hgDeleteTarget* New() const { return New(NULL); }

  hgDeleteTarget* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const hgDeleteTarget& from);
  void MergeFrom(const hgDeleteTarget& from);
  void Clear();
  bool IsInitialized() const;

  size_t ByteSizeLong() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(hgDeleteTarget* other);
  void UnsafeMergeFrom(const hgDeleteTarget& from);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 DeleteType = 1;
  void clear_deletetype();
  static const int kDeleteTypeFieldNumber = 1;
  ::google::protobuf::int32 deletetype() const;
  void set_deletetype(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:hgDeleteTarget)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::int32 deletetype_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_hgDeleteTarget_2eproto_impl();
  friend void  protobuf_AddDesc_hgDeleteTarget_2eproto_impl();
  friend void protobuf_AssignDesc_hgDeleteTarget_2eproto();
  friend void protobuf_ShutdownFile_hgDeleteTarget_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<hgDeleteTarget> hgDeleteTarget_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// hgDeleteTarget

// optional int32 DeleteType = 1;
inline void hgDeleteTarget::clear_deletetype() {
  deletetype_ = 0;
}
inline ::google::protobuf::int32 hgDeleteTarget::deletetype() const {
  // @@protoc_insertion_point(field_get:hgDeleteTarget.DeleteType)
  return deletetype_;
}
inline void hgDeleteTarget::set_deletetype(::google::protobuf::int32 value) {
  
  deletetype_ = value;
  // @@protoc_insertion_point(field_set:hgDeleteTarget.DeleteType)
}

inline const hgDeleteTarget* hgDeleteTarget::internal_default_instance() {
  return &hgDeleteTarget_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::DeleteTarget> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::DeleteTarget>() {
  return ::DeleteTarget_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_hgDeleteTarget_2eproto__INCLUDED
