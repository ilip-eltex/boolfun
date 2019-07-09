#pragma once

#include <vector>
#include <cmath>
#include <GF.h>
#include <polynom.h>

// Max table length 2^n (n <= 32)
// Max var quanity n (n <= 32)

namespace bf {

class polynom;

class ttable {
	public:
		ttable (unsigned char n);
		ttable (const polynom &p);
		bool set (bvect32 vect, uint32_t index);
		unsigned char get_value(uint32_t index);
		bvect32 get_length ();	
	private:
		std::vector<unsigned char> _values; // Value mb 0 or 1
		uint32_t _length; // <= 2^n
};
	
}

