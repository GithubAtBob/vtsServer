// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hgAnchorReserv.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "hgAnchorReserv.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* hgAnchorReserv_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  hgAnchorReserv_reflection_ = NULL;
const ::google::protobuf::Descriptor* hgAnchorReservRepsone_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  hgAnchorReservRepsone_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_hgAnchorReserv_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_hgAnchorReserv_2eproto() {
  protobuf_AddDesc_hgAnchorReserv_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "hgAnchorReserv.proto");
  GOOGLE_CHECK(file != NULL);
  hgAnchorReserv_descriptor_ = file->message_type(0);
  static const int hgAnchorReserv_offsets_[7] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAnchorReserv, mmsi_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAnchorReserv, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAnchorReserv, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAnchorReserv, anchorreserv_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAnchorReserv, eta_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAnchorReserv, etd_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAnchorReserv, tracks_),
  };
  hgAnchorReserv_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      hgAnchorReserv_descriptor_,
      hgAnchorReserv::internal_default_instance(),
      hgAnchorReserv_offsets_,
      -1,
      -1,
      -1,
      sizeof(hgAnchorReserv),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAnchorReserv, _internal_metadata_));
  hgAnchorReservRepsone_descriptor_ = file->message_type(1);
  static const int hgAnchorReservRepsone_offsets_[1] = {
  };
  hgAnchorReservRepsone_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      hgAnchorReservRepsone_descriptor_,
      hgAnchorReservRepsone::internal_default_instance(),
      hgAnchorReservRepsone_offsets_,
      -1,
      -1,
      -1,
      sizeof(hgAnchorReservRepsone),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAnchorReservRepsone, _internal_metadata_));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_hgAnchorReserv_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      hgAnchorReserv_descriptor_, hgAnchorReserv::internal_default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      hgAnchorReservRepsone_descriptor_, hgAnchorReservRepsone::internal_default_instance());
}

}  // namespace

void protobuf_ShutdownFile_hgAnchorReserv_2eproto() {
  hgAnchorReserv_default_instance_.Shutdown();
  delete hgAnchorReserv_reflection_;
  hgAnchorReservRepsone_default_instance_.Shutdown();
  delete hgAnchorReservRepsone_reflection_;
}

void protobuf_InitDefaults_hgAnchorReserv_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::GetEmptyString();
  hgAnchorReserv_default_instance_.DefaultConstruct();
  hgAnchorReservRepsone_default_instance_.DefaultConstruct();
  hgAnchorReserv_default_instance_.get_mutable()->InitAsDefaultInstance();
  hgAnchorReservRepsone_default_instance_.get_mutable()->InitAsDefaultInstance();
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_InitDefaults_hgAnchorReserv_2eproto_once_);
void protobuf_InitDefaults_hgAnchorReserv_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_InitDefaults_hgAnchorReserv_2eproto_once_,
                 &protobuf_InitDefaults_hgAnchorReserv_2eproto_impl);
}
void protobuf_AddDesc_hgAnchorReserv_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  protobuf_InitDefaults_hgAnchorReserv_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\024hgAnchorReserv.proto\"x\n\016hgAnchorReserv"
    "\022\014\n\004MMSI\030\001 \001(\t\022\n\n\002ID\030\002 \001(\t\022\014\n\004Type\030\003 \001(\005"
    "\022\024\n\014AnchorReserv\030\004 \001(\010\022\013\n\003ETA\030\005 \001(\003\022\013\n\003E"
    "TD\030\006 \001(\003\022\016\n\006Tracks\030\007 \001(\005\"\027\n\025hgAnchorRese"
    "rvRepsoneb\006proto3", 177);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "hgAnchorReserv.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_hgAnchorReserv_2eproto);
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_hgAnchorReserv_2eproto_once_);
void protobuf_AddDesc_hgAnchorReserv_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_hgAnchorReserv_2eproto_once_,
                 &protobuf_AddDesc_hgAnchorReserv_2eproto_impl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_hgAnchorReserv_2eproto {
  StaticDescriptorInitializer_hgAnchorReserv_2eproto() {
    protobuf_AddDesc_hgAnchorReserv_2eproto();
  }
} static_descriptor_initializer_hgAnchorReserv_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD GOOGLE_ATTRIBUTE_NORETURN;
static void MergeFromFail(int line) {
  ::google::protobuf::internal::MergeFromFail(__FILE__, line);
}

}  // namespace


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int hgAnchorReserv::kMMSIFieldNumber;
const int hgAnchorReserv::kIDFieldNumber;
const int hgAnchorReserv::kTypeFieldNumber;
const int hgAnchorReserv::kAnchorReservFieldNumber;
const int hgAnchorReserv::kETAFieldNumber;
const int hgAnchorReserv::kETDFieldNumber;
const int hgAnchorReserv::kTracksFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

