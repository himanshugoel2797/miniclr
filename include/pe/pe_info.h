// Copyright (c) 2017 Himanshu Goel
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef PEINFO_H_
#define PEINFO_H_

#include <stdint.h>
#include "cli_file_types.h"
#include "metadata_info.h"
#include "pe_int.h"

typedef struct PEInfo {
    uint8_t *data;
    size_t sz;
    char **argv;
    int argc;
    uint32_t section_hdr_cnt;

    PEOptHeader *opt_hdr;
    PESectionHeader *section_table;

    uint8_t *text;
    uint8_t *import_table;
    uint8_t *import_addr_table;
    CLIHeader *cli_hdr;

    Metadata mdata;
} PEInfo;

#endif