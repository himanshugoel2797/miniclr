// Copyright (c) 2017 Himanshu Goel
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef MINICLR_METADATA_INT_H_
#define MINICLR_METADATA_INT_H_

#include <stdint.h>

#include "metadata.h"
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
  uint8_t data[0];
} MetadataStreamHeader;

typedef enum {
  AssemblyHashAlgorithm_None = 0,
  AssemblyHashAlgorithm_Reserved = 0x8003,
  AssemblyHashAlgorithm_SHA1 = 0x8004,
} AssemblyHashAlgorithm;

typedef enum {
  AssemblyFlags_PublicKey = 0x0001,
  AssemblyFlags_Retargetable = 0x0100,
  AssemblyFlags_DisableJITcompileOptimizer = 0x4000,
  AssemblyFlags_EnableJITcompileTracking = 0x8000
} AssemblyFlags;

typedef enum {
  TypeAttributes_VisibilityMask = 0x0007,
  TypeAttributes_VisibilityMask_NotPublic = 0x0000,
  TypeAttributes_VisibilityMask_Public = 0x0001,
  TypeAttributes_VisibilityMask_NestedPublic = 0x0002,
  TypeAttributes_VisibilityMask_NestedPrivate = 0x0003,
  TypeAttributes_VisibilityMask_NestedFamily = 0x0004,
  TypeAttributes_VisibilityMask_NestedAssembly = 0x0005,
  TypeAttributes_VisibilityMask_NestedFamANDAssem = 0x0006,
  TypeAttributes_VisibilityMask_NestedFamORAssem = 0x0007,

  TypeAttributes_ClassLayout = 0x0018,
  TypeAttributes_ClassLayout_AutoLayout = 0x0000,
  TypeAttributes_ClassLayout_SequentialLayout = 0x0008,
  TypeAttributes_ClassLayout_ExplicitLayout = 0x0010,

  TypeAttributes_ClassSemantics = 0x0020,
  TypeAttributes_ClassSemantics_Class = 0x0000,
  TypeAttributes_ClassSemantics_Interface = 0x0020,

  TypeAttributes_Abstract = 0x0080,
  TypeAttributes_Sealed = 0x0100,
  TypeAttributes_SpecialName = 0x0400,

  TypeAttributes_Import = 0x1000,
  TypeAttributes_Serializable = 0x2000,

  TypeAttributes_StringFormatMask = 0x30000,
  TypeAttributes_StringFormatMask_AnsiClass = 0x0000,
  TypeAttributes_StringFormatMask_UnicodeClass = 0x10000,
  TypeAttributes_StringFormatMask_AutoClass = 0x20000,
  TypeAttributes_StringFormatMask_CustomFormatClass = 0x30000,

  TypeAttributes_BeforeFieldInit = 0x100000,

  TypeAttributes_RTSpecialName = 0x0800,
  TypeAttributes_HasSecurity = 0x40000,
  TypeAttributes_IsTypeForwarder = 0x200000,
} TypeAttributes;

typedef enum {
  FieldAttributes_CompilerControlled = 0x0000,
  FieldAttributes_Private = 0x0001,
  FieldAttributes_FamANDAssem = 0x0002,
  FieldAttributes_Assembly = 0x0003,
  FieldAttributes_Family = 0x0004,
  FieldAttributes_FamORAssem = 0x0005,
  FieldAttributes_Public = 0x0006,
  FieldAttributes_Static = 0x0010,
  FieldAttributes_InitOnly = 0x0020,
  FieldAttributes_Literal = 0x0040,
  FieldAttributes_NotSerialized = 0x0080,
  FieldAttributes_SpecialName = 0x0200,
  FieldAttributes_PInvokeImpl = 0x2000,
  FieldAttributes_RTSpecialName = 0x0400,
  FieldAttributes_HasFieldMarshal = 0x1000,
  FieldAttributes_HasDefault = 0x8000,
  FieldAttributes_HasFieldRVA = 0x0100,
} FieldAttributes;

typedef enum {
  ManifestResourceAttributes_Public = 0x0001,
  ManifestResourceAttributes_Private = 0x0002,
} ManifestResourceAttributes;

typedef enum {
  FileAttributes_ContainsMetaData = 0,
  FieldAttributes_ContainsNoMetaData = 1,
} FileAttributes;

