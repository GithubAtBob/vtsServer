// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: user.proto

#ifndef PROTOBUF_user_2eproto__INCLUDED
#define PROTOBUF_user_2eproto__INCLUDED

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
void protobuf_AddDesc_user_2eproto();
void protobuf_InitDefaults_user_2eproto();
void protobuf_AssignDesc_user_2eproto();
void protobuf_ShutdownFile_user_2eproto();

class UserRepsone;
class UserRequest;

// ===================================================================

class UserRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:UserRequest) */ {
 public:
  UserRequest();
  virtual ~UserRequest();

  UserRequest(const UserRequest& from);

  inline UserRequest& operator=(const UserRequest& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const UserRequest& default_instance();

  static const UserRequest* internal_default_instance();

  void Swap(UserRequest* other);

  // implements Message ----------------------------------------------

  inline UserRequest* New() const { return New(NULL); }

  UserRequest* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UserRequest& from);
  void MergeFrom(const UserRequest& from);
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
  void InternalSwap(UserRequest* other);
  void UnsafeMergeFrom(const UserRequest& from);
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

  // optional string account = 2;
  void clear_account();
  static const int kAccountFieldNumber = 2;
  const ::std::string& account() const;
  void set_account(const ::std::string& value);
  void set_account(const char* value);
  void set_account(const char* value, size_t size);
  ::std::string* mutable_account();
  ::std::string* release_account();
  void set_allocated_account(::std::string* account);

  // optional string userid = 3;
  void clear_userid();
  static const int kUseridFieldNumber = 3;
  const ::std::string& userid() const;
  void set_userid(const ::std::string& value);
  void set_userid(const char* value);
  void set_userid(const char* value, size_t size);
  ::std::string* mutable_userid();
  ::std::string* release_userid();
  void set_allocated_userid(::std::string* userid);

  // optional string loginname = 4;
  void clear_loginname();
  static const int kLoginnameFieldNumber = 4;
  const ::std::string& loginname() const;
  void set_loginname(const ::std::string& value);
  void set_loginname(const char* value);
  void set_loginname(const char* value, size_t size);
  ::std::string* mutable_loginname();
  ::std::string* release_loginname();
  void set_allocated_loginname(::std::string* loginname);

  // optional string username = 5;
  void clear_username();
  static const int kUsernameFieldNumber = 5;
  const ::std::string& username() const;
  void set_username(const ::std::string& value);
  void set_username(const char* value);
  void set_username(const char* value, size_t size);
  ::std::string* mutable_username();
  ::std::string* release_username();
  void set_allocated_username(::std::string* username);

  // optional string password = 6;
  void clear_password();
  static const int kPasswordFieldNumber = 6;
  const ::std::string& password() const;
  void set_password(const ::std::string& value);
  void set_password(const char* value);
  void set_password(const char* value, size_t size);
  ::std::string* mutable_password();
  ::std::string* release_password();
  void set_allocated_password(::std::string* password);

  // optional string phone = 7;
  void clear_phone();
  static const int kPhoneFieldNumber = 7;
  const ::std::string& phone() const;
  void set_phone(const ::std::string& value);
  void set_phone(const char* value);
  void set_phone(const char* value, size_t size);
  ::std::string* mutable_phone();
  ::std::string* release_phone();
  void set_allocated_phone(::std::string* phone);

  // optional string groupID = 8;
  void clear_groupid();
  static const int kGroupIDFieldNumber = 8;
  const ::std::string& groupid() const;
  void set_groupid(const ::std::string& value);
  void set_groupid(const char* value);
  void set_groupid(const char* value, size_t size);
  ::std::string* mutable_groupid();
  ::std::string* release_groupid();
  void set_allocated_groupid(::std::string* groupid);

  // optional string avatar = 9;
  void clear_avatar();
  static const int kAvatarFieldNumber = 9;
  const ::std::string& avatar() const;
  void set_avatar(const ::std::string& value);
  void set_avatar(const char* value);
  void set_avatar(const char* value, size_t size);
  ::std::string* mutable_avatar();
  ::std::string* release_avatar();
  void set_allocated_avatar(::std::string* avatar);

