#include <iostream>
#include <random>

#include <ctime>

#include <functional>

#ifndef COUNT
#define COUNT 1000000000
#endif

#ifndef NUM_FUNCTS
#define NUM_FUNCTS 4
#endif

int main(int argc, char *argv[])
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, NUM_FUNCTS - 1);

    std::function<void(int&)> arr[NUM_FUNCTS];

    for (uint32_t i = 0; i < NUM_FUNCTS; ++i)
    {
        arr[i] = dis(gen) & 0x01 ? [](int &x){++x;} : [](int &x){x += 2;};
    }


    uint32_t *arr2 = new uint32_t[COUNT];

    for (uint32_t i = 0; i < COUNT; ++i)
    {
        arr2[i] = dis(gen) & (NUM_FUNCTS - 1);
    }

    std::clock_t start;
    start = std::clock();

    int x = 7;

    for (uint32_t i = 0; i < COUNT; ++i)
    {
        arr[arr2[i]](x);
    }

    double stop = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << "time lambda:  " << x << "   " << stop << std::endl;

    return 0;
}
