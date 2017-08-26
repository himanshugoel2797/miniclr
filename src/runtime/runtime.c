#include "runtime/runtime.h"
#include "platform.h"

static List *modules;

int Runtime_Initialize(RuntimeInformation *r_info) {

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

  // TODO: setup list of references, requesting load for any references that are
  // not present
  // Find the references in the reference list and specify the indices.

  List_AddEntry(modules, a_info);
  return 0;
}

int Runtime_GenerateCode(uint32_t token) { return 0; }

int Runtime_GenerateType(uint32_t token) { return 0; }