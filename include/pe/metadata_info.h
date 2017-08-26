#ifndef MINICLR_METADATA_INFO_H
#define MINICLR_METADATA_INFO_H

#include <stdint.h>

#define METADATA_STREAM_COUNT 48

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
  
#endif