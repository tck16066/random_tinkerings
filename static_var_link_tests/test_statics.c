#include <stdio.h>

#include "test_statics.h"

static int the_global_static;

void funct_one()
{
    printf("funct_one:  %d     %p\n", the_global_static, &the_global_static);
}

void funct_two()
{
    printf("funct_two:  %d     %p\n", the_global_static, &the_global_static);
}
