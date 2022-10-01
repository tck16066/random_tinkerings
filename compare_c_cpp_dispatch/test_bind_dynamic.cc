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

class base
{
public:
    virtual void add(int &x) = 0;
};


struct cadd1 : public base {virtual void add(int &x) {x += 1;}};
struct cadd2 : public base {virtual void add(int &x) {x += 2;}};
struct cadd3 : public base {virtual void add(int &x) {x += 3;}};
struct cadd4 : public base {virtual void add(int &x) {x += 4;}};
struct cadd5 : public base {virtual void add(int &x) {x += 5;}};
struct cadd6 : public base {virtual void add(int &x) {x += 6;}};
struct cadd7 : public base {virtual void add(int &x) {x += 7;}};
struct cadd8 : public base {virtual void add(int &x) {x += 8;}};
struct cadd9 : public base {virtual void add(int &x) {x += 9;}};
struct cadd10 : public base {virtual void add(int &x) {x += 10;}};
struct cadd11 : public base {virtual void add(int &x) {x += 11;}};
struct cadd12 : public base {virtual void add(int &x) {x += 12;}};
struct cadd13 : public base {virtual void add(int &x) {x += 13;}};
struct cadd14 : public base {virtual void add(int &x) {x += 14;}};
struct cadd15 : public base {virtual void add(int &x) {x += 15;}};
struct cadd16 : public base {virtual void add(int &x) {x += 16;}};


int main(int argc, char *argv[])
{

    base *a1 = new cadd1;
    base *a2 = new cadd2;
    base *a3 = new cadd3;
    base *a4 = new cadd4;
    base *a5 = new cadd5;
    base *a6 = new cadd6;
    base *a7 = new cadd7;
    base *a8 = new cadd8;
    base *a9 = new cadd9;
    base *a10 = new cadd10;
    base *a11 = new cadd11;
    base *a12 = new cadd12;
    base *a13 = new cadd13;
    base *a14 = new cadd14;
    base *a15 = new cadd15;
    base *a16 = new cadd16;

    std::function<void(int&)> add1 = std::bind(&base::add, a1, std::placeholders::_1);
    std::function<void(int&)> add2 = std::bind(&base::add, a2, std::placeholders::_1);
    std::function<void(int&)> add3 = std::bind(&base::add, a3, std::placeholders::_1);
    std::function<void(int&)> add4 = std::bind(&base::add, a4, std::placeholders::_1);
    std::function<void(int&)> add5 = std::bind(&base::add, a5, std::placeholders::_1);
    std::function<void(int&)> add6 = std::bind(&base::add, a6, std::placeholders::_1);
    std::function<void(int&)> add7 = std::bind(&base::add, a7, std::placeholders::_1);
    std::function<void(int&)> add8 = std::bind(&base::add, a8, std::placeholders::_1);
    std::function<void(int&)> add9 = std::bind(&base::add, a9, std::placeholders::_1);
    std::function<void(int&)> add10 = std::bind(&base::add, a10, std::placeholders::_1);
    std::function<void(int&)> add11 = std::bind(&base::add, a11, std::placeholders::_1);
    std::function<void(int&)> add12 = std::bind(&base::add, a12, std::placeholders::_1);
    std::function<void(int&)> add13 = std::bind(&base::add, a13, std::placeholders::_1);
    std::function<void(int&)> add14 = std::bind(&base::add, a14, std::placeholders::_1);
    std::function<void(int&)> add15 = std::bind(&base::add, a15, std::placeholders::_1);
    std::function<void(int&)> add16 = std::bind(&base::add, a16, std::placeholders::_1);


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

    std::cout << "time bind dynamic:  " << x << "   " << stop << std::endl;

    return 0;
}
