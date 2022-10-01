#include <iostream>
#include <random>
#include <functional>
#include <variant>

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

class derived1
{
public:
    void add_der(int &x) {x += 1;}
};

class derived2
{
public:
    void add_der(int &x) {x += 2;}
};

class derived3
{
public:
    void add_der(int &x) {x += 3;}
};

class derived4
{
public:
    void add_der(int &x) {x += 4;}
};

class derived5
{
public:
    void add_der(int &x) {x += 5;}
};

class derived6
{
public:
    void add_der(int &x) {x += 6;}
};

class derived7
{
public:
    void add_der(int &x) {x += 7;}
};

class derived8
{
public:
    void add_der(int &x) {x += 8;}
};

class derived9
{
public:
    void add_der(int &x) {x += 9;}
};

class derived10
{
public:
    void add_der(int &x) {x += 10;}
};

class derived11
{
public:
    void add_der(int &x) {x += 11;}
};

class derived12
{
public:
    void add_der(int &x) {x += 12;}
};

class derived13
{
public:
    void add_der(int &x) {x += 13;}
};

class derived14
{
public:
    void add_der(int &x) {x += 14;}
};

class derived15
{
public:
    void add_der(int &x) {x += 15;}
};

class derived16
{
public:
    void add_der(int &x) {x += 16;}
};

using VarType = std::variant<derived1, derived2, derived3, derived4,
    derived5, derived6, derived7, derived8, derived9, derived10,
    derived11, derived12, derived13, derived14, derived15, derived16>;

using ArrType = std::array<VarType, COUNT / DIVIDER>;

int main()
{
    ArrType *arrp = new ArrType;
    auto &arr = *arrp;

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

    for (uint32_t i = 0; i < (COUNT / DIVIDER); ++i)
    {
        switch (int_arr[i])
        {
            case 0:
                arr[i] = VarType(derived1());
                break;
            case 1:
                arr[i] = VarType(derived2());
                break;
            case 2:
                arr[i] = VarType(derived3());
                break;
            case 3:
                arr[i] = VarType(derived4());
                break;
            case 4:
                arr[i] = VarType(derived5());
                break;
            case 5:
                arr[i] = VarType(derived6());
                break;
            case 6:
                arr[i] = VarType(derived7());
                break;
            case 7:
                arr[i] = VarType(derived8());
                break;
            case 8:
                arr[i] = VarType(derived9());
                break;
            case 9:
                arr[i] = VarType(derived10());
                break;
            case 10:
                arr[i] = VarType(derived11());
                break;
            case 11:
                arr[i] = VarType(derived12());
                break;
            case 12:
                arr[i] = VarType(derived13());
                break;
            case 13:
                arr[i] = VarType(derived14());
                break;
            case 14:
                arr[i] = VarType(derived15());
                break;
            case 15:
                arr[i] = VarType(derived16());
                break;
        }
    }

    std::clock_t start;
    start = std::clock();

    int x = 7;

    for (uint32_t j = 0; j < DIVIDER; ++j)
    {
        for (auto v : arr)
        {
            std::visit([&x](auto&& arg){arg.add_der(x);}, v);   
        }
    }

    double stop = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << "time variant poly:  " << x << "   " << stop << std::endl;

    delete arrp;

    return 0;
}
