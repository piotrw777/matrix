
CC = g++
FLAGS := -g -pthread -Wpedantic -Wall -std=c++17
OUT = prog.out

all:	$(OUT)

$(OUT):	main.cpp main.o matrix.h frac.o frac.h
	$(CC) $(FLAGS)  main.o frac.o -o $(OUT)
main.o:	matrix.h main.cpp
	$(CC) $(FLAGS) -c main.cpp -o main.o
frac.o:	frac.h frac.cpp
	$(CC) $(FLAGS) -c frac.cpp -o frac.o
clean:
	rm $(OUT)
run:
	./$(OUT)
