#include "platform.h"
#include <string.h>
#include <stdio.h>
#include "pe/pe.h"

int Platform_LoadAssembly(const char *assemblyName, PEInfo *info) {

    if(strcmp(assemblyName, "corlib") == 0) {
        //corlib is embedded into the kernel

        //loaded from current directory
        FILE *fd = fopen("corlib.dll", "r");
        if (fd != NULL) {

            fseek(fd, 0, SEEK_END);
            long int pos = ftell(fd);
            fseek(fd, 0, SEEK_SET);

            void *data = malloc(pos);
            if (data == NULL)
                return -1;

            fread(data, 1, pos, fd);
            fclose(fd);

            PE_LoadData(data, pos, NULL, 0, info);
            return 0;
        }
    }

    return -1;
}