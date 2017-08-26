#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "pe/pe.h"
#include "pe/pe_info.h"

#include "pe/metadata_int.h"

void help(const char *pname) {
  printf("%s [options] [executable]\n"
         "Minimal CLR runtime implementation.\n"
         "\tv - verbose output",
         pname);
}

int main(int argc, char *argv[]) {
  char *appName = NULL;
  bool verbose = false;

  if (argc < 2) {
    help(argv[0]);
    return 0;
  }

  // Initialize the runtime

  // Parse arguments
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == 'v' && argv[i][1] == '\0')
      verbose = true;
    else
      appName = argv[i];
  }

  // Load executable
  FILE *fd = fopen(appName, "r");
  if (fd != NULL) {

    fseek(fd, 0, SEEK_END);
    long int pos = ftell(fd);
    fseek(fd, 0, SEEK_SET);

    void *data = malloc(pos);
    if (data == NULL)
      return -1;

    fread(data, 1, pos, fd);
    fclose(fd);

    PEInfo info;
    printf("RetVal: %d\n", PE_LoadData(data, pos, argv, argc, &info));

    // Parse Assembly metadata if present

    MD_AssemblyRef assem;
    Metadata_GetObject(&info, Metadata_BuildToken(MetadataType_AssemblyRef, 1),
                       &assem);

    printf("%s\r\n", Metadata_GetString(&info, assem.name));

    // Parse and load AssemblyRef metadata

    // mscorlib is external with builtin functions used as PInvoke calls.

    // Retrieve entry point from CLI header

    // Generate code for the entry point's class

    // Execute entry point code

    // Start execution of the runtime
  }

  return 0;
}