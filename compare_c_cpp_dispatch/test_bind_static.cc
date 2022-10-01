#include <iostream>
#include <random>
#include <functional>

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

struct cadd1 {void add(int &x) {x += 1;}};
struct cadd2 {void add(int &x) {x += 2;}};
struct cadd3 {void add(int &x) {x += 3;}};
struct cadd4 {void add(int &x) {x += 4;}};
struct cadd5 {void add(int &x) {x += 5;}};
struct cadd6 {void add(int &x) {x += 6;}};
struct cadd7 {void add(int &x) {x += 7;}};
struct cadd8 {void add(int &x) {x += 8;}};
struct cadd9 {void add(int &x) {x += 9;}};
struct cadd10 {void add(int &x) {x += 10;}};
struct cadd11 {void add(int &x) {x += 11;}};
struct cadd12 {void add(int &x) {x += 12;}};
struct cadd13 {void add(int &x) {x += 13;}};
struct cadd14 {void add(int &x) {x += 14;}};
struct cadd15 {void add(int &x) {x += 15;}};
struct cadd16 {void add(int &x) {x += 16;}};


int main(int argc, char *argv[])
{

    cadd1 *a1 = new cadd1;
    cadd2 *a2 = new cadd2;
    cadd3 *a3 = new cadd3;
    cadd4 *a4 = new cadd4;
    cadd5 *a5 = new cadd5;
    cadd6 *a6 = new cadd6;
    cadd7 *a7 = new cadd7;
    cadd8 *a8 = new cadd8;
    cadd9 *a9 = new cadd9;
    cadd10 *a10 = new cadd10;
    cadd11 *a11 = new cadd11;
    cadd12 *a12 = new cadd12;
    cadd13 *a13 = new cadd13;
    cadd14 *a14 = new cadd14;
    cadd15 *a15 = new cadd15;
    cadd16 *a16 = new cadd16;

    std::function<void(int&)> add1 = std::bind(&cadd1::add, a1, std::placeholders::_1);
    std::function<void(int&)> add2 = std::bind(&cadd2::add, a2, std::placeholders::_1);
    std::function<void(int&)> add3 = std::bind(&cadd3::add, a3, std::placeholders::_1);
    std::function<void(int&)> add4 = std::bind(&cadd4::add, a4, std::placeholders::_1);
    std::function<void(int&)> add5 = std::bind(&cadd5::add, a5, std::placeholders::_1);
    std::function<void(int&)> add6 = std::bind(&cadd6::add, a6, std::placeholders::_1);
    std::function<void(int&)> add7 = std::bind(&cadd7::add, a7, std::placeholders::_1);
    std::function<void(int&)> add8 = std::bind(&cadd8::add, a8, std::placeholders::_1);
    std::function<void(int&)> add9 = std::bind(&cadd9::add, a9, std::placeholders::_1);
    std::function<void(int&)> add10 = std::bind(&cadd10::add, a10, std::placeholders::_1);
    std::function<void(int&)> add11 = std::bind(&cadd11::add, a11, std::placeholders::_1);
    std::function<void(int&)> add12 = std::bind(&cadd12::add, a12, std::placeholders::_1);
    std::function<void(int&)> add13 = std::bind(&cadd13::add, a13, std::placeholders::_1);
    std::function<void(int&)> add14 = std::bind(&cadd14::add, a14, std::placeholders::_1);
    std::function<void(int&)> add15 = std::bind(&cadd15::add, a15, std::placeholders::_1);
    std::function<void(int&)> add16 = std::bind(&cadd16::add, a16, std::placeholders::_1);


    std::function<void(int&)> *arr = new std::function<void(int&)>[COUNT / DIVIDER];

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
                arr[i] = add1;
                break;
            case 1:
                arr[i] = add2;
                break;
            case 2:
                arr[i] = add3;
                break;
            case 3:
                arr[i] = add4;
                break;
            case 4:
                arr[i] = add5;
                break;
            case 5:
                arr[i] = add6;
                break;
            case 6:
                arr[i] = add7;
                break;
            case 7:
                arr[i] = add8;
                break;
            case 8:
                arr[i] = add9;
                break;
            case 9:
                arr[i] = add10;
                break;
            case 10:
                arr[i] = add11;
                break;
            case 11:
                arr[i] = add12;
                break;
            case 12:
                arr[i] = add13;
                break;
            case 13:
                arr[i] = add14;
                break;
            case 14:
                arr[i] = add15;
                break;
            case 15:
                arr[i] = add16;
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
            arr[i](x);
        }
    }

    double stop = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << "time bind static:  " << x << "   " << stop << std::endl;

    return 0;
}
