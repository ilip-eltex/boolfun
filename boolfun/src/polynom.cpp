#include <bitslib.h>
#include "polynom.h"
#include "ios.h"
#include "ttable.h"

namespace bf
{
    //FIXME release NM functions
    polynom::polynom(GF *field)
    {
        this->_length = power2(static_cast<uint32_t>(field->get_order()));
        this->_coeff.resize(static_cast<size_t>(this->_length));
    }

    polynom::polynom(ttable &t, GF *field) 
    {
        const uint64_t len = t.get_length();
        
        this-> _m = t.get_output_length(); 
		this-> _length = len;           
        this-> _field = field;
        
        this-> _coeff.resize ( static_cast<size_t>(len) );        
        this-> set_coeff (0, t.get_value(0) ); // Coeff #0 == F(0)
        
        bvect32 temp;
        for (uint64_t j = 1; j < len; j++) {
        	temp = 0;
			for (uint64_t a = 0; a < len; a++) {
				temp ^= field->multiply( t.get_value(a) , field->power( a, (len - 1 - j) ) );  	
			}
			this-> set_coeff(j,temp);
		}
    }

    void polynom::set_coeff(uint32_t index, bvect32 coeff)
    {
        this->_coeff[index] = coeff;
    }

    bvect32 polynom::get_coeff(uint32_t index)
    {
        return this->_coeff[index];
    }

    uint64_t polynom::get_length()
    {
        return this->_length;
    }

    GF *polynom::get_field()
    {
        return this->_field;
    }
    
    unsigned int polynom::get_input_length () {
    	return this->_n;
	}
    unsigned int polynom::get_output_length () {
    	return this->_m;
	}

    bool polynom::set_from_string(const std::string &s)
    {
        // s must be low-cased and a[0] == %number%
		string trimmed = trim_all(s), temp_string;
		const std::vector<uint32_t> FAIL (0);
		
		const unsigned int n = str2int(trimmed);
		this->_n = n;
		if (n==0) 
			return false;
			
		int t=0;
		for (t=0; t<trimmed.size(); t++) // getting length of 'n:'
			if (trimmed[t] == ':')
				break;
				
		char a[trimmed.size()];
		char b[trimmed.size()];
		strcpy(b,trimmed.c_str());
		strncpy(a, &b[t+1], trimmed.size()-t); //cut 'n:'
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
		    
			bool has_degree = true;
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
		this->_coeffs = polynom_coeffs;
        return true;
    }
}
