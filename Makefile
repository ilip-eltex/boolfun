DIR = boolfun/test
SRC = $(DIR)/*.cpp
tests: tests
	g++ -std=c++11 $(SRC) -o tests
