#include <iostream>
#include <random>

#include <ctime>

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


typedef void (*funct_ptr)(int &x);

struct AA
{
    funct_ptr add;
};

struct AAA
{
    AA a;
};


AAA a1{{add1}};
AAA a2{{add2}};
AAA a3{{add3}};
AAA a4{{add4}};
AAA a5{{add5}};
AAA a6{{add6}};
AAA a7{{add7}};
AAA a8{{add8}};
AAA a9{{add9}};
AAA a10{{add10}};
AAA a11{{add11}};
AAA a12{{add12}};
AAA a13{{add13}};
AAA a14{{add14}};
AAA a15{{add15}};
AAA a16{{add16}};

int main(int argc, char *argv[])
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, NUM_FUNCTS - 1);

    AAA **arr = new AAA*[COUNT / DIVIDER];

    for (uint32_t i = 0; i < COUNT / DIVIDER; ++i)
    {
        switch (dis(gen))
        {
            case 0:
                arr[i] = &a1;
                break;
            case 1:
                arr[i] = &a2;
                break;
            case 2:
                arr[i] = &a3;
                break;
            case 3:
                arr[i] = &a4;
                break;
            case 4:
                arr[i] = &a5;
                break;
            case 5:
                arr[i] = &a6;
                break;
            case 6:
                arr[i] = &a7;
                break;
            case 7:
                arr[i] = &a8;
                break;
            case 8:
                arr[i] = &a9;
                break;
            case 9:
                arr[i] = &a10;
                break;
            case 10:
                arr[i] = &a11;
                break;
            case 11:
                arr[i] = &a12;
                break;
            case 12:
                arr[i] = &a13;
                break;
            case 13:
                arr[i] = &a14;
                break;
            case 14:
                arr[i] = &a15;
                break;
            case 15:
                arr[i] = &a16;
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
            arr[i]->a.add(x);
        }
    }

    double stop = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << "time c-ptr double lookup:  " << x << "   " << stop << std::endl;

    return 0;
}
