#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <cstring>

#include "bitslib.h"
#include "GF.h"

// Max polynom length 2^n (n <= 32)
// Max var quanity n (n <= 32)

namespace bf {
	class ttable;

	struct position {
			uint32_t index;
			uint32_t coeff;
		};

	class polynom {
			// over field type

		public:
			polynom (GF *field);
			polynom (ttable &t);

			bool set_from_string (const std::string &s);
			void set_coeff (uint32_t index, bvect32 coeff);

			bvect32	 get_coeff (uint32_t index);
			uint64_t get_length ();
			GF* get_field ();
			
			unsigned int get_input_length ();
			unsigned int get_output_length ();


		private:
			std::vector<bvect32> _coeff;
			uint64_t _length;
			GF* _field;
			unsigned int _n; //input
			unsigned int _m;

	};

}
