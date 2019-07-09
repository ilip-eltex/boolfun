#pragma once

#include <vector>
#include <cmath>
#include "GF.h"

namespace bf {


class ttable;

class polynom {
	
	public:
		polynom (unsigned char n, GF * _field);
		polynom (const ttable &t);
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