hgAnchorReserv::hgAnchorReserv()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (this != internal_default_instance()) protobuf_InitDefaults_hgAnchorReserv_2eproto();
  SharedCtor();
  // @@protoc_insertion_point(constructor:hgAnchorReserv)
}

void hgAnchorReserv::InitAsDefaultInstance() {
}

hgAnchorReserv::hgAnchorReserv(const hgAnchorReserv& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  UnsafeMergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:hgAnchorReserv)
}

void hgAnchorReserv::SharedCtor() {
  mmsi_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  id_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&type_, 0, reinterpret_cast<char*>(&tracks_) -
    reinterpret_cast<char*>(&type_) + sizeof(tracks_));
  _cached_size_ = 0;
}

hgAnchorReserv::~hgAnchorReserv() {
  // @@protoc_insertion_point(destructor:hgAnchorReserv)
  SharedDtor();
}

void hgAnchorReserv::SharedDtor() {
  mmsi_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  id_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void hgAnchorReserv::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* hgAnchorReserv::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return hgAnchorReserv_descriptor_;
}

const hgAnchorReserv& hgAnchorReserv::default_instance() {
  protobuf_InitDefaults_hgAnchorReserv_2eproto();
  return *internal_default_instance();
}

::google::protobuf::internal::ExplicitlyConstructed<hgAnchorReserv> hgAnchorReserv_default_instance_;

hgAnchorReserv* hgAnchorReserv::New(::google::protobuf::Arena* arena) const {
  hgAnchorReserv* n = new hgAnchorReserv;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void hgAnchorReserv::Clear() {
// @@protoc_insertion_point(message_clear_start:hgAnchorReserv)
#if defined(__clang__)
#define ZR_HELPER_(f) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") \
  __builtin_offsetof(hgAnchorReserv, f) \
  _Pragma("clang diagnostic pop")
#else
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<hgAnchorReserv*>(16)->f)
#endif

#define ZR_(first, last) do {\
  ::memset(&(first), 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  ZR_(type_, tracks_);
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());

#undef ZR_HELPER_
#undef ZR_

}

bool hgAnchorReserv::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:hgAnchorReserv)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string MMSI = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_mmsi()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->mmsi().data(), this->mmsi().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "hgAnchorReserv.MMSI"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_ID;
        break;
      }

      // optional string ID = 2;
      case 2: {
        if (tag == 18) {
         parse_ID:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_id()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->id().data(), this->id().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "hgAnchorReserv.ID"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_Type;
        break;
      }

      // optional int32 Type = 3;
      case 3: {
        if (tag == 24) {
         parse_Type:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &type_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_AnchorReserv;
        break;
      }

      // optional bool AnchorReserv = 4;
      case 4: {
        if (tag == 32) {
         parse_AnchorReserv:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &anchorreserv_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(40)) goto parse_ETA;
        break;
      }

      // optional int64 ETA = 5;
      case 5: {
        if (tag == 40) {
         parse_ETA:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &eta_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(48)) goto parse_ETD;
        break;
      }

      // optional int64 ETD = 6;
      case 6: {
        if (tag == 48) {
         parse_ETD:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &etd_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(56)) goto parse_Tracks;
        break;
      }

      // optional int32 Tracks = 7;
      case 7: {
        if (tag == 56) {
         parse_Tracks:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &tracks_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:hgAnchorReserv)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:hgAnchorReserv)
  return false;
#undef DO_
}

void hgAnchorReserv::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:hgAnchorReserv)
  // optional string MMSI = 1;
  if (this->mmsi().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->mmsi().data(), this->mmsi().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "hgAnchorReserv.MMSI");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->mmsi(), output);
  }

  // optional string ID = 2;
  if (this->id().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->id().data(), this->id().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "hgAnchorReserv.ID");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->id(), output);
  }

  // optional int32 Type = 3;
  if (this->type() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->type(), output);
  }

  // optional bool AnchorReserv = 4;
  if (this->anchorreserv() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(4, this->anchorreserv(), output);
  }

  // optional int64 ETA = 5;
  if (this->eta() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(5, this->eta(), output);
  }

  // optional int64 ETD = 6;
  if (this->etd() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(6, this->etd(), output);
  }

  // optional int32 Tracks = 7;
  if (this->tracks() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(7, this->tracks(), output);
  }

  // @@protoc_insertion_point(serialize_end:hgAnchorReserv)
}

