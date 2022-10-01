#include <iostream>
#include <random>

#include <ctime>

#include <functional>

#define DIVIDER 1000

#ifndef RAND
#define RAND 0
#endif

#ifndef COUNT
#define COUNT 1000000000
#elif COUNT < DIVIDER
#error "COUNT must be >= divider ( see file ) and a multiple of divider"
#endif

#ifndef NUM_FUNCTS
#define NUM_FUNCTS 4
#endif

/*
*
*/

std::function<void(int&)> add1 = [](int &x){x += 1;};
std::function<void(int&)> add2 = [](int &x){x += 2;};
std::function<void(int&)> add3 = [](int &x){x += 3;};
std::function<void(int&)> add4 = [](int &x){x += 4;};
std::function<void(int&)> add5 = [](int &x){x += 5;};
std::function<void(int&)> add6 = [](int &x){x += 6;};
std::function<void(int&)> add7 = [](int &x){x += 7;};
std::function<void(int&)> add8 = [](int &x){x += 8;};
std::function<void(int&)> add9 = [](int &x){x += 9;};
std::function<void(int&)> add10 = [](int &x){x += 10;};
std::function<void(int&)> add11 = [](int &x){x += 11;};
std::function<void(int&)> add12 = [](int &x){x += 12;};
std::function<void(int&)> add13 = [](int &x){x += 13;};
std::function<void(int&)> add14 = [](int &x){x += 14;};
std::function<void(int&)> add15 = [](int &x){x += 15;};
std::function<void(int&)> add16 = [](int &x){x += 16;};


int main(int argc, char *argv[])
{
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

    for (uint32_t j = 0; j < DIVIDER; j++)
    {
        for (uint32_t i = 0; i < COUNT / DIVIDER; ++i)
        {
            arr[i](x);
        }
    }

    double stop = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << "time lambda:  " << x << "   " << stop << std::endl;

    return 0;
}
