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

class exception_2 : public std::exception  {};
class exception_3 : public std::exception  {};
class exception_4 : public std::exception  {};
class exception_5 : public std::exception  {};
class exception_6 : public std::exception  {};
class exception_7 : public std::exception  {};
class exception_8 : public std::exception  {};
class exception_9 : public std::exception  {};
class exception_10 : public std::exception {};
class exception_11 : public std::exception {};
class exception_12 : public std::exception {};
class exception_13 : public std::exception {};
class exception_14 : public std::exception {};
class exception_15 : public std::exception {};
class exception_16 : public std::exception {};

void add1(int &x)  {++x   ;}
void add2(int &x)  {x += 2;  throw exception_2();}
void add3(int &x)  {x += 3;  throw exception_3();}
void add4(int &x)  {x += 4;  }
void add5(int &x)  {x += 5;  }
void add6(int &x)  {x += 6;  }
void add7(int &x)  {x += 7;  }
void add8(int &x)  {x += 8;  }
void add9(int &x)  {x += 9;  }
void add10(int &x) {x += 10; }
void add11(int &x) {x += 11; }
void add12(int &x) {x += 12; }
void add13(int &x) {x += 13; }
void add14(int &x) {x += 14; }
void add15(int &x) {x += 15; }
void add16(int &x) {x += 16; }

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
            try
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
            catch (const exception_2 &)
            {
                x += 2;
            }
            catch (const exception_3 &)
            {
                x += 3;
            }
            catch (const exception_4 &)
            {
                x += 4;
            }
            catch (const exception_5 &)
            {
                x += 5;
            }
            catch (const exception_6 &)
            {
                x += 6;
            }
            catch (const exception_7 &)
            {
                x += 7;
            }
            catch (const exception_8 &)
            {
                x += 8;
            }
            catch (const exception_9 &)
            {
                x += 9;
            }
            catch (const exception_10 &)
            {
                x += 10;
            }
            catch (const exception_11 &)
            {
                x += 11;
            }
            catch (const exception_12 &)
            {
                x += 12;
            }
            catch (const exception_13 &)
            {
                x += 13;
            }
            catch (const exception_14 &)
            {
                x += 14;
            }
            catch (const exception_15 &)
            {
                x += 15;
            }
            catch (const exception_16 &)
            {
                x += 16;
            }
            catch (...)
            {
                x += 17;
            }
        }
    }

    double stop = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

    std::string msg("time exception:  ");

    std::cout << msg << x << "   " << stop << std::endl;    return 0;
}
