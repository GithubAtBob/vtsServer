// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: dutyarea.proto

#ifndef PROTOBUF_dutyarea_2eproto__INCLUDED
#define PROTOBUF_dutyarea_2eproto__INCLUDED

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
#include "PointMes.pb.h"
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_dutyarea_2eproto();
void protobuf_InitDefaults_dutyarea_2eproto();
void protobuf_AssignDesc_dutyarea_2eproto();
void protobuf_ShutdownFile_dutyarea_2eproto();

class DutyAreaRepsone;
class DutyAreaRequest;

// ===================================================================

class DutyAreaRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:DutyAreaRequest) */ {
 public:
  DutyAreaRequest();
  virtual ~DutyAreaRequest();

  DutyAreaRequest(const DutyAreaRequest& from);

  inline DutyAreaRequest& operator=(const DutyAreaRequest& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const DutyAreaRequest& default_instance();

  static const DutyAreaRequest* internal_default_instance();

  void Swap(DutyAreaRequest* other);

  // implements Message ----------------------------------------------

  inline DutyAreaRequest* New() const { return New(NULL); }

  DutyAreaRequest* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DutyAreaRequest& from);
  void MergeFrom(const DutyAreaRequest& from);
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
  void InternalSwap(DutyAreaRequest* other);
  void UnsafeMergeFrom(const DutyAreaRequest& from);
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

  // repeated .PointMes point = 4;
  int point_size() const;
  void clear_point();
  static const int kPointFieldNumber = 4;
  const ::PointMes& point(int index) const;
  ::PointMes* mutable_point(int index);
  ::PointMes* add_point();
  ::google::protobuf::RepeatedPtrField< ::PointMes >*
      mutable_point();
  const ::google::protobuf::RepeatedPtrField< ::PointMes >&
      point() const;

  // optional int32 linestyle = 5;
  void clear_linestyle();
  static const int kLinestyleFieldNumber = 5;
  ::google::protobuf::int32 linestyle() const;
  void set_linestyle(::google::protobuf::int32 value);

  // optional int32 fullstyle = 6;
  void clear_fullstyle();
  static const int kFullstyleFieldNumber = 6;
  ::google::protobuf::int32 fullstyle() const;
  void set_fullstyle(::google::protobuf::int32 value);

  // optional int32 linewidth = 7;
  void clear_linewidth();
  static const int kLinewidthFieldNumber = 7;
  ::google::protobuf::int32 linewidth() const;
  void set_linewidth(::google::protobuf::int32 value);

  // optional string dutyman = 8;
  void clear_dutyman();
  static const int kDutymanFieldNumber = 8;
  const ::std::string& dutyman() const;
  void set_dutyman(const ::std::string& value);
  void set_dutyman(const char* value);
  void set_dutyman(const char* value, size_t size);
  ::std::string* mutable_dutyman();
  ::std::string* release_dutyman();
  void set_allocated_dutyman(::std::string* dutyman);

  // optional string drawman = 9;
  void clear_drawman();
  static const int kDrawmanFieldNumber = 9;
  const ::std::string& drawman() const;
  void set_drawman(const ::std::string& value);
  void set_drawman(const char* value);
  void set_drawman(const char* value, size_t size);
  ::std::string* mutable_drawman();
  ::std::string* release_drawman();
  void set_allocated_drawman(::std::string* drawman);

  // optional bool isshare = 10;
  void clear_isshare();
  static const int kIsshareFieldNumber = 10;
  bool isshare() const;
  void set_isshare(bool value);

  // optional string linecolor = 11;
  void clear_linecolor();
  static const int kLinecolorFieldNumber = 11;
  const ::std::string& linecolor() const;
  void set_linecolor(const ::std::string& value);
  void set_linecolor(const char* value);
  void set_linecolor(const char* value, size_t size);
  ::std::string* mutable_linecolor();
  ::std::string* release_linecolor();
  void set_allocated_linecolor(::std::string* linecolor);

  // optional string fullcolor = 12;
  void clear_fullcolor();
  static const int kFullcolorFieldNumber = 12;
  const ::std::string& fullcolor() const;
  void set_fullcolor(const ::std::string& value);
  void set_fullcolor(const char* value);
  void set_fullcolor(const char* value, size_t size);
  ::std::string* mutable_fullcolor();
  ::std::string* release_fullcolor();
  void set_allocated_fullcolor(::std::string* fullcolor);

