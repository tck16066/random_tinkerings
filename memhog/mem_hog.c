#include <stdlib.h>
#include <stdio.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

volatile int run = 1;
int cache_killer = 1;

void sighand(int sig)
{
    run = 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Need a memory bytes arg.");
        return -1;
    }

    signal(SIGINT, sighand);

    size_t alloc_size;
    sscanf(argv[1], "%zu", &alloc_size);
    printf("Allocate %zu bytes\n", alloc_size);

    char *mem = malloc(alloc_size);

    //touch each page
    for (size_t i = 1; i < alloc_size && run; ++i)
    {
        if (++mem[i])
            mem[i] = 9;
    }

    mlockall(MCL_CURRENT);

    while (run)
    {
        if (cache_killer)
            mem[rand() % alloc_size] = (char)rand();
    }

    srand((unsigned) time(NULL));
    printf("Spot val: %c\n", mem[rand() % alloc_size]);
}


