#pragma once

#include <vector>
#include <cmath>

namespace bf {

class polynom;

class ttable {
	public:
		ttable (unsigned char n);
		ttable (const polynom &p);
		bool set (std::vector<bvect32> arr);
		bvect32 get();	
	private:
		std::vector<unsigned char> _values;
		uint32_t length;
};
	
}

