#pragma once
#include "GF.h"

namespace bf 
{
	int getBit32(bvect32 n, int x) 
	{
		return (n >> x) & 1;
	}

	void setBit32(bvect32* n, int x, int value)
	{
		if (value)
			(*n) |= 1 << x;
		else
			(*n) &= ~(1 << x);
	}

	int getBit64(bvect64 n, int x)
	{
		return (n >> x) & 1;
	}

	void setBit64(bvect64* n, int x, int value)
	{
		if (value)
			(*n) |= 1 << x;
		else
			(*n) &= ~(1 << x);
	}
}
