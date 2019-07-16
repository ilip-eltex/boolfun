#!/bin/bash
if [ "$TRAVIS_BRANCH" = "test" ]; then 
	cd boolfun/test 
	make tests
	./tests
	exit $?
fi
#####
if [ "$TRAVIS_BRANCH" = "master" ]; then
	cd boolfun/ 
	cmake .  
	cmake --build .
fi

