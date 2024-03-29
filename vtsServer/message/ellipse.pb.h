// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ellipse.proto

#ifndef PROTOBUF_ellipse_2eproto__INCLUDED
#define PROTOBUF_ellipse_2eproto__INCLUDED

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
void protobuf_AddDesc_ellipse_2eproto();
void protobuf_InitDefaults_ellipse_2eproto();
void protobuf_AssignDesc_ellipse_2eproto();
void protobuf_ShutdownFile_ellipse_2eproto();

class EllipseRepsone;
class EllipseRequest;

// ===================================================================

class EllipseRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:EllipseRequest) */ {
 public:
  EllipseRequest();
  virtual ~EllipseRequest();

  EllipseRequest(const EllipseRequest& from);

  inline EllipseRequest& operator=(const EllipseRequest& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const EllipseRequest& default_instance();

  static const EllipseRequest* internal_default_instance();

  void Swap(EllipseRequest* other);

  // implements Message ----------------------------------------------

  inline EllipseRequest* New() const { return New(NULL); }

  EllipseRequest* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const EllipseRequest& from);
  void MergeFrom(const EllipseRequest& from);
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
  void InternalSwap(EllipseRequest* other);
  void UnsafeMergeFrom(const EllipseRequest& from);
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

  // optional double longaxis = 6;
  void clear_longaxis();
  static const int kLongaxisFieldNumber = 6;
  double longaxis() const;
  void set_longaxis(double value);

  // optional double shortaxis = 7;
  void clear_shortaxis();
  static const int kShortaxisFieldNumber = 7;
  double shortaxis() const;
  void set_shortaxis(double value);

  // optional int32 linestyle = 8;
  void clear_linestyle();
  static const int kLinestyleFieldNumber = 8;
  ::google::protobuf::int32 linestyle() const;
  void set_linestyle(::google::protobuf::int32 value);

  // optional int32 fullstyle = 9;
  void clear_fullstyle();
  static const int kFullstyleFieldNumber = 9;
  ::google::protobuf::int32 fullstyle() const;
  void set_fullstyle(::google::protobuf::int32 value);

  // optional int32 linewidth = 10;
  void clear_linewidth();
  static const int kLinewidthFieldNumber = 10;
  ::google::protobuf::int32 linewidth() const;
  void set_linewidth(::google::protobuf::int32 value);

  // repeated int32 waringID = 11;
  int waringid_size() const;
  void clear_waringid();
  static const int kWaringIDFieldNumber = 11;
  ::google::protobuf::int32 waringid(int index) const;
  void set_waringid(int index, ::google::protobuf::int32 value);
  void add_waringid(::google::protobuf::int32 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
      waringid() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
      mutable_waringid();

  // optional string waringtype = 12;
  void clear_waringtype();
  static const int kWaringtypeFieldNumber = 12;
  const ::std::string& waringtype() const;
  void set_waringtype(const ::std::string& value);
  void set_waringtype(const char* value);
  void set_waringtype(const char* value, size_t size);
  ::std::string* mutable_waringtype();
  ::std::string* release_waringtype();
  void set_allocated_waringtype(::std::string* waringtype);

  // optional string drawman = 13;
  void clear_drawman();
  static const int kDrawmanFieldNumber = 13;
  const ::std::string& drawman() const;
  void set_drawman(const ::std::string& value);
  void set_drawman(const char* value);
  void set_drawman(const char* value, size_t size);
  ::std::string* mutable_drawman();
  ::std::string* release_drawman();
  void set_allocated_drawman(::std::string* drawman);

  // optional bool isshare = 14;
  void clear_isshare();
  static const int kIsshareFieldNumber = 14;
  bool isshare() const;
  void set_isshare(bool value);

  // optional string linecolor = 15;
  void clear_linecolor();
  static const int kLinecolorFieldNumber = 15;
  const ::std::string& linecolor() const;
  void set_linecolor(const ::std::string& value);
  void set_linecolor(const char* value);
  void set_linecolor(const char* value, size_t size);
  ::std::string* mutable_linecolor();
  ::std::string* release_linecolor();
  void set_allocated_linecolor(::std::string* linecolor);

  // optional string fullcolor = 16;
  void clear_fullcolor();
  static const int kFullcolorFieldNumber = 16;
  const ::std::string& fullcolor() const;
  void set_fullcolor(const ::std::string& value);
  void set_fullcolor(const char* value);
  void set_fullcolor(const char* value, size_t size);
  ::std::string* mutable_fullcolor();
  ::std::string* release_fullcolor();
  void set_allocated_fullcolor(::std::string* fullcolor);

  // @@protoc_insertion_point(class_scope:EllipseRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedField< ::google::protobuf::int32 > waringid_;
  mutable int _waringid_cached_byte_size_;
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
  double longaxis_;
  double shortaxis_;
  ::google::protobuf::int32 fullstyle_;
  ::google::protobuf::int32 linewidth_;
  bool isshare_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_ellipse_2eproto_impl();
  friend void  protobuf_AddDesc_ellipse_2eproto_impl();
  friend void protobuf_AssignDesc_ellipse_2eproto();
  friend void protobuf_ShutdownFile_ellipse_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<EllipseRequest> EllipseRequest_default_instance_;

// -------------------------------------------------------------------

class EllipseRepsone : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:EllipseRepsone) */ {
 public:
  EllipseRepsone();
  virtual ~EllipseRepsone();

