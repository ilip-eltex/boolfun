#!/bin/bash
#let x = 0;
let result=`cd boolfun/test && g++ -std=c++11 main_test.cpp -o tests && ./tests`
if [ "$TRAVIS_BRANCH" = "test" ]; then 
	exit $result
fi
#####
if [ "$TRAVIS_BRANCH" = "master" ]; then
  cd boolfun/ 
  cmake .  
  cmake --build .
fi

