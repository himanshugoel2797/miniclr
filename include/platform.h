// Copyright (c) 2017 Himanshu Goel
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef MINICLR_PLATFORM_H_
#define MINICLR_PLATFORM_H_

#include <stdint.h>
#include <stdlib.h>
#include "pe/pe_info.h"

#ifdef __linux__

// Enable support for both 64 bit and 32 bit executables
#define PE_32_BIT
#define PE_64_BIT

#elif __CARDINAL__

// Enable support for only 64 bit executables
#define PE_64_BIT

#endif

#ifdef __x86_64__
#define bitcntll(x) __builtin_popcountll(x)
#endif

#ifndef p_malloc
#define p_malloc(x) malloc(x)
#endif

#ifndef p_free
#define p_free(x) free(x)
#endif

#ifdef __ORDER_LITTLE_ENDIAN__
#define p_memtole16(x) *(uint16_t *)(x)
#define p_memtole32(x) *(uint32_t *)(x)
#elif __ORDER_BIG_ENDIAN__

#endif

#if !defined(p_memtole32) | !defined(p_memtole16)
#error "p_memtole functions not defined"
#endif

int Platform_LoadAssembly(const char *assemblyName, PEInfo *info);

#endif