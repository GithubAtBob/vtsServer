// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hgGPSCom.proto

#ifndef PROTOBUF_hgGPSCom_2eproto__INCLUDED
#define PROTOBUF_hgGPSCom_2eproto__INCLUDED

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
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_hgGPSCom_2eproto();
void protobuf_InitDefaults_hgGPSCom_2eproto();
void protobuf_AssignDesc_hgGPSCom_2eproto();
void protobuf_ShutdownFile_hgGPSCom_2eproto();

class hgGPSCom;

// ===================================================================

class hgGPSCom : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:hgGPSCom) */ {
 public:
  hgGPSCom();
  virtual ~hgGPSCom();

  hgGPSCom(const hgGPSCom& from);

  inline hgGPSCom& operator=(const hgGPSCom& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const hgGPSCom& default_instance();

  static const hgGPSCom* internal_default_instance();

  void Swap(hgGPSCom* other);

  // implements Message ----------------------------------------------

  inline hgGPSCom* New() const { return New(NULL); }

  hgGPSCom* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const hgGPSCom& from);
  void MergeFrom(const hgGPSCom& from);
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
  void InternalSwap(hgGPSCom* other);
  void UnsafeMergeFrom(const hgGPSCom& from);
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

  // optional string gps = 1;
  void clear_gps();
  static const int kGpsFieldNumber = 1;
  const ::std::string& gps() const;
  void set_gps(const ::std::string& value);
  void set_gps(const char* value);
  void set_gps(const char* value, size_t size);
  ::std::string* mutable_gps();
  ::std::string* release_gps();
  void set_allocated_gps(::std::string* gps);

  // @@protoc_insertion_point(class_scope:hgGPSCom)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr gps_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_hgGPSCom_2eproto_impl();
  friend void  protobuf_AddDesc_hgGPSCom_2eproto_impl();
  friend void protobuf_AssignDesc_hgGPSCom_2eproto();
  friend void protobuf_ShutdownFile_hgGPSCom_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<hgGPSCom> hgGPSCom_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// hgGPSCom

// optional string gps = 1;
inline void hgGPSCom::clear_gps() {
  gps_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgGPSCom::gps() const {
  // @@protoc_insertion_point(field_get:hgGPSCom.gps)
  return gps_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgGPSCom::set_gps(const ::std::string& value) {
  
  gps_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgGPSCom.gps)
}
inline void hgGPSCom::set_gps(const char* value) {
  
  gps_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgGPSCom.gps)
}
inline void hgGPSCom::set_gps(const char* value, size_t size) {
  
  gps_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgGPSCom.gps)
}
inline ::std::string* hgGPSCom::mutable_gps() {
  
  // @@protoc_insertion_point(field_mutable:hgGPSCom.gps)
  return gps_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgGPSCom::release_gps() {
  // @@protoc_insertion_point(field_release:hgGPSCom.gps)
  
  return gps_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgGPSCom::set_allocated_gps(::std::string* gps) {
  if (gps != NULL) {
    
  } else {
    
  }
  gps_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), gps);
  // @@protoc_insertion_point(field_set_allocated:hgGPSCom.gps)
}

inline const hgGPSCom* hgGPSCom::internal_default_instance() {
  return &hgGPSCom_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_hgGPSCom_2eproto__INCLUDED
