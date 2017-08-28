/**
 * Copyright (c) 2017 Himanshu Goel
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */
#include <stdio.h>
#include <string.h>

#include "pe/cli_file_types.h"
#include "pe/metadata.h"
#include "pe/metadata_int.h"
#include "pe/pe_info.h"
#include "pe/pe_int.h"
#include "platform.h"

int Metadata_Load(PEInfo *info) {
  uint32_t metadata_root_off = 0, metadata_str_name_len = 0;
  uint8_t *metadata_table = NULL;
  CLIHeader *cli_hdr = NULL;
  MetadataRoot *metadata_root = NULL;
  MetadataRoot2 *metadata_root2 = NULL;
  StreamHeader *strm_hdr = NULL;
  MetadataStreamHeader *mdata_strm_hdr = NULL;

  // Read the CLI header to get the metadata root
  cli_hdr = info->cli_hdr;

  if (PE_RVAToOffset(info, cli_hdr->metadata.rva, &metadata_root_off) != 1)
    return -1; // Can't find metadata table

  metadata_table = &info->data[metadata_root_off];
  metadata_root = (MetadataRoot *)metadata_table;
  info->mdata.metadata_root_off = metadata_root_off;

  // Parse the metadata root
  if (metadata_root->magic != METADATA_ROOT_MAGIC)
    return -1; // Invalid metadata root

  // Find the end of the struct
  for (; metadata_root->version_str[metadata_str_name_len];
       metadata_str_name_len++)
    ;
  metadata_str_name_len = (metadata_str_name_len + 3) & ~0x03;
  metadata_root2 = (MetadataRoot2 *)&metadata_table[sizeof(MetadataRoot) +
                                                    metadata_str_name_len];

  // Parse the stream headers and store them in the PEInfo
  strm_hdr = metadata_root2->streams;
  for (int i = 0; i < metadata_root2->streamCount; i++) {

    int next_hdr =
        ((strlen(strm_hdr->stream_str) + 1 + 3) & ~0x3) + sizeof(StreamHeader);

    if (strcmp(strm_hdr->stream_str, "#~") == 0) {
      info->mdata.metadata_stream_off = strm_hdr->offset;
      info->mdata.metadata_stream_sz = strm_hdr->size;
    } else if (strcmp(strm_hdr->stream_str, "#Strings") == 0) {
      info->mdata.string_heap_off = strm_hdr->offset;
      info->mdata.string_heap_size = strm_hdr->size;
    } else if (strcmp(strm_hdr->stream_str, "#US") == 0) {
      info->mdata.us_heap_off = strm_hdr->offset;
      info->mdata.us_heap_size = strm_hdr->size;
    } else if (strcmp(strm_hdr->stream_str, "#GUID") == 0) {
      info->mdata.guid_heap_off = strm_hdr->offset;
      info->mdata.guid_heap_size = strm_hdr->size;
    } else if (strcmp(strm_hdr->stream_str, "#Blob") == 0) {
      info->mdata.blob_heap_off = strm_hdr->offset;
      info->mdata.blob_heap_size = strm_hdr->size;
    }

    strm_hdr = (StreamHeader *)((uint8_t *)strm_hdr + next_hdr);
  }

  // Store an array of offsets of the sub-tables in the #~ table
  mdata_strm_hdr =
      (MetadataStreamHeader *)&metadata_table[info->mdata.metadata_stream_off];

  info->mdata.metadata_stream_data = mdata_strm_hdr->data;

  uint32_t cur_off = sizeof(uint32_t) * bitcntll(mdata_strm_hdr->valid);
  uint32_t row_idx = 0;

  for (int i = 0; i < METADATA_STREAM_COUNT; i++) {
    info->mdata.metadata_stream_rows[i] = 0;
    info->mdata.metadata_streams[i] = 0;

    if ((1ull << i) & mdata_strm_hdr->valid) {
      info->mdata.metadata_stream_rows[i] = mdata_strm_hdr->rows[row_idx];
      row_idx++;
    }
  }

  row_idx = 0;
  for (int i = 0;
       i < METADATA_STREAM_COUNT && row_idx < bitcntll(mdata_strm_hdr->valid);
       i++) {

    if ((1ull << i) & mdata_strm_hdr->valid) {
      info->mdata.metadata_streams[i] = cur_off;
      cur_off += Metadata_GetItemSize(info, i) * mdata_strm_hdr->rows[row_idx];
      row_idx++;
    }
  }

  return 0;
}

MetadataType Metadata_GetType(uint32_t id) { return id >> 24; }

static inline void append_uint8(uint8_t *src, uint8_t *dst) {
  uint32_t *s = (uint32_t *)src;
  s[0] = *(uint8_t *)dst;
}

static inline void append_uint16(uint8_t *src, uint8_t *dst) {
  uint32_t *s = (uint32_t *)src;
  s[0] = *(uint16_t *)dst;
}

static inline void append_uint32(uint8_t *src, uint8_t *dst) {
  uint32_t *s = (uint32_t *)src;
  s[0] = *(uint32_t *)dst;
}

