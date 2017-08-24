/**
 * Copyright (c) 2017 Himanshu Goel
 *
 * This software is released under the MIT License.
 * https://opensource.org/licenses/MIT
 */
#include <stdbool.h>
#include <string.h>

#include "pe/pe.h"
#include "pe/pe_info.h"
#include "pe/metadata.h"
#include "pe/pe_int.h"
#include "platform.h"

int
PE_RVAToOffset(const PEInfo *info, uint32_t rva, uint32_t *offset) {

    //Loop through the section tables to figure out the offset
    for(int i = 0; i < info->section_hdr_cnt; i++) {

        if(info->section_table[i].virtualAddress <= rva && info->section_table[i].virtualAddress + info->section_table[i].virtualSize > rva) {
            //Save the text section
            if(info->section_table[i].sizeOfRawData < (rva - info->section_table[i].virtualAddress)) {
                *offset = 0;
                return 0;
            }

            *offset = info->section_table[i].pointerToRawData + (rva - info->section_table[i].virtualAddress);
            return 1;
        }
    }

    return -1;
}

int
PE_LoadData(uint8_t *data, size_t data_len, char **argv, int argc, PEInfo *info) {

    uint32_t pe_sig_off = 0, pe_text_off = 0, import_table_off = 0, import_addr_table_off = 0, cli_hdr_off = 0;
    bool supported_arch = false;
    PEHeader *pe_hdr = NULL;
    PEOptHeader *opt_hdr = NULL;
    PESectionHeader *section_hdr = NULL;
    PEDataDirectory *import_table_ddir = NULL, *import_addr_table_ddir = NULL, *cli_hdr_ddir = NULL;

    //Parse the program and find the relevant .NET sections and save their offsets
    if(PE_MAGIC_0_0 != data[0] | PE_MAGIC_0_1 != data[1]) {
        return -1;  //Not a valid PE file
    }

    pe_sig_off = p_memtole32(&data[PE_SIG_OFF_LOC]);

    if(pe_sig_off >= data_len)
        return -1;  //Not a valid PE file

    pe_hdr = (PEHeader*)&data[pe_sig_off];
    if(pe_hdr->magic != PE_MAGIC_1)
        return -1;  //Not a valid PE file

    if(pe_hdr->sizeOfOptionalHeader < sizeof(PEOptHeader))
        return -1;  //Not a valid .NET library

    opt_hdr = (PEOptHeader*)&data[pe_sig_off + sizeof(PEHeader)];

#if defined(PE_32_BIT)
    if((opt_hdr->magic == PE_MAGIC_32BIT))
        supported_arch = true;
#endif

#if defined(PE_64_BIT)
    if((opt_hdr->magic == PE_MAGIC_64BIT))
        supported_arch = true;
#endif

    if(!supported_arch)
        return -2;  //Unsupported target architecture

    if(opt_hdr->numberOfDataDirectories < 15)
        return -1;  //Not a valid .NET executable

    import_table_ddir = &opt_hdr->dataDirectories[1];
    import_addr_table_ddir = &opt_hdr->dataDirectories[12];
    cli_hdr_ddir = &opt_hdr->dataDirectories[14];

    section_hdr = (PESectionHeader*)&data[pe_sig_off + sizeof(PEHeader) + pe_hdr->sizeOfOptionalHeader];

    //Iterate over the section headers, looking for desired sections
    for(int i = 0; i < pe_hdr->numberOfSections; i++) {
        if(strcmp(section_hdr[i].name, ".text") == 0) {
            //Save the text section
            pe_text_off = section_hdr[i].pointerToRawData;
        }
    }
    if(pe_text_off == 0)
        return -3;  //.text section not found!?!!


    //Setup the PE instance
    info->data = data;
    info->sz = data_len;
    info->argv = argv;
    info->argc = argc;
    info->opt_hdr = opt_hdr;
    info->section_table = section_hdr;
    info->section_hdr_cnt = pe_hdr->numberOfSections;
    info->text = &data[pe_text_off];

    //Get the required data directories
    if(PE_RVAToOffset(info, import_table_ddir->rva, &import_table_off) != 1)
        return -1;

    if(PE_RVAToOffset(info, import_addr_table_ddir->rva, &import_addr_table_off) != 1)
        return -1;

    if(PE_RVAToOffset(info, cli_hdr_ddir->rva, &cli_hdr_off) != 1)
        return -1;


    //Fill in the tables
    info->import_table = &data[import_table_off];
    info->import_addr_table = &data[import_addr_table_off];
    info->cli_hdr = (CLIHeader*)&data[cli_hdr_off];

    //Parse the metadata
    return Metadata_Load(info);
}