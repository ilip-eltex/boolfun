#pragma once

#include <vector>
#include <cmath>
#include "GF.h"

// Max polynom length 2^n (n <= 32)
// Max var quanity n (n <= 32)

namespace bf {


class ttable;

class polynom {
	
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
	
}

