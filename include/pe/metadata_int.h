// Copyright (c) 2017 Himanshu Goel
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef MINICLR_METADATA_INT_H_
#define MINICLR_METADATA_INT_H_

#include <stdint.h>

#include "pe_int.h"
#include "types.h"

#define METADATA_ROOT_MAGIC 0x424A5342

typedef struct {
  uint32_t magic;
  uint16_t majorVersion;
  uint16_t minorVersion;
  uint32_t reserved0;
  uint32_t length;
  char version_str[0];
} MetadataRoot;

typedef struct {
  uint32_t offset;
  uint32_t size;
  char stream_str[0];
} StreamHeader;

typedef struct {
  uint16_t flags;
  uint16_t streamCount;
  StreamHeader streams[0];
} MetadataRoot2;

typedef struct {
  uint32_t reserved0;
  uint8_t majorVersion;
  uint8_t minorVersion;
  uint8_t heapSizes;
  uint8_t reserved1;
  uint64_t valid;
  uint64_t sorted;
  uint32_t rows[0];
} MetadataStreamHeader;

typedef enum {
  AssemblyFlags_None = 0,
} AssemblyFlags;

typedef enum {
  TypeAttributes_None = 0,
} TypeAttributes;

typedef enum {
  FieldAttributes_None = 0,
} FieldAttributes;

typedef enum {
  ManifestResourceAttributes_None = 0,
} ManifestResourceAttributes;

typedef enum {
  FileAttributes_None = 0,
} FileAttributes;
git @github.com : himanshugoel2797 / miniclr.git typedef struct {
  uint16_t generation;
  String_t name;
  Guid_t mvId;
  Guid_t encId;
  Guid_t encBaseId;
} MD_Module;

typedef struct {
  ResolutionScope_t scope;
  String_t name;
  String_t ns;
} MD_TypeRef;

typedef struct {
  TypeAttributes flags;
  String_t name;
  String_t ns;
  TypeDefOrRef_t extends;
  Field_t fieldList;
  Method_t methodList;
} MD_TypeDef;

typedef struct {
  FieldAttributes flags;
  String_t name;
  Blob_t signature;
} MD_Field;

typedef struct {
  uint32_t rva;
  uint16_t implFlags;
  uint16_t flags;
  String_t name;
  Param_t paramList;
} MD_MethodDef;

typedef struct {
  uint16_t flags;
  uint16_t sequence;
  String_t name;
} MD_Param;

typedef struct {
  TypeDef_t className;
  TypeDefOrRef_t interface;
} MD_InterfaceImpl;

typedef struct {
  MemberRefParent_t parentclass;
  String_t name;
  Blob_t signature;
} MD_MemberRef;

typedef struct {
  uint8_t type;
  Parent_t parent;
  Blob_t value;
} MD_Constant;

typedef struct {
  Parent_t parent;
  CustomAttribute_t type;
  Blob_t value;
} MD_CustomAttribute;

typedef struct {
  Parent_t parent;
  Blob_t nativeType;
} MD_FieldMarshal;

typedef struct {
  uint16_t action;
  Parent_t parent;
  Blob_t permissionSet;
} MD_DeclSecurity;

typedef struct {
  uint16_t packingSize;
  uint32_t classSize;
  Parent_t parent;
} MD_ClassLayout;

typedef struct {
  uint32_t ofset;
  Field_t field;
} MD_FieldLayout;

typedef struct { Blob_t signature; } MD_StandAloneSig;

typedef struct {
  Parent_t parent;
  EventList_t event;
} MD_EventMap;

typedef struct {
  uint16_t eventFlags;
  String_t name;
  TypeDefOrRef_t eventType;
} MD_Event;

typedef struct {
  TypeDef_t parent;
  Property_t propertyList;
} MD_PropertyMap;

typedef struct {
  uint16_t flags;
  String_t name;
  Blob_t type;
} MD_Property;

typedef struct {
  uint16_t semantics;
  MethodDef_t method;
  HasSemantics_t association;
} MD_MethodSemantics;

typedef struct {
  TypeDef_t pClass;
  MethodDefOrRef_t methodBody;
  MethodDefOrRef_t methodDecl;
} MD_MethodImpl;

typedef struct { String_t name; } MD_ModuleRef;

typedef struct { Blob_t signature; } MD_TypeSpec;

typedef struct {
  uint16_t mappingFlags;
  MemberForwarded_t forwarded;
  String_t importName;
  ModuleRef_t importScope;
} MD_ImplMap;

typedef struct {
  uint32_t rva;
  Field_t field;
} MD_FieldRVA;

typedef struct {
  AssemblyHashAlg_t hashAlgId;
  uint16_t majorVer;
  uint16_t minorVer;
  uint16_t buildNumber;
  uint16_t revisionNumber;
  AssemblyFlags flags;
  Blob_t publicKey;
  String_t name;
  String_t culture;
} MD_Assembly;

typedef struct {
  uint16_t majorVer;
  uint16_t minorVer;
  uint16_t buildNumber;
  uint16_t revisionNumber;
  AssemblyFlags flags;
  Blob_t publicKeyOrToken;
  String_t name;
  String_t culture;
  Blob_t hashValue;
} MD_AssemblyRef;

typedef struct {
  FileAttributes flags;
  String_t name;
  Blob_t hashValue;
} MD_File;

typedef struct {
  TypeAttributes flags;
  TypeDef_t typeDefId;
  String_t name;
  String_t ns;
  Implementation_t implementation;
} MD_ExportedType;

typedef struct {
  uint32_t offset;
  ManifestResourceAttributes flags;
  String_t name;
  Implementation_t implementation;
} MD_ManifestResource;

typedef struct {
  TypeDef_t nestedClass;
  TypeDef_t enclosingClass;
} MD_NestedClass;

typedef struct {
  uint16_t idx;
  uint16_t flags;
  TypeOrMethodDef_t owner;
  String_t name;
} MD_GenericParam;

typedef struct {
  GenericParam_t owner;
  TypeDefOrRef_t constraint;
} MD_GenericParamConstraint;

typedef struct {
  MethodDefOrRef_t method;
  Blob_t instantiation;
} MD_MethodSpec;

#endif