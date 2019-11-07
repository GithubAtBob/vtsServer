// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AlgorithmMode.proto

#ifndef PROTOBUF_AlgorithmMode_2eproto__INCLUDED
#define PROTOBUF_AlgorithmMode_2eproto__INCLUDED

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
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_AlgorithmMode_2eproto();
void protobuf_InitDefaults_AlgorithmMode_2eproto();
void protobuf_AssignDesc_AlgorithmMode_2eproto();
void protobuf_ShutdownFile_AlgorithmMode_2eproto();

class hgAlgorithmMode;

enum AlgorithmModeType {
  EarlyModel = 0,
  ManualModel = 1,
  AutoModel = 2,
  NoneModel = 3,
  AskModel = 4,
  SetModel = 5,
  SetManualModel = 6,
  SetAutoModel = 7,
  AlgorithmModeType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  AlgorithmModeType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool AlgorithmModeType_IsValid(int value);
const AlgorithmModeType AlgorithmModeType_MIN = EarlyModel;
const AlgorithmModeType AlgorithmModeType_MAX = SetAutoModel;
const int AlgorithmModeType_ARRAYSIZE = AlgorithmModeType_MAX + 1;

const ::google::protobuf::EnumDescriptor* AlgorithmModeType_descriptor();
inline const ::std::string& AlgorithmModeType_Name(AlgorithmModeType value) {
  return ::google::protobuf::internal::NameOfEnum(
    AlgorithmModeType_descriptor(), value);
}
inline bool AlgorithmModeType_Parse(
    const ::std::string& name, AlgorithmModeType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<AlgorithmModeType>(
    AlgorithmModeType_descriptor(), name, value);
}
// ===================================================================

class hgAlgorithmMode : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:hgAlgorithmMode) */ {
 public:
  hgAlgorithmMode();
  virtual ~hgAlgorithmMode();

  hgAlgorithmMode(const hgAlgorithmMode& from);

  inline hgAlgorithmMode& operator=(const hgAlgorithmMode& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const hgAlgorithmMode& default_instance();

  static const hgAlgorithmMode* internal_default_instance();

  void Swap(hgAlgorithmMode* other);

  // implements Message ----------------------------------------------

  inline hgAlgorithmMode* New() const { return New(NULL); }

  hgAlgorithmMode* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const hgAlgorithmMode& from);
  void MergeFrom(const hgAlgorithmMode& from);
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
  void InternalSwap(hgAlgorithmMode* other);
  void UnsafeMergeFrom(const hgAlgorithmMode& from);
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

  // optional int32 mode = 1;
  void clear_mode();
  static const int kModeFieldNumber = 1;
  ::google::protobuf::int32 mode() const;
  void set_mode(::google::protobuf::int32 value);

  // optional double alarm1 = 2;
  void clear_alarm1();
  static const int kAlarm1FieldNumber = 2;
  double alarm1() const;
  void set_alarm1(double value);

  // optional double alarm2 = 3;
  void clear_alarm2();
  static const int kAlarm2FieldNumber = 3;
  double alarm2() const;
  void set_alarm2(double value);

  // optional double alarm3 = 4;
  void clear_alarm3();
  static const int kAlarm3FieldNumber = 4;
  double alarm3() const;
  void set_alarm3(double value);

  // @@protoc_insertion_point(class_scope:hgAlgorithmMode)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  double alarm1_;
  double alarm2_;
  double alarm3_;
  ::google::protobuf::int32 mode_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_AlgorithmMode_2eproto_impl();
  friend void  protobuf_AddDesc_AlgorithmMode_2eproto_impl();
  friend void protobuf_AssignDesc_AlgorithmMode_2eproto();
  friend void protobuf_ShutdownFile_AlgorithmMode_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<hgAlgorithmMode> hgAlgorithmMode_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// hgAlgorithmMode

// optional int32 mode = 1;
inline void hgAlgorithmMode::clear_mode() {
  mode_ = 0;
}
inline ::google::protobuf::int32 hgAlgorithmMode::mode() const {
  // @@protoc_insertion_point(field_get:hgAlgorithmMode.mode)
  return mode_;
}
inline void hgAlgorithmMode::set_mode(::google::protobuf::int32 value) {
  
  mode_ = value;
  // @@protoc_insertion_point(field_set:hgAlgorithmMode.mode)
}

// optional double alarm1 = 2;
inline void hgAlgorithmMode::clear_alarm1() {
  alarm1_ = 0;
}
inline double hgAlgorithmMode::alarm1() const {
  // @@protoc_insertion_point(field_get:hgAlgorithmMode.alarm1)
  return alarm1_;
}
inline void hgAlgorithmMode::set_alarm1(double value) {
  
  alarm1_ = value;
  // @@protoc_insertion_point(field_set:hgAlgorithmMode.alarm1)
}

// optional double alarm2 = 3;
inline void hgAlgorithmMode::clear_alarm2() {
  alarm2_ = 0;
}
inline double hgAlgorithmMode::alarm2() const {
  // @@protoc_insertion_point(field_get:hgAlgorithmMode.alarm2)
  return alarm2_;
}
inline void hgAlgorithmMode::set_alarm2(double value) {
  
  alarm2_ = value;
  // @@protoc_insertion_point(field_set:hgAlgorithmMode.alarm2)
}

// optional double alarm3 = 4;
inline void hgAlgorithmMode::clear_alarm3() {
  alarm3_ = 0;
}
inline double hgAlgorithmMode::alarm3() const {
  // @@protoc_insertion_point(field_get:hgAlgorithmMode.alarm3)
  return alarm3_;
}
inline void hgAlgorithmMode::set_alarm3(double value) {
  
  alarm3_ = value;
  // @@protoc_insertion_point(field_set:hgAlgorithmMode.alarm3)
}

inline const hgAlgorithmMode* hgAlgorithmMode::internal_default_instance() {
  return &hgAlgorithmMode_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::AlgorithmModeType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::AlgorithmModeType>() {
  return ::AlgorithmModeType_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_AlgorithmMode_2eproto__INCLUDED