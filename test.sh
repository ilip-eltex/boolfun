#!/bin/bash
if [ "$TRAVIS_BRANCH" = "test" ]; then 
  cd boolfun/test
  g++ -std=c++11 main_test.cpp -o tests
  ./tests
fi
#####
if [ "$TRAVIS_BRANCH" = "master" ]; then
  cd boolfun/ 
  cmake .  
  cmake --build
fi

