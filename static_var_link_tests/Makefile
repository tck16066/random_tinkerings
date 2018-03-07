CC = gcc
CFLAGS = 

all: all_static double_static dlopen_and_static double_dlopen both_static_and_dynamic

test_statics.o: test_statics.h test_statics.c
	$(CC) $(CFLAGS) -c -fPIC test_statics.c -o test_statics.o

libtest_statics.a: test_statics.o
	ar cr libtest_statics.a test_statics.o

all_static: all_static.c test_statics.o
	$(CC) $(CFLAGS) -c all_static.c -o all_static.o
	$(CC) all_static.o test_statics.o -o all_static

libtest_wrappers_static.so: test_wrappers.c libtest_statics.a
	$(CC) $(CFLAGS) -c -fPIC test_wrappers.c -o test_wrappers.o
	gcc -shared -o libtest_wrappers_static.so test_wrappers.o libtest_statics.a

libtest_wrappers_static.a: test_wrappers.c test_statics.o
	$(CC) $(CFLAGS) -c test_wrappers.c -o test_wrappers.o
	ar cr libtest_wrappers_static.a test_statics.o test_wrappers.o

double_static: double_static.c test_statics.o libtest_statics.a libtest_wrappers_static.a
	$(CC) $(CFLAGS) -c double_static.c -o double_static.o
	$(CC) double_static.o  -o double_static libtest_statics.a libtest_wrappers_static.a

both_static_and_dynamic: double_static.c test_statics.o libtest_wrappers_static.so
	$(CC) $(CFLAGS) -c double_static.c -o double_static.o
	$(CC) double_static.o  -o both_static_and_dynamic libtest_statics.a libtest_wrappers_static.so

dlopen_and_static: dlopen.c test_statics.o libtest_wrappers_static.so
	$(CC) $(CFLAGS) -c dlopen.c -o dlopen.o
	$(CC) dlopen.o -o dlopen_and_static -ldl libtest_statics.a

double_dlopen: dlopen.c test_statics.o libtest_wrappers_static.so
	$(CC) $(CFLAGS) -c double_dlopen.c -o double_dlopen.o
	$(CC) double_dlopen.o -o double_dlopen -ldl

clean:
	rm -f all_static double_static dlopen_and_static double_dlopen both_static_and_dynamic
	rm -f *.o *.a *.so
