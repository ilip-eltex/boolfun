#pragma once

#include <vector>
#include "GF.h"

namespace bf {


class ttable;

class polynom {
	
	public:
		polynom ();
		polynom (const ttable &t);
		bool set ();
		bvect32 get ();
		uint32_t get_length ();
			
	private:
		vector<unsigned char> _coeff;
		uint32_t _length; 
};
	
}