  // @@protoc_insertion_point(class_scope:DutyAreaRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::PointMes > point_;
  ::google::protobuf::internal::ArenaStringPtr id_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::internal::ArenaStringPtr dutyman_;
  ::google::protobuf::internal::ArenaStringPtr drawman_;
  ::google::protobuf::internal::ArenaStringPtr linecolor_;
  ::google::protobuf::internal::ArenaStringPtr fullcolor_;
  ::google::protobuf::int32 type_;
  ::google::protobuf::int32 linestyle_;
  ::google::protobuf::int32 fullstyle_;
  ::google::protobuf::int32 linewidth_;
  bool isshare_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_dutyarea_2eproto_impl();
  friend void  protobuf_AddDesc_dutyarea_2eproto_impl();
  friend void protobuf_AssignDesc_dutyarea_2eproto();
  friend void protobuf_ShutdownFile_dutyarea_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<DutyAreaRequest> DutyAreaRequest_default_instance_;

// -------------------------------------------------------------------

class DutyAreaRepsone : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:DutyAreaRepsone) */ {
 public:
  DutyAreaRepsone();
  virtual ~DutyAreaRepsone();

  DutyAreaRepsone(const DutyAreaRepsone& from);

  inline DutyAreaRepsone& operator=(const DutyAreaRepsone& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const DutyAreaRepsone& default_instance();

  static const DutyAreaRepsone* internal_default_instance();

  void Swap(DutyAreaRepsone* other);

  // implements Message ----------------------------------------------

  inline DutyAreaRepsone* New() const { return New(NULL); }

  DutyAreaRepsone* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DutyAreaRepsone& from);
  void MergeFrom(const DutyAreaRepsone& from);
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
  void InternalSwap(DutyAreaRepsone* other);
  void UnsafeMergeFrom(const DutyAreaRepsone& from);
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

  // repeated .DutyAreaRequest dutyareas = 3;
  int dutyareas_size() const;
  void clear_dutyareas();
  static const int kDutyareasFieldNumber = 3;
  const ::DutyAreaRequest& dutyareas(int index) const;
  ::DutyAreaRequest* mutable_dutyareas(int index);
  ::DutyAreaRequest* add_dutyareas();
  ::google::protobuf::RepeatedPtrField< ::DutyAreaRequest >*
      mutable_dutyareas();
  const ::google::protobuf::RepeatedPtrField< ::DutyAreaRequest >&
      dutyareas() const;

  // @@protoc_insertion_point(class_scope:DutyAreaRepsone)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::DutyAreaRequest > dutyareas_;
  ::google::protobuf::internal::ArenaStringPtr result_;
  ::google::protobuf::int32 type_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_dutyarea_2eproto_impl();
  friend void  protobuf_AddDesc_dutyarea_2eproto_impl();
  friend void protobuf_AssignDesc_dutyarea_2eproto();
  friend void protobuf_ShutdownFile_dutyarea_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<DutyAreaRepsone> DutyAreaRepsone_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// DutyAreaRequest

// optional int32 type = 1;
inline void DutyAreaRequest::clear_type() {
  type_ = 0;
}
inline ::google::protobuf::int32 DutyAreaRequest::type() const {
  // @@protoc_insertion_point(field_get:DutyAreaRequest.type)
  return type_;
}
inline void DutyAreaRequest::set_type(::google::protobuf::int32 value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:DutyAreaRequest.type)
}

