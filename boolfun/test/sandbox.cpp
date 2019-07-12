#include "sandbox.h"

	
	bool compare_vals (auto a1, auto a2, size_t size) {
		char x[size] = static_cast<char*>(&a1);
		char y[size] = static_cast<char*>(&a2);
		return !(strcmp(a1,a2));
	}
	
	
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

