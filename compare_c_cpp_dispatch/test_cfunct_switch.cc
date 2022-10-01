#include <iostream>
#include <random>

#include <ctime>

#ifndef RAND
#define RAND 0
#endif

#ifndef COUNT
#define COUNT 1000000000
#endif

#define DIVIDER 1000

#ifndef COUNT
#define COUNT 1000000000
#elif COUNT < DIVIDER
#error "COUNT must be >= divider ( see file ) and a multiple of divider"
#endif

#ifndef NUM_FUNCTS
#define NUM_FUNCTS 4
#endif

#ifndef NOINLINE
void add1(int &x) {++x;}
void add2(int &x) {x += 2;}
void add3(int &x) {x += 3;}
void add4(int &x) {x += 4;}
void add5(int &x) {x += 5;}
void add6(int &x) {x += 6;}
void add7(int &x) {x += 7;}
void add8(int &x) {x += 8;}
void add9(int &x) {x += 9;}
void add10(int &x) {x += 10;}
void add11(int &x) {x += 11;}
void add12(int &x) {x += 12;}
void add13(int &x) {x += 13;}
void add14(int &x) {x += 14;}
void add15(int &x) {x += 15;}
void add16(int &x) {x += 16;}
#else
void __attribute__ ((noinline)) add1(int &x) {++x;}
void __attribute__ ((noinline)) add2(int &x) {x += 2;}
void __attribute__ ((noinline)) add3(int &x) {x += 3;}
void __attribute__ ((noinline)) add4(int &x) {x += 4;}
void __attribute__ ((noinline)) add5(int &x) {x += 5;}
void __attribute__ ((noinline)) add6(int &x) {x += 6;}
void __attribute__ ((noinline)) add7(int &x) {x += 7;}
void __attribute__ ((noinline)) add8(int &x) {x += 8;}
void __attribute__ ((noinline)) add9(int &x) {x += 9;}
void __attribute__ ((noinline)) add10(int &x) {x += 10;}
void __attribute__ ((noinline)) add11(int &x) {x += 11;}
void __attribute__ ((noinline)) add12(int &x) {x += 12;}
void __attribute__ ((noinline)) add13(int &x) {x += 13;}
void __attribute__ ((noinline)) add14(int &x) {x += 14;}
void __attribute__ ((noinline)) add15(int &x) {x += 15;}
void __attribute__ ((noinline)) add16(int &x) {x += 16;}
#endif

int main(int argc, char *argv[])
{

    uint32_t *arr = new uint32_t[COUNT/ DIVIDER];

#if RAND
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, NUM_FUNCTS - 1);

    for (uint32_t i = 0; i < COUNT / DIVIDER; ++i)
    {
        arr[i] = dis(gen);
    }
#else
    for (uint32_t i = 0; i < COUNT / DIVIDER; ++i)
    {
        arr[i] = (i % (NUM_FUNCTS - 1));
    }
#endif

    std::clock_t start;
    start = std::clock();

    int x = 7;

    for (uint32_t j = 0; j < DIVIDER; ++j)
    {
        for (uint32_t i = 0; i < COUNT / DIVIDER; ++i)
        {
            switch (arr[i])
            {
            case 0:
                add1(x);
                break;
            case 1:
                add2(x);
                break;
            case 2:
                add3(x);
                break;
            case 3:
                add4(x);
                break;
            case 4:
                add5(x);
                break;
            case 5:
                add6(x);
                break;
            case 6:
                add7(x);
                break;
            case 7:
                add8(x);
                break;
            case 8:
                add9(x);
                break;
            case 9:
                add10(x);
                break;
            case 10:
                add11(x);
                break;
            case 11:
                add12(x);
                break;
            case 12:
                add13(x);
                break;
            case 13:
                add14(x);
                break;
            case 14:
                add15(x);
                break;
            case 15:
                add16(x);
                break;
            }
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
