#!/usr/bin/bash


function write_header {
CNT=$1
filename="auto_struct_$CNT.hh"
AUTO_STR="struct auto_struct_$CNT {int x;}; auto_struct_$CNT make_auto_struct_$CNT(){return auto_struct_$CNT{5};}"
FPATH="autos/$filename"
echo $AUTO_STR > $FPATH
}


rm -rf autos
mkdir -p autos
for i in {1..10000}
do
    write_header $i
done



function write_top {
    out_file=$1
    for i in {1..10000}
    do
        echo "#include \"autos/auto_struct_$i.hh\"" >> $out_file
    done
    echo "#include <iostream>" >> $out_file
}

function write_auto {
    rm -f test_auto.cc
    write_top test_auto.cc
    echo "int main(int argc, char *argv[]){" >> test_auto.cc

    for i in {1..10000}
    do
        echo "auto x_$i = make_auto_struct_$i();" >> test_auto.cc
        echo "std::cout << x_$i.x << std::endl;" >> test_auto.cc
    done

    echo "}" >> test_auto.cc
}

function write_explicit {
    rm -f test_explicit.cc
    write_top test_explicit.cc
    echo "int main(int argc, char *argv[]){" >> test_explicit.cc

    for i in {1..10000}
    do
        echo "auto_struct_$i x_$i = make_auto_struct_$i();" >> test_explicit.cc
        echo "std::cout << x_$i.x << std::endl;" >> test_explicit.cc
    done

    echo "}" >> test_explicit.cc
}

function write_template {
    rm -f test_template.cc
    write_top test_template.cc
    echo "template<typename T>" >> test_template.cc
    echo "T make_t() {" >> test_template.cc
    echo "    T ret; ret.x = 5;" >> test_template.cc
    echo "    return ret;" >> test_template.cc
    echo "}" >> test_template.cc
    echo "int main(int argc, char *argv[]){" >> test_template.cc

    for i in {1..10000}
    do
        echo "auto_struct_$i x_$i = make_t<auto_struct_$i>();" >> test_template.cc
        echo "std::cout << x_$i.x << std::endl;" >> test_template.cc
    done

    echo "}" >> test_template.cc
}

function write_explicit_template {
    rm -f test_ex_template.cc
    write_top test_ex_template.cc
    echo "template<typename T>" >> test_ex_template.cc
    echo "T make_t() {" >> test_ex_template.cc
    echo "    T ret; ret.x = 5;" >> test_ex_template.cc
    echo "    return ret;" >> test_ex_template.cc
    echo "}" >> test_ex_template.cc
    echo "int main(int argc, char *argv[]){" >> test_ex_template.cc

    for i in {1..10000}
    do
        echo "auto_struct_$i x_$i = make_t<auto_struct_$i>();" >> test_ex_template.cc
        echo "std::cout << x_$i.x << std::endl;" >> test_ex_template.cc
    done

    echo "}" >> test_ex_template.cc
}


function prepare_build {
    rm -f *.o
    rm -f a.out
}

function do_auto_build {
    g++ --std=c++11 test_auto.cc
}

function do_explicit_build {
    g++ --std=c++11 test_explicit.cc
}

function do_template_build {
    g++ --std=c++11 test_template.cc
}

function do_explicit_template_build {
    g++ --std=c++11 test_ex_template.cc
}

# Now write the c files
write_auto
write_template
write_explicit
write_explicit_template

echo "using explicit declarations"
prepare_build
date
do_explicit_build
date
echo "done"

echo "Using autos:"
prepare_build
date
do_auto_build
date
echo "done using autos."

echo "using explicit templates"
prepare_build
date
do_explicit_template_build
date
echo "done using explicit templates"

echo "using autos and templates"
prepare_build
date
do_template_build
date
echo "done using autos and templates"

