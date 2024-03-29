// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hgAisChange.proto

#ifndef PROTOBUF_hgAisChange_2eproto__INCLUDED
#define PROTOBUF_hgAisChange_2eproto__INCLUDED

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
void protobuf_AddDesc_hgAisChange_2eproto();
void protobuf_InitDefaults_hgAisChange_2eproto();
void protobuf_AssignDesc_hgAisChange_2eproto();
void protobuf_ShutdownFile_hgAisChange_2eproto();

class hgAisChange;
class hgAisChangeRepsone;

// ===================================================================

class hgAisChange : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:hgAisChange) */ {
 public:
  hgAisChange();
  virtual ~hgAisChange();

  hgAisChange(const hgAisChange& from);

  inline hgAisChange& operator=(const hgAisChange& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const hgAisChange& default_instance();

  static const hgAisChange* internal_default_instance();

  void Swap(hgAisChange* other);

  // implements Message ----------------------------------------------

  inline hgAisChange* New() const { return New(NULL); }

  hgAisChange* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const hgAisChange& from);
  void MergeFrom(const hgAisChange& from);
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
  void InternalSwap(hgAisChange* other);
  void UnsafeMergeFrom(const hgAisChange& from);
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

  // optional int32 Class = 2;
  void clear_class_();
  static const int kClassFieldNumber = 2;
  ::google::protobuf::int32 class_() const;
  void set_class_(::google::protobuf::int32 value);

  // optional int32 IMO = 3;
  void clear_imo();
  static const int kIMOFieldNumber = 3;
  ::google::protobuf::int32 imo() const;
  void set_imo(::google::protobuf::int32 value);

  // optional string CallSign = 4;
  void clear_callsign();
  static const int kCallSignFieldNumber = 4;
  const ::std::string& callsign() const;
  void set_callsign(const ::std::string& value);
  void set_callsign(const char* value);
  void set_callsign(const char* value, size_t size);
  ::std::string* mutable_callsign();
  ::std::string* release_callsign();
  void set_allocated_callsign(::std::string* callsign);

  // optional string EnShipName = 5;
  void clear_enshipname();
  static const int kEnShipNameFieldNumber = 5;
  const ::std::string& enshipname() const;
  void set_enshipname(const ::std::string& value);
  void set_enshipname(const char* value);
  void set_enshipname(const char* value, size_t size);
  ::std::string* mutable_enshipname();
  ::std::string* release_enshipname();
  void set_allocated_enshipname(::std::string* enshipname);

  // optional string ChShipName = 6;
  void clear_chshipname();
  static const int kChShipNameFieldNumber = 6;
  const ::std::string& chshipname() const;
  void set_chshipname(const ::std::string& value);
  void set_chshipname(const char* value);
  void set_chshipname(const char* value, size_t size);
  ::std::string* mutable_chshipname();
  ::std::string* release_chshipname();
  void set_allocated_chshipname(::std::string* chshipname);

  // optional string ShipType = 7;
  void clear_shiptype();
  static const int kShipTypeFieldNumber = 7;
  const ::std::string& shiptype() const;
  void set_shiptype(const ::std::string& value);
  void set_shiptype(const char* value);
  void set_shiptype(const char* value, size_t size);
  ::std::string* mutable_shiptype();
  ::std::string* release_shiptype();
  void set_allocated_shiptype(::std::string* shiptype);

  // optional string Nationality = 8;
  void clear_nationality();
  static const int kNationalityFieldNumber = 8;
  const ::std::string& nationality() const;
  void set_nationality(const ::std::string& value);
  void set_nationality(const char* value);
  void set_nationality(const char* value, size_t size);
  ::std::string* mutable_nationality();
  ::std::string* release_nationality();
  void set_allocated_nationality(::std::string* nationality);

  // optional int32 DimA = 9;
  void clear_dima();
  static const int kDimAFieldNumber = 9;
  ::google::protobuf::int32 dima() const;
  void set_dima(::google::protobuf::int32 value);

