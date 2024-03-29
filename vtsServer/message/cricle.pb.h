// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: cricle.proto

#ifndef PROTOBUF_cricle_2eproto__INCLUDED
#define PROTOBUF_cricle_2eproto__INCLUDED

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
#include "waringinfo.pb.h"
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_cricle_2eproto();
void protobuf_InitDefaults_cricle_2eproto();
void protobuf_AssignDesc_cricle_2eproto();
void protobuf_ShutdownFile_cricle_2eproto();

class CricleRepsone;
class CricleRequest;

// ===================================================================

class CricleRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:CricleRequest) */ {
 public:
  CricleRequest();
  virtual ~CricleRequest();

  CricleRequest(const CricleRequest& from);

  inline CricleRequest& operator=(const CricleRequest& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const CricleRequest& default_instance();

  static const CricleRequest* internal_default_instance();

  void Swap(CricleRequest* other);

  // implements Message ----------------------------------------------

  inline CricleRequest* New() const { return New(NULL); }

  CricleRequest* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CricleRequest& from);
  void MergeFrom(const CricleRequest& from);
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
  void InternalSwap(CricleRequest* other);
  void UnsafeMergeFrom(const CricleRequest& from);
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

  // optional int32 type = 1;
  void clear_type();
  static const int kTypeFieldNumber = 1;
  ::google::protobuf::int32 type() const;
  void set_type(::google::protobuf::int32 value);

  // optional string ID = 2;
  void clear_id();
  static const int kIDFieldNumber = 2;
  const ::std::string& id() const;
  void set_id(const ::std::string& value);
  void set_id(const char* value);
  void set_id(const char* value, size_t size);
  ::std::string* mutable_id();
  ::std::string* release_id();
  void set_allocated_id(::std::string* id);

  // optional string name = 3;
  void clear_name();
  static const int kNameFieldNumber = 3;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // optional double lat = 4;
  void clear_lat();
  static const int kLatFieldNumber = 4;
  double lat() const;
  void set_lat(double value);

  // optional double lon = 5;
  void clear_lon();
  static const int kLonFieldNumber = 5;
  double lon() const;
  void set_lon(double value);

  // optional double radius = 6;
  void clear_radius();
  static const int kRadiusFieldNumber = 6;
  double radius() const;
  void set_radius(double value);

  // optional int32 linestyle = 7;
  void clear_linestyle();
  static const int kLinestyleFieldNumber = 7;
  ::google::protobuf::int32 linestyle() const;
  void set_linestyle(::google::protobuf::int32 value);

  // optional int32 fullstyle = 8;
  void clear_fullstyle();
  static const int kFullstyleFieldNumber = 8;
  ::google::protobuf::int32 fullstyle() const;
  void set_fullstyle(::google::protobuf::int32 value);

  // optional int32 linewidth = 9;
  void clear_linewidth();
  static const int kLinewidthFieldNumber = 9;
  ::google::protobuf::int32 linewidth() const;
  void set_linewidth(::google::protobuf::int32 value);

  // repeated string waringID = 10;
  int waringid_size() const;
  void clear_waringid();
  static const int kWaringIDFieldNumber = 10;
  const ::std::string& waringid(int index) const;
  ::std::string* mutable_waringid(int index);
  void set_waringid(int index, const ::std::string& value);
  void set_waringid(int index, const char* value);
  void set_waringid(int index, const char* value, size_t size);
  ::std::string* add_waringid();
  void add_waringid(const ::std::string& value);
  void add_waringid(const char* value);
  void add_waringid(const char* value, size_t size);
  const ::google::protobuf::RepeatedPtrField< ::std::string>& waringid() const;
  ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_waringid();

  // optional string waringtype = 11;
  void clear_waringtype();
  static const int kWaringtypeFieldNumber = 11;
  const ::std::string& waringtype() const;
  void set_waringtype(const ::std::string& value);
  void set_waringtype(const char* value);
  void set_waringtype(const char* value, size_t size);
  ::std::string* mutable_waringtype();
  ::std::string* release_waringtype();
  void set_allocated_waringtype(::std::string* waringtype);

