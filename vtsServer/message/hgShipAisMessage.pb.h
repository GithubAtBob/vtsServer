// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hgShipAisMessage.proto

#ifndef PROTOBUF_hgShipAisMessage_2eproto__INCLUDED
#define PROTOBUF_hgShipAisMessage_2eproto__INCLUDED

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
void protobuf_AddDesc_hgShipAisMessage_2eproto();
void protobuf_InitDefaults_hgShipAisMessage_2eproto();
void protobuf_AssignDesc_hgShipAisMessage_2eproto();
void protobuf_ShutdownFile_hgShipAisMessage_2eproto();

class hgShipAisMessage;

// ===================================================================

class hgShipAisMessage : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:hgShipAisMessage) */ {
 public:
  hgShipAisMessage();
  virtual ~hgShipAisMessage();

  hgShipAisMessage(const hgShipAisMessage& from);

  inline hgShipAisMessage& operator=(const hgShipAisMessage& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const hgShipAisMessage& default_instance();

  static const hgShipAisMessage* internal_default_instance();

  void Swap(hgShipAisMessage* other);

  // implements Message ----------------------------------------------

  inline hgShipAisMessage* New() const { return New(NULL); }

  hgShipAisMessage* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const hgShipAisMessage& from);
  void MergeFrom(const hgShipAisMessage& from);
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
  void InternalSwap(hgShipAisMessage* other);
  void UnsafeMergeFrom(const hgShipAisMessage& from);
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

  // optional string ID = 1;
  void clear_id();
  static const int kIDFieldNumber = 1;
  const ::std::string& id() const;
  void set_id(const ::std::string& value);
  void set_id(const char* value);
  void set_id(const char* value, size_t size);
  ::std::string* mutable_id();
  ::std::string* release_id();
  void set_allocated_id(::std::string* id);

  // optional string MMSI = 2;
  void clear_mmsi();
  static const int kMMSIFieldNumber = 2;
  const ::std::string& mmsi() const;
  void set_mmsi(const ::std::string& value);
  void set_mmsi(const char* value);
  void set_mmsi(const char* value, size_t size);
  ::std::string* mutable_mmsi();
  ::std::string* release_mmsi();
  void set_allocated_mmsi(::std::string* mmsi);

  // optional double SOG = 3;
  void clear_sog();
  static const int kSOGFieldNumber = 3;
  double sog() const;
  void set_sog(double value);

  // optional double Lon = 4;
  void clear_lon();
  static const int kLonFieldNumber = 4;
  double lon() const;
  void set_lon(double value);

  // optional double Lat = 5;
  void clear_lat();
  static const int kLatFieldNumber = 5;
  double lat() const;
  void set_lat(double value);

  // optional double COG = 6;
  void clear_cog();
  static const int kCOGFieldNumber = 6;
  double cog() const;
  void set_cog(double value);

  // optional double HDG = 7;
  void clear_hdg();
  static const int kHDGFieldNumber = 7;
  double hdg() const;
  void set_hdg(double value);

  // optional double Length = 8;
  void clear_length();
  static const int kLengthFieldNumber = 8;
  double length() const;
  void set_length(double value);

  // optional double Width = 9;
  void clear_width();
  static const int kWidthFieldNumber = 9;
  double width() const;
  void set_width(double value);

  // optional int32 DimA = 10;
  void clear_dima();
  static const int kDimAFieldNumber = 10;
  ::google::protobuf::int32 dima() const;
  void set_dima(::google::protobuf::int32 value);

  // optional int32 DimB = 11;
  void clear_dimb();
  static const int kDimBFieldNumber = 11;
  ::google::protobuf::int32 dimb() const;
  void set_dimb(::google::protobuf::int32 value);

  // optional int32 DimC = 12;
  void clear_dimc();
  static const int kDimCFieldNumber = 12;
  ::google::protobuf::int32 dimc() const;
  void set_dimc(::google::protobuf::int32 value);

  // optional int32 DimD = 13;
  void clear_dimd();
  static const int kDimDFieldNumber = 13;
  ::google::protobuf::int32 dimd() const;
  void set_dimd(::google::protobuf::int32 value);

  // optional int64 ReportTicks = 14;
  void clear_reportticks();
  static const int kReportTicksFieldNumber = 14;
  ::google::protobuf::int64 reportticks() const;
  void set_reportticks(::google::protobuf::int64 value);

