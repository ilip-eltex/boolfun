#CC = g++
#CFLAGS = -std=c++11

#OBJ = $(CC) -c $< -o $@ $(CFLAGS)
#MKDIR_BUILD_SRC = mkdir -p build/src

#.PHONY: clean test

#default: bin/iv.exe


#bin/iv.exe: build/src/main.o build/src/strings.o build/src/units.o build/src/ivlib.o
#	mkdir -p bin
#	$(CC) $(CFLAGS) $^ -o $@

tests: main_test.o sandbox.o
	#mkdir -p bin
	g++ main_test.o sandbox.o -o tests#GF.o ios.o linear.o -o test

main_test.o: main_test.cpp
	g++ main_test.cpp

sandbox.o: sandbox.cpp
	g++ sandbox.cpp
	
#GF.o:   GF.cpp                                                                                                                 
#	gcc GF.cpp

#ios.o:	ios.cpp
#	gcc ios.cpp

#linear.o: linear.cpp
#	gcc linear.cpp


#clean:
	#rm -rf bin build