  // optional string drawman = 12;
  void clear_drawman();
  static const int kDrawmanFieldNumber = 12;
  const ::std::string& drawman() const;
  void set_drawman(const ::std::string& value);
  void set_drawman(const char* value);
  void set_drawman(const char* value, size_t size);
  ::std::string* mutable_drawman();
  ::std::string* release_drawman();
  void set_allocated_drawman(::std::string* drawman);

  // optional bool isshare = 13;
  void clear_isshare();
  static const int kIsshareFieldNumber = 13;
  bool isshare() const;
  void set_isshare(bool value);

  // optional string linecolor = 14;
  void clear_linecolor();
  static const int kLinecolorFieldNumber = 14;
  const ::std::string& linecolor() const;
  void set_linecolor(const ::std::string& value);
  void set_linecolor(const char* value);
  void set_linecolor(const char* value, size_t size);
  ::std::string* mutable_linecolor();
  ::std::string* release_linecolor();
  void set_allocated_linecolor(::std::string* linecolor);

  // optional string fullcolor = 15;
  void clear_fullcolor();
  static const int kFullcolorFieldNumber = 15;
  const ::std::string& fullcolor() const;
  void set_fullcolor(const ::std::string& value);
  void set_fullcolor(const char* value);
  void set_fullcolor(const char* value, size_t size);
  ::std::string* mutable_fullcolor();
  ::std::string* release_fullcolor();
  void set_allocated_fullcolor(::std::string* fullcolor);

  // repeated .WaringInfo info = 16;
  int info_size() const;
  void clear_info();
  static const int kInfoFieldNumber = 16;
  const ::WaringInfo& info(int index) const;
  ::WaringInfo* mutable_info(int index);
  ::WaringInfo* add_info();
  ::google::protobuf::RepeatedPtrField< ::WaringInfo >*
      mutable_info();
  const ::google::protobuf::RepeatedPtrField< ::WaringInfo >&
      info() const;

  // @@protoc_insertion_point(class_scope:CricleRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::std::string> waringid_;
  ::google::protobuf::RepeatedPtrField< ::WaringInfo > info_;
  ::google::protobuf::internal::ArenaStringPtr id_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::internal::ArenaStringPtr waringtype_;
  ::google::protobuf::internal::ArenaStringPtr drawman_;
  ::google::protobuf::internal::ArenaStringPtr linecolor_;
  ::google::protobuf::internal::ArenaStringPtr fullcolor_;
  double lat_;
  ::google::protobuf::int32 type_;
  ::google::protobuf::int32 linestyle_;
  double lon_;
  double radius_;
  ::google::protobuf::int32 fullstyle_;
  ::google::protobuf::int32 linewidth_;
  bool isshare_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_cricle_2eproto_impl();
  friend void  protobuf_AddDesc_cricle_2eproto_impl();
  friend void protobuf_AssignDesc_cricle_2eproto();
  friend void protobuf_ShutdownFile_cricle_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<CricleRequest> CricleRequest_default_instance_;

// -------------------------------------------------------------------

class CricleRepsone : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:CricleRepsone) */ {
 public:
  CricleRepsone();
  virtual ~CricleRepsone();

  CricleRepsone(const CricleRepsone& from);

  inline CricleRepsone& operator=(const CricleRepsone& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const CricleRepsone& default_instance();

  static const CricleRepsone* internal_default_instance();

  void Swap(CricleRepsone* other);

  // implements Message ----------------------------------------------

  inline CricleRepsone* New() const { return New(NULL); }

  CricleRepsone* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const CricleRepsone& from);
  void MergeFrom(const CricleRepsone& from);
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
  void InternalSwap(CricleRepsone* other);
  void UnsafeMergeFrom(const CricleRepsone& from);
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

  // optional int32 type = 1;
  void clear_type();
  static const int kTypeFieldNumber = 1;
  ::google::protobuf::int32 type() const;
  void set_type(::google::protobuf::int32 value);

  // optional string result = 2;
  void clear_result();
  static const int kResultFieldNumber = 2;
  const ::std::string& result() const;
  void set_result(const ::std::string& value);
  void set_result(const char* value);
  void set_result(const char* value, size_t size);
  ::std::string* mutable_result();
  ::std::string* release_result();
  void set_allocated_result(::std::string* result);

