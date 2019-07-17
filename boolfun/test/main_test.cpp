#include <bits/stdc++.h>
#include <stdint.h>
#include <cstdlib>
#include "bitslib.h"
#include "ios.h"
#include <cstdint>
//#include "ttable.h"
//#include "polynom.h"
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
std::vector<uint32_t> set_from_string(const std::string &s);

using namespace bf;
int main () {
	std::vector<test> tests;
	test temp;
	bool quit = false;
	uint32_t result32=0;
	uint64_t result64=0;
	unsigned char temp_char='\0';
	std::cout << "\n########################\n\n";
	
	// get_bit_32 
	result32 = get_bit_32 ( static_cast<uint32_t>(0) , static_cast<unsigned int>(0) );
	temp.set ("get_bit_32(0,0) =0", result32 == 0);
	tests.push_back(temp);
	
	// set_bit_32
	result32 = 0;
	set_bit_32 (result32,1,10);
	temp.set("set_bit_32 (0,1,10) =1024", result32 == 1024 );
	tests.push_back(temp);
	
	// set_bit_32 9[3],0 = 1  
	result32 = 9;
	set_bit_32(result32,0,3);
	temp.set("set_bit_32 (9,0,3) =1", result32==1);
	tests.push_back(temp);
	
	// set_bit1_32
	result32 = 0;
	set_bit1_32 (result32,10);
	temp.set("set_bit1_32 (0,10) =1024", result32 == 1024);
	tests.push_back(temp);
	
	//set_bit0_32
	result32 = 1023;
	set_bit0_32 (result32,9);
	temp.set("set_bit0_32(1023,9) =511", result32 == 511);
	tests.push_back(temp);
	
	//get_weight_32
	result32 = get_weight_32 (15);
	temp.set("get_weight_32(15) =4", result32 == 4);
	tests.push_back(temp);
	
	// is_odd_32 
	result32 = 10;
	temp.set("is_odd_32(10) =TRUE", is_odd_32(result32) == true);
	
	// scalar_product 10 5 = 0
	 result32 = scalar_product_32(10,5);
	 temp.set("scalar_product_32(10,5) =0", result32 == 0);
	 tests.push_back(temp);
	 
	// deg_32 (2048) 
	temp_char = deg_32(2048);
	temp.set("deg_32(2048) =11", temp_char == 11);
	tests.push_back(temp); 
	
	// set_from_string ("4: 10x^2 + 5x^29")
	bool b;
	std:vector<uint32_t> result_vect = set_from_string("4: 10x^2 + 66x^29");
	for (int i=0; i<result_vect.size(); i++)
		std::cout << result_vect[i] << ' ';
	std::cout << "\n\n\n";
	if (result_vect[2] == 0)
		b = false;
	else
		b = result_vect[2]==10 and result_vect[29]==5;
	temp.set("set_from_string('4: 11x^2 + 6x^29')", b);
	tests.push_back(temp);
	
	// 
	//bf::GF *field = bf::get_field(6);
	
	for (int i=0; i<tests.size(); i++) {
		if ( not tests[i].result() ) 			
			quit = true;
		print_test(tests,i);
	}
	std::cout << "\n########################\n\n";
	if (quit) return 1; 
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////
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
			<< t[index].name();
		std::string temp = t[index].name();
		std::cout << ' ';
		if (temp.size() < 27) {
			for (int i=0; i < (27-temp.size()); i++)
				std::cout << '-';	
		}
		std::cout << '>'; 
		if (t[index].result())	
			std::cout << " DONE\n";  
		else std::cout << " FAIL\n";
	}
	
	void test::set (std::string name, bool result) {
		this->_name = name;
		this->_result = result;
	}
	
	std::vector<uint32_t> set_from_string(const std::string &s) {
		// s must be low-cased and a[0] == %number%
		std::string in = s, s1;
		in = trim_all(in);
		stringstream ss, ss1;
		ss1 << s;
		char c;
		const std::vector<uint32_t> FAIL (0); 
		ss.clear();
		ss << in;
		std::vector<string> words;

		while (getline(ss, s1, '+')) // get words between '+'
			words.push_back(s1);

		ss.clear();

		// Begin checking control (first) word {n:}
		ss << words[0];
		uint32_t t; //temp

		ss >> t; // read first word from stream


		if (t == 0)
			return FAIL; // n
		std::cout << '=' << t << std::endl;
		//this->_n = t;
		int max_degree=-1, tempd;
		for (uint32_t i=0; i<s.size(); i++) {
			if (s[i] == '^') {
				ss >> tempd;
				if (tempd > max_degree)
					max_degree = tempd;
			}
		}
		cout << max_degree << '\n';
		std::vector<uint32_t> coeffs;
		coeffs.resize( static_cast<size_t>(max_degree) );
		for (uint32_t i = 0; i < coeffs.size(); i++)
			coeffs[i] = 0;
		std::string tstr = words[0]; // temp string; get first word
		t = 0; // set vector<uint32_t> begin counter value
		//if ( tstr[tstr.length()-1] != ':' ) { // if wrote {n:C1x} in first word
		ss >> c; //skip ':'
		ss >> t;
		coeffs[0] = t;
		t = 1; // set begin counter to second element due to first word wrote wrong


		for (uint32_t i = t; i < words.size(); i++) {
			uint32_t degree = 0;
			ss.clear();

			tstr = words[i];
			ss << tstr;
			t = str2int(tstr);
			if (t == 0) // if no coeff
				t = 1; // coeff == 1
			ss >> c;
			if (c != 'x') {
				if (t == 1)
					return FAIL;
				coeffs[0] ^= t;
				continue;
			}
			while (ss >> c)
				if (c == '^') {
					ss >>
					   tstr;
					if (tstr == "0") {
						degree = 0;
						break;
					}
					degree = str2int(tstr);
					break;
				}
			coeffs[degree-1] ^= t;
		}
		//this->_coeff = coeffs;
		return coeffs;		
	}
