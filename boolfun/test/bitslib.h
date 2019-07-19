#pragma once

#include <cstdint>

namespace bf
{
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
}