  // repeated .CricleRequest cricles = 3;
  int cricles_size() const;
  void clear_cricles();
  static const int kCriclesFieldNumber = 3;
  const ::CricleRequest& cricles(int index) const;
  ::CricleRequest* mutable_cricles(int index);
  ::CricleRequest* add_cricles();
  ::google::protobuf::RepeatedPtrField< ::CricleRequest >*
      mutable_cricles();
  const ::google::protobuf::RepeatedPtrField< ::CricleRequest >&
      cricles() const;

  // @@protoc_insertion_point(class_scope:CricleRepsone)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::CricleRequest > cricles_;
  ::google::protobuf::internal::ArenaStringPtr result_;
  ::google::protobuf::int32 type_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_cricle_2eproto_impl();
  friend void  protobuf_AddDesc_cricle_2eproto_impl();
  friend void protobuf_AssignDesc_cricle_2eproto();
  friend void protobuf_ShutdownFile_cricle_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<CricleRepsone> CricleRepsone_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// CricleRequest

// optional int32 type = 1;
inline void CricleRequest::clear_type() {
  type_ = 0;
}
inline ::google::protobuf::int32 CricleRequest::type() const {
  // @@protoc_insertion_point(field_get:CricleRequest.type)
  return type_;
}
inline void CricleRequest::set_type(::google::protobuf::int32 value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:CricleRequest.type)
}

// optional string ID = 2;
inline void CricleRequest::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& CricleRequest::id() const {
  // @@protoc_insertion_point(field_get:CricleRequest.ID)
  return id_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CricleRequest::set_id(const ::std::string& value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:CricleRequest.ID)
}
inline void CricleRequest::set_id(const char* value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:CricleRequest.ID)
}
inline void CricleRequest::set_id(const char* value, size_t size) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:CricleRequest.ID)
}
inline ::std::string* CricleRequest::mutable_id() {
  
  // @@protoc_insertion_point(field_mutable:CricleRequest.ID)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CricleRequest::release_id() {
  // @@protoc_insertion_point(field_release:CricleRequest.ID)
  
  return id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CricleRequest::set_allocated_id(::std::string* id) {
  if (id != NULL) {
    
  } else {
    
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:CricleRequest.ID)
}

// optional string name = 3;
inline void CricleRequest::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& CricleRequest::name() const {
  // @@protoc_insertion_point(field_get:CricleRequest.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CricleRequest::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:CricleRequest.name)
}
inline void CricleRequest::set_name(const char* value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:CricleRequest.name)
}
inline void CricleRequest::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:CricleRequest.name)
}
inline ::std::string* CricleRequest::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:CricleRequest.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CricleRequest::release_name() {
  // @@protoc_insertion_point(field_release:CricleRequest.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CricleRequest::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:CricleRequest.name)
}

// optional double lat = 4;
inline void CricleRequest::clear_lat() {
  lat_ = 0;
}
inline double CricleRequest::lat() const {
  // @@protoc_insertion_point(field_get:CricleRequest.lat)
  return lat_;
}
inline void CricleRequest::set_lat(double value) {
  
  lat_ = value;
  // @@protoc_insertion_point(field_set:CricleRequest.lat)
}

// optional double lon = 5;
inline void CricleRequest::clear_lon() {
  lon_ = 0;
}
inline double CricleRequest::lon() const {
  // @@protoc_insertion_point(field_get:CricleRequest.lon)
  return lon_;
}
inline void CricleRequest::set_lon(double value) {
  
  lon_ = value;
  // @@protoc_insertion_point(field_set:CricleRequest.lon)
}

// optional double radius = 6;
inline void CricleRequest::clear_radius() {
  radius_ = 0;
}
inline double CricleRequest::radius() const {
  // @@protoc_insertion_point(field_get:CricleRequest.radius)
  return radius_;
}
inline void CricleRequest::set_radius(double value) {
  
  radius_ = value;
  // @@protoc_insertion_point(field_set:CricleRequest.radius)
}

