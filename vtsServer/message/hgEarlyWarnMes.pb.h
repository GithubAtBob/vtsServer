// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hgEarlyWarnMes.proto

#ifndef PROTOBUF_hgEarlyWarnMes_2eproto__INCLUDED
#define PROTOBUF_hgEarlyWarnMes_2eproto__INCLUDED

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
#include "hgWarningType.pb.h"
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_hgEarlyWarnMes_2eproto();
void protobuf_InitDefaults_hgEarlyWarnMes_2eproto();
void protobuf_AssignDesc_hgEarlyWarnMes_2eproto();
void protobuf_ShutdownFile_hgEarlyWarnMes_2eproto();

class hgEarlyWarnMes;
class hgWarnPoint;

enum hgWarningLevel {
  NoWarn = 0,
  FirstWarn = 1,
  SecondWarn = 2,
  ThirdWarn = 3,
  FourthWarn = 4,
  hgWarningLevel_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  hgWarningLevel_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool hgWarningLevel_IsValid(int value);
const hgWarningLevel hgWarningLevel_MIN = NoWarn;
const hgWarningLevel hgWarningLevel_MAX = FourthWarn;
const int hgWarningLevel_ARRAYSIZE = hgWarningLevel_MAX + 1;

const ::google::protobuf::EnumDescriptor* hgWarningLevel_descriptor();
inline const ::std::string& hgWarningLevel_Name(hgWarningLevel value) {
  return ::google::protobuf::internal::NameOfEnum(
    hgWarningLevel_descriptor(), value);
}
inline bool hgWarningLevel_Parse(
    const ::std::string& name, hgWarningLevel* value) {
  return ::google::protobuf::internal::ParseNamedEnum<hgWarningLevel>(
    hgWarningLevel_descriptor(), name, value);
}
// ===================================================================

class hgWarnPoint : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:hgWarnPoint) */ {
 public:
  hgWarnPoint();
  virtual ~hgWarnPoint();

  hgWarnPoint(const hgWarnPoint& from);

  inline hgWarnPoint& operator=(const hgWarnPoint& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const hgWarnPoint& default_instance();

  static const hgWarnPoint* internal_default_instance();

  void Swap(hgWarnPoint* other);

  // implements Message ----------------------------------------------

  inline hgWarnPoint* New() const { return New(NULL); }

  hgWarnPoint* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const hgWarnPoint& from);
  void MergeFrom(const hgWarnPoint& from);
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
  void InternalSwap(hgWarnPoint* other);
  void UnsafeMergeFrom(const hgWarnPoint& from);
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

  // optional int64 time = 1;
  void clear_time();
  static const int kTimeFieldNumber = 1;
  ::google::protobuf::int64 time() const;
  void set_time(::google::protobuf::int64 value);

  // optional double distance = 2;
  void clear_distance();
  static const int kDistanceFieldNumber = 2;
  double distance() const;
  void set_distance(double value);

  // @@protoc_insertion_point(class_scope:hgWarnPoint)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::int64 time_;
  double distance_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_hgEarlyWarnMes_2eproto_impl();
  friend void  protobuf_AddDesc_hgEarlyWarnMes_2eproto_impl();
  friend void protobuf_AssignDesc_hgEarlyWarnMes_2eproto();
  friend void protobuf_ShutdownFile_hgEarlyWarnMes_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<hgWarnPoint> hgWarnPoint_default_instance_;

// -------------------------------------------------------------------

class hgEarlyWarnMes : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:hgEarlyWarnMes) */ {
 public:
  hgEarlyWarnMes();
  virtual ~hgEarlyWarnMes();

  hgEarlyWarnMes(const hgEarlyWarnMes& from);

  inline hgEarlyWarnMes& operator=(const hgEarlyWarnMes& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const hgEarlyWarnMes& default_instance();

  static const hgEarlyWarnMes* internal_default_instance();

  void Swap(hgEarlyWarnMes* other);

  // implements Message ----------------------------------------------

  inline hgEarlyWarnMes* New() const { return New(NULL); }

  hgEarlyWarnMes* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const hgEarlyWarnMes& from);
  void MergeFrom(const hgEarlyWarnMes& from);
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
  void InternalSwap(hgEarlyWarnMes* other);
  void UnsafeMergeFrom(const hgEarlyWarnMes& from);
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

