all: test_return_code test_exception test_return_code_sparse test_exception_sparse test_return_code_none test_exception_none

test_return_code: test_return_code.cc
	g++ -std=c++11 test_return_code.cc -o test_return_code
test_return_code_sparse: test_return_code_sparse.cc
	g++ -std=c++11 test_return_code_sparse.cc -o test_return_code_sparse
test_return_code_none: test_return_code_none.cc
	g++ -std=c++11 test_return_code_none.cc -o test_return_code_none


test_exception: test_exception.cc
	g++ -std=c++11 test_exception.cc -o test_exception
test_exception_sparse: test_exception_sparse.cc
	g++ -std=c++11 test_exception_sparse.cc -o test_exception_sparse
test_exception_none: test_exception_none.cc
	g++ -std=c++11 test_exception_none.cc -o test_exception_none

clean:
	rm -f test_return_code test_exception test_return_code_sparse test_exception_sparse test_return_code_none test_exception_none
