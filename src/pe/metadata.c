/**
 * Copyright (c) 2017 Himanshu Goel
 * 
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */
#include <stdio.h>
#include <string.h>

#include "platform.h"
#include "pe/pe_info.h"
#include "pe/metadata.h"
#include "pe/metadata_int.h"
#include "pe/pe_int.h"
#include "pe/cli_file_types.h"

int
Metadata_Load(PEInfo *info) {
    uint32_t metadata_root_off = 0, metadata_str_name_len = 0;
    uint8_t *metadata_table = NULL;
    CLIHeader *cli_hdr = NULL;
    MetadataRoot *metadata_root = NULL;
    MetadataRoot2 *metadata_root2 = NULL;
    StreamHeader *strm_hdr = NULL;
    MetadataStreamHeader *mdata_strm_hdr = NULL;

    //Read the CLI header to get the metadata root
    cli_hdr = info->cli_hdr;

    if(PE_RVAToOffset(info, cli_hdr->metadata.rva, &metadata_root_off) != 1)
        return -1;  //Can't find metadata table

    metadata_table = &info->data[metadata_root_off];
    metadata_root = (MetadataRoot*)metadata_table;
    info->mdata.metadata_root_off = metadata_root_off;

    //Parse the metadata root
    if(metadata_root->magic != METADATA_ROOT_MAGIC)
        return -1;  //Invalid metadata root

    //Find the end of the struct
    for(;metadata_root->version_str[metadata_str_name_len]; metadata_str_name_len++);
    metadata_str_name_len = (metadata_str_name_len + 3) & ~0x03;
    metadata_root2 = (MetadataRoot2*)&metadata_table[sizeof(MetadataRoot) + metadata_str_name_len];

    //Parse the stream headers and store them in the PEInfo
    strm_hdr = metadata_root2->streams;
    for(int i = 0; i < metadata_root2->streamCount; i++) {

        int next_hdr = ((strlen(strm_hdr->stream_str) + 1 + 3) & ~0x3) + sizeof(StreamHeader);

        if(strcmp(strm_hdr->stream_str, "#~") == 0) {
            info->mdata.metadata_stream_off = strm_hdr->offset;
        }else if(strcmp(strm_hdr->stream_str, "#Strings") == 0) {
            info->mdata.string_heap_off = strm_hdr->offset;
        }else if(strcmp(strm_hdr->stream_str, "#US") == 0) {
            info->mdata.us_heap_off = strm_hdr->offset;
        }else if(strcmp(strm_hdr->stream_str, "#GUID") == 0) {
            info->mdata.guid_heap_off = strm_hdr->offset;
        }else if(strcmp(strm_hdr->stream_str, "#Blob") == 0) {
            info->mdata.blob_heap_off = strm_hdr->offset;
        }

        strm_hdr = (StreamHeader*)((uint8_t*)strm_hdr + next_hdr);
    }

    //Store an array of offsets of the sub-tables in the #~ table
    mdata_strm_hdr = (MetadataStreamHeader*)&metadata_table[info->mdata.metadata_stream_off];

    

    return 0;
}

int
Metadata_GetObject(uint32_t id, void *obj) {

    return 0;
}