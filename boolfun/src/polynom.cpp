#include "polynom.h"

namespace bf {

	polynom::polynom (unsigned char n) 
	
	polynom::polynom (unsigned char n, GF * _field) {
		this->_length = power2( static_cast<uint32_t>(n) );
		this->_coeff.resize( static_cast<size_t>(this->_length) );
	}

	void polynom::set_coeff(uint32_t index, bvect32 coeff) {
		this->_coeff[index] = coeff;
	}

	unsigned char polynom::get_coeff(uint32_t index) {
		return this->_coeff[index];
	}

	polynom::polynom(const ttable &t) {
		
	}

	uint32_t polynom::get_length() {
		return this->_length;
	}

	GF * polynom::get_field() {
		return this->_field; 
	}
}

