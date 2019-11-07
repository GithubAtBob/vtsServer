// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hgDomain.proto

#ifndef PROTOBUF_hgDomain_2eproto__INCLUDED
#define PROTOBUF_hgDomain_2eproto__INCLUDED

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
void protobuf_AddDesc_hgDomain_2eproto();
void protobuf_InitDefaults_hgDomain_2eproto();
void protobuf_AssignDesc_hgDomain_2eproto();
void protobuf_ShutdownFile_hgDomain_2eproto();

class hgDomain;
class hgDomainRepsone;

// ===================================================================

class hgDomain : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:hgDomain) */ {
 public:
  hgDomain();
  virtual ~hgDomain();

  hgDomain(const hgDomain& from);

  inline hgDomain& operator=(const hgDomain& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const hgDomain& default_instance();

  static const hgDomain* internal_default_instance();

  void Swap(hgDomain* other);

  // implements Message ----------------------------------------------

  inline hgDomain* New() const { return New(NULL); }

  hgDomain* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const hgDomain& from);
  void MergeFrom(const hgDomain& from);
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
  void InternalSwap(hgDomain* other);
  void UnsafeMergeFrom(const hgDomain& from);
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

  // optional bool DomainWatch = 2;
  void clear_domainwatch();
  static const int kDomainWatchFieldNumber = 2;
  bool domainwatch() const;
  void set_domainwatch(bool value);

  // optional double DomainRadius = 3;
  void clear_domainradius();
  static const int kDomainRadiusFieldNumber = 3;
  double domainradius() const;
  void set_domainradius(double value);

  // optional int32 DomainColorR = 4;
  void clear_domaincolorr();
  static const int kDomainColorRFieldNumber = 4;
  ::google::protobuf::int32 domaincolorr() const;
  void set_domaincolorr(::google::protobuf::int32 value);

  // optional int32 DomainColorG = 5;
  void clear_domaincolorg();
  static const int kDomainColorGFieldNumber = 5;
  ::google::protobuf::int32 domaincolorg() const;
  void set_domaincolorg(::google::protobuf::int32 value);

  // optional int32 DomainColorB = 6;
  void clear_domaincolorb();
  static const int kDomainColorBFieldNumber = 6;
  ::google::protobuf::int32 domaincolorb() const;
  void set_domaincolorb(::google::protobuf::int32 value);

  // optional bool DomainShow = 7;
  void clear_domainshow();
  static const int kDomainShowFieldNumber = 7;
  bool domainshow() const;
  void set_domainshow(bool value);

  // @@protoc_insertion_point(class_scope:hgDomain)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr mmsi_;
  double domainradius_;
  ::google::protobuf::int32 domaincolorr_;
  bool domainwatch_;
  bool domainshow_;
  ::google::protobuf::int32 domaincolorg_;
  ::google::protobuf::int32 domaincolorb_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_hgDomain_2eproto_impl();
  friend void  protobuf_AddDesc_hgDomain_2eproto_impl();
  friend void protobuf_AssignDesc_hgDomain_2eproto();
  friend void protobuf_ShutdownFile_hgDomain_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<hgDomain> hgDomain_default_instance_;

// -------------------------------------------------------------------

class hgDomainRepsone : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:hgDomainRepsone) */ {
 public:
  hgDomainRepsone();
  virtual ~hgDomainRepsone();

  hgDomainRepsone(const hgDomainRepsone& from);

  inline hgDomainRepsone& operator=(const hgDomainRepsone& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const hgDomainRepsone& default_instance();

  static const hgDomainRepsone* internal_default_instance();

  void Swap(hgDomainRepsone* other);

  // implements Message ----------------------------------------------

  inline hgDomainRepsone* New() const { return New(NULL); }

  hgDomainRepsone* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const hgDomainRepsone& from);
  void MergeFrom(const hgDomainRepsone& from);
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
  void InternalSwap(hgDomainRepsone* other);
  void UnsafeMergeFrom(const hgDomainRepsone& from);
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

