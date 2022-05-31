# This isn't a cleanly written makefile. It has potential for errors if you kill
# it while it's building, it duplicates logic, etc. Lazy man's Makefile.

NUM_FUNCTS = 16
COUNT = 10000000000


FLAGS = -O2 -std=c++17
DEBUG_FLAGS = -O0 -std=c++17 -g

EXECS = variant_poly poly pointer_lambda lambda cfunct_if cfunct_switch cfunct_switch_noinline cfunct_if_noinline cptr cptr_double bind_dynamic bind_static

all: $(EXECS)

variant_poly: test_variant_poly.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT)  test_variant_poly.cc -o variant_poly
	g++ $(DEBUG_FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT)  test_variant_poly.cc -o variant_poly_debug
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT)  test_variant_poly.cc -S -o variant_poly.asm

poly: test_poly.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT)  test_poly.cc -o poly
	g++ $(DEBUG_FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT)  test_poly.cc -o poly_debug
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT)  test_poly.cc -S -o poly.asm

lambda: test_lambda.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_lambda.cc -o lambda
	g++ $(DEBUG_FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_lambda.cc -o lambda_debug
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_lambda.cc -S -o lambda.asm

pointer_lambda: test_pointer_lambda.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_pointer_lambda.cc -o pointer_lambda
	g++ $(DEBUG_FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_pointer_lambda.cc -o pointer_lambda_debug
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_pointer_lambda.cc -S -o pointer_lambda.asm


cfunct_if: test_cfunct_if.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cfunct_if.cc -o cfunct_if
	g++ $(DEBUG_FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cfunct_if.cc -o cfunct_if_debug
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cfunct_if.cc -S -o cfunct_if.asm

cfunct_switch: test_cfunct_if.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cfunct_switch.cc -o cfunct_switch
	g++ $(DEBUG_FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cfunct_switch.cc -o cfunct_switch_debug
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cfunct_switch.cc -S -o cfunct_switch.asm

cfunct_switch_noinline: test_cfunct_switch.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) -DNOINLINE test_cfunct_switch.cc -o cfunct_switch_noinline
	g++ $(DEBUG_FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) -DNOINLINE test_cfunct_switch.cc -o cfunct_switch_noinline_debug
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) -DNOINLINE test_cfunct_switch.cc -S -o cfunct_switch_noinline.asm

cfunct_if_noinline: test_cfunct_if.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) -DNOINLINE test_cfunct_if.cc -o cfunct_if_noinline
	g++ $(DEBUG_FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) -DNOINLINE test_cfunct_if.cc -o cfunct_if_noinline_debug
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) -DNOINLINE test_cfunct_if.cc -S -o cfunct_if_noinline.asm

cptr_double: test_cptr_double_lookup.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cptr_double_lookup.cc -o cptr_double
	g++ $(DEBUG_FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cptr_double_lookup.cc -o cptr_double_debug
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cptr_double_lookup.cc -S -o cptr_double.asm

cptr: test_cptr.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cptr.cc -o cptr
	g++ $(DEBUG_FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cptr.cc -o cptr_debug
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_cptr.cc -S -o cptr.asm

bind_dynamic: test_bind_dynamic.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_bind_dynamic.cc -o bind_dynamic
	g++ $(DEBUG_FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_bind_dynamic.cc -o bind_dynamic_debug
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_bind_dynamic.cc -S -o bind_dynamic.asm

bind_static: test_bind_static.cc
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_bind_static.cc -o bind_static
	g++ $(DEBUG_FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_bind_static.cc -o bind_static_debug
	g++ $(FLAGS) -DNUM_FUNCTS=$(NUM_FUNCTS) -DCOUNT=$(COUNT) test_bind_static.cc -S -o bind_static.asm


clean:
	rm -f $(EXECS) *_debug  *.asm
