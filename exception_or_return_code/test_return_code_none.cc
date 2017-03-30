#include <iostream>
#include <random>
#include <cstdint>
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
#define NUM_FUNCTS 16
#endif

#define MAKE_CODE(CODE, SUB) ((uint32_t)((CODE << 16) | SUB))
#define GET_ERROR(CODE)      ((uint32_t)(CODE >> 16))

typedef uint32_t return_code_t;

return_code_t add1(int &x)  {++x;     return MAKE_CODE(0, 0);}
return_code_t add2(int &x)  {x += 2;  return MAKE_CODE(0, 0);}
return_code_t add3(int &x)  {x += 3;  return MAKE_CODE(0, 0);}
return_code_t add4(int &x)  {x += 4;  return MAKE_CODE(0, 0);}
return_code_t add5(int &x)  {x += 5;  return MAKE_CODE(0, 0);}
return_code_t add6(int &x)  {x += 6;  return MAKE_CODE(0, 0);}
return_code_t add7(int &x)  {x += 7;  return MAKE_CODE(0, 0);}
return_code_t add8(int &x)  {x += 8;  return MAKE_CODE(0, 0);}
return_code_t add9(int &x)  {x += 9;  return MAKE_CODE(0, 0);}
return_code_t add10(int &x) {x += 10; return MAKE_CODE(0, 0);}
return_code_t add11(int &x) {x += 11; return MAKE_CODE(0, 0);}
return_code_t add12(int &x) {x += 12; return MAKE_CODE(0, 0);}
return_code_t add13(int &x) {x += 13; return MAKE_CODE(0, 0);}
return_code_t add14(int &x) {x += 14; return MAKE_CODE(0, 0);}
return_code_t add15(int &x) {x += 15; return MAKE_CODE(0, 0);}
return_code_t add16(int &x) {x += 16; return MAKE_CODE(0, 0);}

int main(int argc, char *argv[])
{

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, NUM_FUNCTS - 1);

    uint32_t *arr = new uint32_t[COUNT / DIVIDER];

    for (uint32_t i = 0; i < COUNT / DIVIDER; ++i)
    {
        arr[i] = dis(gen);
    }

    std::clock_t start;
    start = std::clock();

    int x = 7;

    for (uint32_t j = 0; j < DIVIDER; ++j)
    {
        for (uint32_t i = 0; i < COUNT / DIVIDER; ++i)
        {
            return_code_t ret;
            switch (arr[i])
            {
            case 0:
                ret = add1(x);
                break;
            case 1:
                ret = add2(x);
                break;
            case 2:
                ret = add3(x);
                break;
            case 3:
                ret = add4(x);
                break;
            case 4:
                ret = add5(x);
                break;
            case 5:
                ret = add6(x);
                break;
            case 6:
                ret = add7(x);
                break;
            case 7:
                ret = add8(x);
                break;
            case 8:
                ret = add9(x);
                break;
            case 9:
                ret = add10(x);
                break;
            case 10:
                ret = add11(x);
                break;
            case 11:
                ret = add12(x);
                break;
            case 12:
                ret = add13(x);
                break;
            case 13:
                ret = add14(x);
                break;
            case 14:
                ret = add15(x);
                break;
            case 15:
                ret = add16(x);
                break;
            }

            switch (GET_ERROR(ret))
            {
            case 0:
                break;
            case 1:
                x += 1;
                break;
            case 2:
                x += 2;
                break;
            case 3:
                x += 3;
                break;
            case 4:
                x += 4;
                break;
            case 5:
                x += 5;
                break;
            case 6:
                x += 6;
                break;
            case 7:
                x += 7;
                break;
            case 8:
                x += 8;
                break;
            case 9:
                x += 9;
                break;
            case 10:
                x += 10;
                break;
            case 11:
                x += 11;
                break;
            case 12:
                x += 12;
                break;
            case 13:
                x += 13;
                break;
            case 14:
                x += 14;
                break;
            case 15:
                x += 15;
                break;
            }
        }
    }

    double stop = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::string msg("time return code if:  ");

    std::cout << msg << x << "   " << stop << std::endl;    return 0;
}