  // optional string WarningID = 1;
  void clear_warningid();
  static const int kWarningIDFieldNumber = 1;
  const ::std::string& warningid() const;
  void set_warningid(const ::std::string& value);
  void set_warningid(const char* value);
  void set_warningid(const char* value, size_t size);
  ::std::string* mutable_warningid();
  ::std::string* release_warningid();
  void set_allocated_warningid(::std::string* warningid);

  // optional string WarningGUID = 2;
  void clear_warningguid();
  static const int kWarningGUIDFieldNumber = 2;
  const ::std::string& warningguid() const;
  void set_warningguid(const ::std::string& value);
  void set_warningguid(const char* value);
  void set_warningguid(const char* value, size_t size);
  ::std::string* mutable_warningguid();
  ::std::string* release_warningguid();
  void set_allocated_warningguid(::std::string* warningguid);

  // optional int32 WarningPriority = 3;
  void clear_warningpriority();
  static const int kWarningPriorityFieldNumber = 3;
  ::google::protobuf::int32 warningpriority() const;
  void set_warningpriority(::google::protobuf::int32 value);

  // optional string WarningName = 4;
  void clear_warningname();
  static const int kWarningNameFieldNumber = 4;
  const ::std::string& warningname() const;
  void set_warningname(const ::std::string& value);
  void set_warningname(const char* value);
  void set_warningname(const char* value, size_t size);
  ::std::string* mutable_warningname();
  ::std::string* release_warningname();
  void set_allocated_warningname(::std::string* warningname);

  // optional string MMSI = 5;
  void clear_mmsi();
  static const int kMMSIFieldNumber = 5;
  const ::std::string& mmsi() const;
  void set_mmsi(const ::std::string& value);
  void set_mmsi(const char* value);
  void set_mmsi(const char* value, size_t size);
  ::std::string* mutable_mmsi();
  ::std::string* release_mmsi();
  void set_allocated_mmsi(::std::string* mmsi);

  // optional string TargetMMSI = 6;
  void clear_targetmmsi();
  static const int kTargetMMSIFieldNumber = 6;
  const ::std::string& targetmmsi() const;
  void set_targetmmsi(const ::std::string& value);
  void set_targetmmsi(const char* value);
  void set_targetmmsi(const char* value, size_t size);
  ::std::string* mutable_targetmmsi();
  ::std::string* release_targetmmsi();
  void set_allocated_targetmmsi(::std::string* targetmmsi);

  // optional int64 WarningTime = 7;
  void clear_warningtime();
  static const int kWarningTimeFieldNumber = 7;
  ::google::protobuf::int64 warningtime() const;
  void set_warningtime(::google::protobuf::int64 value);

  // optional .hgWarningLevel Level = 8;
  void clear_level();
  static const int kLevelFieldNumber = 8;
  ::hgWarningLevel level() const;
  void set_level(::hgWarningLevel value);

  // repeated .hgWarnPoint Point = 9;
  int point_size() const;
  void clear_point();
  static const int kPointFieldNumber = 9;
  const ::hgWarnPoint& point(int index) const;
  ::hgWarnPoint* mutable_point(int index);
  ::hgWarnPoint* add_point();
  ::google::protobuf::RepeatedPtrField< ::hgWarnPoint >*
      mutable_point();
  const ::google::protobuf::RepeatedPtrField< ::hgWarnPoint >&
      point() const;

  // optional bool StartPaint = 10;
  void clear_startpaint();
  static const int kStartPaintFieldNumber = 10;
  bool startpaint() const;
  void set_startpaint(bool value);

  // optional .hgWarningType WarningType = 11;
  void clear_warningtype();
  static const int kWarningTypeFieldNumber = 11;
  ::hgWarningType warningtype() const;
  void set_warningtype(::hgWarningType value);

