CC = g++
CFLAGS = -std=c++11

OBJ = $(CC) -c $< -o $@ $(CFLAGS)
#MKDIR_BUILD_SRC = mkdir -p build/src

#.PHONY: clean test

#default: bin/iv.exe


#bin/iv.exe: build/src/main.o build/src/strings.o build/src/units.o build/src/ivlib.o
#	mkdir -p bin
#	$(CC) $(CFLAGS) $^ -o $@

tests: main_test.o GF.o ios.o linear.o
	#mkdir -p bin
	$(CC) $(CFLAGS) $^ -o $@

main_test.o: main_test.cpp
	$(OBJ)
	
GF.o:   GF.cpp                                                                                                                 
	$(OBJ)

ios.o:	ios.cpp
	$(OBJ)

linear.o: linear.cpp
	$(OBJ)


#clean:
	#rm -rf bin build

