#ifndef MINICLR_RUNTIME_H
#define MINICLR_RUNTIME_H

#include "list.h"
#include "pe/pe_info.h"
#include <stdint.h>

#define TypePresentFlag (1 << 31)

typedef struct TypeInformation {
    uint32_t *vtable;
    uint32_t *fields;
    uint32_t flags;
    int vtable_cnt;
    int field_cnt;
} TypeInformation;

typedef struct AssemblyInformation {
    uint32_t *references;
    TypeInformation *types;
    uint64_t *compiled_mthds;
    PEInfo *info;

    int reference_cnt;
    int type_cnt;
    int compiled_mthd_cnt;
} AssemblyInformation;

typedef struct {
    List *modules;
} RuntimeInformation;

int Runtime_Initialize(void);

int Runtime_LoadAssembly(PEInfo *info);

int Runtime_BuildVTable(int assembly_idx, uint32_t token,
                        TypeInformation *type);

int Runtime_GenerateCode(int assembly_idx, uint32_t token, uint64_t *code_addr);

int Runtime_CallMethodByName(const char *assembly_name,
                             const char *method_name);

#endif