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
        if (arr2[i] == 0)
            add1(x);
        else if (arr2[i] == 1)
            add2(x);
        else if (arr2[i] == 2)
            add1(x);
        else if (arr2[i] == 3)
            add2(x);
        else if (arr2[i] == 4)
            add1(x);
        else if (arr2[i] == 5)
            add2(x);
        else if (arr2[i] == 6)
            add1(x);
        else if (arr2[i] == 7)
            add2(x);
        else if (arr2[i] == 8)
            add1(x);
        else if (arr2[i] == 9)
            add2(x);
        else if (arr2[i] == 10)
            add1(x);
        else if (arr2[i] ==11)
            add2(x);
        else if (arr2[i] == 12)
            add1(x);
        else if (arr2[i] == 13)
            add2(x);
        else if (arr2[i] == 14)
            add1(x);
        else if (arr2[i] == 15)
            add2(x);
    }

    double stop = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

#ifndef NOINLINE
    std::string msg("time c-funct if:  ");
#else

    std::string msg("time c-funct if noinline:  ");
#endif

    std::cout << msg << x << "   " << stop << std::endl;

    return 0;
}
