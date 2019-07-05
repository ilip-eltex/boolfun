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
			
	private:
		vector<unsigned char> _values; 
};
	
}

