CXX=		g++
CXXFLAGS=	-g -Wall -std=gnu++11
SHELL=		bash

all: lib_info test

lib_info: 
	$(CXX) $(CXXFLAGS) -o lib_info lib_info.cpp
test: lib_info
	./lib_info small.txt

clean:
	rm lib_info
