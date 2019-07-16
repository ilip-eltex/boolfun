#pragma once

#include <vector>

#include "bitslib.h"
#include "polynom.h"
#include "bitslib.h"

// Max table length 2^n (n <= 32)
// Max var quanity n (n <= 32)

using namespace std;

namespace bf {

	class polynom;

	class ttable {
		public:
			
			//ttable (GF *field); //from field
			ttable (GF *field, polynom &p); // from polynom 
			ttable (GF *field, std::vector< vector<bvect64> > anf); // ANF as value table
			ttable (GF *field, std::vector<bvect32> values);  
			
			void set (std::vector<bvect32> value, uint32_t index); // index aka f(index)
			void set (std::vector<bvect32> values);
			bvect32 get_value(uint32_t index);
			bvect32 get_length();
			GF *get_field();
			int get_output_length() { return 0; } // get _m
			int get_input_length() { return 0; } // get _n
			int is_NM_function() { return 0; } //FIXME release
		private:
			std::vector<bvect32> _values; // Values mb 0 or 1
			uint64_t _length; // <= 2^n
			GF *_field;
			int _n; // input
			int _m; // output
	};
}

