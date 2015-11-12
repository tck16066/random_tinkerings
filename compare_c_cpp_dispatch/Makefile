NUM_FUNCTS = 16
COUNT = 1000000000


FLAGS = -O2 -std=c++11

all: poly lambda cfunct_if cfunct_switch cfunct_switch_noinline cfunct_if_noinline cptr


poly: test_poly.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT)  test_poly.cc -o poly
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT)  test_poly.cc -S -o poly.asm

lambda: test_lambda.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_lambda.cc -o lambda
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_lambda.cc -S -o lambda.asm

cfunct_if: test_cfunct_if.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cfunct_if.cc -o cfunct_if
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cfunct_if.cc -S -o cfunct_if.asm

cfunct_switch: test_cfunct_if.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cfunct_switch.cc -o cfunct_switch
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cfunct_switch.cc -S -o cfunct_switch.asm

cfunct_switch_noinline: test_cfunct_switch.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) -DNOINLINE test_cfunct_switch.cc -o cfunct_switch_noinline
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) -DNOINLINE test_cfunct_switch.cc -S -o cfunct_switch_noinline.asm

cfunct_if_noinline: test_cfunct_if.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) -DNOINLINE test_cfunct_if.cc -o cfunct_if_noinline
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) -DNOINLINE test_cfunct_if.cc -S -o cfunct_if_noinline.asm

cptr: test_cptr.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cptr.cc -o cptr
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cptr.cc -S -o cptr.asm

clean:
	rm -f poly lambda cfunct_if cfunct_switch cfunct_switch_noinline cfunct_if_noinline cptr *.asm
