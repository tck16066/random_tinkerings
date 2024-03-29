#!/bin/bash

if [ "$#" -ne "1" ]; then
    RESULTS_DIR="res_dir"
else
    RESULTS_DIR=$1
fi


rm -rf $RESULTS_DIR
mkdir -p $RESULTS_DIR

doit () {
    ./$1 > $RESULTS_DIR/$1
}

doit cfunct_if
doit cfunct_if_noinline
doit cfunct_switch
doit cfunct_switch_noinline
doit cptr
doit cptr_double
doit lambda
doit pointer_lambda
doit poly
doit variant_poly
doit bind_dynamic
doit bind_static
