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


#endif