  // optional int64 RecentPeriod = 15;
  void clear_recentperiod();
  static const int kRecentPeriodFieldNumber = 15;
  ::google::protobuf::int64 recentperiod() const;
  void set_recentperiod(::google::protobuf::int64 value);

  // optional bool OwnShip = 16;
  void clear_ownship();
  static const int kOwnShipFieldNumber = 16;
  bool ownship() const;
  void set_ownship(bool value);

  // optional int32 Source = 17;
  void clear_source();
  static const int kSourceFieldNumber = 17;
  ::google::protobuf::int32 source() const;
  void set_source(::google::protobuf::int32 value);

  // optional int32 Result = 18;
  void clear_result();
  static const int kResultFieldNumber = 18;
  ::google::protobuf::int32 result() const;
  void set_result(::google::protobuf::int32 value);

  // optional int32 Class = 19;
  void clear_class_();
  static const int kClassFieldNumber = 19;
  ::google::protobuf::int32 class_() const;
  void set_class_(::google::protobuf::int32 value);

  // optional int32 ReportInterval = 20;
  void clear_reportinterval();
  static const int kReportIntervalFieldNumber = 20;
  ::google::protobuf::int32 reportinterval() const;
  void set_reportinterval(::google::protobuf::int32 value);

  // optional string ShipName = 21;
  void clear_shipname();
  static const int kShipNameFieldNumber = 21;
  const ::std::string& shipname() const;
  void set_shipname(const ::std::string& value);
  void set_shipname(const char* value);
  void set_shipname(const char* value, size_t size);
  ::std::string* mutable_shipname();
  ::std::string* release_shipname();
  void set_allocated_shipname(::std::string* shipname);

  // optional int32 hdgtype = 22;
  void clear_hdgtype();
  static const int kHdgtypeFieldNumber = 22;
  ::google::protobuf::int32 hdgtype() const;
  void set_hdgtype(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:hgShipAisMessage)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr id_;
  ::google::protobuf::internal::ArenaStringPtr mmsi_;
  ::google::protobuf::internal::ArenaStringPtr shipname_;
  double sog_;
  double lon_;
  double lat_;
  double cog_;
  double hdg_;
  double length_;
  double width_;
  ::google::protobuf::int32 dima_;
  ::google::protobuf::int32 dimb_;
  ::google::protobuf::int32 dimc_;
  ::google::protobuf::int32 dimd_;
  ::google::protobuf::int64 reportticks_;
  ::google::protobuf::int64 recentperiod_;
  bool ownship_;
  ::google::protobuf::int32 source_;
  ::google::protobuf::int32 result_;
  ::google::protobuf::int32 class__;
  ::google::protobuf::int32 reportinterval_;
  ::google::protobuf::int32 hdgtype_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_hgShipAisMessage_2eproto_impl();
  friend void  protobuf_AddDesc_hgShipAisMessage_2eproto_impl();
  friend void protobuf_AssignDesc_hgShipAisMessage_2eproto();
  friend void protobuf_ShutdownFile_hgShipAisMessage_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<hgShipAisMessage> hgShipAisMessage_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// hgShipAisMessage

// optional string ID = 1;
inline void hgShipAisMessage::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgShipAisMessage::id() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.ID)
  return id_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgShipAisMessage::set_id(const ::std::string& value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgShipAisMessage.ID)
}
inline void hgShipAisMessage::set_id(const char* value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgShipAisMessage.ID)
}
inline void hgShipAisMessage::set_id(const char* value, size_t size) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgShipAisMessage.ID)
}
inline ::std::string* hgShipAisMessage::mutable_id() {
  
  // @@protoc_insertion_point(field_mutable:hgShipAisMessage.ID)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgShipAisMessage::release_id() {
  // @@protoc_insertion_point(field_release:hgShipAisMessage.ID)
  
  return id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgShipAisMessage::set_allocated_id(::std::string* id) {
  if (id != NULL) {
    
  } else {
    
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:hgShipAisMessage.ID)
}

// optional string MMSI = 2;
inline void hgShipAisMessage::clear_mmsi() {
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgShipAisMessage::mmsi() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.MMSI)
  return mmsi_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgShipAisMessage::set_mmsi(const ::std::string& value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgShipAisMessage.MMSI)
}
inline void hgShipAisMessage::set_mmsi(const char* value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgShipAisMessage.MMSI)
}
inline void hgShipAisMessage::set_mmsi(const char* value, size_t size) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgShipAisMessage.MMSI)
}
inline ::std::string* hgShipAisMessage::mutable_mmsi() {
  
  // @@protoc_insertion_point(field_mutable:hgShipAisMessage.MMSI)
  return mmsi_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgShipAisMessage::release_mmsi() {
  // @@protoc_insertion_point(field_release:hgShipAisMessage.MMSI)
  
  return mmsi_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgShipAisMessage::set_allocated_mmsi(::std::string* mmsi) {
  if (mmsi != NULL) {
    
  } else {
    
  }
  mmsi_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), mmsi);
  // @@protoc_insertion_point(field_set_allocated:hgShipAisMessage.MMSI)
}