// optional string ID = 2;
inline void DutyAreaRequest::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& DutyAreaRequest::id() const {
  // @@protoc_insertion_point(field_get:DutyAreaRequest.ID)
  return id_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DutyAreaRequest::set_id(const ::std::string& value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:DutyAreaRequest.ID)
}
inline void DutyAreaRequest::set_id(const char* value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:DutyAreaRequest.ID)
}
inline void DutyAreaRequest::set_id(const char* value, size_t size) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:DutyAreaRequest.ID)
}
inline ::std::string* DutyAreaRequest::mutable_id() {
  
  // @@protoc_insertion_point(field_mutable:DutyAreaRequest.ID)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* DutyAreaRequest::release_id() {
  // @@protoc_insertion_point(field_release:DutyAreaRequest.ID)
  
  return id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DutyAreaRequest::set_allocated_id(::std::string* id) {
  if (id != NULL) {
    
  } else {
    
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:DutyAreaRequest.ID)
}

// optional string name = 3;
inline void DutyAreaRequest::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& DutyAreaRequest::name() const {
  // @@protoc_insertion_point(field_get:DutyAreaRequest.name)
  return name_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DutyAreaRequest::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:DutyAreaRequest.name)
}
inline void DutyAreaRequest::set_name(const char* value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:DutyAreaRequest.name)
}
inline void DutyAreaRequest::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:DutyAreaRequest.name)
}
inline ::std::string* DutyAreaRequest::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:DutyAreaRequest.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* DutyAreaRequest::release_name() {
  // @@protoc_insertion_point(field_release:DutyAreaRequest.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DutyAreaRequest::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:DutyAreaRequest.name)
}

// repeated .PointMes point = 4;
inline int DutyAreaRequest::point_size() const {
  return point_.size();
}
inline void DutyAreaRequest::clear_point() {
  point_.Clear();
}
inline const ::PointMes& DutyAreaRequest::point(int index) const {
  // @@protoc_insertion_point(field_get:DutyAreaRequest.point)
  return point_.Get(index);
}
inline ::PointMes* DutyAreaRequest::mutable_point(int index) {
  // @@protoc_insertion_point(field_mutable:DutyAreaRequest.point)
  return point_.Mutable(index);
}
inline ::PointMes* DutyAreaRequest::add_point() {
  // @@protoc_insertion_point(field_add:DutyAreaRequest.point)
  return point_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::PointMes >*
DutyAreaRequest::mutable_point() {
  // @@protoc_insertion_point(field_mutable_list:DutyAreaRequest.point)
  return &point_;
}
inline const ::google::protobuf::RepeatedPtrField< ::PointMes >&
DutyAreaRequest::point() const {
  // @@protoc_insertion_point(field_list:DutyAreaRequest.point)
  return point_;
}

// optional int32 linestyle = 5;
inline void DutyAreaRequest::clear_linestyle() {
  linestyle_ = 0;
}
inline ::google::protobuf::int32 DutyAreaRequest::linestyle() const {
  // @@protoc_insertion_point(field_get:DutyAreaRequest.linestyle)
  return linestyle_;
}
inline void DutyAreaRequest::set_linestyle(::google::protobuf::int32 value) {
  
  linestyle_ = value;
  // @@protoc_insertion_point(field_set:DutyAreaRequest.linestyle)
}

// optional int32 fullstyle = 6;
inline void DutyAreaRequest::clear_fullstyle() {
  fullstyle_ = 0;
}
inline ::google::protobuf::int32 DutyAreaRequest::fullstyle() const {
  // @@protoc_insertion_point(field_get:DutyAreaRequest.fullstyle)
  return fullstyle_;
}
inline void DutyAreaRequest::set_fullstyle(::google::protobuf::int32 value) {
  
  fullstyle_ = value;
  // @@protoc_insertion_point(field_set:DutyAreaRequest.fullstyle)
}

// optional int32 linewidth = 7;
inline void DutyAreaRequest::clear_linewidth() {
  linewidth_ = 0;
}
inline ::google::protobuf::int32 DutyAreaRequest::linewidth() const {
  // @@protoc_insertion_point(field_get:DutyAreaRequest.linewidth)
  return linewidth_;
}
inline void DutyAreaRequest::set_linewidth(::google::protobuf::int32 value) {
  
  linewidth_ = value;
  // @@protoc_insertion_point(field_set:DutyAreaRequest.linewidth)
}

// optional string dutyman = 8;
inline void DutyAreaRequest::clear_dutyman() {
  dutyman_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& DutyAreaRequest::dutyman() const {
  // @@protoc_insertion_point(field_get:DutyAreaRequest.dutyman)
  return dutyman_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DutyAreaRequest::set_dutyman(const ::std::string& value) {
  
  dutyman_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:DutyAreaRequest.dutyman)
}
inline void DutyAreaRequest::set_dutyman(const char* value) {
  
  dutyman_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:DutyAreaRequest.dutyman)
}
inline void DutyAreaRequest::set_dutyman(const char* value, size_t size) {
  
  dutyman_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:DutyAreaRequest.dutyman)
}
inline ::std::string* DutyAreaRequest::mutable_dutyman() {
  
  // @@protoc_insertion_point(field_mutable:DutyAreaRequest.dutyman)
  return dutyman_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* DutyAreaRequest::release_dutyman() {
  // @@protoc_insertion_point(field_release:DutyAreaRequest.dutyman)
  
  return dutyman_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DutyAreaRequest::set_allocated_dutyman(::std::string* dutyman) {
  if (dutyman != NULL) {
    
  } else {
    
  }
  dutyman_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), dutyman);
  // @@protoc_insertion_point(field_set_allocated:DutyAreaRequest.dutyman)
}

