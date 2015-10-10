ifndef CXX
CXX=g++
endif

OS=`uname`

ifeq ($(OS), Darwin)
CXXFLAGS=-I/usr/local/include
else
CXXFLAGS=-I/usr/include
endif

CXXFLAGS+=-Werror -Wall -Wextra -Wpedantic -g -std=c++11

all:
	$(CXX) $(CXXFLAGS) main.cpp -o cpp-cast

clean:
	rm cpp-cast