  // optional string oldloginname = 10;
  void clear_oldloginname();
  static const int kOldloginnameFieldNumber = 10;
  const ::std::string& oldloginname() const;
  void set_oldloginname(const ::std::string& value);
  void set_oldloginname(const char* value);
  void set_oldloginname(const char* value, size_t size);
  ::std::string* mutable_oldloginname();
  ::std::string* release_oldloginname();
  void set_allocated_oldloginname(::std::string* oldloginname);

  // @@protoc_insertion_point(class_scope:UserRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr account_;
  ::google::protobuf::internal::ArenaStringPtr userid_;
  ::google::protobuf::internal::ArenaStringPtr loginname_;
  ::google::protobuf::internal::ArenaStringPtr username_;
  ::google::protobuf::internal::ArenaStringPtr password_;
  ::google::protobuf::internal::ArenaStringPtr phone_;
  ::google::protobuf::internal::ArenaStringPtr groupid_;
  ::google::protobuf::internal::ArenaStringPtr avatar_;
  ::google::protobuf::internal::ArenaStringPtr oldloginname_;
  ::google::protobuf::int32 type_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_user_2eproto_impl();
  friend void  protobuf_AddDesc_user_2eproto_impl();
  friend void protobuf_AssignDesc_user_2eproto();
  friend void protobuf_ShutdownFile_user_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<UserRequest> UserRequest_default_instance_;

// -------------------------------------------------------------------

class UserRepsone : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:UserRepsone) */ {
 public:
  UserRepsone();
  virtual ~UserRepsone();

  UserRepsone(const UserRepsone& from);

  inline UserRepsone& operator=(const UserRepsone& from) {
    CopyFrom(from);
    return *this;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const UserRepsone& default_instance();

  static const UserRepsone* internal_default_instance();

  void Swap(UserRepsone* other);

  // implements Message ----------------------------------------------

  inline UserRepsone* New() const { return New(NULL); }

  UserRepsone* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const UserRepsone& from);
  void MergeFrom(const UserRepsone& from);
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
  void InternalSwap(UserRepsone* other);
  void UnsafeMergeFrom(const UserRepsone& from);
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

  // optional string message = 2;
  void clear_message();
  static const int kMessageFieldNumber = 2;
  const ::std::string& message() const;
  void set_message(const ::std::string& value);
  void set_message(const char* value);
  void set_message(const char* value, size_t size);
  ::std::string* mutable_message();
  ::std::string* release_message();
  void set_allocated_message(::std::string* message);

  // optional string result = 3;
  void clear_result();
  static const int kResultFieldNumber = 3;
  const ::std::string& result() const;
  void set_result(const ::std::string& value);
  void set_result(const char* value);
  void set_result(const char* value, size_t size);
  ::std::string* mutable_result();
  ::std::string* release_result();
  void set_allocated_result(::std::string* result);

  // @@protoc_insertion_point(class_scope:UserRepsone)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr message_;
  ::google::protobuf::internal::ArenaStringPtr result_;
  ::google::protobuf::int32 type_;
  mutable int _cached_size_;
  friend void  protobuf_InitDefaults_user_2eproto_impl();
  friend void  protobuf_AddDesc_user_2eproto_impl();
  friend void protobuf_AssignDesc_user_2eproto();
  friend void protobuf_ShutdownFile_user_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<UserRepsone> UserRepsone_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// UserRequest

// optional int32 type = 1;
inline void UserRequest::clear_type() {
  type_ = 0;
}
inline ::google::protobuf::int32 UserRequest::type() const {
  // @@protoc_insertion_point(field_get:UserRequest.type)
  return type_;
}
inline void UserRequest::set_type(::google::protobuf::int32 value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:UserRequest.type)
}