// optional string drawman = 9;
inline void DutyAreaRequest::clear_drawman() {
  drawman_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& DutyAreaRequest::drawman() const {
  // @@protoc_insertion_point(field_get:DutyAreaRequest.drawman)
  return drawman_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DutyAreaRequest::set_drawman(const ::std::string& value) {
  
  drawman_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:DutyAreaRequest.drawman)
}
inline void DutyAreaRequest::set_drawman(const char* value) {
  
  drawman_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:DutyAreaRequest.drawman)
}
inline void DutyAreaRequest::set_drawman(const char* value, size_t size) {
  
  drawman_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:DutyAreaRequest.drawman)
}
inline ::std::string* DutyAreaRequest::mutable_drawman() {
  
  // @@protoc_insertion_point(field_mutable:DutyAreaRequest.drawman)
  return drawman_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* DutyAreaRequest::release_drawman() {
  // @@protoc_insertion_point(field_release:DutyAreaRequest.drawman)
  
  return drawman_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DutyAreaRequest::set_allocated_drawman(::std::string* drawman) {
  if (drawman != NULL) {
    
  } else {
    
  }
  drawman_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), drawman);
  // @@protoc_insertion_point(field_set_allocated:DutyAreaRequest.drawman)
}

// optional bool isshare = 10;
inline void DutyAreaRequest::clear_isshare() {
  isshare_ = false;
}
inline bool DutyAreaRequest::isshare() const {
  // @@protoc_insertion_point(field_get:DutyAreaRequest.isshare)
  return isshare_;
}
inline void DutyAreaRequest::set_isshare(bool value) {
  
  isshare_ = value;
  // @@protoc_insertion_point(field_set:DutyAreaRequest.isshare)
}

// optional string linecolor = 11;
inline void DutyAreaRequest::clear_linecolor() {
  linecolor_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& DutyAreaRequest::linecolor() const {
  // @@protoc_insertion_point(field_get:DutyAreaRequest.linecolor)
  return linecolor_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DutyAreaRequest::set_linecolor(const ::std::string& value) {
  
  linecolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:DutyAreaRequest.linecolor)
}
inline void DutyAreaRequest::set_linecolor(const char* value) {
  
  linecolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:DutyAreaRequest.linecolor)
}
inline void DutyAreaRequest::set_linecolor(const char* value, size_t size) {
  
  linecolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:DutyAreaRequest.linecolor)
}
inline ::std::string* DutyAreaRequest::mutable_linecolor() {
  
  // @@protoc_insertion_point(field_mutable:DutyAreaRequest.linecolor)
  return linecolor_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* DutyAreaRequest::release_linecolor() {
  // @@protoc_insertion_point(field_release:DutyAreaRequest.linecolor)
  
  return linecolor_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DutyAreaRequest::set_allocated_linecolor(::std::string* linecolor) {
  if (linecolor != NULL) {
    
  } else {
    
  }
  linecolor_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), linecolor);
  // @@protoc_insertion_point(field_set_allocated:DutyAreaRequest.linecolor)
}

