#pragma once

#include <vector>
#include <cmath>
#include <GF.h>
#include <polynom.h>

namespace bf {

class polynom;

class ttable {
	public:
		ttable (unsigned char n);
		ttable (const polynom &p);
		bool set (bvect32 vect, bvect32 n);
		bvect32 get_value(bvect32 n);
		bvect32 get_length ();	
	private:
		std::vector<unsigned char> _values;
		uint32_t _length;
};
	
}