::google::protobuf::uint8* hgAnchorReserv::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:hgAnchorReserv)
  // optional string MMSI = 1;
  if (this->mmsi().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->mmsi().data(), this->mmsi().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "hgAnchorReserv.MMSI");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->mmsi(), target);
  }

  // optional string ID = 2;
  if (this->id().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->id().data(), this->id().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "hgAnchorReserv.ID");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->id(), target);
  }

  // optional int32 Type = 3;
  if (this->type() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->type(), target);
  }

  // optional bool AnchorReserv = 4;
  if (this->anchorreserv() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(4, this->anchorreserv(), target);
  }

  // optional int64 ETA = 5;
  if (this->eta() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(5, this->eta(), target);
  }

  // optional int64 ETD = 6;
  if (this->etd() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(6, this->etd(), target);
  }

  // optional int32 Tracks = 7;
  if (this->tracks() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(7, this->tracks(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:hgAnchorReserv)
  return target;
}

size_t hgAnchorReserv::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:hgAnchorReserv)
  size_t total_size = 0;

  // optional string MMSI = 1;
  if (this->mmsi().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->mmsi());
  }

  // optional string ID = 2;
  if (this->id().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->id());
  }

  // optional int32 Type = 3;
  if (this->type() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->type());
  }

  // optional bool AnchorReserv = 4;
  if (this->anchorreserv() != 0) {
    total_size += 1 + 1;
  }

  // optional int64 ETA = 5;
  if (this->eta() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->eta());
  }

  // optional int64 ETD = 6;
  if (this->etd() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->etd());
  }

  // optional int32 Tracks = 7;
  if (this->tracks() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->tracks());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void hgAnchorReserv::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:hgAnchorReserv)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const hgAnchorReserv* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const hgAnchorReserv>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:hgAnchorReserv)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:hgAnchorReserv)
    UnsafeMergeFrom(*source);
  }
}

void hgAnchorReserv::MergeFrom(const hgAnchorReserv& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:hgAnchorReserv)
  if (GOOGLE_PREDICT_TRUE(&from != this)) {
    UnsafeMergeFrom(from);
  } else {
    MergeFromFail(__LINE__);
  }
}

void hgAnchorReserv::UnsafeMergeFrom(const hgAnchorReserv& from) {
  GOOGLE_DCHECK(&from != this);
  if (from.mmsi().size() > 0) {

    mmsi_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.mmsi_);
  }
  if (from.id().size() > 0) {

    id_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.id_);
  }
  if (from.type() != 0) {
    set_type(from.type());
  }
  if (from.anchorreserv() != 0) {
    set_anchorreserv(from.anchorreserv());
  }
  if (from.eta() != 0) {
    set_eta(from.eta());
  }
  if (from.etd() != 0) {
    set_etd(from.etd());
  }
  if (from.tracks() != 0) {
    set_tracks(from.tracks());
  }
}

void hgAnchorReserv::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:hgAnchorReserv)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void hgAnchorReserv::CopyFrom(const hgAnchorReserv& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:hgAnchorReserv)
  if (&from == this) return;
  Clear();
  UnsafeMergeFrom(from);
}

bool hgAnchorReserv::IsInitialized() const {

  return true;
}

