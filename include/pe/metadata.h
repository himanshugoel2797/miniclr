// Copyright (c) 2017 Himanshu Goel
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef MINICLR_METADATA_H_
#define MINICLR_METADATA_H_

#include <stdint.h>

#include "pe.h"
#include "types.h"

#define METADATA_STREAM_COUNT 48

typedef enum {
  MetadataType_Module = 0x00,
  MetadataType_TypeRef = 0x01,
  MetadataType_TypeDef = 0x02,
  MetadataType_Field = 0x04,
  MetadataType_MethodDef = 0x06,
  MetadataType_Param = 0x08,
  MetadataType_InterfaceImpl = 0x09,
  MetadataType_MemberRef = 0x0A,
  MetadataType_Constant = 0x0B,
  MetadataType_CustomAttribute = 0x0C,
  MetadataType_FieldMarshal = 0x0D,
  MetadataType_DeclSecurity = 0x0E,
  MetadataType_ClassLayout = 0x0F,
  MetadataType_FieldLayout = 0x10,
  MetadataType_StandAloneSig = 0x11,
  MetadataType_EventMap = 0x12,
  MetadataType_Event = 0x14,
  MetadataType_PropertyMap = 0x15,
  MetadataType_Property = 0x17,
  MetadataType_MethodSemantics = 0x18,
  MetadataType_MethodImpl = 0x19,
  MetadataType_ModuleRef = 0x1A,
  MetadataType_TypeSpec = 0x1B,
  MetadataType_ImplMap = 0x1C,
  MetadataType_FieldRVA = 0x1D,
  MetadataType_Assembly = 0x20,
  MetadataType_AssemblyRef = 0x23,
  MetadataType_File = 0x26,
  MetadataType_ExportedType = 0x27,
  MetadataType_ManifestResource = 0x28,
  MetadataType_NestedClass = 0x29,
  MetadataType_GenericParam = 0x2A,
  MetadataType_MethodSpec = 0x2B,
  MetadataType_GenericParamConstraint = 0x2C,
} MetadataType;

typedef struct {
  uint32_t metadata_root_off;

  uint32_t string_heap_off;
  uint32_t string_heap_size;

  uint32_t us_heap_off;
  uint32_t us_heap_size;

  uint32_t blob_heap_off;
  uint32_t blob_heap_size;

  uint32_t guid_heap_off;
  uint32_t guid_heap_size;

  uint32_t metadata_stream_sz;

  uint32_t metadata_stream_off;
  uint8_t *metadata_stream_data;
  uint32_t metadata_streams[METADATA_STREAM_COUNT];
  uint32_t metadata_stream_rows[METADATA_STREAM_COUNT];
} Metadata;

int Metadata_Load(PEInfo *info);

MetadataType Metadata_GetType(uint32_t id);

uint32_t Metadata_BuildToken(MetadataType t, uint32_t idx);

int Metadata_GetObject(PEInfo *info, uint32_t id, void *obj);

const char *Metadata_GetString(PEInfo *info, String_t off);

size_t Metadata_GetItemSize(PEInfo *info, MetadataType t);

uint32_t Metadata_GetItemCount(PEInfo *info, MetadataType t);

#endif