  EllipseRepsone(const EllipseRepsone& from);

  inline EllipseRepsone& operator=(const EllipseRepsone& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const EllipseRepsone& default_instance();

  static const EllipseRepsone* internal_default_instance();

  void Swap(EllipseRepsone* other);

  // implements Message ----------------------------------------------

  inline EllipseRepsone* New() const { return New(NULL); }

  EllipseRepsone* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const EllipseRepsone& from);
  void MergeFrom(const EllipseRepsone& from);
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
  void InternalSwap(EllipseRepsone* other);
  void UnsafeMergeFrom(const EllipseRepsone& from);
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

  // repeated .EllipseRequest ellipses = 3;
  int ellipses_size() const;
  void clear_ellipses();
  static const int kEllipsesFieldNumber = 3;
  const ::EllipseRequest& ellipses(int index) const;
  ::EllipseRequest* mutable_ellipses(int index);
  ::EllipseRequest* add_ellipses();
  ::google::protobuf::RepeatedPtrField< ::EllipseRequest >*
      mutable_ellipses();
  const ::google::protobuf::RepeatedPtrField< ::EllipseRequest >&
      ellipses() const;

  // @@protoc_insertion_point(class_scope:EllipseRepsone)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::EllipseRequest > ellipses_;
  ::google::protobuf::internal::ArenaStringPtr result_;
  ::google::protobuf::int32 type_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_ellipse_2eproto_impl();
  friend void  protobuf_AddDesc_ellipse_2eproto_impl();
  friend void protobuf_AssignDesc_ellipse_2eproto();
  friend void protobuf_ShutdownFile_ellipse_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<EllipseRepsone> EllipseRepsone_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// EllipseRequest

// optional int32 type = 1;
inline void EllipseRequest::clear_type() {
  type_ = 0;
}
inline ::google::protobuf::int32 EllipseRequest::type() const {
  // @@protoc_insertion_point(field_get:EllipseRequest.type)
  return type_;
}
inline void EllipseRequest::set_type(::google::protobuf::int32 value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:EllipseRequest.type)
}

// optional string ID = 2;
inline void EllipseRequest::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& EllipseRequest::id() const {
  // @@protoc_insertion_point(field_get:EllipseRequest.ID)
  return id_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void EllipseRequest::set_id(const ::std::string& value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:EllipseRequest.ID)
}
inline void EllipseRequest::set_id(const char* value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:EllipseRequest.ID)
}
inline void EllipseRequest::set_id(const char* value, size_t size) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:EllipseRequest.ID)
}
inline ::std::string* EllipseRequest::mutable_id() {
  
  // @@protoc_insertion_point(field_mutable:EllipseRequest.ID)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* EllipseRequest::release_id() {
  // @@protoc_insertion_point(field_release:EllipseRequest.ID)
  
  return id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void EllipseRequest::set_allocated_id(::std::string* id) {
  if (id != NULL) {
    
  } else {
    
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:EllipseRequest.ID)
}

// optional string name = 3;
inline void EllipseRequest::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& EllipseRequest::name() const {
  // @@protoc_insertion_point(field_get:EllipseRequest.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void EllipseRequest::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:EllipseRequest.name)
}
inline void EllipseRequest::set_name(const char* value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:EllipseRequest.name)
}
inline void EllipseRequest::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:EllipseRequest.name)
}
inline ::std::string* EllipseRequest::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:EllipseRequest.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* EllipseRequest::release_name() {
  // @@protoc_insertion_point(field_release:EllipseRequest.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void EllipseRequest::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:EllipseRequest.name)
}

