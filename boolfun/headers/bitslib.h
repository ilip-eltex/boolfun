#pragma once

#include <GF.h>

namespace bf {
	
/////////////// for bvect32 ///////////////////////////////////////////////

	int get_bit_32 (bvect32 &x, unsigned int index) {
		return (index >> x) & 1;
	}

	void set_bit1_32 (bvect32 &x, unsigned int index) {
		x |= (1 << index);
	}

	void set_bit0_32 (bvect32 &x, unsigned int index) {
		x &= ~(1 << index);
	}

	void set_bit_32 (bvect32 &x, unsigned int value, unsigned int index) {
		if (value)
			x |= 1 << index;
		else
			x &= ~(1 << index);
	}

	unsigned int get_weight_32 (bvect32 x) {
		bvect32 result = 0;
		while (x != 0) {
			x &= x - 1;
			result++;
		}
		return result;
	}

	int is_odd_32 (bvect32 x) {
		x ^= (x >> 16);
		x ^= (x >> 8);
		x ^= (x >> 4);
		x ^= (x >> 2);
		x ^= (x >> 1);
		return (x & 1);
	}

	int prod_32 (bvect32 x, bvect32 y) {
		return is_odd_32 (x & y);
	}
//////////////// for bvect64 ///////////////////////////////////////////////

	int get_bit_64 (bvect64 &x, unsigned int index) {
		return (index >> x) & 1;
	}

	void set_bit1_64 (bvect64 &x, unsigned int index) {
		x |= (static_cast<bvect64>(1) << index);
	}

	void set_bit0_64 (bvect64 &x, unsigned int index) {
		x &= ~(static_cast<bvect64>(1) << index);
	}

	void set_bit_64 (bvect64 &x, unsigned int value, unsigned int index) {
		if (value)
			x |= static_cast<bvect64>(1) << index;
		else
			x &= ~(static_cast<bvect64>(1) << index);
	}

	unsigned int get_weight_64 (bvect64 x) {
		bvect32 result = 0;
		while (x != 0) {
			x &= x - 1;
			result++;
		}
		return result;
	}

	int is_odd_64 (bvect64 x) {
		x ^= (x >> 32);
		x ^= (x >> 16);
		x ^= (x >> 8);
		x ^= (x >> 4);
		x ^= (x >> 2);
		x ^= (x >> 1);
		return (x & 1);
	}

	int prod_64 (bvect64 x, bvect64 y) {
		return is_odd_64 (x & y);
	}
}

