#pragma once

#include <vector>
#include <cmath>
#include "GF.h"
#include "ttable.h"

// Max polynom length 2^n (n <= 32)
// Max var quanity n (n <= 32)

namespace bf {


class ttable;
class ttable64;

class polynom { // over field type
	
	public:
		polynom (GF * field);
		polynom::polynom(const ttable &t, GF * field);
		void set_coeff (uint32_t index, bvect32 coeff);
		unsigned char get_coeff (uint32_t index);
		uint32_t get_length ();
		GF* get_field();
			
	private:
		std::vector<unsigned char> _coeff;
		uint32_t _length;
		GF * _field;
};

class polynom64 { // over field type
	
	public:
		polynom64 (GF * field);
		polynom64::polynom64(const ttable &t, GF * field);
		void set_coeff (uint64_t index, bvect64 coeff);
		unsigned char get_coeff (uint64_t index);
		uint64_t get_length ();
		GF* get_field();
			
	private:
		std::vector<unsigned char> _coeff;
		uint64_t _length;
		GF * _field;
};
	
}

