// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hgPositionPrediction.proto

#ifndef PROTOBUF_hgPositionPrediction_2eproto__INCLUDED
#define PROTOBUF_hgPositionPrediction_2eproto__INCLUDED

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
void protobuf_AddDesc_hgPositionPrediction_2eproto();
void protobuf_InitDefaults_hgPositionPrediction_2eproto();
void protobuf_AssignDesc_hgPositionPrediction_2eproto();
void protobuf_ShutdownFile_hgPositionPrediction_2eproto();

class hgPositionRepsone;
class hgPositionRequest;

// ===================================================================

class hgPositionRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:hgPositionRequest) */ {
 public:
  hgPositionRequest();
  virtual ~hgPositionRequest();

  hgPositionRequest(const hgPositionRequest& from);

  inline hgPositionRequest& operator=(const hgPositionRequest& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const hgPositionRequest& default_instance();

  static const hgPositionRequest* internal_default_instance();

  void Swap(hgPositionRequest* other);

  // implements Message ----------------------------------------------

  inline hgPositionRequest* New() const { return New(NULL); }

  hgPositionRequest* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const hgPositionRequest& from);
  void MergeFrom(const hgPositionRequest& from);
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
  void InternalSwap(hgPositionRequest* other);
  void UnsafeMergeFrom(const hgPositionRequest& from);
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

  // optional double COG = 2;
  void clear_cog();
  static const int kCOGFieldNumber = 2;
  double cog() const;
  void set_cog(double value);

  // optional double SOG = 3;
  void clear_sog();
  static const int kSOGFieldNumber = 3;
  double sog() const;
  void set_sog(double value);

  // optional int32 Time = 4;
  void clear_time();
  static const int kTimeFieldNumber = 4;
  ::google::protobuf::int32 time() const;
  void set_time(::google::protobuf::int32 value);

  // optional double Lat = 5;
  void clear_lat();
  static const int kLatFieldNumber = 5;
  double lat() const;
  void set_lat(double value);

  // optional double Lon = 6;
  void clear_lon();
  static const int kLonFieldNumber = 6;
  double lon() const;
  void set_lon(double value);

  // @@protoc_insertion_point(class_scope:hgPositionRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr mmsi_;
  double cog_;
  double sog_;
  double lat_;
  double lon_;
  ::google::protobuf::int32 time_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_hgPositionPrediction_2eproto_impl();
  friend void  protobuf_AddDesc_hgPositionPrediction_2eproto_impl();
  friend void protobuf_AssignDesc_hgPositionPrediction_2eproto();
  friend void protobuf_ShutdownFile_hgPositionPrediction_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<hgPositionRequest> hgPositionRequest_default_instance_;

// -------------------------------------------------------------------

class hgPositionRepsone : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:hgPositionRepsone) */ {
 public:
  hgPositionRepsone();
  virtual ~hgPositionRepsone();

  hgPositionRepsone(const hgPositionRepsone& from);

  inline hgPositionRepsone& operator=(const hgPositionRepsone& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const hgPositionRepsone& default_instance();

  static const hgPositionRepsone* internal_default_instance();

  void Swap(hgPositionRepsone* other);

  // implements Message ----------------------------------------------

  inline hgPositionRepsone* New() const { return New(NULL); }

  hgPositionRepsone* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const hgPositionRepsone& from);
  void MergeFrom(const hgPositionRepsone& from);
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
  void InternalSwap(hgPositionRepsone* other);
  void UnsafeMergeFrom(const hgPositionRepsone& from);
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

  // optional double Lat = 2;
  void clear_lat();
  static const int kLatFieldNumber = 2;
  double lat() const;
  void set_lat(double value);

  // optional double Lon = 3;
  void clear_lon();
  static const int kLonFieldNumber = 3;
  double lon() const;
  void set_lon(double value);

  // @@protoc_insertion_point(class_scope:hgPositionRepsone)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr mmsi_;
  double lat_;
  double lon_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_hgPositionPrediction_2eproto_impl();
  friend void  protobuf_AddDesc_hgPositionPrediction_2eproto_impl();
  friend void protobuf_AssignDesc_hgPositionPrediction_2eproto();
  friend void protobuf_ShutdownFile_hgPositionPrediction_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<hgPositionRepsone> hgPositionRepsone_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// hgPositionRequest

// optional string MMSI = 1;
inline void hgPositionRequest::clear_mmsi() {
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgPositionRequest::mmsi() const {
  // @@protoc_insertion_point(field_get:hgPositionRequest.MMSI)
  return mmsi_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgPositionRequest::set_mmsi(const ::std::string& value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgPositionRequest.MMSI)
}
inline void hgPositionRequest::set_mmsi(const char* value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgPositionRequest.MMSI)
}
inline void hgPositionRequest::set_mmsi(const char* value, size_t size) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgPositionRequest.MMSI)
}
inline ::std::string* hgPositionRequest::mutable_mmsi() {
  
  // @@protoc_insertion_point(field_mutable:hgPositionRequest.MMSI)
  return mmsi_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgPositionRequest::release_mmsi() {
  // @@protoc_insertion_point(field_release:hgPositionRequest.MMSI)
  
  return mmsi_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgPositionRequest::set_allocated_mmsi(::std::string* mmsi) {
  if (mmsi != NULL) {
    
  } else {
    
  }
  mmsi_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), mmsi);
  // @@protoc_insertion_point(field_set_allocated:hgPositionRequest.MMSI)
}