// optional double lat = 4;
inline void EllipseRequest::clear_lat() {
  lat_ = 0;
}
inline double EllipseRequest::lat() const {
  // @@protoc_insertion_point(field_get:EllipseRequest.lat)
  return lat_;
}
inline void EllipseRequest::set_lat(double value) {
  
  lat_ = value;
  // @@protoc_insertion_point(field_set:EllipseRequest.lat)
}

// optional double lon = 5;
inline void EllipseRequest::clear_lon() {
  lon_ = 0;
}
inline double EllipseRequest::lon() const {
  // @@protoc_insertion_point(field_get:EllipseRequest.lon)
  return lon_;
}
inline void EllipseRequest::set_lon(double value) {
  
  lon_ = value;
  // @@protoc_insertion_point(field_set:EllipseRequest.lon)
}

// optional double longaxis = 6;
inline void EllipseRequest::clear_longaxis() {
  longaxis_ = 0;
}
inline double EllipseRequest::longaxis() const {
  // @@protoc_insertion_point(field_get:EllipseRequest.longaxis)
  return longaxis_;
}
inline void EllipseRequest::set_longaxis(double value) {
  
  longaxis_ = value;
  // @@protoc_insertion_point(field_set:EllipseRequest.longaxis)
}

// optional double shortaxis = 7;
inline void EllipseRequest::clear_shortaxis() {
  shortaxis_ = 0;
}
inline double EllipseRequest::shortaxis() const {
  // @@protoc_insertion_point(field_get:EllipseRequest.shortaxis)
  return shortaxis_;
}
inline void EllipseRequest::set_shortaxis(double value) {
  
  shortaxis_ = value;
  // @@protoc_insertion_point(field_set:EllipseRequest.shortaxis)
}

// optional int32 linestyle = 8;
inline void EllipseRequest::clear_linestyle() {
  linestyle_ = 0;
}
inline ::google::protobuf::int32 EllipseRequest::linestyle() const {
  // @@protoc_insertion_point(field_get:EllipseRequest.linestyle)
  return linestyle_;
}
inline void EllipseRequest::set_linestyle(::google::protobuf::int32 value) {
  
  linestyle_ = value;
  // @@protoc_insertion_point(field_set:EllipseRequest.linestyle)
}

// optional int32 fullstyle = 9;
inline void EllipseRequest::clear_fullstyle() {
  fullstyle_ = 0;
}
inline ::google::protobuf::int32 EllipseRequest::fullstyle() const {
  // @@protoc_insertion_point(field_get:EllipseRequest.fullstyle)
  return fullstyle_;
}
inline void EllipseRequest::set_fullstyle(::google::protobuf::int32 value) {
  
  fullstyle_ = value;
  // @@protoc_insertion_point(field_set:EllipseRequest.fullstyle)
}

// optional int32 linewidth = 10;
inline void EllipseRequest::clear_linewidth() {
  linewidth_ = 0;
}
inline ::google::protobuf::int32 EllipseRequest::linewidth() const {
  // @@protoc_insertion_point(field_get:EllipseRequest.linewidth)
  return linewidth_;
}
inline void EllipseRequest::set_linewidth(::google::protobuf::int32 value) {
  
  linewidth_ = value;
  // @@protoc_insertion_point(field_set:EllipseRequest.linewidth)
}