int Metadata_GetObject(PEInfo *info, uint32_t id, void *obj) {

  MetadataType t = Metadata_GetType(id);
  uint32_t idx = (id & 0xFFFFFF);

  if (idx == 0)
    return -1;

  idx--;

  if (idx >= info->mdata.metadata_stream_rows[t])
    return -2;

  MetadataStreamHeader *mdata_strm_hdr =
      (MetadataStreamHeader *)&info->data[info->mdata.metadata_root_off +
                                          info->mdata.metadata_stream_off];

  uint8_t *baseData =
      &info->mdata.metadata_stream_data[info->mdata.metadata_streams[t] +
                                        Metadata_GetItemSize(info, t) * idx];

  uint8_t *targetData = obj;

  char *rep = metadataTypeFields[t];

  while (*rep != 0) {
    switch (*rep) {
    case 's':
      append_uint16(targetData, baseData);
      baseData += sizeof(uint16_t);
      break;
    case 'u':
      append_uint32(targetData, baseData);
      baseData += sizeof(uint32_t);
      break;
    case 'b':
      append_uint8(targetData, baseData);
      baseData += sizeof(uint8_t);
      break;
    case 'S':
      if (mdata_strm_hdr->heapSizes & 0x1) {
        append_uint32(targetData, baseData);
        baseData += sizeof(uint32_t);
      } else {
        append_uint16(targetData, baseData);
        baseData += sizeof(uint16_t);
      }
      break;
    case 'G':
      if (mdata_strm_hdr->heapSizes & 0x2) {
        append_uint32(targetData, baseData);
        baseData += sizeof(uint32_t);
      } else {
        append_uint16(targetData, baseData);
        baseData += sizeof(uint16_t);
      }
      break;
    case 'F':
      if (info->mdata.metadata_stream_rows[MetadataType_Field] >= (1 << 16)) {
        append_uint32(targetData, baseData);
        baseData += sizeof(uint32_t);
      } else {
        append_uint16(targetData, baseData);
        baseData += sizeof(uint16_t);
      }
      break;
    case 'M':
      if (info->mdata.metadata_stream_rows[MetadataType_MethodDef] >=
          (1 << 16)) {
        append_uint32(targetData, baseData);
        baseData += sizeof(uint32_t);
      } else {
        append_uint16(targetData, baseData);
        baseData += sizeof(uint16_t);
      }
      break;
    case 'B':
      if (mdata_strm_hdr->heapSizes & 0x4) {
        append_uint32(targetData, baseData);
        baseData += sizeof(uint32_t);
      } else {
        append_uint16(targetData, baseData);
        baseData += sizeof(uint16_t);
      }
      break;
    case 'P':
      if (info->mdata.metadata_stream_rows[MetadataType_Param] >= (1 << 16)) {
        append_uint32(targetData, baseData);
        baseData += sizeof(uint32_t);
      } else {
        append_uint16(targetData, baseData);
        baseData += sizeof(uint16_t);
      }
      break;
    case 'T':
      if (info->mdata.metadata_stream_rows[MetadataType_TypeDef] >= (1 << 16)) {
        append_uint32(targetData, baseData);
        baseData += sizeof(uint32_t);
      } else {
        append_uint16(targetData, baseData);
        baseData += sizeof(uint16_t);
      }
      break;
    case 'E':
      if (info->mdata.metadata_stream_rows[MetadataType_Event] >= (1 << 16)) {
        append_uint32(targetData, baseData);
        baseData += sizeof(uint32_t);
      } else {
        append_uint16(targetData, baseData);
        baseData += sizeof(uint16_t);
      }
      break;
    case 'R':
      if (info->mdata.metadata_stream_rows[MetadataType_Property] >=
          (1 << 16)) {
        append_uint32(targetData, baseData);
        baseData += sizeof(uint32_t);
      } else {
        append_uint16(targetData, baseData);
        baseData += sizeof(uint16_t);
      }
      break;
    case 'm':
      if (info->mdata.metadata_stream_rows[MetadataType_MethodDef] >=
          (1 << 16)) {
        append_uint32(targetData, baseData);
        baseData += sizeof(uint32_t);
      } else {
        append_uint16(targetData, baseData);
        baseData += sizeof(uint16_t);
      }
      break;
    case 'g':
      if (info->mdata.metadata_stream_rows[MetadataType_GenericParam] >=
          (1 << 16)) {
        append_uint32(targetData, baseData);
        baseData += sizeof(uint32_t);
      } else {
        append_uint16(targetData, baseData);
        baseData += sizeof(uint16_t);
      }
      break;
    default: {
      if (*rep >= '0' && *rep <= '>') {
        int bitCnt = specialCodingBitCnt[*rep - '0'];
        char *coding = specialCoding[*rep - '0'];
        uint32_t val = 0;
        if (info->mdata.specialCodingSize[*rep - '0'] == sizeof(uint16_t)) {
          append_uint16((uint8_t *)&val, baseData);
          baseData += sizeof(uint16_t);
        } else {
          append_uint32((uint8_t *)&val, baseData);
          baseData += sizeof(uint32_t);
        }

        // Decode val and convert it into a token
        uint32_t key = val & ~(0xFFFFFFFF << bitCnt);
        *(uint32_t *)targetData =
            Metadata_BuildToken(coding[key], val >> bitCnt);
      }
    } break;
    }

    targetData += sizeof(uint32_t);
    rep++;
  }

  return 0;
}