// optional string account = 2;
inline void UserRequest::clear_account() {
  account_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& UserRequest::account() const {
  // @@protoc_insertion_point(field_get:UserRequest.account)
  return account_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_account(const ::std::string& value) {
  
  account_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:UserRequest.account)
}
inline void UserRequest::set_account(const char* value) {
  
  account_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:UserRequest.account)
}
inline void UserRequest::set_account(const char* value, size_t size) {
  
  account_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:UserRequest.account)
}
inline ::std::string* UserRequest::mutable_account() {
  
  // @@protoc_insertion_point(field_mutable:UserRequest.account)
  return account_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* UserRequest::release_account() {
  // @@protoc_insertion_point(field_release:UserRequest.account)
  
  return account_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_allocated_account(::std::string* account) {
  if (account != NULL) {
    
  } else {
    
  }
  account_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), account);
  // @@protoc_insertion_point(field_set_allocated:UserRequest.account)
}

// optional string userid = 3;
inline void UserRequest::clear_userid() {
  userid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& UserRequest::userid() const {
  // @@protoc_insertion_point(field_get:UserRequest.userid)
  return userid_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_userid(const ::std::string& value) {
  
  userid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:UserRequest.userid)
}
inline void UserRequest::set_userid(const char* value) {
  
  userid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:UserRequest.userid)
}
inline void UserRequest::set_userid(const char* value, size_t size) {
  
  userid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:UserRequest.userid)
}
inline ::std::string* UserRequest::mutable_userid() {
  
  // @@protoc_insertion_point(field_mutable:UserRequest.userid)
  return userid_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* UserRequest::release_userid() {
  // @@protoc_insertion_point(field_release:UserRequest.userid)
  
  return userid_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_allocated_userid(::std::string* userid) {
  if (userid != NULL) {
    
  } else {
    
  }
  userid_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), userid);
  // @@protoc_insertion_point(field_set_allocated:UserRequest.userid)
}

// optional string loginname = 4;
inline void UserRequest::clear_loginname() {
  loginname_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& UserRequest::loginname() const {
  // @@protoc_insertion_point(field_get:UserRequest.loginname)
  return loginname_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_loginname(const ::std::string& value) {
  
  loginname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:UserRequest.loginname)
}
inline void UserRequest::set_loginname(const char* value) {
  
  loginname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:UserRequest.loginname)
}
inline void UserRequest::set_loginname(const char* value, size_t size) {
  
  loginname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:UserRequest.loginname)
}
inline ::std::string* UserRequest::mutable_loginname() {
  
  // @@protoc_insertion_point(field_mutable:UserRequest.loginname)
  return loginname_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* UserRequest::release_loginname() {
  // @@protoc_insertion_point(field_release:UserRequest.loginname)
  
  return loginname_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_allocated_loginname(::std::string* loginname) {
  if (loginname != NULL) {
    
  } else {
    
  }
  loginname_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), loginname);
  // @@protoc_insertion_point(field_set_allocated:UserRequest.loginname)
}

// optional string username = 5;
inline void UserRequest::clear_username() {
  username_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& UserRequest::username() const {
  // @@protoc_insertion_point(field_get:UserRequest.username)
  return username_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_username(const ::std::string& value) {
  
  username_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:UserRequest.username)
}
inline void UserRequest::set_username(const char* value) {
  
  username_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:UserRequest.username)
}
inline void UserRequest::set_username(const char* value, size_t size) {
  
  username_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:UserRequest.username)
}
inline ::std::string* UserRequest::mutable_username() {
  
  // @@protoc_insertion_point(field_mutable:UserRequest.username)
  return username_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* UserRequest::release_username() {
  // @@protoc_insertion_point(field_release:UserRequest.username)
  
  return username_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_allocated_username(::std::string* username) {
  if (username != NULL) {
    
  } else {
    
  }
  username_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), username);
  // @@protoc_insertion_point(field_set_allocated:UserRequest.username)
}

