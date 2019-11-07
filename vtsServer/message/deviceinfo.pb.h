// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: deviceinfo.proto

#ifndef PROTOBUF_deviceinfo_2eproto__INCLUDED
#define PROTOBUF_deviceinfo_2eproto__INCLUDED

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
void protobuf_AddDesc_deviceinfo_2eproto();
void protobuf_InitDefaults_deviceinfo_2eproto();
void protobuf_AssignDesc_deviceinfo_2eproto();
void protobuf_ShutdownFile_deviceinfo_2eproto();

class Device;
class DeviceDetail;

enum DeviceType {
  DeviceAIS = 0,
  DeviceCCTV = 1,
  DeviceVHF = 2,
  DeviceRadar = 3,
  DeviceTrack = 4,
  DeviceMeteo = 5,
  DeviceSQL = 6,
  DeviceServer = 7,
  DeviceType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  DeviceType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool DeviceType_IsValid(int value);
const DeviceType DeviceType_MIN = DeviceAIS;
const DeviceType DeviceType_MAX = DeviceServer;
const int DeviceType_ARRAYSIZE = DeviceType_MAX + 1;

const ::google::protobuf::EnumDescriptor* DeviceType_descriptor();
inline const ::std::string& DeviceType_Name(DeviceType value) {
  return ::google::protobuf::internal::NameOfEnum(
    DeviceType_descriptor(), value);
}
inline bool DeviceType_Parse(
    const ::std::string& name, DeviceType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<DeviceType>(
    DeviceType_descriptor(), name, value);
}
// ===================================================================

class Device : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Device) */ {
 public:
  Device();
  virtual ~Device();

  Device(const Device& from);

  inline Device& operator=(const Device& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Device& default_instance();

  static const Device* internal_default_instance();

  void Swap(Device* other);

  // implements Message ----------------------------------------------

  inline Device* New() const { return New(NULL); }

  Device* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Device& from);
  void MergeFrom(const Device& from);
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
  void InternalSwap(Device* other);
  void UnsafeMergeFrom(const Device& from);
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

  // optional .DeviceType type = 1;
  void clear_type();
  static const int kTypeFieldNumber = 1;
  ::DeviceType type() const;
  void set_type(::DeviceType value);

  // optional bool status = 3;
  void clear_status();
  static const int kStatusFieldNumber = 3;
  bool status() const;
  void set_status(bool value);

  // @@protoc_insertion_point(class_scope:Device)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  int type_;
  bool status_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_deviceinfo_2eproto_impl();
  friend void  protobuf_AddDesc_deviceinfo_2eproto_impl();
  friend void protobuf_AssignDesc_deviceinfo_2eproto();
  friend void protobuf_ShutdownFile_deviceinfo_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<Device> Device_default_instance_;

// -------------------------------------------------------------------

class DeviceDetail : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:DeviceDetail) */ {
 public:
  DeviceDetail();
  virtual ~DeviceDetail();

  DeviceDetail(const DeviceDetail& from);

  inline DeviceDetail& operator=(const DeviceDetail& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const DeviceDetail& default_instance();

  static const DeviceDetail* internal_default_instance();

  void Swap(DeviceDetail* other);

  // implements Message ----------------------------------------------

  inline DeviceDetail* New() const { return New(NULL); }

  DeviceDetail* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const DeviceDetail& from);
  void MergeFrom(const DeviceDetail& from);
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
  void InternalSwap(DeviceDetail* other);
  void UnsafeMergeFrom(const DeviceDetail& from);
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

  // optional string DeviceName = 1;
  void clear_devicename();
  static const int kDeviceNameFieldNumber = 1;
  const ::std::string& devicename() const;
  void set_devicename(const ::std::string& value);
  void set_devicename(const char* value);
  void set_devicename(const char* value, size_t size);
  ::std::string* mutable_devicename();
  ::std::string* release_devicename();
  void set_allocated_devicename(::std::string* devicename);

  // optional string MonitorName = 2;
  void clear_monitorname();
  static const int kMonitorNameFieldNumber = 2;
  const ::std::string& monitorname() const;
  void set_monitorname(const ::std::string& value);
  void set_monitorname(const char* value);
  void set_monitorname(const char* value, size_t size);
  ::std::string* mutable_monitorname();
  ::std::string* release_monitorname();
  void set_allocated_monitorname(::std::string* monitorname);

  // optional bool status = 3;
  void clear_status();
  static const int kStatusFieldNumber = 3;
  bool status() const;
  void set_status(bool value);

  // optional int64 time = 4;
  void clear_time();
  static const int kTimeFieldNumber = 4;
  ::google::protobuf::int64 time() const;
  void set_time(::google::protobuf::int64 value);

