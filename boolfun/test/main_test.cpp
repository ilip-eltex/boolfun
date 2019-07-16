#include <bits/stdc++.h>
#include <stdint.h>
#include "bitslib.h"
//#include "sandbox.h"

class test {
		
		public:
			bool result ();
			std::string name ();
			void set (std::string name, bool result);
			
		private:
			bool _result;
			std::string _name;
};

//bool compare_vals (uint64_t a1, uint64_t a2, size_t size);
void print_test (std::vector<test> &t, unsigned int index);

using namespace bf;
int main () {
	std::vector<test> tests;
	test temp;
	bool quit = false;
	uint32_t result32=0;
	uint64_t result64=0;
	unsigned char temp_char='\0';
	
	// get_bit_32 
	result32 = get_bit_32 ( static_cast<uint32_t>(0) , static_cast<unsigned int>(0) );
	temp.set ("get_bit_32 (0,0)", result32 == 0);
	tests.push_back(temp);
	
	// set_bit_32
	result32 = 0;
	set_bit_32 (result32,1,10);
	temp.set("set_bit_32 (0,1,10)", result32 == 1024 );
	tests.push_back(temp);
	
	// set_bit1_32
	result32 = 0;
	set_bit1_32 (result32,10);
	temp.set("set_bit1_32 (0,10)", result32 == 1024);
	tests.push_back(temp);
	
	//set_bit0_32
	result32 = 1023;
	set_bit0_32 (result32,9);
	temp.set("set_bit0_32 (1023,9)", result32 == 511);
	tests.push_back(temp);
	
	//get_weight_32
	result32 = get_weight_32 (1065);
	temp.set("get_weight_32 (15)", result32 == 4);
	tests.push_back(temp);
	
	// is_odd_32 
	result32 = 9;
	temp.set("is_odd_32 (10)", is_odd_32(result32) == true);
	
	// scalar_product 10 5 = 0
	 result32 = scalar_product_32(10,5);
	 temp.set("scalar_product_32 (10,5)", result32 == 0);
	 tests.push_back(temp);
	 
	// deg_32 (2048) 
	temp_char = deg_32(2048);
	temp.set("deg_32 (2048)", temp_char == 11);
	tests.push_back(temp); 
	
	for (int i=0; i<tests.size(); i++) {
		print_test(tests,i);
		if (tests[i].result() == false)
			quit = true;
	}
	if (quit) return 1; 
	return 0;
}

/////////SOURCE

	/*bool compare_vals (auto a1, auto a2, size_t size) {
		char x[size] = static_cast<char*>(&a1);
		char y[size] = static_cast<char*>(&a2);
		return !(strcmp(a1,a2));
	} */
	
	
	bool test::result () {
		return this->_result;
	}
	
	std::string test::name () {
		return this->_name;
	}
	
	void print_test (std::vector<test> &t, unsigned int index) {
		std::cout 
			<< '#'
			<< index+1
			<< ' '
			<< t[index].name() 
			<< ' ';
		std::cout 
			<< (t[index].result() ? "==PASSED==" : "==FAILED==")
			<< std::endl;
	}
	
	void test::set (std::string name, bool result) {
		this->_name = name;
		this->_result = result;
	}