  // @@protoc_insertion_point(class_scope:hgDomainRepsone)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_hgDomain_2eproto_impl();
  friend void  protobuf_AddDesc_hgDomain_2eproto_impl();
  friend void protobuf_AssignDesc_hgDomain_2eproto();
  friend void protobuf_ShutdownFile_hgDomain_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<hgDomainRepsone> hgDomainRepsone_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// hgDomain

// optional string MMSI = 1;
inline void hgDomain::clear_mmsi() {
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgDomain::mmsi() const {
  // @@protoc_insertion_point(field_get:hgDomain.MMSI)
  return mmsi_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgDomain::set_mmsi(const ::std::string& value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgDomain.MMSI)
}
inline void hgDomain::set_mmsi(const char* value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgDomain.MMSI)
}
inline void hgDomain::set_mmsi(const char* value, size_t size) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgDomain.MMSI)
}
inline ::std::string* hgDomain::mutable_mmsi() {
  
  // @@protoc_insertion_point(field_mutable:hgDomain.MMSI)
  return mmsi_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgDomain::release_mmsi() {
  // @@protoc_insertion_point(field_release:hgDomain.MMSI)
  
  return mmsi_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgDomain::set_allocated_mmsi(::std::string* mmsi) {
  if (mmsi != NULL) {
    
  } else {
    
  }
  mmsi_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), mmsi);
  // @@protoc_insertion_point(field_set_allocated:hgDomain.MMSI)
}

// optional bool DomainWatch = 2;
inline void hgDomain::clear_domainwatch() {
  domainwatch_ = false;
}
inline bool hgDomain::domainwatch() const {
  // @@protoc_insertion_point(field_get:hgDomain.DomainWatch)
  return domainwatch_;
}
inline void hgDomain::set_domainwatch(bool value) {
  
  domainwatch_ = value;
  // @@protoc_insertion_point(field_set:hgDomain.DomainWatch)
}

// optional double DomainRadius = 3;
inline void hgDomain::clear_domainradius() {
  domainradius_ = 0;
}
inline double hgDomain::domainradius() const {
  // @@protoc_insertion_point(field_get:hgDomain.DomainRadius)
  return domainradius_;
}
inline void hgDomain::set_domainradius(double value) {
  
  domainradius_ = value;
  // @@protoc_insertion_point(field_set:hgDomain.DomainRadius)
}

// optional int32 DomainColorR = 4;
inline void hgDomain::clear_domaincolorr() {
  domaincolorr_ = 0;
}
inline ::google::protobuf::int32 hgDomain::domaincolorr() const {
  // @@protoc_insertion_point(field_get:hgDomain.DomainColorR)
  return domaincolorr_;
}
inline void hgDomain::set_domaincolorr(::google::protobuf::int32 value) {
  
  domaincolorr_ = value;
  // @@protoc_insertion_point(field_set:hgDomain.DomainColorR)
}

// optional int32 DomainColorG = 5;
inline void hgDomain::clear_domaincolorg() {
  domaincolorg_ = 0;
}
inline ::google::protobuf::int32 hgDomain::domaincolorg() const {
  // @@protoc_insertion_point(field_get:hgDomain.DomainColorG)
  return domaincolorg_;
}
inline void hgDomain::set_domaincolorg(::google::protobuf::int32 value) {
  
  domaincolorg_ = value;
  // @@protoc_insertion_point(field_set:hgDomain.DomainColorG)
}

// optional int32 DomainColorB = 6;
inline void hgDomain::clear_domaincolorb() {
  domaincolorb_ = 0;
}
inline ::google::protobuf::int32 hgDomain::domaincolorb() const {
  // @@protoc_insertion_point(field_get:hgDomain.DomainColorB)
  return domaincolorb_;
}
inline void hgDomain::set_domaincolorb(::google::protobuf::int32 value) {
  
  domaincolorb_ = value;
  // @@protoc_insertion_point(field_set:hgDomain.DomainColorB)
}

// optional bool DomainShow = 7;
inline void hgDomain::clear_domainshow() {
  domainshow_ = false;
}
inline bool hgDomain::domainshow() const {
  // @@protoc_insertion_point(field_get:hgDomain.DomainShow)
  return domainshow_;
}
inline void hgDomain::set_domainshow(bool value) {
  
  domainshow_ = value;
  // @@protoc_insertion_point(field_set:hgDomain.DomainShow)
}

inline const hgDomain* hgDomain::internal_default_instance() {
  return &hgDomain_default_instance_.get();
}
// -------------------------------------------------------------------

// hgDomainRepsone

inline const hgDomainRepsone* hgDomainRepsone::internal_default_instance() {
  return &hgDomainRepsone_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_hgDomain_2eproto__INCLUDED