void hgAnchorReserv::Swap(hgAnchorReserv* other) {
  if (other == this) return;
  InternalSwap(other);
}
void hgAnchorReserv::InternalSwap(hgAnchorReserv* other) {
  mmsi_.Swap(&other->mmsi_);
  id_.Swap(&other->id_);
  std::swap(type_, other->type_);
  std::swap(anchorreserv_, other->anchorreserv_);
  std::swap(eta_, other->eta_);
  std::swap(etd_, other->etd_);
  std::swap(tracks_, other->tracks_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata hgAnchorReserv::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = hgAnchorReserv_descriptor_;
  metadata.reflection = hgAnchorReserv_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// hgAnchorReserv

// optional string MMSI = 1;
void hgAnchorReserv::clear_mmsi() {
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& hgAnchorReserv::mmsi() const {
  // @@protoc_insertion_point(field_get:hgAnchorReserv.MMSI)
  return mmsi_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void hgAnchorReserv::set_mmsi(const ::std::string& value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgAnchorReserv.MMSI)
}
void hgAnchorReserv::set_mmsi(const char* value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgAnchorReserv.MMSI)
}
void hgAnchorReserv::set_mmsi(const char* value, size_t size) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgAnchorReserv.MMSI)
}
::std::string* hgAnchorReserv::mutable_mmsi() {
  
  // @@protoc_insertion_point(field_mutable:hgAnchorReserv.MMSI)
  return mmsi_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* hgAnchorReserv::release_mmsi() {
  // @@protoc_insertion_point(field_release:hgAnchorReserv.MMSI)
  
  return mmsi_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void hgAnchorReserv::set_allocated_mmsi(::std::string* mmsi) {
  if (mmsi != NULL) {
    
  } else {
    
  }
  mmsi_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), mmsi);
  // @@protoc_insertion_point(field_set_allocated:hgAnchorReserv.MMSI)
}

// optional string ID = 2;
void hgAnchorReserv::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& hgAnchorReserv::id() const {
  // @@protoc_insertion_point(field_get:hgAnchorReserv.ID)
  return id_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void hgAnchorReserv::set_id(const ::std::string& value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgAnchorReserv.ID)
}
void hgAnchorReserv::set_id(const char* value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgAnchorReserv.ID)
}
void hgAnchorReserv::set_id(const char* value, size_t size) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgAnchorReserv.ID)
}
::std::string* hgAnchorReserv::mutable_id() {
  
  // @@protoc_insertion_point(field_mutable:hgAnchorReserv.ID)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* hgAnchorReserv::release_id() {
  // @@protoc_insertion_point(field_release:hgAnchorReserv.ID)
  
  return id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void hgAnchorReserv::set_allocated_id(::std::string* id) {
  if (id != NULL) {
    
  } else {
    
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:hgAnchorReserv.ID)
}

// optional int32 Type = 3;
void hgAnchorReserv::clear_type() {
  type_ = 0;
}
::google::protobuf::int32 hgAnchorReserv::type() const {
  // @@protoc_insertion_point(field_get:hgAnchorReserv.Type)
  return type_;
}
void hgAnchorReserv::set_type(::google::protobuf::int32 value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:hgAnchorReserv.Type)
}

// optional bool AnchorReserv = 4;
void hgAnchorReserv::clear_anchorreserv() {
  anchorreserv_ = false;
}
bool hgAnchorReserv::anchorreserv() const {
  // @@protoc_insertion_point(field_get:hgAnchorReserv.AnchorReserv)
  return anchorreserv_;
}
void hgAnchorReserv::set_anchorreserv(bool value) {
  
  anchorreserv_ = value;
  // @@protoc_insertion_point(field_set:hgAnchorReserv.AnchorReserv)
}

// optional int64 ETA = 5;
void hgAnchorReserv::clear_eta() {
  eta_ = GOOGLE_LONGLONG(0);
}
::google::protobuf::int64 hgAnchorReserv::eta() const {
  // @@protoc_insertion_point(field_get:hgAnchorReserv.ETA)
  return eta_;
}
void hgAnchorReserv::set_eta(::google::protobuf::int64 value) {
  
  eta_ = value;
  // @@protoc_insertion_point(field_set:hgAnchorReserv.ETA)
}

// optional int64 ETD = 6;
void hgAnchorReserv::clear_etd() {
  etd_ = GOOGLE_LONGLONG(0);
}
::google::protobuf::int64 hgAnchorReserv::etd() const {
  // @@protoc_insertion_point(field_get:hgAnchorReserv.ETD)
  return etd_;
}
void hgAnchorReserv::set_etd(::google::protobuf::int64 value) {
  
  etd_ = value;
  // @@protoc_insertion_point(field_set:hgAnchorReserv.ETD)
}

// optional int32 Tracks = 7;
void hgAnchorReserv::clear_tracks() {
  tracks_ = 0;
}
::google::protobuf::int32 hgAnchorReserv::tracks() const {
  // @@protoc_insertion_point(field_get:hgAnchorReserv.Tracks)
  return tracks_;
}
void hgAnchorReserv::set_tracks(::google::protobuf::int32 value) {
  
  tracks_ = value;
  // @@protoc_insertion_point(field_set:hgAnchorReserv.Tracks)
}

