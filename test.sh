#!/bin/bash
if [ "$TRAVIS_BRANCH" = "test" ]; then 
	bash test_branch.sh
fi
#####
if [ "$TRAVIS_BRANCH" = "master" ]; then
	bash master_branch.sh
fi

