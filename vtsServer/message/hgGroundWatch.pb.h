// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hgGroundWatch.proto

#ifndef PROTOBUF_hgGroundWatch_2eproto__INCLUDED
#define PROTOBUF_hgGroundWatch_2eproto__INCLUDED

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
void protobuf_AddDesc_hgGroundWatch_2eproto();
void protobuf_InitDefaults_hgGroundWatch_2eproto();
void protobuf_AssignDesc_hgGroundWatch_2eproto();
void protobuf_ShutdownFile_hgGroundWatch_2eproto();

class hgGroundWatch;
class hgGroundWatchRepsone;

// ===================================================================

class hgGroundWatch : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:hgGroundWatch) */ {
 public:
  hgGroundWatch();
  virtual ~hgGroundWatch();

  hgGroundWatch(const hgGroundWatch& from);

  inline hgGroundWatch& operator=(const hgGroundWatch& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const hgGroundWatch& default_instance();

  static const hgGroundWatch* internal_default_instance();

  void Swap(hgGroundWatch* other);

  // implements Message ----------------------------------------------

  inline hgGroundWatch* New() const { return New(NULL); }

  hgGroundWatch* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const hgGroundWatch& from);
  void MergeFrom(const hgGroundWatch& from);
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
  void InternalSwap(hgGroundWatch* other);
  void UnsafeMergeFrom(const hgGroundWatch& from);
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

  // optional string MMSI = 1;
  void clear_mmsi();
  static const int kMMSIFieldNumber = 1;
  const ::std::string& mmsi() const;
  void set_mmsi(const ::std::string& value);
  void set_mmsi(const char* value);
  void set_mmsi(const char* value, size_t size);
  ::std::string* mutable_mmsi();
  ::std::string* release_mmsi();
  void set_allocated_mmsi(::std::string* mmsi);

  // optional bool GroundWatch = 2;
  void clear_groundwatch();
  static const int kGroundWatchFieldNumber = 2;
  bool groundwatch() const;
  void set_groundwatch(bool value);

  // optional double GroundDraught = 3;
  void clear_grounddraught();
  static const int kGroundDraughtFieldNumber = 3;
  double grounddraught() const;
  void set_grounddraught(double value);

  // optional double KeelClearance = 4;
  void clear_keelclearance();
  static const int kKeelClearanceFieldNumber = 4;
  double keelclearance() const;
  void set_keelclearance(double value);

  // @@protoc_insertion_point(class_scope:hgGroundWatch)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr mmsi_;
  double grounddraught_;
  double keelclearance_;
  bool groundwatch_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_hgGroundWatch_2eproto_impl();
  friend void  protobuf_AddDesc_hgGroundWatch_2eproto_impl();
  friend void protobuf_AssignDesc_hgGroundWatch_2eproto();
  friend void protobuf_ShutdownFile_hgGroundWatch_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<hgGroundWatch> hgGroundWatch_default_instance_;

// -------------------------------------------------------------------

class hgGroundWatchRepsone : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:hgGroundWatchRepsone) */ {
 public:
  hgGroundWatchRepsone();
  virtual ~hgGroundWatchRepsone();

  hgGroundWatchRepsone(const hgGroundWatchRepsone& from);

  inline hgGroundWatchRepsone& operator=(const hgGroundWatchRepsone& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const hgGroundWatchRepsone& default_instance();

  static const hgGroundWatchRepsone* internal_default_instance();

  void Swap(hgGroundWatchRepsone* other);

  // implements Message ----------------------------------------------

  inline hgGroundWatchRepsone* New() const { return New(NULL); }

  hgGroundWatchRepsone* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const hgGroundWatchRepsone& from);
  void MergeFrom(const hgGroundWatchRepsone& from);
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
  void InternalSwap(hgGroundWatchRepsone* other);
  void UnsafeMergeFrom(const hgGroundWatchRepsone& from);
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

  // @@protoc_insertion_point(class_scope:hgGroundWatchRepsone)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_hgGroundWatch_2eproto_impl();
  friend void  protobuf_AddDesc_hgGroundWatch_2eproto_impl();
  friend void protobuf_AssignDesc_hgGroundWatch_2eproto();
  friend void protobuf_ShutdownFile_hgGroundWatch_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<hgGroundWatchRepsone> hgGroundWatchRepsone_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// hgGroundWatch

// optional string MMSI = 1;
inline void hgGroundWatch::clear_mmsi() {
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgGroundWatch::mmsi() const {
  // @@protoc_insertion_point(field_get:hgGroundWatch.MMSI)
  return mmsi_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgGroundWatch::set_mmsi(const ::std::string& value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgGroundWatch.MMSI)
}
inline void hgGroundWatch::set_mmsi(const char* value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgGroundWatch.MMSI)
}
inline void hgGroundWatch::set_mmsi(const char* value, size_t size) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgGroundWatch.MMSI)
}
inline ::std::string* hgGroundWatch::mutable_mmsi() {
  
  // @@protoc_insertion_point(field_mutable:hgGroundWatch.MMSI)
  return mmsi_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgGroundWatch::release_mmsi() {
  // @@protoc_insertion_point(field_release:hgGroundWatch.MMSI)
  
  return mmsi_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgGroundWatch::set_allocated_mmsi(::std::string* mmsi) {
  if (mmsi != NULL) {
    
  } else {
    
  }
  mmsi_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), mmsi);
  // @@protoc_insertion_point(field_set_allocated:hgGroundWatch.MMSI)
}

// optional bool GroundWatch = 2;
inline void hgGroundWatch::clear_groundwatch() {
  groundwatch_ = false;
}
inline bool hgGroundWatch::groundwatch() const {
  // @@protoc_insertion_point(field_get:hgGroundWatch.GroundWatch)
  return groundwatch_;
}
inline void hgGroundWatch::set_groundwatch(bool value) {
  
  groundwatch_ = value;
  // @@protoc_insertion_point(field_set:hgGroundWatch.GroundWatch)
}

// optional double GroundDraught = 3;
inline void hgGroundWatch::clear_grounddraught() {
  grounddraught_ = 0;
}
inline double hgGroundWatch::grounddraught() const {
  // @@protoc_insertion_point(field_get:hgGroundWatch.GroundDraught)
  return grounddraught_;
}
inline void hgGroundWatch::set_grounddraught(double value) {
  
  grounddraught_ = value;
  // @@protoc_insertion_point(field_set:hgGroundWatch.GroundDraught)
}

// optional double KeelClearance = 4;
inline void hgGroundWatch::clear_keelclearance() {
  keelclearance_ = 0;
}
inline double hgGroundWatch::keelclearance() const {
  // @@protoc_insertion_point(field_get:hgGroundWatch.KeelClearance)
  return keelclearance_;
}
inline void hgGroundWatch::set_keelclearance(double value) {
  
  keelclearance_ = value;
  // @@protoc_insertion_point(field_set:hgGroundWatch.KeelClearance)
}

inline const hgGroundWatch* hgGroundWatch::internal_default_instance() {
  return &hgGroundWatch_default_instance_.get();
}
// -------------------------------------------------------------------

// hgGroundWatchRepsone

inline const hgGroundWatchRepsone* hgGroundWatchRepsone::internal_default_instance() {
  return &hgGroundWatchRepsone_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_hgGroundWatch_2eproto__INCLUDED