  // @@protoc_insertion_point(class_scope:hgEarlyWarnMes)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::hgWarnPoint > point_;
  ::google::protobuf::internal::ArenaStringPtr warningid_;
  ::google::protobuf::internal::ArenaStringPtr warningguid_;
  ::google::protobuf::internal::ArenaStringPtr warningname_;
  ::google::protobuf::internal::ArenaStringPtr mmsi_;
  ::google::protobuf::internal::ArenaStringPtr targetmmsi_;
  ::google::protobuf::int32 warningpriority_;
  int level_;
  ::google::protobuf::int64 warningtime_;
  bool startpaint_;
  int warningtype_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_hgEarlyWarnMes_2eproto_impl();
  friend void  protobuf_AddDesc_hgEarlyWarnMes_2eproto_impl();
  friend void protobuf_AssignDesc_hgEarlyWarnMes_2eproto();
  friend void protobuf_ShutdownFile_hgEarlyWarnMes_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<hgEarlyWarnMes> hgEarlyWarnMes_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// hgWarnPoint

// optional int64 time = 1;
inline void hgWarnPoint::clear_time() {
  time_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 hgWarnPoint::time() const {
  // @@protoc_insertion_point(field_get:hgWarnPoint.time)
  return time_;
}
inline void hgWarnPoint::set_time(::google::protobuf::int64 value) {
  
  time_ = value;
  // @@protoc_insertion_point(field_set:hgWarnPoint.time)
}

// optional double distance = 2;
inline void hgWarnPoint::clear_distance() {
  distance_ = 0;
}
inline double hgWarnPoint::distance() const {
  // @@protoc_insertion_point(field_get:hgWarnPoint.distance)
  return distance_;
}
inline void hgWarnPoint::set_distance(double value) {
  
  distance_ = value;
  // @@protoc_insertion_point(field_set:hgWarnPoint.distance)
}

inline const hgWarnPoint* hgWarnPoint::internal_default_instance() {
  return &hgWarnPoint_default_instance_.get();
}
// -------------------------------------------------------------------

// hgEarlyWarnMes

// optional string WarningID = 1;
inline void hgEarlyWarnMes::clear_warningid() {
  warningid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgEarlyWarnMes::warningid() const {
  // @@protoc_insertion_point(field_get:hgEarlyWarnMes.WarningID)
  return warningid_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgEarlyWarnMes::set_warningid(const ::std::string& value) {
  
  warningid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgEarlyWarnMes.WarningID)
}
inline void hgEarlyWarnMes::set_warningid(const char* value) {
  
  warningid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgEarlyWarnMes.WarningID)
}
inline void hgEarlyWarnMes::set_warningid(const char* value, size_t size) {
  
  warningid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgEarlyWarnMes.WarningID)
}
inline ::std::string* hgEarlyWarnMes::mutable_warningid() {
  
  // @@protoc_insertion_point(field_mutable:hgEarlyWarnMes.WarningID)
  return warningid_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgEarlyWarnMes::release_warningid() {
  // @@protoc_insertion_point(field_release:hgEarlyWarnMes.WarningID)
  
  return warningid_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgEarlyWarnMes::set_allocated_warningid(::std::string* warningid) {
  if (warningid != NULL) {
    
  } else {
    
  }
  warningid_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), warningid);
  // @@protoc_insertion_point(field_set_allocated:hgEarlyWarnMes.WarningID)
}

// optional string WarningGUID = 2;
inline void hgEarlyWarnMes::clear_warningguid() {
  warningguid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgEarlyWarnMes::warningguid() const {
  // @@protoc_insertion_point(field_get:hgEarlyWarnMes.WarningGUID)
  return warningguid_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgEarlyWarnMes::set_warningguid(const ::std::string& value) {
  
  warningguid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgEarlyWarnMes.WarningGUID)
}
inline void hgEarlyWarnMes::set_warningguid(const char* value) {
  
  warningguid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgEarlyWarnMes.WarningGUID)
}
inline void hgEarlyWarnMes::set_warningguid(const char* value, size_t size) {
  
  warningguid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgEarlyWarnMes.WarningGUID)
}
inline ::std::string* hgEarlyWarnMes::mutable_warningguid() {
  
  // @@protoc_insertion_point(field_mutable:hgEarlyWarnMes.WarningGUID)
  return warningguid_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgEarlyWarnMes::release_warningguid() {
  // @@protoc_insertion_point(field_release:hgEarlyWarnMes.WarningGUID)
  
  return warningguid_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgEarlyWarnMes::set_allocated_warningguid(::std::string* warningguid) {
  if (warningguid != NULL) {
    
  } else {
    
  }
  warningguid_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), warningguid);
  // @@protoc_insertion_point(field_set_allocated:hgEarlyWarnMes.WarningGUID)
}

