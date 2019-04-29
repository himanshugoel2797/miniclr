// Copyright (c) 2017 Himanshu Goel
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef MINICLR_CLI_FILE_TYPES_H_
#define MINICLR_CLI_FILE_TYPES_H_

#include <stdint.h>

#include "pe_int.h"

typedef enum {
    CLIHeaderFlag_ILOnly = (1 << 0),
    CLIHeaderFlag_32BitRequired = (1 << 1),
    CLIHeaderFlag_StrongNameSigned = (1 << 3),
    CLIHeaderFlag_NativeEntryPoint = (1 << 4),
} CLIHeaderFlag;

typedef struct {
    uint32_t headerSize;
    uint16_t majorVersion;
    uint16_t minorVersion;
    PEDataDirectory metadata;
    CLIHeaderFlag flags;
    uint32_t entryPointToken;
    PEDataDirectory resources;
    PEDataDirectory strongNameSignature;
    PEDataDirectory codeManagerTable;
    PEDataDirectory vTableFixups;
    PEDataDirectory exportAddressTableJumps;
    PEDataDirectory managedNativeHeader;
} CLIHeader;

typedef enum {
    MethodDataFlag_Tiny = 0x2,
    MethodDataFlag_Fat = 0x3,
    MethodDataFlag_MoreSects = 0x8,
    MethodDataFlag_InitLocals = 0x10,
} MethodDataFlag;

typedef struct {
    uint8_t flags : 2;
    uint8_t size : 6;
} MethodDataTinyHeader;

typedef struct {
    uint16_t flags : 12;
    uint16_t size : 4;
    uint16_t maxStack;
    uint32_t codeSize;
    uint32_t localVarSigToken;
} MethodDataFatHeader;

typedef enum {
    ExceptionClauseFlags_Filter = 0x01,
    ExceptionClauseFlags_Finally = 0x02,
    ExceptionClauseFlags_Fault = 0x04,
} ExceptionClauseFlags;

typedef struct {
    uint16_t flags;
    uint16_t tryOffset;
    uint32_t tryLength : 8;
    uint32_t handlerOffset : 16;
    uint32_t handlerLength : 8;
    uint32_t classToken;
    uint32_t filterOffset;
} ExceptionClauseSmall;

typedef struct {
    uint32_t flags;
    uint32_t tryOffset;
    uint32_t tryLength;
    uint32_t handlerOffset;
    uint32_t handlerLength;
    uint32_t classToken;
    uint32_t filterOffset;
} ExceptionClauseFat;

typedef enum {
    MethodDataSectionHeader_EHTable = 0x1,
    MethodDataSectionHeader_FatFormat = 0x40,
    MethodDataSectionHeader_MoreSects = 0x80,
} MethodDataSectionHeaderFlags;

typedef struct {
    uint8_t kind;
    uint8_t dataSize;
    uint16_t reserved;
    ExceptionClauseSmall clauses[0];
} MethodDataSectionSmallHeader;

typedef struct {
    uint32_t kind : 8;
    uint32_t dataSize : 24;
    ExceptionClauseFat clauses[0];
} MethodDataSectionFatHeader;

#endif