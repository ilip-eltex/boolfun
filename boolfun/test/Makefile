CC = g++
CFLAGS = -std=c++11

OBJ = $(CC) -c $< -o $@ $(CFLAGS)
#MKDIR_BUILD_SRC = mkdir -p build/src

#.PHONY: clean test

#default: bin/iv.exe

test: test/

#bin/iv.exe: build/src/main.o build/src/strings.o build/src/units.o build/src/ivlib.o
#	mkdir -p bin
#	$(CC) $(CFLAGS) $^ -o $@

tests: main_test.o GF.o
	#mkdir -p bin
	$(CC) $(CFLAGS) $^ -o $@

main_test.o: main_test.c
	$(OBJ)
	
GF.o:   GF.cpp                                                                                                                 
	$(OBJ)


#clean:
	#rm -rf bin build

