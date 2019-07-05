#pragma once

#include <vector>
#include <iostream>
#include <cmath>

namespace bf {

class pol;

class ttable {
	public:
		ttable (unsigned char n);
		ttable (const pol &p);
		bool set (std::vector<bvect32> arr);
		bvect32 get();	
	private:
		std::vector<bvect32> _values; 
};
	
}