// optional int32 linestyle = 7;
inline void CricleRequest::clear_linestyle() {
  linestyle_ = 0;
}
inline ::google::protobuf::int32 CricleRequest::linestyle() const {
  // @@protoc_insertion_point(field_get:CricleRequest.linestyle)
  return linestyle_;
}
inline void CricleRequest::set_linestyle(::google::protobuf::int32 value) {
  
  linestyle_ = value;
  // @@protoc_insertion_point(field_set:CricleRequest.linestyle)
}

// optional int32 fullstyle = 8;
inline void CricleRequest::clear_fullstyle() {
  fullstyle_ = 0;
}
inline ::google::protobuf::int32 CricleRequest::fullstyle() const {
  // @@protoc_insertion_point(field_get:CricleRequest.fullstyle)
  return fullstyle_;
}
inline void CricleRequest::set_fullstyle(::google::protobuf::int32 value) {
  
  fullstyle_ = value;
  // @@protoc_insertion_point(field_set:CricleRequest.fullstyle)
}

// optional int32 linewidth = 9;
inline void CricleRequest::clear_linewidth() {
  linewidth_ = 0;
}
inline ::google::protobuf::int32 CricleRequest::linewidth() const {
  // @@protoc_insertion_point(field_get:CricleRequest.linewidth)
  return linewidth_;
}
inline void CricleRequest::set_linewidth(::google::protobuf::int32 value) {
  
  linewidth_ = value;
  // @@protoc_insertion_point(field_set:CricleRequest.linewidth)
}

// repeated string waringID = 10;
inline int CricleRequest::waringid_size() const {
  return waringid_.size();
}
inline void CricleRequest::clear_waringid() {
  waringid_.Clear();
}
inline const ::std::string& CricleRequest::waringid(int index) const {
  // @@protoc_insertion_point(field_get:CricleRequest.waringID)
  return waringid_.Get(index);
}
inline ::std::string* CricleRequest::mutable_waringid(int index) {
  // @@protoc_insertion_point(field_mutable:CricleRequest.waringID)
  return waringid_.Mutable(index);
}
inline void CricleRequest::set_waringid(int index, const ::std::string& value) {
  // @@protoc_insertion_point(field_set:CricleRequest.waringID)
  waringid_.Mutable(index)->assign(value);
}
inline void CricleRequest::set_waringid(int index, const char* value) {
  waringid_.Mutable(index)->assign(value);
  // @@protoc_insertion_point(field_set_char:CricleRequest.waringID)
}
inline void CricleRequest::set_waringid(int index, const char* value, size_t size) {
  waringid_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:CricleRequest.waringID)
}
inline ::std::string* CricleRequest::add_waringid() {
  // @@protoc_insertion_point(field_add_mutable:CricleRequest.waringID)
  return waringid_.Add();
}
inline void CricleRequest::add_waringid(const ::std::string& value) {
  waringid_.Add()->assign(value);
  // @@protoc_insertion_point(field_add:CricleRequest.waringID)
}
inline void CricleRequest::add_waringid(const char* value) {
  waringid_.Add()->assign(value);
  // @@protoc_insertion_point(field_add_char:CricleRequest.waringID)
}
inline void CricleRequest::add_waringid(const char* value, size_t size) {
  waringid_.Add()->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_add_pointer:CricleRequest.waringID)
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
CricleRequest::waringid() const {
  // @@protoc_insertion_point(field_list:CricleRequest.waringID)
  return waringid_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
CricleRequest::mutable_waringid() {
  // @@protoc_insertion_point(field_mutable_list:CricleRequest.waringID)
  return &waringid_;
}

// optional string waringtype = 11;
inline void CricleRequest::clear_waringtype() {
  waringtype_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& CricleRequest::waringtype() const {
  // @@protoc_insertion_point(field_get:CricleRequest.waringtype)
  return waringtype_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CricleRequest::set_waringtype(const ::std::string& value) {
  
  waringtype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:CricleRequest.waringtype)
}
inline void CricleRequest::set_waringtype(const char* value) {
  
  waringtype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:CricleRequest.waringtype)
}
inline void CricleRequest::set_waringtype(const char* value, size_t size) {
  
  waringtype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:CricleRequest.waringtype)
}
inline ::std::string* CricleRequest::mutable_waringtype() {
  
  // @@protoc_insertion_point(field_mutable:CricleRequest.waringtype)
  return waringtype_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CricleRequest::release_waringtype() {
  // @@protoc_insertion_point(field_release:CricleRequest.waringtype)
  
  return waringtype_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CricleRequest::set_allocated_waringtype(::std::string* waringtype) {
  if (waringtype != NULL) {
    
  } else {
    
  }
  waringtype_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), waringtype);
  // @@protoc_insertion_point(field_set_allocated:CricleRequest.waringtype)
}

