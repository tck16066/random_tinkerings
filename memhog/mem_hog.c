#include <stdlib.h>
#include <stdio.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

int run = 1;

void sighand(int sig)
{
    run = 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Need a memory percentage arg.");
        return -1;
    }

    double percentage = atof(argv[1]) / 100.0;
    if (percentage <= 0.0 || percentage > 100.0)
    {
        fprintf(stderr, "Need a valid memory percentage arg.");
        return -1;
    }

    signal(SIGINT, sighand);

    struct sysinfo si;
    sysinfo(&si);

    size_t sys_bytes = si.mem_unit * si.freeram;
    size_t alloc_size = (sys_bytes * percentage);

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
        sleep(1);
    }

    srand((unsigned) time(NULL));
    printf("Spot val: %c\n", mem[rand() % alloc_size]);
}


