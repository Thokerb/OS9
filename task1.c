#include <stdlib.h>
#include <stdio.h> 
#include <dlfcn.h>
#include <pthread.h>

int numberAlloc;
int sizeAlloc;
void* (*func_my_malloc)(const int);
void (*func_my_free)(void*);

void* threadMethod( void* arg ){
    struct data* dataArg = (struct data*) arg;
    for (int i = 0; i < numberAlloc; i++)
    {
        void* obj = func_my_malloc(sizeAlloc);
        func_my_free(obj);
    }
    

    pthread_exit(dataArg);
}


int main(int argc, char const *argv[])
{
    void *handle;


    if(argc != 5){
        perror("Invalid number of arguments");
        return EXIT_FAILURE;
    }

    const char* fileName = argv[1];
    int numberThreads = atoi(argv[2]);
    numberAlloc = atoi(argv[3]);
    sizeAlloc = atoi(argv[4]);

    handle = dlopen(fileName, RTLD_LAZY);
    if (!handle) {
        /* fail to load the library */
        perror("dlopen failed");
        printf("%s",fileName);
        return EXIT_FAILURE;
    }

    *(void**)(&func_my_free) = dlsym(handle, "my_free");
    if (!func_my_free) {
        /* no such symbol */
        printf("ERROR: dlsym_my_free\n");
        dlclose(handle);
        return EXIT_FAILURE;
    }

    *(void**)(&func_my_malloc) = dlsym(handle, "my_malloc");
    if (!func_my_malloc) {
        /* no such symbol */
        printf("ERROR: dlsym_my_malloc\n");
        dlclose(handle);
        return EXIT_FAILURE;
    }


    pthread_t id[numberThreads];
    for (int i = 0; i < numberThreads; i++)
    {
        pthread_create(&id[i],NULL,&threadMethod,NULL);
    }

    for (int i = 0; i < numberThreads; i++)
    {
        pthread_join(id[i],NULL);
    }
    

    dlclose(handle);

    /* code */
    return EXIT_SUCCESS;
}
