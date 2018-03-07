#include <stdio.h>

#include "test_statics.h"
#include "test_wrappers.h"

int main(int argc, char *argv[])
{
    printf("Unwrapped:  \n");
    funct_one();
    funct_two();

    printf("\nWrappers:\n");
    wrapper1();
    wrapper2();

    return 0;
}
