#pragma once

#include "GF.h"
#include "ttable.h"

namespace bf {
	bool is_affine(const ttable &t, bvect32 &coeffs, bool &cnst);
	bool is_affine (const ttable &t);
	bool is_linear (const ttable &t, bvect32 &coeffs);
	bool is_linear (const ttable &t);
}
