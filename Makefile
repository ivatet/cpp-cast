CC=g++

OS=`uname`

ifeq ($(OS), Darwin)
CFLAGS=-I/usr/local/include
else
CFLAGS=-I/usr/include
endif

all:
	${CC} ${CFLAGS} main.cpp -o cpp-cast

clean:
	rm cpp-cast

