CC=g++

OS=`uname`

ifeq ($(OS), Darwin)
CFLAGS=-I/usr/local/include
else
CFLAGS=-I/usr/include
endif

CFLAGS+=-Wall -Werror -Wpedantic

all:
	${CC} ${CFLAGS} main.cpp -o cpp-cast

clean:
	rm cpp-cast

