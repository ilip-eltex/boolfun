SRC = boolfun/test/main_test.cpp boolfun/src/bitslib.cpp boolfun/src/ios.cpp #linear.cpp polynom.cpp ttable.cpp GF.cpp ANF.cpp GFSimple.cpp
tests: tests
	g++ -std=c++11 $(SRC) -o tests
