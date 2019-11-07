// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hgBerthWatch.proto

#ifndef PROTOBUF_hgBerthWatch_2eproto__INCLUDED
#define PROTOBUF_hgBerthWatch_2eproto__INCLUDED

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
void protobuf_AddDesc_hgBerthWatch_2eproto();
void protobuf_InitDefaults_hgBerthWatch_2eproto();
void protobuf_AssignDesc_hgBerthWatch_2eproto();
void protobuf_ShutdownFile_hgBerthWatch_2eproto();

class hgBerthWatch;
class hgBerthWatchRepsone;

// ===================================================================

class hgBerthWatch : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:hgBerthWatch) */ {
 public:
  hgBerthWatch();
  virtual ~hgBerthWatch();

  hgBerthWatch(const hgBerthWatch& from);

  inline hgBerthWatch& operator=(const hgBerthWatch& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const hgBerthWatch& default_instance();

  static const hgBerthWatch* internal_default_instance();

  void Swap(hgBerthWatch* other);

  // implements Message ----------------------------------------------

  inline hgBerthWatch* New() const { return New(NULL); }

  hgBerthWatch* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const hgBerthWatch& from);
  void MergeFrom(const hgBerthWatch& from);
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
  void InternalSwap(hgBerthWatch* other);
  void UnsafeMergeFrom(const hgBerthWatch& from);
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

  // optional bool BerthWatch = 2;
  void clear_berthwatch();
  static const int kBerthWatchFieldNumber = 2;
  bool berthwatch() const;
  void set_berthwatch(bool value);

  // optional double Distance = 3;
  void clear_distance();
  static const int kDistanceFieldNumber = 3;
  double distance() const;
  void set_distance(double value);

  // optional double Lat = 4;
  void clear_lat();
  static const int kLatFieldNumber = 4;
  double lat() const;
  void set_lat(double value);

  // optional double Lon = 5;
  void clear_lon();
  static const int kLonFieldNumber = 5;
  double lon() const;
  void set_lon(double value);

  // @@protoc_insertion_point(class_scope:hgBerthWatch)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr mmsi_;
  double distance_;
  double lat_;
  double lon_;
  bool berthwatch_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_hgBerthWatch_2eproto_impl();
  friend void  protobuf_AddDesc_hgBerthWatch_2eproto_impl();
  friend void protobuf_AssignDesc_hgBerthWatch_2eproto();
  friend void protobuf_ShutdownFile_hgBerthWatch_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<hgBerthWatch> hgBerthWatch_default_instance_;

// -------------------------------------------------------------------

class hgBerthWatchRepsone : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:hgBerthWatchRepsone) */ {
 public:
  hgBerthWatchRepsone();
  virtual ~hgBerthWatchRepsone();

  hgBerthWatchRepsone(const hgBerthWatchRepsone& from);

  inline hgBerthWatchRepsone& operator=(const hgBerthWatchRepsone& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const hgBerthWatchRepsone& default_instance();

  static const hgBerthWatchRepsone* internal_default_instance();

  void Swap(hgBerthWatchRepsone* other);

  // implements Message ----------------------------------------------

  inline hgBerthWatchRepsone* New() const { return New(NULL); }

  hgBerthWatchRepsone* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const hgBerthWatchRepsone& from);
  void MergeFrom(const hgBerthWatchRepsone& from);
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
  void InternalSwap(hgBerthWatchRepsone* other);
  void UnsafeMergeFrom(const hgBerthWatchRepsone& from);
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

  // @@protoc_insertion_point(class_scope:hgBerthWatchRepsone)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_hgBerthWatch_2eproto_impl();
  friend void  protobuf_AddDesc_hgBerthWatch_2eproto_impl();
  friend void protobuf_AssignDesc_hgBerthWatch_2eproto();
  friend void protobuf_ShutdownFile_hgBerthWatch_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<hgBerthWatchRepsone> hgBerthWatchRepsone_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// hgBerthWatch

// optional string MMSI = 1;
inline void hgBerthWatch::clear_mmsi() {
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgBerthWatch::mmsi() const {
  // @@protoc_insertion_point(field_get:hgBerthWatch.MMSI)
  return mmsi_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgBerthWatch::set_mmsi(const ::std::string& value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgBerthWatch.MMSI)
}
inline void hgBerthWatch::set_mmsi(const char* value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgBerthWatch.MMSI)
}
inline void hgBerthWatch::set_mmsi(const char* value, size_t size) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgBerthWatch.MMSI)
}
inline ::std::string* hgBerthWatch::mutable_mmsi() {
  
  // @@protoc_insertion_point(field_mutable:hgBerthWatch.MMSI)
  return mmsi_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgBerthWatch::release_mmsi() {
  // @@protoc_insertion_point(field_release:hgBerthWatch.MMSI)
  
  return mmsi_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgBerthWatch::set_allocated_mmsi(::std::string* mmsi) {
  if (mmsi != NULL) {
    
  } else {
    
  }
  mmsi_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), mmsi);
  // @@protoc_insertion_point(field_set_allocated:hgBerthWatch.MMSI)
}

// optional bool BerthWatch = 2;
inline void hgBerthWatch::clear_berthwatch() {
  berthwatch_ = false;
}
inline bool hgBerthWatch::berthwatch() const {
  // @@protoc_insertion_point(field_get:hgBerthWatch.BerthWatch)
  return berthwatch_;
}
inline void hgBerthWatch::set_berthwatch(bool value) {
  
  berthwatch_ = value;
  // @@protoc_insertion_point(field_set:hgBerthWatch.BerthWatch)
}

// optional double Distance = 3;
inline void hgBerthWatch::clear_distance() {
  distance_ = 0;
}
inline double hgBerthWatch::distance() const {
  // @@protoc_insertion_point(field_get:hgBerthWatch.Distance)
  return distance_;
}
inline void hgBerthWatch::set_distance(double value) {
  
  distance_ = value;
  // @@protoc_insertion_point(field_set:hgBerthWatch.Distance)
}

// optional double Lat = 4;
inline void hgBerthWatch::clear_lat() {
  lat_ = 0;
}
inline double hgBerthWatch::lat() const {
  // @@protoc_insertion_point(field_get:hgBerthWatch.Lat)
  return lat_;
}
inline void hgBerthWatch::set_lat(double value) {
  
  lat_ = value;
  // @@protoc_insertion_point(field_set:hgBerthWatch.Lat)
}

// optional double Lon = 5;
inline void hgBerthWatch::clear_lon() {
  lon_ = 0;
}
inline double hgBerthWatch::lon() const {
  // @@protoc_insertion_point(field_get:hgBerthWatch.Lon)
  return lon_;
}
inline void hgBerthWatch::set_lon(double value) {
  
  lon_ = value;
  // @@protoc_insertion_point(field_set:hgBerthWatch.Lon)
}

inline const hgBerthWatch* hgBerthWatch::internal_default_instance() {
  return &hgBerthWatch_default_instance_.get();
}
// -------------------------------------------------------------------

// hgBerthWatchRepsone

inline const hgBerthWatchRepsone* hgBerthWatchRepsone::internal_default_instance() {
  return &hgBerthWatchRepsone_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_hgBerthWatch_2eproto__INCLUDED