// optional int32 WarningPriority = 3;
inline void hgEarlyWarnMes::clear_warningpriority() {
  warningpriority_ = 0;
}
inline ::google::protobuf::int32 hgEarlyWarnMes::warningpriority() const {
  // @@protoc_insertion_point(field_get:hgEarlyWarnMes.WarningPriority)
  return warningpriority_;
}
inline void hgEarlyWarnMes::set_warningpriority(::google::protobuf::int32 value) {
  
  warningpriority_ = value;
  // @@protoc_insertion_point(field_set:hgEarlyWarnMes.WarningPriority)
}

// optional string WarningName = 4;
inline void hgEarlyWarnMes::clear_warningname() {
  warningname_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgEarlyWarnMes::warningname() const {
  // @@protoc_insertion_point(field_get:hgEarlyWarnMes.WarningName)
  return warningname_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgEarlyWarnMes::set_warningname(const ::std::string& value) {
  
  warningname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgEarlyWarnMes.WarningName)
}
inline void hgEarlyWarnMes::set_warningname(const char* value) {
  
  warningname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgEarlyWarnMes.WarningName)
}
inline void hgEarlyWarnMes::set_warningname(const char* value, size_t size) {
  
  warningname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgEarlyWarnMes.WarningName)
}
inline ::std::string* hgEarlyWarnMes::mutable_warningname() {
  
  // @@protoc_insertion_point(field_mutable:hgEarlyWarnMes.WarningName)
  return warningname_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgEarlyWarnMes::release_warningname() {
  // @@protoc_insertion_point(field_release:hgEarlyWarnMes.WarningName)
  
  return warningname_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgEarlyWarnMes::set_allocated_warningname(::std::string* warningname) {
  if (warningname != NULL) {
    
  } else {
    
  }
  warningname_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), warningname);
  // @@protoc_insertion_point(field_set_allocated:hgEarlyWarnMes.WarningName)
}

// optional string MMSI = 5;
inline void hgEarlyWarnMes::clear_mmsi() {
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgEarlyWarnMes::mmsi() const {
  // @@protoc_insertion_point(field_get:hgEarlyWarnMes.MMSI)
  return mmsi_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgEarlyWarnMes::set_mmsi(const ::std::string& value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgEarlyWarnMes.MMSI)
}
inline void hgEarlyWarnMes::set_mmsi(const char* value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgEarlyWarnMes.MMSI)
}
inline void hgEarlyWarnMes::set_mmsi(const char* value, size_t size) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgEarlyWarnMes.MMSI)
}
inline ::std::string* hgEarlyWarnMes::mutable_mmsi() {
  
  // @@protoc_insertion_point(field_mutable:hgEarlyWarnMes.MMSI)
  return mmsi_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgEarlyWarnMes::release_mmsi() {
  // @@protoc_insertion_point(field_release:hgEarlyWarnMes.MMSI)
  
  return mmsi_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgEarlyWarnMes::set_allocated_mmsi(::std::string* mmsi) {
  if (mmsi != NULL) {
    
  } else {
    
  }
  mmsi_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), mmsi);
  // @@protoc_insertion_point(field_set_allocated:hgEarlyWarnMes.MMSI)
}

// optional string TargetMMSI = 6;
inline void hgEarlyWarnMes::clear_targetmmsi() {
  targetmmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgEarlyWarnMes::targetmmsi() const {
  // @@protoc_insertion_point(field_get:hgEarlyWarnMes.TargetMMSI)
  return targetmmsi_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgEarlyWarnMes::set_targetmmsi(const ::std::string& value) {
  
  targetmmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgEarlyWarnMes.TargetMMSI)
}
inline void hgEarlyWarnMes::set_targetmmsi(const char* value) {
  
  targetmmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgEarlyWarnMes.TargetMMSI)
}
inline void hgEarlyWarnMes::set_targetmmsi(const char* value, size_t size) {
  
  targetmmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgEarlyWarnMes.TargetMMSI)
}
inline ::std::string* hgEarlyWarnMes::mutable_targetmmsi() {
  
  // @@protoc_insertion_point(field_mutable:hgEarlyWarnMes.TargetMMSI)
  return targetmmsi_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgEarlyWarnMes::release_targetmmsi() {
  // @@protoc_insertion_point(field_release:hgEarlyWarnMes.TargetMMSI)
  
  return targetmmsi_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgEarlyWarnMes::set_allocated_targetmmsi(::std::string* targetmmsi) {
  if (targetmmsi != NULL) {
    
  } else {
    
  }
  targetmmsi_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), targetmmsi);
  // @@protoc_insertion_point(field_set_allocated:hgEarlyWarnMes.TargetMMSI)
}

