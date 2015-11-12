#include <iostream>
#include <random>

#include <ctime>

#ifndef COUNT
#define COUNT 1000000000
#endif

#ifndef NUM_FUNCTS
#define NUM_FUNCTS 4
#endif

#ifndef NOINLINE
int   add1(int &x) {++x;}
int   add2(int &x) {x += 2;}
#else
int __attribute__ ((noinline))  add1(int &x) {++x;}
int __attribute__ ((noinline))   add2(int &x) {x += 2;}
#endif



int main(int argc, char *argv[])
{

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, NUM_FUNCTS - 1);

    uint32_t *arr2 = new uint32_t[COUNT];

    for (uint32_t i = 0; i < COUNT; ++i)
    {
        arr2[i] = dis(gen);
    }

    std::clock_t start;
    start = std::clock();

    int x = 7;

    for (uint32_t i = 0; i < COUNT; ++i)
    {
        switch (arr2[i])
        {
        case 0:
        case 2:
        case 4:
        case 5:
        case 9:
        case 10:
        case 12:
        case 14:
            add1(x);
            break;
        case 1:
        case 3:
        case 6:
        case 7:
        case 8:
        case 11:
        case 13:
        case 15:
            add2(x);
            break;
        }
    }

    double stop = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

#ifndef NOINLINE
    std::string msg("time switch if:  ");
#else

    std::string msg("time switch if noinline:  ");
#endif

    std::cout << msg << x << "   " << stop << std::endl;    return 0;
}
