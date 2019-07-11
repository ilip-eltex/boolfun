#pragma once

#include <vector>
#include <cmath>
#include <GF.h>
#include <polynom.h>
#include "bitslib.h"

// Max table length 2^n (n <= 32)
// Max var quanity n (n <= 32)

namespace bf {

class polynom;
class polynom64;

class ttable { //in field type
	public:
		ttable(GF * field);
		ttable (const polynom& p, GF * field);
		ttable (const std::vector<bvect32> &vect);
		void set (bvect32 vect, uint32_t index);
		unsigned char get_value(uint32_t index);
		bvect32 get_length ();
		GF * get_field ();	
	private:
		std::vector<unsigned char> _values; // Values mb 0 or 1
		uint32_t _length; // <= 2^n
		GF * _field;
};

class ttable64 { //in field type
	public:
		ttable64 (GF * field);
		ttable64 (const polynom& p, GF * field);
		ttable (const std::vector<bvect32> &vect);
		void set (unsigned char vect, uint64_t index);
		unsigned char get_value(uint64_t index);
		bvect64 get_length ();
		GF * get_field ();	
	private:
		std::vector<unsigned char> _values; // Values mb 0 or 1
		uint64_t _length; // <= 2^n
		GF * _field;
};
	
}

