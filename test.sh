#!/bin/bash
if [[ $TRAVIS_BRANCH == 'test' ]]
  cd boolfun/test
  g++ -std=c++11 main_test.cpp -o tests
  ./tests
fi