// optional string drawman = 12;
inline void CricleRequest::clear_drawman() {
  drawman_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& CricleRequest::drawman() const {
  // @@protoc_insertion_point(field_get:CricleRequest.drawman)
  return drawman_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CricleRequest::set_drawman(const ::std::string& value) {
  
  drawman_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:CricleRequest.drawman)
}
inline void CricleRequest::set_drawman(const char* value) {
  
  drawman_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:CricleRequest.drawman)
}
inline void CricleRequest::set_drawman(const char* value, size_t size) {
  
  drawman_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:CricleRequest.drawman)
}
inline ::std::string* CricleRequest::mutable_drawman() {
  
  // @@protoc_insertion_point(field_mutable:CricleRequest.drawman)
  return drawman_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CricleRequest::release_drawman() {
  // @@protoc_insertion_point(field_release:CricleRequest.drawman)
  
  return drawman_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CricleRequest::set_allocated_drawman(::std::string* drawman) {
  if (drawman != NULL) {
    
  } else {
    
  }
  drawman_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), drawman);
  // @@protoc_insertion_point(field_set_allocated:CricleRequest.drawman)
}

// optional bool isshare = 13;
inline void CricleRequest::clear_isshare() {
  isshare_ = false;
}
inline bool CricleRequest::isshare() const {
  // @@protoc_insertion_point(field_get:CricleRequest.isshare)
  return isshare_;
}
inline void CricleRequest::set_isshare(bool value) {
  
  isshare_ = value;
  // @@protoc_insertion_point(field_set:CricleRequest.isshare)
}

// optional string linecolor = 14;
inline void CricleRequest::clear_linecolor() {
  linecolor_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& CricleRequest::linecolor() const {
  // @@protoc_insertion_point(field_get:CricleRequest.linecolor)
  return linecolor_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CricleRequest::set_linecolor(const ::std::string& value) {
  
  linecolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:CricleRequest.linecolor)
}
inline void CricleRequest::set_linecolor(const char* value) {
  
  linecolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:CricleRequest.linecolor)
}
inline void CricleRequest::set_linecolor(const char* value, size_t size) {
  
  linecolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:CricleRequest.linecolor)
}
inline ::std::string* CricleRequest::mutable_linecolor() {
  
  // @@protoc_insertion_point(field_mutable:CricleRequest.linecolor)
  return linecolor_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CricleRequest::release_linecolor() {
  // @@protoc_insertion_point(field_release:CricleRequest.linecolor)
  
  return linecolor_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CricleRequest::set_allocated_linecolor(::std::string* linecolor) {
  if (linecolor != NULL) {
    
  } else {
    
  }
  linecolor_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), linecolor);
  // @@protoc_insertion_point(field_set_allocated:CricleRequest.linecolor)
}

// optional string fullcolor = 15;
inline void CricleRequest::clear_fullcolor() {
  fullcolor_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& CricleRequest::fullcolor() const {
  // @@protoc_insertion_point(field_get:CricleRequest.fullcolor)
  return fullcolor_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CricleRequest::set_fullcolor(const ::std::string& value) {
  
  fullcolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:CricleRequest.fullcolor)
}
inline void CricleRequest::set_fullcolor(const char* value) {
  
  fullcolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:CricleRequest.fullcolor)
}
inline void CricleRequest::set_fullcolor(const char* value, size_t size) {
  
  fullcolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:CricleRequest.fullcolor)
}
inline ::std::string* CricleRequest::mutable_fullcolor() {
  
  // @@protoc_insertion_point(field_mutable:CricleRequest.fullcolor)
  return fullcolor_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CricleRequest::release_fullcolor() {
  // @@protoc_insertion_point(field_release:CricleRequest.fullcolor)
  
  return fullcolor_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CricleRequest::set_allocated_fullcolor(::std::string* fullcolor) {
  if (fullcolor != NULL) {
    
  } else {
    
  }
  fullcolor_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), fullcolor);
  // @@protoc_insertion_point(field_set_allocated:CricleRequest.fullcolor)
}