// repeated int32 waringID = 11;
inline int EllipseRequest::waringid_size() const {
  return waringid_.size();
}
inline void EllipseRequest::clear_waringid() {
  waringid_.Clear();
}
inline ::google::protobuf::int32 EllipseRequest::waringid(int index) const {
  // @@protoc_insertion_point(field_get:EllipseRequest.waringID)
  return waringid_.Get(index);
}
inline void EllipseRequest::set_waringid(int index, ::google::protobuf::int32 value) {
  waringid_.Set(index, value);
  // @@protoc_insertion_point(field_set:EllipseRequest.waringID)
}
inline void EllipseRequest::add_waringid(::google::protobuf::int32 value) {
  waringid_.Add(value);
  // @@protoc_insertion_point(field_add:EllipseRequest.waringID)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::int32 >&
EllipseRequest::waringid() const {
  // @@protoc_insertion_point(field_list:EllipseRequest.waringID)
  return waringid_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::int32 >*
EllipseRequest::mutable_waringid() {
  // @@protoc_insertion_point(field_mutable_list:EllipseRequest.waringID)
  return &waringid_;
}

// optional string waringtype = 12;
inline void EllipseRequest::clear_waringtype() {
  waringtype_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& EllipseRequest::waringtype() const {
  // @@protoc_insertion_point(field_get:EllipseRequest.waringtype)
  return waringtype_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void EllipseRequest::set_waringtype(const ::std::string& value) {
  
  waringtype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:EllipseRequest.waringtype)
}
inline void EllipseRequest::set_waringtype(const char* value) {
  
  waringtype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:EllipseRequest.waringtype)
}
inline void EllipseRequest::set_waringtype(const char* value, size_t size) {
  
  waringtype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:EllipseRequest.waringtype)
}
inline ::std::string* EllipseRequest::mutable_waringtype() {
  
  // @@protoc_insertion_point(field_mutable:EllipseRequest.waringtype)
  return waringtype_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* EllipseRequest::release_waringtype() {
  // @@protoc_insertion_point(field_release:EllipseRequest.waringtype)
  
  return waringtype_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void EllipseRequest::set_allocated_waringtype(::std::string* waringtype) {
  if (waringtype != NULL) {
    
  } else {
    
  }
  waringtype_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), waringtype);
  // @@protoc_insertion_point(field_set_allocated:EllipseRequest.waringtype)
}

// optional string drawman = 13;
inline void EllipseRequest::clear_drawman() {
  drawman_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& EllipseRequest::drawman() const {
  // @@protoc_insertion_point(field_get:EllipseRequest.drawman)
  return drawman_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void EllipseRequest::set_drawman(const ::std::string& value) {
  
  drawman_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:EllipseRequest.drawman)
}
inline void EllipseRequest::set_drawman(const char* value) {
  
  drawman_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:EllipseRequest.drawman)
}
inline void EllipseRequest::set_drawman(const char* value, size_t size) {
  
  drawman_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:EllipseRequest.drawman)
}
inline ::std::string* EllipseRequest::mutable_drawman() {
  
  // @@protoc_insertion_point(field_mutable:EllipseRequest.drawman)
  return drawman_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* EllipseRequest::release_drawman() {
  // @@protoc_insertion_point(field_release:EllipseRequest.drawman)
  
  return drawman_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void EllipseRequest::set_allocated_drawman(::std::string* drawman) {
  if (drawman != NULL) {
    
  } else {
    
  }
  drawman_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), drawman);
  // @@protoc_insertion_point(field_set_allocated:EllipseRequest.drawman)
}

// optional bool isshare = 14;
inline void EllipseRequest::clear_isshare() {
  isshare_ = false;
}
inline bool EllipseRequest::isshare() const {
  // @@protoc_insertion_point(field_get:EllipseRequest.isshare)
  return isshare_;
}
inline void EllipseRequest::set_isshare(bool value) {
  
  isshare_ = value;
  // @@protoc_insertion_point(field_set:EllipseRequest.isshare)
}

// optional string linecolor = 15;
inline void EllipseRequest::clear_linecolor() {
  linecolor_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& EllipseRequest::linecolor() const {
  // @@protoc_insertion_point(field_get:EllipseRequest.linecolor)
  return linecolor_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void EllipseRequest::set_linecolor(const ::std::string& value) {
  
  linecolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:EllipseRequest.linecolor)
}
inline void EllipseRequest::set_linecolor(const char* value) {
  
  linecolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:EllipseRequest.linecolor)
}
inline void EllipseRequest::set_linecolor(const char* value, size_t size) {
  
  linecolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:EllipseRequest.linecolor)
}
inline ::std::string* EllipseRequest::mutable_linecolor() {
  
  // @@protoc_insertion_point(field_mutable:EllipseRequest.linecolor)
  return linecolor_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* EllipseRequest::release_linecolor() {
  // @@protoc_insertion_point(field_release:EllipseRequest.linecolor)
  
  return linecolor_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void EllipseRequest::set_allocated_linecolor(::std::string* linecolor) {
  if (linecolor != NULL) {
    
  } else {
    
  }
  linecolor_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), linecolor);
  // @@protoc_insertion_point(field_set_allocated:EllipseRequest.linecolor)
}

