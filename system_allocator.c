#include <stdlib.h>
#include <stdio.h>
#include "my_memory.h"


void* my_malloc(int size){
    return malloc(size);
}

void my_free(void* ptr){
    free(ptr);
}