#pragma once
///s/s/ss/s/
#include <vector>
#include "polynom.h"

// Max table length 2^n (n <= 32)
// Max var quanity n (n <= 32)

using namespace std;

namespace bf {
	class polynom;

	class ttable {
			//in field type
		public:
			
			ttable(polynom &p);
			ttable(vector< vector<bvect64> > anf_db);
			ttable (vector<bvect32> values);
			
			void set(bvect32 vect, uint32_t index);
			
			bvect32 get_value(uint32_t index);
			std::vector<bvect32> get_all ()
			uint64_t get_length();
			
			int get_output_length();
			int get_input_length();
			int is_NM_function();
			
		private:
			std::vector<bvect32> _values;
			uint64_t _length;
	};

}

