ifndef CXX
CXX=g++
endif

OS=`uname`

ifdef BOOST
CXXFLAGS=-I$(BOOST)
else
ifeq ($(OS), Darwin)
CXXFLAGS=-I/usr/local/include
else
CXXFLAGS=-I/usr/include
endif
endif

CXXFLAGS+=-Werror -Wall -Wextra -Wpedantic -g -std=c++11

all:
	$(CXX) $(CXXFLAGS) main.cpp -o cpp-cast

clean:
	rm cpp-cast
