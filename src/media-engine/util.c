#include <stdlib.h>
#include <string.h>

void freen(void* obj)
{
    while(obj) {
        free(obj);
        obj=NULL;
    }
}

char *str(char *source)
{
    char *str = calloc(strlen(source) + 1, sizeof(char));
    strcpy(str, source);
    return str;
}