  // optional int32 DimB = 10;
  void clear_dimb();
  static const int kDimBFieldNumber = 10;
  ::google::protobuf::int32 dimb() const;
  void set_dimb(::google::protobuf::int32 value);

  // optional int32 DimC = 11;
  void clear_dimc();
  static const int kDimCFieldNumber = 11;
  ::google::protobuf::int32 dimc() const;
  void set_dimc(::google::protobuf::int32 value);

  // optional int32 DimD = 12;
  void clear_dimd();
  static const int kDimDFieldNumber = 12;
  ::google::protobuf::int32 dimd() const;
  void set_dimd(::google::protobuf::int32 value);

  // optional string Note = 13;
  void clear_note();
  static const int kNoteFieldNumber = 13;
  const ::std::string& note() const;
  void set_note(const ::std::string& value);
  void set_note(const char* value);
  void set_note(const char* value, size_t size);
  ::std::string* mutable_note();
  ::std::string* release_note();
  void set_allocated_note(::std::string* note);

  // @@protoc_insertion_point(class_scope:hgAisChange)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr mmsi_;
  ::google::protobuf::internal::ArenaStringPtr callsign_;
  ::google::protobuf::internal::ArenaStringPtr enshipname_;
  ::google::protobuf::internal::ArenaStringPtr chshipname_;
  ::google::protobuf::internal::ArenaStringPtr shiptype_;
  ::google::protobuf::internal::ArenaStringPtr nationality_;
  ::google::protobuf::internal::ArenaStringPtr note_;
  ::google::protobuf::int32 class__;
  ::google::protobuf::int32 imo_;
  ::google::protobuf::int32 dima_;
  ::google::protobuf::int32 dimb_;
  ::google::protobuf::int32 dimc_;
  ::google::protobuf::int32 dimd_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_hgAisChange_2eproto_impl();
  friend void  protobuf_AddDesc_hgAisChange_2eproto_impl();
  friend void protobuf_AssignDesc_hgAisChange_2eproto();
  friend void protobuf_ShutdownFile_hgAisChange_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<hgAisChange> hgAisChange_default_instance_;

// -------------------------------------------------------------------

class hgAisChangeRepsone : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:hgAisChangeRepsone) */ {
 public:
  hgAisChangeRepsone();
  virtual ~hgAisChangeRepsone();

  hgAisChangeRepsone(const hgAisChangeRepsone& from);

  inline hgAisChangeRepsone& operator=(const hgAisChangeRepsone& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const hgAisChangeRepsone& default_instance();

  static const hgAisChangeRepsone* internal_default_instance();

  void Swap(hgAisChangeRepsone* other);

  // implements Message ----------------------------------------------

  inline hgAisChangeRepsone* New() const { return New(NULL); }

  hgAisChangeRepsone* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const hgAisChangeRepsone& from);
  void MergeFrom(const hgAisChangeRepsone& from);
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
  void InternalSwap(hgAisChangeRepsone* other);
  void UnsafeMergeFrom(const hgAisChangeRepsone& from);
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

  // optional string result = 1;
  void clear_result();
  static const int kResultFieldNumber = 1;
  const ::std::string& result() const;
  void set_result(const ::std::string& value);
  void set_result(const char* value);
  void set_result(const char* value, size_t size);
  ::std::string* mutable_result();
  ::std::string* release_result();
  void set_allocated_result(::std::string* result);

