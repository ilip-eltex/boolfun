#pragma once
#include "GF.h"

namespace bf {
	unsigned char deg(bvect32 a)
	{
		for (int i = 31; i >= 0; --i)
			if ((a >> i) % 2)
				return (unsigned char)i;
		return 0;
	}
}