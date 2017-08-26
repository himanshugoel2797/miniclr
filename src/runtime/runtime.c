#include "runtime/runtime.h"
#include "platform.h"
#include "pe/metadata.h"
#include "pe/metadata_int.h"
#include <string.h>
#include <stdio.h>

static List *modules;

int Runtime_Initialize(void) {

  modules = List_Create();

  return 0;
}

int Runtime_LoadAssembly(PEInfo *info) {
  AssemblyInformation *a_info = p_malloc(sizeof(AssemblyInformation));

  a_info->reference_cnt = Metadata_GetItemCount(info, MetadataType_AssemblyRef);
  a_info->type_cnt = Metadata_GetItemCount(info, MetadataType_TypeDef);
  a_info->compiled_mthd_cnt =
      Metadata_GetItemCount(info, MetadataType_MethodDef);
  a_info->info = info;

  a_info->references = p_malloc(sizeof(uint32_t) * a_info->reference_cnt);
  a_info->types = p_malloc(sizeof(TypeInformation) * a_info->type_cnt);
  a_info->compiled_mthds =
      p_malloc(sizeof(uint64_t) * a_info->compiled_mthd_cnt);

  memset(a_info->references, 0, sizeof(uint32_t) * a_info->reference_cnt);
  memset(a_info->types, 0, sizeof(TypeInformation) * a_info->type_cnt);
  memset(a_info->compiled_mthds, 0,
         sizeof(uint64_t) * a_info->compiled_mthd_cnt);

  // setup list of references, requesting load for any references that are
  // not present
  // Find the references in the reference list and specify the indices.
  for(int i = 0; i < a_info->reference_cnt; i++) {
    MD_AssemblyRef assem_ref;
    Metadata_GetObject(info, Metadata_BuildToken(MetadataType_AssemblyRef, i + 1), &assem_ref);

    PEInfo ref_info;
    if(Platform_LoadAssembly(Metadata_GetString(info, assem_ref.name), &ref_info) != 0){
        printf("ERROR: Can't find referenced assembly.\r\n");
        exit(0);
    }
    a_info->references[i] = Runtime_LoadAssembly(&ref_info);
  }

  // Setup static methods
  for(int i = 0; i < a_info->compiled_mthd_cnt; i++) {
    a_info->compiled_mthds[i] = 0;
  }

  // Build type vtables.
  for(int i = 0; i < a_info->type_cnt; i++) {
    Runtime_BuildVTable(Metadata_BuildToken(MetadataType_MethodDef, i + 1), &a_info->types[i]); 
  }

  List_AddEntry(modules, a_info);
  return List_Length(modules) - 1;
}

int Runtime_BuildVTable(uint32_t token, TypeInformation *type) { return 0; }

int Runtime_GenerateCode(uint32_t token, uint64_t *code_addr) { 
    return 0; 
}

int Runtime_GenerateType(uint32_t token) { return 0; }

int Runtime_CallMethodByTokenAssemblyIndex(int assembly_idx, uint32_t token) {

    //Generate the method's code if it hasn't been generated

    //Call the method

    return 0;
}

int Runtime_CallMethodByToken(const char *assembly_name, uint32_t token) { 
    //Resolve the assembly and call 'CallMethodByTokenAssemblyIndex'
    return 0; 
}
int Runtime_CallMethodByName(const char *assembly_name, const char *method_name) {
    //Resolve the assembly and function and call 'CallMethodByTokenAssemblyIndex'
    return 0;
}