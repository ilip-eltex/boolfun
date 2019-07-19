#include <bits/stdc++.h>
#include <stdint.h>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include "ttable.h"
#include "polynom.h"
#include "ANF.h"
#include "boolean_utils.h"
#include "ios.h"
#include "bitslib.h"
using namespace std;
using namespace bf;

class test	{
		
		public:
			bool result ();
			std::string name ();
			void set (std::string name, bool result);
			
		private:
			bool _result;
			std::string _name;
};



void print_test (std::vector<test> &t, unsigned int index);




int main () {
	std::vector<test> tests;
	test temp;
	bool quit = false;
	uint32_t result32=0;
	uint64_t result64=0;
	unsigned char temp_char='\0';
	std::cout << '\n';
	
	// get_bit_32 
	result32 = bf::get_bit_32 ( static_cast<uint32_t>(0) , static_cast<unsigned int>(0) );
	temp.set ("get_bit_32(0,0) =0", result32 == 0);
	tests.push_back(temp);
	
	// set_bit_32
	result32 = 0;
	bf::set_bit_32 (result32,1,10);
	temp.set("set_bit_32 (0,1,10) =1024", result32 == 1024 );
	tests.push_back(temp);
	
	// set_bit_32 9[3],0 = 1  
	result32 = 9;
	bf::set_bit_32(result32,0,3);
	temp.set("set_bit_32 (9,0,3) =1", result32==1);
	tests.push_back(temp);
	
	// set_bit1_32
	result32 = 0;
	bf::set_bit1_32 (result32,10);
	temp.set("set_bit1_32 (0,10) =1024", result32 == 1024);
	tests.push_back(temp);
	
	//set_bit0_32
	result32 = 1023;
	bf::set_bit0_32 (result32,9);
	temp.set("set_bit0_32(1023,9) =511", result32 == 511);
	tests.push_back(temp);
	
	//get_weight_32
	result32 = bf::get_weight_32 (15);
	temp.set("get_weight_32(15) =4", result32 == 4);
	tests.push_back(temp);
	
	// is_odd_32 
	result32 = 10;
	temp.set("is_odd_32(10) =TRUE", bf::is_odd_32(result32) == true);
	
	// scalar_product 10 5 = 0
	 result32 = bf::scalar_product_32(10,5);
	 temp.set("scalar_product_32(10,5) =0", result32 == 0);
	 tests.push_back(temp);
	 
	// deg_32 (2048) 
	temp_char = bf::deg_32(2048);
	temp.set("deg_32(2048) =11", temp_char == 11);
	tests.push_back(temp); 
	
	
	
	// trim (" b ")
	temp.set("trim(' b ')", bf::trim(" b ") == "b");
	tests.push_back(temp);
	
	// trim_left ("    b") 
	temp.set("trim('  b')", "b" == bf::trim_left("   b"));
	tests.push_back(temp);
	
	// trim_rigth ("b     ")
	temp.set("trim_rigth('b   ')", "b" == bf::trim_right("b    "));
	tests.push_back(temp);
	
	// lower_case
	string tempstr = "QwERtyuIo";
	bf::lower_case(tempstr);
	temp.set("lower_case('QwERtyuIo')", "qwertyuio" == tempstr );
	tests.push_back(temp);
	
	// str2int
	temp.set("str2int('1256')", 1256 == bf::str2int("1256"));
	tests.push_back(temp);
	
	// int2str
	temp.set("int2str(1256)", 1256 == bf::str2int("1256") );
	tests.push_back(temp);
	
	// trim_all
	temp.set("trim_all('a b c d e ')", "abcde" == bf::trim_all("a  b  cd e   ") );
	tests.push_back(temp);
	
	
		
	// 
	//bf::GF *field = bf::get_field(6);
	
	for (int i=0; i<tests.size(); i++) {
		if ( not tests[i].result() ) 			
			quit = true;
		print_test(tests,i);
	}
	std::cout << "\n########################\n\n";
	
	// Full analyze
	
	std::cout << "Analyze example (ANF): 'x1x2x3 +x2x4x5 + x1x2 + x1x4 + x2x6 + x3x5 + x4x5 + x7x8'\n\n";
	bf::ANF anf;
    anf.parse_ANF("x1x2x3 +x2x4x5 + x1x2 + x1x4 + x2x6 + x3x5 + x4x5 + x7x8");
    bf::ttable a = anf.getFunction();
    bf::full_analysis(a);
	
	if (quit) return 1;
	std::cout << "\n\n==TESTS PASSED SUCCESSFULLY==\n\n"; 
	return 0;
}


///////////////////////////////////////////////////////////////////////////////////
/////////SOURCE

	
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
			<< (index < 9 ? " " : "")
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


