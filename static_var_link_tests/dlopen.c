#include <dlfcn.h>
#include <stdio.h>

#include "test_statics.h"

int main(int argc, char *argv[])
{
    printf("Static versions:  \n");
    funct_one();
    funct_two();

    printf("\nDLOPEN wrappers:\n");
    void *handle = dlopen("libtest_wrappers_static.so", RTLD_NOW);
    void (*wrapper1)() = dlsym(handle, "wrapper1");
    void (*wrapper2)() = dlsym(handle, "wrapper2");
    wrapper1();
    wrapper2();

    dlclose(handle);

    return 0;
}
