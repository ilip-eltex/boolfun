#include <vector>
#include "GF.h"

namespace bf {


class ttable;

class pol {
	
	public:
		pol (GF(power(2)));
		pol (const ttable &t);
		bool set ();
			
	private:
		vector<bvect32> _values; 
};
	
}

