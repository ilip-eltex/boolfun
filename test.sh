#!/bin/bash
x = 0;
result = 0;
if [ "$TRAVIS_BRANCH" = "test" ]; then 
	result =  cd boolfun/test && g++ -std=c++11 main_test.cpp -o tests && ./tests

	exit $result
fi
#####
if [ "$TRAVIS_BRANCH" = "master" ]; then
  cd boolfun/ 
  cmake .  
  cmake --build .
fi