inline const hgAnchorReserv* hgAnchorReserv::internal_default_instance() {
  return &hgAnchorReserv_default_instance_.get();
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

hgAnchorReservRepsone::hgAnchorReservRepsone()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (this != internal_default_instance()) protobuf_InitDefaults_hgAnchorReserv_2eproto();
  SharedCtor();
  // @@protoc_insertion_point(constructor:hgAnchorReservRepsone)
}

void hgAnchorReservRepsone::InitAsDefaultInstance() {
}

hgAnchorReservRepsone::hgAnchorReservRepsone(const hgAnchorReservRepsone& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  UnsafeMergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:hgAnchorReservRepsone)
}

void hgAnchorReservRepsone::SharedCtor() {
  _cached_size_ = 0;
}

hgAnchorReservRepsone::~hgAnchorReservRepsone() {
  // @@protoc_insertion_point(destructor:hgAnchorReservRepsone)
  SharedDtor();
}

void hgAnchorReservRepsone::SharedDtor() {
}

void hgAnchorReservRepsone::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* hgAnchorReservRepsone::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return hgAnchorReservRepsone_descriptor_;
}

const hgAnchorReservRepsone& hgAnchorReservRepsone::default_instance() {
  protobuf_InitDefaults_hgAnchorReserv_2eproto();
  return *internal_default_instance();
}

::google::protobuf::internal::ExplicitlyConstructed<hgAnchorReservRepsone> hgAnchorReservRepsone_default_instance_;

hgAnchorReservRepsone* hgAnchorReservRepsone::New(::google::protobuf::Arena* arena) const {
  hgAnchorReservRepsone* n = new hgAnchorReservRepsone;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void hgAnchorReservRepsone::Clear() {
// @@protoc_insertion_point(message_clear_start:hgAnchorReservRepsone)
}

bool hgAnchorReservRepsone::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:hgAnchorReservRepsone)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
  handle_unusual:
    if (tag == 0 ||
        ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      goto success;
    }
    DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
  }
success:
  // @@protoc_insertion_point(parse_success:hgAnchorReservRepsone)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:hgAnchorReservRepsone)
  return false;
#undef DO_
}

void hgAnchorReservRepsone::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:hgAnchorReservRepsone)
  // @@protoc_insertion_point(serialize_end:hgAnchorReservRepsone)
}

::google::protobuf::uint8* hgAnchorReservRepsone::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:hgAnchorReservRepsone)
  // @@protoc_insertion_point(serialize_to_array_end:hgAnchorReservRepsone)
  return target;
}

size_t hgAnchorReservRepsone::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:hgAnchorReservRepsone)
  size_t total_size = 0;

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void hgAnchorReservRepsone::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:hgAnchorReservRepsone)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const hgAnchorReservRepsone* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const hgAnchorReservRepsone>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:hgAnchorReservRepsone)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:hgAnchorReservRepsone)
    UnsafeMergeFrom(*source);
  }
}

void hgAnchorReservRepsone::MergeFrom(const hgAnchorReservRepsone& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:hgAnchorReservRepsone)
  if (GOOGLE_PREDICT_TRUE(&from != this)) {
    UnsafeMergeFrom(from);
  } else {
    MergeFromFail(__LINE__);
  }
}

void hgAnchorReservRepsone::UnsafeMergeFrom(const hgAnchorReservRepsone& from) {
  GOOGLE_DCHECK(&from != this);
}

void hgAnchorReservRepsone::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:hgAnchorReservRepsone)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void hgAnchorReservRepsone::CopyFrom(const hgAnchorReservRepsone& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:hgAnchorReservRepsone)
  if (&from == this) return;
  Clear();
  UnsafeMergeFrom(from);
}

bool hgAnchorReservRepsone::IsInitialized() const {

  return true;
}

void hgAnchorReservRepsone::Swap(hgAnchorReservRepsone* other) {
  if (other == this) return;
  InternalSwap(other);
}
void hgAnchorReservRepsone::InternalSwap(hgAnchorReservRepsone* other) {
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata hgAnchorReservRepsone::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = hgAnchorReservRepsone_descriptor_;
  metadata.reflection = hgAnchorReservRepsone_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// hgAnchorReservRepsone

inline const hgAnchorReservRepsone* hgAnchorReservRepsone::internal_default_instance() {
  return &hgAnchorReservRepsone_default_instance_.get();
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