typedef struct {
  uint32_t generation;
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

typedef enum {
  MethodAttributes_MemberAccessMask = 0x07,
  MethodAttributes_MemberAccessMask_CompilerControlled = 0x0,
  MethodAttributes_MemberAccessMask_Private = 0x1,
  MethodAttributes_MemberAccessMask_FamANDAssem = 0x2,
  MethodAttributes_MemberAccessMask_Assem = 0x3,
  MethodAttributes_MemberAccessMask_Family = 0x4,
  MethodAttributes_MemberAccessMask_FamORAssem = 0x5,
  MethodAttributes_MemberAccessMask_Public = 0x6,

  MethodAttributes_Static = 0x10,
  MethodAttributes_Final = 0x20,
  MethodAttributes_Virtual = 0x40,
  MethodAttributes_HideBySig = 0x80,

  MethodAttributes_VtableLayoutMask = 0x100,
  MethodAttributes_VtableLayoutMask_ReuseSlot = 0x0,
  MethodAttributes_VtableLayoutMask_NewSlot = 0x100,

  MethodAttributes_Strict = 0x200,
  MethodAttributes_Abstract = 0x400,
  MethodAttributes_SpecialName = 0x800,

  MethodAttributes_Interop_PInvokeImpl = 0x2000,
  MethodAttributes_Interop_UnmanagedExport = 0x0008,

  MethodAttributes_RTSpecialName = 0x1000,
  MethodAttributes_HasSecurity = 0x4000,
  MethodAttributes_RequireSecObject = 0x8000,
} MethodAttributes;

typedef enum {
  MethodImplAttributes_CodeTypeMask = 0x03,
  MethodImplAttributes_CodeTypeMask_IL = 0x00,
  MethodImplAttributes_CodeTypeMask_Native = 0x01,
  MethodImplAttributes_CodeTypeMask_OPTIL = 0x02,
  MethodImplAttributes_CodeTypeMask_Runtime = 0x03,

  MethodImplAttributes_ManagedMask = 0x04,
  MethodImplAttributes_ManagedMask_Unmanaged = 0x04,
  MethodImplAttributes_ManagedMask_Managed = 0x00,

  MethodImplAttributes_ForwardRef = 0x10,
  MethodImplAttributes_PreserveSig = 0x80,
  MethodImplAttributes_InternalCall = 0x1000,
  MethodImplAttributes_Synchronized = 0x20,
  MethodImplAttributes_NoInlining = 0x8,
  MethodImplAttributes_MaxMethodImplVal = 0xffff,
  MethodImplAttributes_NoOptimization = 0x40,
} MethodImplAttributes;

typedef struct {
  uint32_t rva;
  uint32_t implFlags;
  uint32_t flags;
  String_t name;
  Blob_t signature;
  Param_t paramList;
} MD_MethodDef;

typedef struct {
  uint32_t flags;
  uint32_t sequence;
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
  uint32_t type;
  HasConstant_t parent;
  Blob_t value;
} MD_Constant;

typedef struct {
  HasCustomAttribute_t parent;
  CustomAttribute_t type;
  Blob_t value;
} MD_CustomAttribute;

typedef struct {
  Parent_t parent;
  Blob_t nativeType;
} MD_FieldMarshal;

typedef struct {
  uint32_t action;
  Parent_t parent;
  Blob_t permissionSet;
} MD_DeclSecurity;

typedef struct {
  uint32_t packingSize;
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
  uint32_t eventFlags;
  String_t name;
  TypeDefOrRef_t eventType;
} MD_Event;

typedef struct {
  TypeDef_t parent;
  Property_t propertyList;
} MD_PropertyMap;

typedef struct {
  uint32_t flags;
  String_t name;
  Blob_t type;
} MD_Property;

typedef struct {
  uint32_t semantics;
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
  uint32_t mappingFlags;
  MemberForwarded_t forwarded;
  String_t importName;
  ModuleRef_t importScope;
} MD_ImplMap;

typedef struct {
  uint32_t rva;
  Field_t field;
} MD_FieldRVA;

typedef struct {
  AssemblyHashAlgorithm hashAlgId;
  uint32_t majorVer;
  uint32_t minorVer;
  uint32_t buildNumber;
  uint32_t revisionNumber;
  AssemblyFlags flags;
  Blob_t publicKey;
  String_t name;
  String_t culture;
} MD_Assembly;

typedef struct {
  uint32_t majorVer;
  uint32_t minorVer;
  uint32_t buildNumber;
  uint32_t revisionNumber;
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
  uint32_t idx;
  uint32_t flags;
  TypeOrMethodDef_t owner;
  String_t name;
} MD_GenericParam;

typedef struct {
  MethodDefOrRef_t method;
  Blob_t instantiation;
} MD_MethodSpec;

typedef struct {
  GenericParam_t owner;
  TypeDefOrRef_t constraint;
} MD_GenericParamConstraint;

// Management of above definitions
static size_t typeSizeMap[] = {sizeof(MD_Module),
                               sizeof(MD_TypeRef),
                               sizeof(MD_TypeDef),
                               0,
                               sizeof(MD_Field),
                               0,
                               sizeof(MD_MethodDef),
                               0,
                               sizeof(MD_Param),
                               sizeof(MD_InterfaceImpl),
                               sizeof(MD_MemberRef),
                               sizeof(MD_Constant),
                               sizeof(MD_CustomAttribute),
                               sizeof(MD_FieldMarshal),
                               sizeof(MD_DeclSecurity),
                               sizeof(MD_ClassLayout),
                               sizeof(MD_FieldLayout),
                               sizeof(MD_StandAloneSig),
                               sizeof(MD_EventMap),
                               0,
                               sizeof(MD_Event),
                               sizeof(MD_PropertyMap),
                               0,
                               sizeof(MD_Property),
                               sizeof(MD_MethodSemantics),
                               sizeof(MD_MethodImpl),
                               sizeof(MD_ModuleRef),
                               sizeof(MD_TypeSpec),
                               sizeof(MD_ImplMap),
                               sizeof(MD_FieldRVA),
                               0,
                               0,
                               sizeof(MD_Assembly),
                               0,
                               0,
                               sizeof(MD_AssemblyRef),
                               0,
                               0,
                               sizeof(MD_File),
                               sizeof(MD_ExportedType),
                               sizeof(MD_ManifestResource),
                               sizeof(MD_NestedClass),
                               sizeof(MD_GenericParam),
                               sizeof(MD_MethodSpec),
                               sizeof(MD_GenericParamConstraint)};

// s - short
// S - String
// G - Guid
// u - uint
// F - Field
// M - Method
// B - Blob
// P - Param
// T - TypeDef
// b - byte
// E - EventList
// R - Property
// m - MethodDef
// g - GenericParam

// 0 - TypeDefOrRef
// 1 - HasConstant
// 2 - ModuleRef
// 3 - HasCustomAttribute
// 4 - MethodDefOrRef
// 5 - HasDeclSecurity
// 6 - HasFieldMarshall
// 7 - Parent
// 8 - MemberRefParent
// 9 - ResolutionScope
//: - MemberForwarded
//; - HasSemantics
//< - CustomAttributeType
//= - TypeOrMethodDef
//> - Implementation

static char *metadataTypeFields[] = {"sSGGG",  // Module
                                     "9SS",    // TypeRef
                                     "uSS0FM", // TypeDef
                                     NULL,
                                     "sSB", // Field
                                     NULL,
                                     "ussSBP", // MethodDef
                                     NULL,
                                     "ssS", // Param
                                     "T0",  // InterfaceImpl
                                     "8SB", // MemberRef
                                     "s1B", // Constant
                                     "3<B", // CustomAttribute
                                     "6B",  // FieldMarshal
                                     "s5B", // DeclSecurity
                                     "suT", // ClassLayout
                                     "uF",  // FieldLayout
                                     "B",   // StandAloneSig
                                     "TE",  // EventMap
                                     NULL,
                                     "sS0", // Event
                                     "TR",  // PropertyMap
                                     NULL,
                                     "sSB",  // Property
                                     "sm;",  // MethodSemantics
                                     "T44",  // MethodImpl
                                     "S",    // ModuleRef
                                     "B",    // TypeSpec
                                     "s:S2", // ImplMap
                                     "uF",   // FieldRVA
                                     NULL,        NULL,
                                     "ussssuBSS", // Assembly
                                     NULL,        NULL,
                                     "ssssuBSSB", // AssemblyRef
                                     NULL,        NULL,
                                     "uSB",   // File
                                     "uTSS>", // ExportedType
                                     "uuS>",  // ManifestResource
                                     "TT",    // NestedClass
                                     "ss=S",  // GenericParam
                                     "4B",    // MethodSpec
                                     "g0"};   // GenericParamConstraint

#define SPECIAL_CODING_COUNT 15

static int specialCodingBitCnt[] = {2, 2, 0, 5, 1, 2, 1, 0,
                                    3, 2, 1, 1, 3, 1, 2};

static char *specialCoding[] = {
    "\x02\x01\x1Bqz",
    "\x04\x08\x17qz",
    NULL,
    "\x06\x04\x01\x02\x08\x09\x0A\x00\x0E\x17\x14\x11\x1A\x1B\x20\x23\x26\x27"
    "\x28qqqqqqqqqqqz",
    "\x06\x0Aqqqqqqz",
    "\x02\x06\x20qqqqqz",
    "\x04\x08qqqqqqqqz",
    NULL,
    "\x02\x01\x1A\x06\x1Bqqqqqz",
    "\x00\x1A\x23\x01qqqqqqqqz",
    "\x04\x06qqqqqqqqz",
    "\x14\x17qqqqqqz",
    "qq\x06\x0Aqqqqqqz",
    "\x02\x06qqqqqqqqqz",
    "\x26\x23\x27qqqqqqqqqqz",
};

#endif