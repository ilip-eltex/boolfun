#pragma once
#include "GF.h"

namespace bf 
{
	int get_bit_32(bvect32 n, int x) 
	{
		return (n >> x) & 1;
	}

	void set_bit_32(bvect32* n, int x, int value)
	{
		if (value)
			(*n) |= 1 << x;
		else
			(*n) &= ~(1 << x);
	}

	int get_bit_64(bvect64 n, int x)
	{
		return (n >> x) & 1;
	}

	void set_bit_64(bvect64* n, int x, int value)
	{
		if (value)
			(*n) |= 1 << x;
		else
			(*n) &= ~(1 << x);
	}
}
