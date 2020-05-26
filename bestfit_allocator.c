#include <stdlib.h>
#include <stdio.h>
#include "my_memory.h"


struct my_memory
{
    size_t size;
    size_t sizeToRestore;
    void* data;
    struct my_memory* nextElement;
};

static struct my_memory* memoryAlloc;

static struct my_memory* initMemory(size_t blocks,size_t size){
    struct my_memory* temp = malloc(sizeof(struct my_memory));
    struct my_memory* root = temp;
    temp->data = malloc(1024*1000);
    temp->size = size;
    for (size_t i = 0; i < blocks; i++)
    {
        struct my_memory* nextMem = malloc(sizeof(struct my_memory));
        temp->nextElement = nextMem;
        temp = temp->nextElement;
    }
    return root;
}

static struct my_memory* findBlock(size_t size){
    struct my_memory* toTraverse = memoryAlloc;
    struct my_memory* bestMatch = memoryAlloc;
    while (toTraverse->nextElement != NULL)
    {
        if(toTraverse->size > size && toTraverse->size > bestMatch->size){
            
        }
    }
    if(toTraverse->size > size){
        return toTraverse;
    }
    printf("ERROR, we didn't find a big enough block, should never happen");
    return bestMatch;
}

static struct my_memory* findBlockByPointer(void* ptr){
    struct my_memory* toTraverse = memoryAlloc;
    while (toTraverse->nextElement != NULL)
    {
        if(toTraverse->data == ptr){
            return toTraverse;
        }
    }
    printf("ERROR, we didn't find the block, which we want to free,should never happen!!!!!!!");
    return toTraverse;
}

void* my_malloc(int size){
    printf("hello");
    if(memoryAlloc == NULL){
        memoryAlloc = initMemory(100,1024*1000);
    }
    struct my_memory* block = findBlock(size);
    block->nextElement->size = block->nextElement->size + block->size - size;
    block->size = 0;
    block->sizeToRestore = size;
    return block->data;
}


void my_free(void* ptr){
    printf("hello");
    struct my_memory* block = findBlockByPointer(ptr);
    block->data = NULL;
    block->size = block->sizeToRestore;
}