// optional string password = 6;
inline void UserRequest::clear_password() {
  password_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& UserRequest::password() const {
  // @@protoc_insertion_point(field_get:UserRequest.password)
  return password_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_password(const ::std::string& value) {
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:UserRequest.password)
}
inline void UserRequest::set_password(const char* value) {
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:UserRequest.password)
}
inline void UserRequest::set_password(const char* value, size_t size) {
  
  password_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:UserRequest.password)
}
inline ::std::string* UserRequest::mutable_password() {
  
  // @@protoc_insertion_point(field_mutable:UserRequest.password)
  return password_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* UserRequest::release_password() {
  // @@protoc_insertion_point(field_release:UserRequest.password)
  
  return password_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_allocated_password(::std::string* password) {
  if (password != NULL) {
    
  } else {
    
  }
  password_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), password);
  // @@protoc_insertion_point(field_set_allocated:UserRequest.password)
}

// optional string phone = 7;
inline void UserRequest::clear_phone() {
  phone_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& UserRequest::phone() const {
  // @@protoc_insertion_point(field_get:UserRequest.phone)
  return phone_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_phone(const ::std::string& value) {
  
  phone_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:UserRequest.phone)
}
inline void UserRequest::set_phone(const char* value) {
  
  phone_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:UserRequest.phone)
}
inline void UserRequest::set_phone(const char* value, size_t size) {
  
  phone_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:UserRequest.phone)
}
inline ::std::string* UserRequest::mutable_phone() {
  
  // @@protoc_insertion_point(field_mutable:UserRequest.phone)
  return phone_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* UserRequest::release_phone() {
  // @@protoc_insertion_point(field_release:UserRequest.phone)
  
  return phone_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_allocated_phone(::std::string* phone) {
  if (phone != NULL) {
    
  } else {
    
  }
  phone_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), phone);
  // @@protoc_insertion_point(field_set_allocated:UserRequest.phone)
}

// optional string groupID = 8;
inline void UserRequest::clear_groupid() {
  groupid_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& UserRequest::groupid() const {
  // @@protoc_insertion_point(field_get:UserRequest.groupID)
  return groupid_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_groupid(const ::std::string& value) {
  
  groupid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:UserRequest.groupID)
}
inline void UserRequest::set_groupid(const char* value) {
  
  groupid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:UserRequest.groupID)
}
inline void UserRequest::set_groupid(const char* value, size_t size) {
  
  groupid_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:UserRequest.groupID)
}
inline ::std::string* UserRequest::mutable_groupid() {
  
  // @@protoc_insertion_point(field_mutable:UserRequest.groupID)
  return groupid_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* UserRequest::release_groupid() {
  // @@protoc_insertion_point(field_release:UserRequest.groupID)
  
  return groupid_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_allocated_groupid(::std::string* groupid) {
  if (groupid != NULL) {
    
  } else {
    
  }
  groupid_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), groupid);
  // @@protoc_insertion_point(field_set_allocated:UserRequest.groupID)
}

// optional string avatar = 9;
inline void UserRequest::clear_avatar() {
  avatar_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& UserRequest::avatar() const {
  // @@protoc_insertion_point(field_get:UserRequest.avatar)
  return avatar_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_avatar(const ::std::string& value) {
  
  avatar_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:UserRequest.avatar)
}
inline void UserRequest::set_avatar(const char* value) {
  
  avatar_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:UserRequest.avatar)
}
inline void UserRequest::set_avatar(const char* value, size_t size) {
  
  avatar_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:UserRequest.avatar)
}
inline ::std::string* UserRequest::mutable_avatar() {
  
  // @@protoc_insertion_point(field_mutable:UserRequest.avatar)
  return avatar_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* UserRequest::release_avatar() {
  // @@protoc_insertion_point(field_release:UserRequest.avatar)
  
  return avatar_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_allocated_avatar(::std::string* avatar) {
  if (avatar != NULL) {
    
  } else {
    
  }
  avatar_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), avatar);
  // @@protoc_insertion_point(field_set_allocated:UserRequest.avatar)
}

