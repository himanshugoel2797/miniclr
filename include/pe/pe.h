// Copyright (c) 2017 Himanshu Goel
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
#ifndef MINICLR_PE_H_
#define MINICLR_PE_H_

#include <stdint.h>
#include <stddef.h>

#include "platform.h"

typedef struct PEInfo PEInfo;

int
PE_RVAToOffset(const PEInfo *info, uint32_t rva, uint32_t *offset);

int
PE_LoadData(uint8_t *data, size_t data_len, char **argv, int argc, PEInfo *info);

#endif