  // @@protoc_insertion_point(class_scope:hgAisChangeRepsone)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr result_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_hgAisChange_2eproto_impl();
  friend void  protobuf_AddDesc_hgAisChange_2eproto_impl();
  friend void protobuf_AssignDesc_hgAisChange_2eproto();
  friend void protobuf_ShutdownFile_hgAisChange_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<hgAisChangeRepsone> hgAisChangeRepsone_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// hgAisChange

// optional string MMSI = 1;
inline void hgAisChange::clear_mmsi() {
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgAisChange::mmsi() const {
  // @@protoc_insertion_point(field_get:hgAisChange.MMSI)
  return mmsi_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgAisChange::set_mmsi(const ::std::string& value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgAisChange.MMSI)
}
inline void hgAisChange::set_mmsi(const char* value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgAisChange.MMSI)
}
inline void hgAisChange::set_mmsi(const char* value, size_t size) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgAisChange.MMSI)
}
inline ::std::string* hgAisChange::mutable_mmsi() {
  
  // @@protoc_insertion_point(field_mutable:hgAisChange.MMSI)
  return mmsi_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgAisChange::release_mmsi() {
  // @@protoc_insertion_point(field_release:hgAisChange.MMSI)
  
  return mmsi_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgAisChange::set_allocated_mmsi(::std::string* mmsi) {
  if (mmsi != NULL) {
    
  } else {
    
  }
  mmsi_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), mmsi);
  // @@protoc_insertion_point(field_set_allocated:hgAisChange.MMSI)
}

// optional int32 Class = 2;
inline void hgAisChange::clear_class_() {
  class__ = 0;
}
inline ::google::protobuf::int32 hgAisChange::class_() const {
  // @@protoc_insertion_point(field_get:hgAisChange.Class)
  return class__;
}
inline void hgAisChange::set_class_(::google::protobuf::int32 value) {
  
  class__ = value;
  // @@protoc_insertion_point(field_set:hgAisChange.Class)
}

// optional int32 IMO = 3;
inline void hgAisChange::clear_imo() {
  imo_ = 0;
}
inline ::google::protobuf::int32 hgAisChange::imo() const {
  // @@protoc_insertion_point(field_get:hgAisChange.IMO)
  return imo_;
}
inline void hgAisChange::set_imo(::google::protobuf::int32 value) {
  
  imo_ = value;
  // @@protoc_insertion_point(field_set:hgAisChange.IMO)
}

// optional string CallSign = 4;
inline void hgAisChange::clear_callsign() {
  callsign_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgAisChange::callsign() const {
  // @@protoc_insertion_point(field_get:hgAisChange.CallSign)
  return callsign_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgAisChange::set_callsign(const ::std::string& value) {
  
  callsign_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgAisChange.CallSign)
}
inline void hgAisChange::set_callsign(const char* value) {
  
  callsign_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgAisChange.CallSign)
}
inline void hgAisChange::set_callsign(const char* value, size_t size) {
  
  callsign_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgAisChange.CallSign)
}
inline ::std::string* hgAisChange::mutable_callsign() {
  
  // @@protoc_insertion_point(field_mutable:hgAisChange.CallSign)
  return callsign_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgAisChange::release_callsign() {
  // @@protoc_insertion_point(field_release:hgAisChange.CallSign)
  
  return callsign_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgAisChange::set_allocated_callsign(::std::string* callsign) {
  if (callsign != NULL) {
    
  } else {
    
  }
  callsign_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), callsign);
  // @@protoc_insertion_point(field_set_allocated:hgAisChange.CallSign)
}

// optional string EnShipName = 5;
inline void hgAisChange::clear_enshipname() {
  enshipname_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgAisChange::enshipname() const {
  // @@protoc_insertion_point(field_get:hgAisChange.EnShipName)
  return enshipname_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgAisChange::set_enshipname(const ::std::string& value) {
  
  enshipname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgAisChange.EnShipName)
}
inline void hgAisChange::set_enshipname(const char* value) {
  
  enshipname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgAisChange.EnShipName)
}
inline void hgAisChange::set_enshipname(const char* value, size_t size) {
  
  enshipname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgAisChange.EnShipName)
}
inline ::std::string* hgAisChange::mutable_enshipname() {
  
  // @@protoc_insertion_point(field_mutable:hgAisChange.EnShipName)
  return enshipname_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgAisChange::release_enshipname() {
  // @@protoc_insertion_point(field_release:hgAisChange.EnShipName)
  
  return enshipname_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgAisChange::set_allocated_enshipname(::std::string* enshipname) {
  if (enshipname != NULL) {
    
  } else {
    
  }
  enshipname_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), enshipname);
  // @@protoc_insertion_point(field_set_allocated:hgAisChange.EnShipName)
}

