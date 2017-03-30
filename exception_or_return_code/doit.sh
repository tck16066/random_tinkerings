#!/bin/bash

make clean
make

run_test ()
{
    echo "Running $1:"
    ./$1
    echo ""
}

run_test test_return_code_none
run_test test_exception_none
run_test test_return_code_sparse
run_test test_exception_sparse
run_test test_return_code
run_test test_exception