// optional int64 WarningTime = 7;
inline void hgEarlyWarnMes::clear_warningtime() {
  warningtime_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 hgEarlyWarnMes::warningtime() const {
  // @@protoc_insertion_point(field_get:hgEarlyWarnMes.WarningTime)
  return warningtime_;
}
inline void hgEarlyWarnMes::set_warningtime(::google::protobuf::int64 value) {
  
  warningtime_ = value;
  // @@protoc_insertion_point(field_set:hgEarlyWarnMes.WarningTime)
}

// optional .hgWarningLevel Level = 8;
inline void hgEarlyWarnMes::clear_level() {
  level_ = 0;
}
inline ::hgWarningLevel hgEarlyWarnMes::level() const {
  // @@protoc_insertion_point(field_get:hgEarlyWarnMes.Level)
  return static_cast< ::hgWarningLevel >(level_);
}
inline void hgEarlyWarnMes::set_level(::hgWarningLevel value) {
  
  level_ = value;
  // @@protoc_insertion_point(field_set:hgEarlyWarnMes.Level)
}

// repeated .hgWarnPoint Point = 9;
inline int hgEarlyWarnMes::point_size() const {
  return point_.size();
}
inline void hgEarlyWarnMes::clear_point() {
  point_.Clear();
}
inline const ::hgWarnPoint& hgEarlyWarnMes::point(int index) const {
  // @@protoc_insertion_point(field_get:hgEarlyWarnMes.Point)
  return point_.Get(index);
}
inline ::hgWarnPoint* hgEarlyWarnMes::mutable_point(int index) {
  // @@protoc_insertion_point(field_mutable:hgEarlyWarnMes.Point)
  return point_.Mutable(index);
}
inline ::hgWarnPoint* hgEarlyWarnMes::add_point() {
  // @@protoc_insertion_point(field_add:hgEarlyWarnMes.Point)
  return point_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::hgWarnPoint >*
hgEarlyWarnMes::mutable_point() {
  // @@protoc_insertion_point(field_mutable_list:hgEarlyWarnMes.Point)
  return &point_;
}
inline const ::google::protobuf::RepeatedPtrField< ::hgWarnPoint >&
hgEarlyWarnMes::point() const {
  // @@protoc_insertion_point(field_list:hgEarlyWarnMes.Point)
  return point_;
}

// optional bool StartPaint = 10;
inline void hgEarlyWarnMes::clear_startpaint() {
  startpaint_ = false;
}
inline bool hgEarlyWarnMes::startpaint() const {
  // @@protoc_insertion_point(field_get:hgEarlyWarnMes.StartPaint)
  return startpaint_;
}
inline void hgEarlyWarnMes::set_startpaint(bool value) {
  
  startpaint_ = value;
  // @@protoc_insertion_point(field_set:hgEarlyWarnMes.StartPaint)
}

// optional .hgWarningType WarningType = 11;
inline void hgEarlyWarnMes::clear_warningtype() {
  warningtype_ = 0;
}
inline ::hgWarningType hgEarlyWarnMes::warningtype() const {
  // @@protoc_insertion_point(field_get:hgEarlyWarnMes.WarningType)
  return static_cast< ::hgWarningType >(warningtype_);
}
inline void hgEarlyWarnMes::set_warningtype(::hgWarningType value) {
  
  warningtype_ = value;
  // @@protoc_insertion_point(field_set:hgEarlyWarnMes.WarningType)
}

inline const hgEarlyWarnMes* hgEarlyWarnMes::internal_default_instance() {
  return &hgEarlyWarnMes_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::hgWarningLevel> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::hgWarningLevel>() {
  return ::hgWarningLevel_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_hgEarlyWarnMes_2eproto__INCLUDED