// optional string ChShipName = 6;
inline void hgAisChange::clear_chshipname() {
  chshipname_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgAisChange::chshipname() const {
  // @@protoc_insertion_point(field_get:hgAisChange.ChShipName)
  return chshipname_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgAisChange::set_chshipname(const ::std::string& value) {
  
  chshipname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgAisChange.ChShipName)
}
inline void hgAisChange::set_chshipname(const char* value) {
  
  chshipname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgAisChange.ChShipName)
}
inline void hgAisChange::set_chshipname(const char* value, size_t size) {
  
  chshipname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgAisChange.ChShipName)
}
inline ::std::string* hgAisChange::mutable_chshipname() {
  
  // @@protoc_insertion_point(field_mutable:hgAisChange.ChShipName)
  return chshipname_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgAisChange::release_chshipname() {
  // @@protoc_insertion_point(field_release:hgAisChange.ChShipName)
  
  return chshipname_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgAisChange::set_allocated_chshipname(::std::string* chshipname) {
  if (chshipname != NULL) {
    
  } else {
    
  }
  chshipname_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), chshipname);
  // @@protoc_insertion_point(field_set_allocated:hgAisChange.ChShipName)
}

// optional string ShipType = 7;
inline void hgAisChange::clear_shiptype() {
  shiptype_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgAisChange::shiptype() const {
  // @@protoc_insertion_point(field_get:hgAisChange.ShipType)
  return shiptype_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgAisChange::set_shiptype(const ::std::string& value) {
  
  shiptype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgAisChange.ShipType)
}
inline void hgAisChange::set_shiptype(const char* value) {
  
  shiptype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgAisChange.ShipType)
}
inline void hgAisChange::set_shiptype(const char* value, size_t size) {
  
  shiptype_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgAisChange.ShipType)
}
inline ::std::string* hgAisChange::mutable_shiptype() {
  
  // @@protoc_insertion_point(field_mutable:hgAisChange.ShipType)
  return shiptype_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgAisChange::release_shiptype() {
  // @@protoc_insertion_point(field_release:hgAisChange.ShipType)
  
  return shiptype_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgAisChange::set_allocated_shiptype(::std::string* shiptype) {
  if (shiptype != NULL) {
    
  } else {
    
  }
  shiptype_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), shiptype);
  // @@protoc_insertion_point(field_set_allocated:hgAisChange.ShipType)
}

// optional string Nationality = 8;
inline void hgAisChange::clear_nationality() {
  nationality_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgAisChange::nationality() const {
  // @@protoc_insertion_point(field_get:hgAisChange.Nationality)
  return nationality_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgAisChange::set_nationality(const ::std::string& value) {
  
  nationality_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgAisChange.Nationality)
}
inline void hgAisChange::set_nationality(const char* value) {
  
  nationality_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgAisChange.Nationality)
}
inline void hgAisChange::set_nationality(const char* value, size_t size) {
  
  nationality_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgAisChange.Nationality)
}
inline ::std::string* hgAisChange::mutable_nationality() {
  
  // @@protoc_insertion_point(field_mutable:hgAisChange.Nationality)
  return nationality_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgAisChange::release_nationality() {
  // @@protoc_insertion_point(field_release:hgAisChange.Nationality)
  
  return nationality_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgAisChange::set_allocated_nationality(::std::string* nationality) {
  if (nationality != NULL) {
    
  } else {
    
  }
  nationality_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), nationality);
  // @@protoc_insertion_point(field_set_allocated:hgAisChange.Nationality)
}

// optional int32 DimA = 9;
inline void hgAisChange::clear_dima() {
  dima_ = 0;
}
inline ::google::protobuf::int32 hgAisChange::dima() const {
  // @@protoc_insertion_point(field_get:hgAisChange.DimA)
  return dima_;
}
inline void hgAisChange::set_dima(::google::protobuf::int32 value) {
  
  dima_ = value;
  // @@protoc_insertion_point(field_set:hgAisChange.DimA)
}