// optional double COG = 2;
inline void hgPositionRequest::clear_cog() {
  cog_ = 0;
}
inline double hgPositionRequest::cog() const {
  // @@protoc_insertion_point(field_get:hgPositionRequest.COG)
  return cog_;
}
inline void hgPositionRequest::set_cog(double value) {
  
  cog_ = value;
  // @@protoc_insertion_point(field_set:hgPositionRequest.COG)
}

// optional double SOG = 3;
inline void hgPositionRequest::clear_sog() {
  sog_ = 0;
}
inline double hgPositionRequest::sog() const {
  // @@protoc_insertion_point(field_get:hgPositionRequest.SOG)
  return sog_;
}
inline void hgPositionRequest::set_sog(double value) {
  
  sog_ = value;
  // @@protoc_insertion_point(field_set:hgPositionRequest.SOG)
}

// optional int32 Time = 4;
inline void hgPositionRequest::clear_time() {
  time_ = 0;
}
inline ::google::protobuf::int32 hgPositionRequest::time() const {
  // @@protoc_insertion_point(field_get:hgPositionRequest.Time)
  return time_;
}
inline void hgPositionRequest::set_time(::google::protobuf::int32 value) {
  
  time_ = value;
  // @@protoc_insertion_point(field_set:hgPositionRequest.Time)
}

// optional double Lat = 5;
inline void hgPositionRequest::clear_lat() {
  lat_ = 0;
}
inline double hgPositionRequest::lat() const {
  // @@protoc_insertion_point(field_get:hgPositionRequest.Lat)
  return lat_;
}
inline void hgPositionRequest::set_lat(double value) {
  
  lat_ = value;
  // @@protoc_insertion_point(field_set:hgPositionRequest.Lat)
}

// optional double Lon = 6;
inline void hgPositionRequest::clear_lon() {
  lon_ = 0;
}
inline double hgPositionRequest::lon() const {
  // @@protoc_insertion_point(field_get:hgPositionRequest.Lon)
  return lon_;
}
inline void hgPositionRequest::set_lon(double value) {
  
  lon_ = value;
  // @@protoc_insertion_point(field_set:hgPositionRequest.Lon)
}

inline const hgPositionRequest* hgPositionRequest::internal_default_instance() {
  return &hgPositionRequest_default_instance_.get();
}
// -------------------------------------------------------------------

// hgPositionRepsone

// optional string MMSI = 1;
inline void hgPositionRepsone::clear_mmsi() {
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgPositionRepsone::mmsi() const {
  // @@protoc_insertion_point(field_get:hgPositionRepsone.MMSI)
  return mmsi_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgPositionRepsone::set_mmsi(const ::std::string& value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgPositionRepsone.MMSI)
}
inline void hgPositionRepsone::set_mmsi(const char* value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgPositionRepsone.MMSI)
}
inline void hgPositionRepsone::set_mmsi(const char* value, size_t size) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgPositionRepsone.MMSI)
}
inline ::std::string* hgPositionRepsone::mutable_mmsi() {
  
  // @@protoc_insertion_point(field_mutable:hgPositionRepsone.MMSI)
  return mmsi_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgPositionRepsone::release_mmsi() {
  // @@protoc_insertion_point(field_release:hgPositionRepsone.MMSI)
  
  return mmsi_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgPositionRepsone::set_allocated_mmsi(::std::string* mmsi) {
  if (mmsi != NULL) {
    
  } else {
    
  }
  mmsi_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), mmsi);
  // @@protoc_insertion_point(field_set_allocated:hgPositionRepsone.MMSI)
}

// optional double Lat = 2;
inline void hgPositionRepsone::clear_lat() {
  lat_ = 0;
}
inline double hgPositionRepsone::lat() const {
  // @@protoc_insertion_point(field_get:hgPositionRepsone.Lat)
  return lat_;
}
inline void hgPositionRepsone::set_lat(double value) {
  
  lat_ = value;
  // @@protoc_insertion_point(field_set:hgPositionRepsone.Lat)
}

// optional double Lon = 3;
inline void hgPositionRepsone::clear_lon() {
  lon_ = 0;
}
inline double hgPositionRepsone::lon() const {
  // @@protoc_insertion_point(field_get:hgPositionRepsone.Lon)
  return lon_;
}
inline void hgPositionRepsone::set_lon(double value) {
  
  lon_ = value;
  // @@protoc_insertion_point(field_set:hgPositionRepsone.Lon)
}

inline const hgPositionRepsone* hgPositionRepsone::internal_default_instance() {
  return &hgPositionRepsone_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_hgPositionPrediction_2eproto__INCLUDED
