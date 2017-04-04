// Copyright (c) 2017 Himanshu Goel
// 
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#ifndef MINICLR_PE_INT_H_
#define MINICLR_PE_INT_H_

#include <stdint.h>
#include <stddef.h>

#include "metadata.h"

#define PE_MAGIC_0_0 0x4D
#define PE_MAGIC_0_1 0x5A

#define PE_SIG_OFF_LOC 0x3C

#define PE_MAGIC_1 0x00004550

#define PE_MAGIC_32BIT 0x010B
#define PE_MAGIC_64BIT 0x020B

typedef struct {
	uint32_t magic;
	uint16_t machine;
	uint16_t numberOfSections;
	uint32_t timeDateStamp;
	uint32_t pointerToSymbolTable;
	uint32_t numberOfSymbols;
	uint16_t sizeOfOptionalHeader;
	uint16_t characteristics;
} PEHeader;

typedef struct {
    uint32_t rva;
    uint32_t size;
} PEDataDirectory;

// 1 byte aligned
typedef struct {
	uint16_t magic; // 0x010b - PE32, 0x020b - PE32+ (64 bit)
	uint8_t  majorLinkerVersion;
	uint8_t  minorLinkerVersion;
	uint32_t sizeOfCode;
	uint32_t sizeOfInitializedData;
	uint32_t sizeOfUninitializedData;
	uint32_t addressOfEntryPoint;
	uint32_t baseOfCode;
	uint32_t baseOfData;
	uint32_t imageBase;
	uint32_t sectionAlignment;
	uint32_t fileAlignment;
	uint16_t majorOperatingSystemVersion;
	uint16_t minorOperatingSystemVersion;
	uint16_t majorImageVersion;
	uint16_t minorImageVersion;
	uint16_t majorSubsystemVersion;
	uint16_t minorSubsystemVersion;
	uint32_t win32VersionValue;
	uint32_t sizeOfImage;
	uint32_t sizeOfHeaders;
	uint32_t checkSum;
	uint16_t subsystem;
	uint16_t dllCharacteristics;
	uint32_t sizeOfStackReserve;
	uint32_t sizeOfStackCommit;
	uint32_t sizeOfHeapReserve;
	uint32_t sizeOfHeapCommit;
	uint32_t loaderFlags;
	uint32_t numberOfDataDirectories;
    PEDataDirectory dataDirectories[0];
}PEOptHeader;

typedef struct { // size 40 bytes
	char name[8];
	uint32_t virtualSize;
	uint32_t virtualAddress;
	uint32_t sizeOfRawData;
	uint32_t pointerToRawData;
	uint32_t pointerToRealocations;
	uint32_t pointerToLinenumbers;
	uint16_t numberOfRealocations;
	uint16_t numberOfLinenumbers;
	uint32_t characteristics;
} PESectionHeader;

#endif