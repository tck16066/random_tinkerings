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

class base
{
public:
    virtual void add(int &x) = 0;
};


struct add1 : public base {virtual void add(int &x) {x += 1;}};
struct add2 : public base {virtual void add(int &x) {x += 2;}};
struct add3 : public base {virtual void add(int &x) {x += 3;}};
struct add4 : public base {virtual void add(int &x) {x += 4;}};
struct add5 : public base {virtual void add(int &x) {x += 5;}};
struct add6 : public base {virtual void add(int &x) {x += 6;}};
struct add7 : public base {virtual void add(int &x) {x += 7;}};
struct add8 : public base {virtual void add(int &x) {x += 8;}};
struct add9 : public base {virtual void add(int &x) {x += 9;}};
struct add10 : public base {virtual void add(int &x) {x += 10;}};
struct add11 : public base {virtual void add(int &x) {x += 11;}};
struct add12 : public base {virtual void add(int &x) {x += 12;}};
struct add13 : public base {virtual void add(int &x) {x += 13;}};
struct add14 : public base {virtual void add(int &x) {x += 14;}};
struct add15 : public base {virtual void add(int &x) {x += 15;}};
struct add16 : public base {virtual void add(int &x) {x += 16;}};


int main(int argc, char *argv[])
{

    base *a1 = new add1;
    base *a2 = new add2;
    base *a3 = new add3;
    base *a4 = new add4;
    base *a5 = new add5;
    base *a6 = new add6;
    base *a7 = new add7;
    base *a8 = new add8;
    base *a9 = new add9;
    base *a10 = new add10;
    base *a11 = new add11;
    base *a12 = new add12;
    base *a13 = new add13;
    base *a14 = new add14;
    base *a15 = new add15;
    base *a16 = new add16;

    base **arr = new base *[COUNT / DIVIDER];

    uint32_t *int_arr = new uint32_t[COUNT / DIVIDER];
#if RAND
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, NUM_FUNCTS - 1);

    for (uint32_t i = 0; i < COUNT / DIVIDER; ++i)
    {
        int_arr[i] = dis(gen);
    }
#else
    for (uint32_t i = 0; i < COUNT / DIVIDER; ++i)
    {
        int_arr[i] = (i % (NUM_FUNCTS - 1));
    }
#endif

    for (uint32_t i = 0; i < COUNT / DIVIDER; ++i)
    {
        switch (int_arr[i])
        {
            case 0:
                arr[i] = a1;
                break;
            case 1:
                arr[i] = a2;
                break;
            case 2:
                arr[i] = a3;
                break;
            case 3:
                arr[i] = a4;
                break;
            case 4:
                arr[i] = a5;
                break;
            case 5:
                arr[i] = a6;
                break;
            case 6:
                arr[i] = a7;
                break;
            case 7:
                arr[i] = a8;
                break;
            case 8:
                arr[i] = a9;
                break;
            case 9:
                arr[i] = a10;
                break;
            case 10:
                arr[i] = a11;
                break;
            case 11:
                arr[i] = a12;
                break;
            case 12:
                arr[i] = a13;
                break;
            case 13:
                arr[i] = a14;
                break;
            case 14:
                arr[i] = a15;
                break;
            case 15:
                arr[i] = a16;
                break;
        }
    }

    std::clock_t start;
    start = std::clock();

    int x = 7;

    for (uint32_t j = 0; j < DIVIDER; ++j)
    {
        for (uint32_t i = 0; i < COUNT / DIVIDER; ++i)
        {
            arr[i]->add(x);
        }
    }

    double stop = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << "time poly:  " << x << "   " << stop << std::endl;

    return 0;
}