// optional string fullcolor = 16;
inline void EllipseRequest::clear_fullcolor() {
  fullcolor_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& EllipseRequest::fullcolor() const {
  // @@protoc_insertion_point(field_get:EllipseRequest.fullcolor)
  return fullcolor_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void EllipseRequest::set_fullcolor(const ::std::string& value) {
  
  fullcolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:EllipseRequest.fullcolor)
}
inline void EllipseRequest::set_fullcolor(const char* value) {
  
  fullcolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:EllipseRequest.fullcolor)
}
inline void EllipseRequest::set_fullcolor(const char* value, size_t size) {
  
  fullcolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:EllipseRequest.fullcolor)
}
inline ::std::string* EllipseRequest::mutable_fullcolor() {
  
  // @@protoc_insertion_point(field_mutable:EllipseRequest.fullcolor)
  return fullcolor_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* EllipseRequest::release_fullcolor() {
  // @@protoc_insertion_point(field_release:EllipseRequest.fullcolor)
  
  return fullcolor_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void EllipseRequest::set_allocated_fullcolor(::std::string* fullcolor) {
  if (fullcolor != NULL) {
    
  } else {
    
  }
  fullcolor_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), fullcolor);
  // @@protoc_insertion_point(field_set_allocated:EllipseRequest.fullcolor)
}

inline const EllipseRequest* EllipseRequest::internal_default_instance() {
  return &EllipseRequest_default_instance_.get();
}
// -------------------------------------------------------------------

// EllipseRepsone

// optional int32 type = 1;
inline void EllipseRepsone::clear_type() {
  type_ = 0;
}
inline ::google::protobuf::int32 EllipseRepsone::type() const {
  // @@protoc_insertion_point(field_get:EllipseRepsone.type)
  return type_;
}
inline void EllipseRepsone::set_type(::google::protobuf::int32 value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:EllipseRepsone.type)
}

// optional string result = 2;
inline void EllipseRepsone::clear_result() {
  result_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& EllipseRepsone::result() const {
  // @@protoc_insertion_point(field_get:EllipseRepsone.result)
  return result_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void EllipseRepsone::set_result(const ::std::string& value) {
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:EllipseRepsone.result)
}
inline void EllipseRepsone::set_result(const char* value) {
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:EllipseRepsone.result)
}
inline void EllipseRepsone::set_result(const char* value, size_t size) {
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:EllipseRepsone.result)
}
inline ::std::string* EllipseRepsone::mutable_result() {
  
  // @@protoc_insertion_point(field_mutable:EllipseRepsone.result)
  return result_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* EllipseRepsone::release_result() {
  // @@protoc_insertion_point(field_release:EllipseRepsone.result)
  
  return result_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void EllipseRepsone::set_allocated_result(::std::string* result) {
  if (result != NULL) {
    
  } else {
    
  }
  result_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), result);
  // @@protoc_insertion_point(field_set_allocated:EllipseRepsone.result)
}

// repeated .EllipseRequest ellipses = 3;
inline int EllipseRepsone::ellipses_size() const {
  return ellipses_.size();
}
inline void EllipseRepsone::clear_ellipses() {
  ellipses_.Clear();
}
inline const ::EllipseRequest& EllipseRepsone::ellipses(int index) const {
  // @@protoc_insertion_point(field_get:EllipseRepsone.ellipses)
  return ellipses_.Get(index);
}
inline ::EllipseRequest* EllipseRepsone::mutable_ellipses(int index) {
  // @@protoc_insertion_point(field_mutable:EllipseRepsone.ellipses)
  return ellipses_.Mutable(index);
}
inline ::EllipseRequest* EllipseRepsone::add_ellipses() {
  // @@protoc_insertion_point(field_add:EllipseRepsone.ellipses)
  return ellipses_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::EllipseRequest >*
EllipseRepsone::mutable_ellipses() {
  // @@protoc_insertion_point(field_mutable_list:EllipseRepsone.ellipses)
  return &ellipses_;
}
inline const ::google::protobuf::RepeatedPtrField< ::EllipseRequest >&
EllipseRepsone::ellipses() const {
  // @@protoc_insertion_point(field_list:EllipseRepsone.ellipses)
  return ellipses_;
}

inline const EllipseRepsone* EllipseRepsone::internal_default_instance() {
  return &EllipseRepsone_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_ellipse_2eproto__INCLUDED
