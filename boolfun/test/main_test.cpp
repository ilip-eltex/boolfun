#include <bits/stdc++.h>
#include <stdint.h>
#include "bitslib.h"
#include "sandbox.h"


using namespace bf;
int main () {
	std::vector<test> tests;
	test temp;
	bool quit = false;
	
	// get_bit_32 
	uint32_t result32 = get_bit_32 ( static_cast<uint32_t>(0) , static_cast<unsigned int>(0) );
	temp.set ("get_bit_32", result32 == 0);
	tests.push_back(temp);
	
	// set_bit_32
	result32 = 0;
	set_bit_32 (result32,1,10);
	temp.set("set_bit_32", result32 == 1024 );
	tests.push_back(temp);
	
	// set_bit1_32
	result32 = 0;
	set_bit1_32 (result32,10);
	temp.set("set_bit1_32", result32 == 1024);
	tests.push_back(temp);
	
	//set_bit0_32
	result32 = 1023;
	set_bit0_32 (result32,9);
	temp.set("set_bit0_32", result32 == 511);
	tests.push_back(temp);
	
	for (int i=0; i<tests.size(); i++) {
		print_test(tests,i);
		if (tests[i].result() == false)
			quit = true;
	}
	if (quit) return 1;
	return 0;
}