// optional string oldloginname = 10;
inline void UserRequest::clear_oldloginname() {
  oldloginname_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& UserRequest::oldloginname() const {
  // @@protoc_insertion_point(field_get:UserRequest.oldloginname)
  return oldloginname_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_oldloginname(const ::std::string& value) {
  
  oldloginname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:UserRequest.oldloginname)
}
inline void UserRequest::set_oldloginname(const char* value) {
  
  oldloginname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:UserRequest.oldloginname)
}
inline void UserRequest::set_oldloginname(const char* value, size_t size) {
  
  oldloginname_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:UserRequest.oldloginname)
}
inline ::std::string* UserRequest::mutable_oldloginname() {
  
  // @@protoc_insertion_point(field_mutable:UserRequest.oldloginname)
  return oldloginname_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* UserRequest::release_oldloginname() {
  // @@protoc_insertion_point(field_release:UserRequest.oldloginname)
  
  return oldloginname_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRequest::set_allocated_oldloginname(::std::string* oldloginname) {
  if (oldloginname != NULL) {
    
  } else {
    
  }
  oldloginname_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), oldloginname);
  // @@protoc_insertion_point(field_set_allocated:UserRequest.oldloginname)
}

inline const UserRequest* UserRequest::internal_default_instance() {
  return &UserRequest_default_instance_.get();
}
// -------------------------------------------------------------------

// UserRepsone

// optional int32 type = 1;
inline void UserRepsone::clear_type() {
  type_ = 0;
}
inline ::google::protobuf::int32 UserRepsone::type() const {
  // @@protoc_insertion_point(field_get:UserRepsone.type)
  return type_;
}
inline void UserRepsone::set_type(::google::protobuf::int32 value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:UserRepsone.type)
}

// optional string message = 2;
inline void UserRepsone::clear_message() {
  message_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& UserRepsone::message() const {
  // @@protoc_insertion_point(field_get:UserRepsone.message)
  return message_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRepsone::set_message(const ::std::string& value) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:UserRepsone.message)
}
inline void UserRepsone::set_message(const char* value) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:UserRepsone.message)
}
inline void UserRepsone::set_message(const char* value, size_t size) {
  
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:UserRepsone.message)
}
inline ::std::string* UserRepsone::mutable_message() {
  
  // @@protoc_insertion_point(field_mutable:UserRepsone.message)
  return message_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* UserRepsone::release_message() {
  // @@protoc_insertion_point(field_release:UserRepsone.message)
  
  return message_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRepsone::set_allocated_message(::std::string* message) {
  if (message != NULL) {
    
  } else {
    
  }
  message_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), message);
  // @@protoc_insertion_point(field_set_allocated:UserRepsone.message)
}

// optional string result = 3;
inline void UserRepsone::clear_result() {
  result_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& UserRepsone::result() const {
  // @@protoc_insertion_point(field_get:UserRepsone.result)
  return result_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRepsone::set_result(const ::std::string& value) {
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:UserRepsone.result)
}
inline void UserRepsone::set_result(const char* value) {
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:UserRepsone.result)
}
inline void UserRepsone::set_result(const char* value, size_t size) {
  
  result_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:UserRepsone.result)
}
inline ::std::string* UserRepsone::mutable_result() {
  
  // @@protoc_insertion_point(field_mutable:UserRepsone.result)
  return result_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* UserRepsone::release_result() {
  // @@protoc_insertion_point(field_release:UserRepsone.result)
  
  return result_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void UserRepsone::set_allocated_result(::std::string* result) {
  if (result != NULL) {
    
  } else {
    
  }
  result_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), result);
  // @@protoc_insertion_point(field_set_allocated:UserRepsone.result)
}

inline const UserRepsone* UserRepsone::internal_default_instance() {
  return &UserRepsone_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_user_2eproto__INCLUDED