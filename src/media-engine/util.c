#include <stdlib.h>

void freen(void* obj)
{
    while(obj) {
        free(obj);
        obj=NULL;
    }
}
