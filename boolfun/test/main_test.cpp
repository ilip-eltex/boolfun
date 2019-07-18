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

/////////////START HEADERS ////////////////////
void print_test (std::vector<test> &t, unsigned int index);
string trim(string s);
    string trim_left(string s);
    string trim_right(string s);
    void lower_case(string &s);
    int str2int(string s);
    string int2str(int x);
    string trim_all(string s);

std::vector<uint32_t> set_from_string(const std::string &s);

typedef uint32_t bvect32;
    typedef uint64_t bvect64;

	unsigned int get_bit_32(bvect32 x, unsigned int index);
	void set_bit1_32(bvect32 &x, unsigned int index);
	void set_bit0_32(bvect32 &x, unsigned int index);
	void set_bit_32(bvect32 &x, unsigned int value, unsigned int index);
	unsigned int get_weight_32(bvect32 x);
	bool is_odd_32(bvect32 x);
	bvect32 scalar_product_32(bvect32 a, bvect32 b);
	unsigned char deg_32(bvect32 a);

	///// uint64_t /////////////////////////////////
	
	unsigned int get_bit_64(bvect64 x, unsigned int index);
	void set_bit1_64(bvect64 &x, unsigned int index);
	void set_bit0_64(bvect64 &x, unsigned int index);
	void set_bit_64(bvect64 &x, unsigned int value, unsigned int index);
	unsigned int get_weight_64(bvect64 x);
	bvect64 scalar_product_64(bvect64 a, bvect64 b);
	bool is_odd_64(bvect64 x);
	uint32_t power2(uint32_t y);
	unsigned char deg_64(bvect64 a);
	
////////////////// END HEADERS

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
	
	
	
	// trim (" b ")
	temp.set("trim(' b ')", trim(" b ") == "b");
	tests.push_back(temp);
	
	// trim_left ("    b") 
	temp.set("trim('  b')", "b" == trim_left("   b"));
	tests.push_back(temp);
	
	// trim_rigth ("b     ")
	temp.set("trim_rigth('b   ')", "b" == trim_right("b    "));
	tests.push_back(temp);
	
	// lower_case
	string tempstr = "QwERtyuIo";
	lower_case(tempstr);
	temp.set("lower_case('QwERtyuIo')", "qwertyuio" == tempstr );
	tests.push_back(temp);
	
	// str2int
	temp.set("str2int('1256')", 1256 == str2int("1256"));
	tests.push_back(temp);
	
	// int2str
	temp.set("int2str(1256)", 1256 == str2int("1256") );
	tests.push_back(temp);
	
	// trim_all
	temp.set("trim_all('a b c d e ')", "abcde" == trim_all("a  b  cd e   ") );
	tests.push_back(temp);
	
	// set_from_string ("4: 10x^2 + 5x^29")
	bool b;
	std:vector<uint32_t> result_vect = set_from_string("2: 15x^2 + 31x^29");
	for (int i=0; i<result_vect.size(); i++)
		std::cout << result_vect[i] << ' ';
	std::cout << "\n\n\n";
	if (result_vect[2] == 0)
		b = false;
	else
		b = (result_vect[0]==0) and (result_vect[2]==16);
	temp.set("set_from_string('2: 15x^2 + 31x^29') a[2]=16", b);
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
// get_from_string	
	struct position {
			uint32_t index;
			uint32_t coeff;
		};
	std::vector<uint32_t> set_from_string(const std::string &s) {
		// s must be low-cased and a[0] == %number%
		string trimmed = trim_all(s), temp_string;
		const std::vector<uint32_t> FAIL (0);
		
		const unsigned int n = str2int(trimmed);
		
		if (n==0) 
			return FAIL;
			
		int t=0;
		for (t=0; t<trimmed.size(); t++)
			if (trimmed[t] == ':')
				break;
		char a[trimmed.size()];
		char b[trimmed.size()];
		strcpy(b,trimmed.c_str());
		strncpy(a, &b[t+1], trimmed.size()-t);
		trimmed = a;
		stringstream ss;
		ss.clear();
		ss << trimmed;
		
		std::vector<string> words;

		while (getline(ss, temp_string, '+')) 
			words.push_back(temp_string); // get words between '+'
		ss.clear();
		
		vector<position> got;
		int max_degree=-1, tempd;
		char temp_char;

		for (int i=0; i<words.size(); i++) {
		    bool has_degree=true;
			bool no_x = true;
			
		
			position temp_got;
			if ( words[i][0] != 'x' )
				tempd = str2int(words[i]);
			else 
				tempd = 1;
			
			temp_got.coeff = tempd;
			
			for (int j=0; j<words[i].size(); j++) {
				if (words[i][j] == 'x' ) {
					no_x = false;
					break;
				}
			}
			
			if (no_x) {
				temp_got.index = 0;
				got.push_back(temp_got);
				continue;
			}
			
			temp_char = words[i][words[i].length()-1];
			
			if ( not ((temp_char >= '0') and (temp_char <= '9')) ) {
				has_degree = false;
				temp_string = "1";
			}

			ss.clear();
			ss << words[i];
			while ( (ss >> temp_char) and has_degree) {
				if (temp_char == '^') {
					temp_string = "";
					temp_char = '0';
					while ( (temp_char >= '0') and (temp_char <= '9') and (ss >> temp_char) ) 
						temp_string += temp_char;
	
					break;
				}
			}
			temp_got.index = str2int(temp_string);
			got.push_back(temp_got);
		}
			 
		vector<uint32_t> polynom_coeffs(1 << n);
		for (uint32_t i=0; i<got.size(); i++) {
			uint32_t index = got[i].index;
			index %= power2(n) - 1;
			if ( (index == 0) and (got[i].index != 0) )
				 index = power2(n) - 1;
			polynom_coeffs[index] ^= got[i].coeff;
		}
		return polynom_coeffs;		
}
//////////////////// end get_from_string ////////////////////
string trim_left(string s)
    {
        if (s.empty()) return s;
        string result;
        int i;
        for (i = 0; s[i] == ' '; ++i);
        for (i = i; i < s.length(); ++i)
            result += s[i];
        return result;
    }

    string trim_right(string s)
    {
        if (s.empty()) return s;
        string result;
        int j;
        for (j = s.length() - 1; s[j - 1] == ' '; --j);
        for (int i = 0; i < j; ++i)
            result += s[i];
        return result;
    }

    string trim(string s)
    {
        return trim_left(trim_right(s));
    }

    void lower_case(string &s)
    {
        for (unsigned int i = 0; i < s.length(); i++)
            if ((s[i] >= 'A') && (s[i] <= 'Z'))
                s[i] = 'a' + (s[i] - 'A');
    }

    int str2int(string s)
    {
        int x;
        stringstream ss;
        ss.clear();
        ss << s;
        ss >> x;
        return x;
    }

    string int2str(int x)
    {
        string s;
        stringstream ss;
        ss.clear();
        ss << x;
        ss >> s;
        return s;
    }

    vector<string> get_words(const string s)
    {
        vector<string> result;
        stringstream ss;
        ss.clear();
        ss << s;
        string s1;
        while (ss >> s1)
            result.push_back(s1);
        return result;
    }
