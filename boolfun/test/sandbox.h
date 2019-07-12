#pragma once

#include <cstring>
#include <string>
#include <malloc.h>
#include <vector>
#include <iostream>

class test {
		
		public:
			bool result ();
			std::string name ();
			void set (std::string name, bool result);
			
		private:
			bool _result;
			std::string _name;
};

bool compare_vals (uint64_t a1, uint64_t a2, size_t size);
void print_test (std::vector<test> &t, unsigned int index);

// TESTING SANDBOX
