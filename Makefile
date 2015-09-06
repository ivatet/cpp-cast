CC=g++
CFLAGS=-I/usr/local/include
all:
	${CC} ${CFLAGS} main.cpp -o cpp-cast

clean:
	rm cpp-cast

