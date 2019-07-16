OBJ = main_test.o
SRC = main_test.cpp
main_test.o: main_test.cpp
	g++ -std=c++11 -c -o main_test.o main_test.cpp
tests: $(OBJ)
	g++ -std=c++11 -o tests $(OBJ)