  // @@protoc_insertion_point(class_scope:DeviceDetail)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr devicename_;
  ::google::protobuf::internal::ArenaStringPtr monitorname_;
  ::google::protobuf::int64 time_;
  bool status_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_deviceinfo_2eproto_impl();
  friend void  protobuf_AddDesc_deviceinfo_2eproto_impl();
  friend void protobuf_AssignDesc_deviceinfo_2eproto();
  friend void protobuf_ShutdownFile_deviceinfo_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<DeviceDetail> DeviceDetail_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Device

// optional .DeviceType type = 1;
inline void Device::clear_type() {
  type_ = 0;
}
inline ::DeviceType Device::type() const {
  // @@protoc_insertion_point(field_get:Device.type)
  return static_cast< ::DeviceType >(type_);
}
inline void Device::set_type(::DeviceType value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:Device.type)
}

// optional bool status = 3;
inline void Device::clear_status() {
  status_ = false;
}
inline bool Device::status() const {
  // @@protoc_insertion_point(field_get:Device.status)
  return status_;
}
inline void Device::set_status(bool value) {
  
  status_ = value;
  // @@protoc_insertion_point(field_set:Device.status)
}

inline const Device* Device::internal_default_instance() {
  return &Device_default_instance_.get();
}
// -------------------------------------------------------------------

// DeviceDetail

// optional string DeviceName = 1;
inline void DeviceDetail::clear_devicename() {
  devicename_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& DeviceDetail::devicename() const {
  // @@protoc_insertion_point(field_get:DeviceDetail.DeviceName)
  return devicename_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DeviceDetail::set_devicename(const ::std::string& value) {
  
  devicename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:DeviceDetail.DeviceName)
}
inline void DeviceDetail::set_devicename(const char* value) {
  
  devicename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:DeviceDetail.DeviceName)
}
inline void DeviceDetail::set_devicename(const char* value, size_t size) {
  
  devicename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:DeviceDetail.DeviceName)
}
inline ::std::string* DeviceDetail::mutable_devicename() {
  
  // @@protoc_insertion_point(field_mutable:DeviceDetail.DeviceName)
  return devicename_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* DeviceDetail::release_devicename() {
  // @@protoc_insertion_point(field_release:DeviceDetail.DeviceName)
  
  return devicename_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DeviceDetail::set_allocated_devicename(::std::string* devicename) {
  if (devicename != NULL) {
    
  } else {
    
  }
  devicename_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), devicename);
  // @@protoc_insertion_point(field_set_allocated:DeviceDetail.DeviceName)
}

// optional string MonitorName = 2;
inline void DeviceDetail::clear_monitorname() {
  monitorname_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& DeviceDetail::monitorname() const {
  // @@protoc_insertion_point(field_get:DeviceDetail.MonitorName)
  return monitorname_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DeviceDetail::set_monitorname(const ::std::string& value) {
  
  monitorname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:DeviceDetail.MonitorName)
}
inline void DeviceDetail::set_monitorname(const char* value) {
  
  monitorname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:DeviceDetail.MonitorName)
}
inline void DeviceDetail::set_monitorname(const char* value, size_t size) {
  
  monitorname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:DeviceDetail.MonitorName)
}
inline ::std::string* DeviceDetail::mutable_monitorname() {
  
  // @@protoc_insertion_point(field_mutable:DeviceDetail.MonitorName)
  return monitorname_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* DeviceDetail::release_monitorname() {
  // @@protoc_insertion_point(field_release:DeviceDetail.MonitorName)
  
  return monitorname_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void DeviceDetail::set_allocated_monitorname(::std::string* monitorname) {
  if (monitorname != NULL) {
    
  } else {
    
  }
  monitorname_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), monitorname);
  // @@protoc_insertion_point(field_set_allocated:DeviceDetail.MonitorName)
}

// optional bool status = 3;
inline void DeviceDetail::clear_status() {
  status_ = false;
}
inline bool DeviceDetail::status() const {
  // @@protoc_insertion_point(field_get:DeviceDetail.status)
  return status_;
}
inline void DeviceDetail::set_status(bool value) {
  
  status_ = value;
  // @@protoc_insertion_point(field_set:DeviceDetail.status)
}

// optional int64 time = 4;
inline void DeviceDetail::clear_time() {
  time_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 DeviceDetail::time() const {
  // @@protoc_insertion_point(field_get:DeviceDetail.time)
  return time_;
}
inline void DeviceDetail::set_time(::google::protobuf::int64 value) {
  
  time_ = value;
  // @@protoc_insertion_point(field_set:DeviceDetail.time)
}

inline const DeviceDetail* DeviceDetail::internal_default_instance() {
  return &DeviceDetail_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::DeviceType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::DeviceType>() {
  return ::DeviceType_descriptor();
}

}  // namespace protobuf
}  // namespace google
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_deviceinfo_2eproto__INCLUDED
