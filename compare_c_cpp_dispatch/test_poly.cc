#include <iostream>
#include <random>

#include <ctime>

#ifndef COUNT
#define COUNT 1000000000
#endif

#ifndef NUM_FUNCTS
#define NUM_FUNCTS 4
#endif

class base
{
public:
    virtual void add(int &x) = 0;
};


class foo : public base
{

public:
    virtual void add(int &x) {++x;}

};


class bar : public base
{
public:
    virtual void add(int &x) {x +=2;}
};

int main(int argc, char *argv[])
{

    base *f = new foo;
    base *b = new bar;

    uint32_t *arr2 = new uint32_t[COUNT];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, NUM_FUNCTS - 1);

    base *arr[NUM_FUNCTS];

    for (uint32_t i = 0; i < NUM_FUNCTS; ++i)
    {
        arr[i] = dis(gen) & 0x01 ? f : b;
    }
 

    for (uint32_t i = 0; i < COUNT; ++i)
    {
        arr2[i] = dis(gen) & (NUM_FUNCTS - 1);
    }

    std::clock_t start;
    start = std::clock();

    int x = 7;

    for (uint32_t i = 0; i < COUNT; ++i)
    {
        arr[arr2[i]]->add(x);
    }

    double stop = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << "time poly:  " << x << "   " << stop << std::endl;

    return 0;
}