// optional double SOG = 3;
inline void hgShipAisMessage::clear_sog() {
  sog_ = 0;
}
inline double hgShipAisMessage::sog() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.SOG)
  return sog_;
}
inline void hgShipAisMessage::set_sog(double value) {
  
  sog_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.SOG)
}

// optional double Lon = 4;
inline void hgShipAisMessage::clear_lon() {
  lon_ = 0;
}
inline double hgShipAisMessage::lon() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.Lon)
  return lon_;
}
inline void hgShipAisMessage::set_lon(double value) {
  
  lon_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.Lon)
}

// optional double Lat = 5;
inline void hgShipAisMessage::clear_lat() {
  lat_ = 0;
}
inline double hgShipAisMessage::lat() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.Lat)
  return lat_;
}
inline void hgShipAisMessage::set_lat(double value) {
  
  lat_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.Lat)
}

// optional double COG = 6;
inline void hgShipAisMessage::clear_cog() {
  cog_ = 0;
}
inline double hgShipAisMessage::cog() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.COG)
  return cog_;
}
inline void hgShipAisMessage::set_cog(double value) {
  
  cog_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.COG)
}

// optional double HDG = 7;
inline void hgShipAisMessage::clear_hdg() {
  hdg_ = 0;
}
inline double hgShipAisMessage::hdg() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.HDG)
  return hdg_;
}
inline void hgShipAisMessage::set_hdg(double value) {
  
  hdg_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.HDG)
}

// optional double Length = 8;
inline void hgShipAisMessage::clear_length() {
  length_ = 0;
}
inline double hgShipAisMessage::length() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.Length)
  return length_;
}
inline void hgShipAisMessage::set_length(double value) {
  
  length_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.Length)
}

// optional double Width = 9;
inline void hgShipAisMessage::clear_width() {
  width_ = 0;
}
inline double hgShipAisMessage::width() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.Width)
  return width_;
}
inline void hgShipAisMessage::set_width(double value) {
  
  width_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.Width)
}

// optional int32 DimA = 10;
inline void hgShipAisMessage::clear_dima() {
  dima_ = 0;
}
inline ::google::protobuf::int32 hgShipAisMessage::dima() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.DimA)
  return dima_;
}
inline void hgShipAisMessage::set_dima(::google::protobuf::int32 value) {
  
  dima_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.DimA)
}

// optional int32 DimB = 11;
inline void hgShipAisMessage::clear_dimb() {
  dimb_ = 0;
}
inline ::google::protobuf::int32 hgShipAisMessage::dimb() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.DimB)
  return dimb_;
}
inline void hgShipAisMessage::set_dimb(::google::protobuf::int32 value) {
  
  dimb_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.DimB)
}

// optional int32 DimC = 12;
inline void hgShipAisMessage::clear_dimc() {
  dimc_ = 0;
}
inline ::google::protobuf::int32 hgShipAisMessage::dimc() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.DimC)
  return dimc_;
}
inline void hgShipAisMessage::set_dimc(::google::protobuf::int32 value) {
  
  dimc_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.DimC)
}

// optional int32 DimD = 13;
inline void hgShipAisMessage::clear_dimd() {
  dimd_ = 0;
}
inline ::google::protobuf::int32 hgShipAisMessage::dimd() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.DimD)
  return dimd_;
}
inline void hgShipAisMessage::set_dimd(::google::protobuf::int32 value) {
  
  dimd_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.DimD)
}