// optional string fullcolor = 12;
inline void DutyAreaRequest::clear_fullcolor() {
  fullcolor_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& DutyAreaRequest::fullcolor() const {
  // @@protoc_insertion_point(field_get:DutyAreaRequest.fullcolor)
  return fullcolor_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DutyAreaRequest::set_fullcolor(const ::std::string& value) {
  
  fullcolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:DutyAreaRequest.fullcolor)
}
inline void DutyAreaRequest::set_fullcolor(const char* value) {
  
  fullcolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:DutyAreaRequest.fullcolor)
}
inline void DutyAreaRequest::set_fullcolor(const char* value, size_t size) {
  
  fullcolor_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:DutyAreaRequest.fullcolor)
}
inline ::std::string* DutyAreaRequest::mutable_fullcolor() {
  
  // @@protoc_insertion_point(field_mutable:DutyAreaRequest.fullcolor)
  return fullcolor_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* DutyAreaRequest::release_fullcolor() {
  // @@protoc_insertion_point(field_release:DutyAreaRequest.fullcolor)
  
  return fullcolor_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DutyAreaRequest::set_allocated_fullcolor(::std::string* fullcolor) {
  if (fullcolor != NULL) {
    
  } else {
    
  }
  fullcolor_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), fullcolor);
  // @@protoc_insertion_point(field_set_allocated:DutyAreaRequest.fullcolor)
}

inline const DutyAreaRequest* DutyAreaRequest::internal_default_instance() {
  return &DutyAreaRequest_default_instance_.get();
}
// -------------------------------------------------------------------

// DutyAreaRepsone

// optional int32 type = 1;
inline void DutyAreaRepsone::clear_type() {
  type_ = 0;
}
inline ::google::protobuf::int32 DutyAreaRepsone::type() const {
  // @@protoc_insertion_point(field_get:DutyAreaRepsone.type)
  return type_;
}
inline void DutyAreaRepsone::set_type(::google::protobuf::int32 value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:DutyAreaRepsone.type)
}

// optional string result = 2;
inline void DutyAreaRepsone::clear_result() {
  result_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& DutyAreaRepsone::result() const {
  // @@protoc_insertion_point(field_get:DutyAreaRepsone.result)
  return result_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DutyAreaRepsone::set_result(const ::std::string& value) {
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:DutyAreaRepsone.result)
}
inline void DutyAreaRepsone::set_result(const char* value) {
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:DutyAreaRepsone.result)
}
inline void DutyAreaRepsone::set_result(const char* value, size_t size) {
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:DutyAreaRepsone.result)
}
inline ::std::string* DutyAreaRepsone::mutable_result() {
  
  // @@protoc_insertion_point(field_mutable:DutyAreaRepsone.result)
  return result_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* DutyAreaRepsone::release_result() {
  // @@protoc_insertion_point(field_release:DutyAreaRepsone.result)
  
  return result_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DutyAreaRepsone::set_allocated_result(::std::string* result) {
  if (result != NULL) {
    
  } else {
    
  }
  result_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), result);
  // @@protoc_insertion_point(field_set_allocated:DutyAreaRepsone.result)
}

// repeated .DutyAreaRequest dutyareas = 3;
inline int DutyAreaRepsone::dutyareas_size() const {
  return dutyareas_.size();
}
inline void DutyAreaRepsone::clear_dutyareas() {
  dutyareas_.Clear();
}
inline const ::DutyAreaRequest& DutyAreaRepsone::dutyareas(int index) const {
  // @@protoc_insertion_point(field_get:DutyAreaRepsone.dutyareas)
  return dutyareas_.Get(index);
}
inline ::DutyAreaRequest* DutyAreaRepsone::mutable_dutyareas(int index) {
  // @@protoc_insertion_point(field_mutable:DutyAreaRepsone.dutyareas)
  return dutyareas_.Mutable(index);
}
inline ::DutyAreaRequest* DutyAreaRepsone::add_dutyareas() {
  // @@protoc_insertion_point(field_add:DutyAreaRepsone.dutyareas)
  return dutyareas_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::DutyAreaRequest >*
DutyAreaRepsone::mutable_dutyareas() {
  // @@protoc_insertion_point(field_mutable_list:DutyAreaRepsone.dutyareas)
  return &dutyareas_;
}
inline const ::google::protobuf::RepeatedPtrField< ::DutyAreaRequest >&
DutyAreaRepsone::dutyareas() const {
  // @@protoc_insertion_point(field_list:DutyAreaRepsone.dutyareas)
  return dutyareas_;
}

inline const DutyAreaRepsone* DutyAreaRepsone::internal_default_instance() {
  return &DutyAreaRepsone_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_dutyarea_2eproto__INCLUDED
