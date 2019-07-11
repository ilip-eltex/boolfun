#include "linear.h"

namespace bf {
	
	bool is_affine(const ttable &t, bvect32 &coeffs, bool &cnst) {
		uint32_t mid = t->get_length();
		int flag = -1;
		int j=0;
		int cast = 0;
		bvect32 vect=0;
		vector<bvect32> values;
		for (uint32_t i=0; i < mid; i++)
			values.push_back(t.get_value(i));
		mid /= 2;
		while (mid != 0) {
			cast = static_cast<int>(values[j] == values[j+mid]);
			if (flag == -1)
				flag = cast;			
			if (flag != cast)
				return false;
			
			if (j == mid) {
				j = 0;
				mid /= 2;
				if (flag == 1) 
					vect ^= mid;
				flag = -1;
				continue;
			}
			j++;
		}
		coeffs = vect;
		cnst = (values[0] != 0);
		return true;
	}
	
	bool is_affine (const ttable &t) {
		bool b;
		bvect32 v;
		return (t,v,b);
	}
	
	bool is_linear (const ttable &t, bvect32 &coeffs) {
		if (t.get_value(0) == 0) 
			return false;
		bool b;
		return is_affine(t, coeffs, b);
		
	}
	
	bool is_linear (const ttable &t) {
		bvect32 b;
		return is_linear (t,b);
	}
	
}
