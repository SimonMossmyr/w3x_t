.DEFAULT_GOAL := all

all:
	g++ -o main.o src/main.cpp -lstorm -lz -lbz2