// optional int64 ReportTicks = 14;
inline void hgShipAisMessage::clear_reportticks() {
  reportticks_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 hgShipAisMessage::reportticks() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.ReportTicks)
  return reportticks_;
}
inline void hgShipAisMessage::set_reportticks(::google::protobuf::int64 value) {
  
  reportticks_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.ReportTicks)
}

// optional int64 RecentPeriod = 15;
inline void hgShipAisMessage::clear_recentperiod() {
  recentperiod_ = GOOGLE_LONGLONG(0);
}
inline ::google::protobuf::int64 hgShipAisMessage::recentperiod() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.RecentPeriod)
  return recentperiod_;
}
inline void hgShipAisMessage::set_recentperiod(::google::protobuf::int64 value) {
  
  recentperiod_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.RecentPeriod)
}

// optional bool OwnShip = 16;
inline void hgShipAisMessage::clear_ownship() {
  ownship_ = false;
}
inline bool hgShipAisMessage::ownship() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.OwnShip)
  return ownship_;
}
inline void hgShipAisMessage::set_ownship(bool value) {
  
  ownship_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.OwnShip)
}

// optional int32 Source = 17;
inline void hgShipAisMessage::clear_source() {
  source_ = 0;
}
inline ::google::protobuf::int32 hgShipAisMessage::source() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.Source)
  return source_;
}
inline void hgShipAisMessage::set_source(::google::protobuf::int32 value) {
  
  source_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.Source)
}

// optional int32 Result = 18;
inline void hgShipAisMessage::clear_result() {
  result_ = 0;
}
inline ::google::protobuf::int32 hgShipAisMessage::result() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.Result)
  return result_;
}
inline void hgShipAisMessage::set_result(::google::protobuf::int32 value) {
  
  result_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.Result)
}

// optional int32 Class = 19;
inline void hgShipAisMessage::clear_class_() {
  class__ = 0;
}
inline ::google::protobuf::int32 hgShipAisMessage::class_() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.Class)
  return class__;
}
inline void hgShipAisMessage::set_class_(::google::protobuf::int32 value) {
  
  class__ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.Class)
}

// optional int32 ReportInterval = 20;
inline void hgShipAisMessage::clear_reportinterval() {
  reportinterval_ = 0;
}
inline ::google::protobuf::int32 hgShipAisMessage::reportinterval() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.ReportInterval)
  return reportinterval_;
}
inline void hgShipAisMessage::set_reportinterval(::google::protobuf::int32 value) {
  
  reportinterval_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.ReportInterval)
}

// optional string ShipName = 21;
inline void hgShipAisMessage::clear_shipname() {
  shipname_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& hgShipAisMessage::shipname() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.ShipName)
  return shipname_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgShipAisMessage::set_shipname(const ::std::string& value) {
  
  shipname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgShipAisMessage.ShipName)
}
inline void hgShipAisMessage::set_shipname(const char* value) {
  
  shipname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgShipAisMessage.ShipName)
}
inline void hgShipAisMessage::set_shipname(const char* value, size_t size) {
  
  shipname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgShipAisMessage.ShipName)
}
inline ::std::string* hgShipAisMessage::mutable_shipname() {
  
  // @@protoc_insertion_point(field_mutable:hgShipAisMessage.ShipName)
  return shipname_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* hgShipAisMessage::release_shipname() {
  // @@protoc_insertion_point(field_release:hgShipAisMessage.ShipName)
  
  return shipname_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void hgShipAisMessage::set_allocated_shipname(::std::string* shipname) {
  if (shipname != NULL) {
    
  } else {
    
  }
  shipname_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), shipname);
  // @@protoc_insertion_point(field_set_allocated:hgShipAisMessage.ShipName)
}

// optional int32 hdgtype = 22;
inline void hgShipAisMessage::clear_hdgtype() {
  hdgtype_ = 0;
}
inline ::google::protobuf::int32 hgShipAisMessage::hdgtype() const {
  // @@protoc_insertion_point(field_get:hgShipAisMessage.hdgtype)
  return hdgtype_;
}
inline void hgShipAisMessage::set_hdgtype(::google::protobuf::int32 value) {
  
  hdgtype_ = value;
  // @@protoc_insertion_point(field_set:hgShipAisMessage.hdgtype)
}

inline const hgShipAisMessage* hgShipAisMessage::internal_default_instance() {
  return &hgShipAisMessage_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_hgShipAisMessage_2eproto__INCLUDED