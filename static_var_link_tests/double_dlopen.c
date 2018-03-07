#include <dlfcn.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    void *handle1 = dlopen("libtest_wrappers_static.so", RTLD_NOW);
    void (*wrapper1_1)() = dlsym(handle1, "wrapper1");
    void (*wrapper1_2)() = dlsym(handle1, "wrapper2");

    void *handle2 = dlopen("libtest_wrappers_static.so", RTLD_NOW);
    void (*wrapper2_1)() = dlsym(handle2, "wrapper1");
    void (*wrapper2_2)() = dlsym(handle2, "wrapper2");

    printf("DLOPEN wrappers 1:  \n");
    wrapper1_1();
    wrapper1_2();

    printf("\nDLOPEN wrappers 2:\n");
    wrapper2_1();
    wrapper2_2();

    dlclose(handle1);
    dlclose(handle2);

    return 0;
}