// optional int32 DimB = 10;
inline void hgAisChange::clear_dimb() {
  dimb_ = 0;
}
inline ::google::protobuf::int32 hgAisChange::dimb() const {
  // @@protoc_insertion_point(field_get:hgAisChange.DimB)
  return dimb_;
}
inline void hgAisChange::set_dimb(::google::protobuf::int32 value) {
  
  dimb_ = value;
  // @@protoc_insertion_point(field_set:hgAisChange.DimB)
}

// optional int32 DimC = 11;
inline void hgAisChange::clear_dimc() {
  dimc_ = 0;
}
inline ::google::protobuf::int32 hgAisChange::dimc() const {
  // @@protoc_insertion_point(field_get:hgAisChange.DimC)
  return dimc_;
}
inline void hgAisChange::set_dimc(::google::protobuf::int32 value) {
  
  dimc_ = value;
  // @@protoc_insertion_point(field_set:hgAisChange.DimC)
}

// optional int32 DimD = 12;
inline void hgAisChange::clear_dimd() {
  dimd_ = 0;
}
inline ::google::protobuf::int32 hgAisChange::dimd() const {
  // @@protoc_insertion_point(field_get:hgAisChange.DimD)
  return dimd_;
}
inline void hgAisChange::set_dimd(::google::protobuf::int32 value) {
  
  dimd_ = value;
  // @@protoc_insertion_point(field_set:hgAisChange.DimD)
}

// optional string Note = 13;
inline void hgAisChange::clear_note() {
  note_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgAisChange::note() const {
  // @@protoc_insertion_point(field_get:hgAisChange.Note)
  return note_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgAisChange::set_note(const ::std::string& value) {
  
  note_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgAisChange.Note)
}
inline void hgAisChange::set_note(const char* value) {
  
  note_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgAisChange.Note)
}
inline void hgAisChange::set_note(const char* value, size_t size) {
  
  note_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgAisChange.Note)
}
inline ::std::string* hgAisChange::mutable_note() {
  
  // @@protoc_insertion_point(field_mutable:hgAisChange.Note)
  return note_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgAisChange::release_note() {
  // @@protoc_insertion_point(field_release:hgAisChange.Note)
  
  return note_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgAisChange::set_allocated_note(::std::string* note) {
  if (note != NULL) {
    
  } else {
    
  }
  note_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), note);
  // @@protoc_insertion_point(field_set_allocated:hgAisChange.Note)
}

inline const hgAisChange* hgAisChange::internal_default_instance() {
  return &hgAisChange_default_instance_.get();
}
// -------------------------------------------------------------------

// hgAisChangeRepsone

// optional string result = 1;
inline void hgAisChangeRepsone::clear_result() {
  result_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgAisChangeRepsone::result() const {
  // @@protoc_insertion_point(field_get:hgAisChangeRepsone.result)
  return result_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgAisChangeRepsone::set_result(const ::std::string& value) {
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgAisChangeRepsone.result)
}
inline void hgAisChangeRepsone::set_result(const char* value) {
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgAisChangeRepsone.result)
}
inline void hgAisChangeRepsone::set_result(const char* value, size_t size) {
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgAisChangeRepsone.result)
}
inline ::std::string* hgAisChangeRepsone::mutable_result() {
  
  // @@protoc_insertion_point(field_mutable:hgAisChangeRepsone.result)
  return result_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgAisChangeRepsone::release_result() {
  // @@protoc_insertion_point(field_release:hgAisChangeRepsone.result)
  
  return result_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgAisChangeRepsone::set_allocated_result(::std::string* result) {
  if (result != NULL) {
    
  } else {
    
  }
  result_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), result);
  // @@protoc_insertion_point(field_set_allocated:hgAisChangeRepsone.result)
}

inline const hgAisChangeRepsone* hgAisChangeRepsone::internal_default_instance() {
  return &hgAisChangeRepsone_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_hgAisChange_2eproto__INCLUDED