// repeated .WaringInfo info = 16;
inline int CricleRequest::info_size() const {
  return info_.size();
}
inline void CricleRequest::clear_info() {
  info_.Clear();
}
inline const ::WaringInfo& CricleRequest::info(int index) const {
  // @@protoc_insertion_point(field_get:CricleRequest.info)
  return info_.Get(index);
}
inline ::WaringInfo* CricleRequest::mutable_info(int index) {
  // @@protoc_insertion_point(field_mutable:CricleRequest.info)
  return info_.Mutable(index);
}
inline ::WaringInfo* CricleRequest::add_info() {
  // @@protoc_insertion_point(field_add:CricleRequest.info)
  return info_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::WaringInfo >*
CricleRequest::mutable_info() {
  // @@protoc_insertion_point(field_mutable_list:CricleRequest.info)
  return &info_;
}
inline const ::google::protobuf::RepeatedPtrField< ::WaringInfo >&
CricleRequest::info() const {
  // @@protoc_insertion_point(field_list:CricleRequest.info)
  return info_;
}

inline const CricleRequest* CricleRequest::internal_default_instance() {
  return &CricleRequest_default_instance_.get();
}
// -------------------------------------------------------------------

// CricleRepsone

// optional int32 type = 1;
inline void CricleRepsone::clear_type() {
  type_ = 0;
}
inline ::google::protobuf::int32 CricleRepsone::type() const {
  // @@protoc_insertion_point(field_get:CricleRepsone.type)
  return type_;
}
inline void CricleRepsone::set_type(::google::protobuf::int32 value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:CricleRepsone.type)
}

// optional string result = 2;
inline void CricleRepsone::clear_result() {
  result_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& CricleRepsone::result() const {
  // @@protoc_insertion_point(field_get:CricleRepsone.result)
  return result_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CricleRepsone::set_result(const ::std::string& value) {
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:CricleRepsone.result)
}
inline void CricleRepsone::set_result(const char* value) {
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:CricleRepsone.result)
}
inline void CricleRepsone::set_result(const char* value, size_t size) {
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:CricleRepsone.result)
}
inline ::std::string* CricleRepsone::mutable_result() {
  
  // @@protoc_insertion_point(field_mutable:CricleRepsone.result)
  return result_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CricleRepsone::release_result() {
  // @@protoc_insertion_point(field_release:CricleRepsone.result)
  
  return result_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CricleRepsone::set_allocated_result(::std::string* result) {
  if (result != NULL) {
    
  } else {
    
  }
  result_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), result);
  // @@protoc_insertion_point(field_set_allocated:CricleRepsone.result)
}

// repeated .CricleRequest cricles = 3;
inline int CricleRepsone::cricles_size() const {
  return cricles_.size();
}
inline void CricleRepsone::clear_cricles() {
  cricles_.Clear();
}
inline const ::CricleRequest& CricleRepsone::cricles(int index) const {
  // @@protoc_insertion_point(field_get:CricleRepsone.cricles)
  return cricles_.Get(index);
}
inline ::CricleRequest* CricleRepsone::mutable_cricles(int index) {
  // @@protoc_insertion_point(field_mutable:CricleRepsone.cricles)
  return cricles_.Mutable(index);
}
inline ::CricleRequest* CricleRepsone::add_cricles() {
  // @@protoc_insertion_point(field_add:CricleRepsone.cricles)
  return cricles_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::CricleRequest >*
CricleRepsone::mutable_cricles() {
  // @@protoc_insertion_point(field_mutable_list:CricleRepsone.cricles)
  return &cricles_;
}
inline const ::google::protobuf::RepeatedPtrField< ::CricleRequest >&
CricleRepsone::cricles() const {
  // @@protoc_insertion_point(field_list:CricleRepsone.cricles)
  return cricles_;
}

inline const CricleRepsone* CricleRepsone::internal_default_instance() {
  return &CricleRepsone_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_cricle_2eproto__INCLUDED