//s
    string trim_all(string s)
    {
        string result;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == ' ')
                continue;
            result += s[i];
        }
        return result;
    }
    
        unsigned int get_bit_32(bvect32 x, unsigned int index)
    {
        return (x >> index) & (unsigned) 1;
    }

    void set_bit1_32(bvect32 &x, unsigned int index)
    {
        x |= ((unsigned) 1 << index);
    }

    void set_bit0_32(bvect32 &x, unsigned int index)
    {
        x &= ~((unsigned) 1 << index);
    }

    void set_bit_32(bvect32 &x, unsigned int value, unsigned int index)
    {
        if (value)
            x |= (unsigned) 1 << index;
        else
            x &= ~((unsigned) 1 << index);
    }

    unsigned int get_weight_32(bvect32 x)
    {
        bvect32 result = 0;
        while (x != 0)
        {
            x &= x - 1;
            result++;
        }
        return result;
    }

    bool is_odd_32(bvect32 x)
    {
        x ^= (x >> (unsigned) 16);
        x ^= (x >> (unsigned) 8);
        x ^= (x >> (unsigned) 4);
        x ^= (x >> (unsigned) 2);
        x ^= (x >> (unsigned) 1);
        return (x & (unsigned) 1);
    }

    bvect32 scalar_product_32(bvect32 a, bvect32 b)
    {
        return is_odd_32(a & b);
    }

    unsigned char deg_32(bvect32 a)
    {
        if (a == 0)
            return 0;
		for (int i = 31; i >= 0; --i)
            if ((a >> (unsigned) i) & (unsigned) 1)
                return (unsigned char) i;
        return 0;
    }

//////////////// for bvect64 ///////////////////////////////////////////////

    unsigned int get_bit_64(bvect64 x, unsigned int index)
    {
        return (x >> index) & (unsigned) 1;
    }

    void set_bit1_64(bvect64 &x, unsigned int index)
    {
        x |= (static_cast<bvect64>(1) << index);
    }

    void set_bit0_64(bvect64 &x, unsigned int index)
    {
        x &= ~(static_cast<bvect64>(1) << index);
    }

    void set_bit_64(bvect64 &x, unsigned int value, unsigned int index)
    {
        if (value)
            x |= static_cast<bvect64>(1) << index;
        else
            x &= ~(static_cast<bvect64>(1) << index);
    }

    unsigned int get_weight_64(bvect64 x)
    {
        bvect32 result = 0;
        while (x != 0)
        {
            x &= x - 1;
            result++;
        }
        return result;
    }
	bool is_odd_64(bvect64 x)
    {
        x ^= (x >> (unsigned) 32);
        x ^= (x >> (unsigned) 16);
        x ^= (x >> (unsigned) 8);
        x ^= (x >> (unsigned) 4);
        x ^= (x >> (unsigned) 2);
        x ^= (x >> (unsigned) 1);
        return (x & (unsigned) 1);
    }
    bvect64 scalar_product_64(bvect64 a, bvect64 b)
    {
        return is_odd_64(a & b);
    }

    

    uint32_t power2(uint32_t y)
    {
        return (static_cast<uint32_t>(1) << y);
    }

    unsigned char deg_64(bvect64 a)
    {
        if (a == 0)
            return 0;
		for (int i = 63; i >= 0; --i)
            if ((a >> (unsigned) i) & (unsigned) 1)
                return (unsigned char) i;
        return 0;
    }
