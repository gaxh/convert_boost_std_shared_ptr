all : shared_ptr_convert.test.out

shared_ptr_convert.test.out : shared_ptr_convert.h shared_ptr_convert.test.cpp
	${CXX} -o $@ $^ -g -Wall -O2

clean:
	rm -f *.out