uint32_t Metadata_BuildToken(MetadataType t, uint32_t idx) {
  return (t << 24) | (idx & 0xFFFFFF);
}

const char *Metadata_GetString(PEInfo *info, String_t off) {

  return &info->data[info->mdata.metadata_root_off +
                     info->mdata.string_heap_off + off];
}

size_t Metadata_GetItemSize(PEInfo *info, MetadataType t) {

  char *rep = metadataTypeFields[t];
  if (rep == NULL)
    return 0;

  size_t sz = 0;

  MetadataStreamHeader *mdata_strm_hdr =
      (MetadataStreamHeader *)&info->data[info->mdata.metadata_root_off +
                                          info->mdata.metadata_stream_off];

  while (*rep != 0) {
    switch (*rep) {
    case 's':
      sz += sizeof(uint16_t);
      break;
    case 'u':
      sz += sizeof(uint32_t);
      break;
    case 'b':
      sz += sizeof(uint8_t);
      break;
    case 'S':
      if (mdata_strm_hdr->heapSizes & 0x1)
        sz += sizeof(uint32_t);
      else
        sz += sizeof(uint16_t);
      break;
    case 'G':
      if (mdata_strm_hdr->heapSizes & 0x2)
        sz += sizeof(uint32_t);
      else
        sz += sizeof(uint16_t);
      break;
    case 'F':
      if (info->mdata.metadata_stream_rows[MetadataType_Field] >= (1 << 16))
        sz += sizeof(uint32_t);
      else
        sz += sizeof(uint16_t);
      break;
    case 'M':
      if (info->mdata.metadata_stream_rows[MetadataType_MethodDef] >= (1 << 16))
        sz += sizeof(uint32_t);
      else
        sz += sizeof(uint16_t);
      break;
    case 'B':
      if (mdata_strm_hdr->heapSizes & 0x4)
        sz += sizeof(uint32_t);
      else
        sz += sizeof(uint16_t);
      break;
    case 'P':
      if (info->mdata.metadata_stream_rows[MetadataType_Param] >= (1 << 16))
        sz += sizeof(uint32_t);
      else
        sz += sizeof(uint16_t);
      break;
    case 'T':
      if (info->mdata.metadata_stream_rows[MetadataType_TypeDef] >= (1 << 16))
        sz += sizeof(uint32_t);
      else
        sz += sizeof(uint16_t);
      break;
    case 'E':
      if (info->mdata.metadata_stream_rows[MetadataType_Event] >= (1 << 16))
        sz += sizeof(uint32_t);
      else
        sz += sizeof(uint16_t);
      break;
    case 'R':
      if (info->mdata.metadata_stream_rows[MetadataType_Property] >= (1 << 16))
        sz += sizeof(uint32_t);
      else
        sz += sizeof(uint16_t);
      break;
    case 'm':
      if (info->mdata.metadata_stream_rows[MetadataType_MethodDef] >= (1 << 16))
        sz += sizeof(uint32_t);
      else
        sz += sizeof(uint16_t);
      break;
    case 'g':
      if (info->mdata.metadata_stream_rows[MetadataType_GenericParam] >=
          (1 << 16))
        sz += sizeof(uint32_t);
      else
        sz += sizeof(uint16_t);
      break;
    default: {
      if (*rep >= '0' && *rep <= '>') {
        int bitCnt = specialCodingBitCnt[*rep - '0'];
        char *coding = specialCoding[*rep - '0'];

        int netSize = sizeof(uint16_t);

        while (coding != NULL && *coding != 'z') {
          if (*coding != 'q') {
            if (info->mdata.metadata_stream_rows[*coding] >=
                (1 << (16 - bitCnt))) {
              netSize = sizeof(uint32_t);
            }
          }
          coding++;
        }

        info->mdata.specialCodingSize[*rep - '0'] = netSize;
        sz += netSize;
      }
    }
    }

    rep++;
  }

  return sz;
}

uint32_t Metadata_GetItemCount(PEInfo *info, MetadataType t) {
  return info->mdata.metadata_stream_rows[t];
}

void *Metadata_GetMethodBody(PEInfo *info, uint32_t token) {
  // Retrieve the offset at the RVA from the methoddef token.
  MD_MethodDef mthd_def;
  if (Metadata_GetObject(info, token, &mthd_def) != 0)
    return NULL;

  uint32_t offset = -1;

  if (PE_RVAToOffset(info, mthd_def.rva, &offset) != 1)
    return NULL;

  return &info->data[offset];

  // TODO: start writing JIT engine that takes the method body and generates
  // native code from it
  // TODO: the JIT engine emits a call to its code generation routines for calls
  // that haven't been resolved yet, patching out the call once it has been
  // resolved.
}

uint32_t Metadata_GetItemIndex(uint32_t token) { return token & 0xFFFFFF; }