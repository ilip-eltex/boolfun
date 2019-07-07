#include "polynom.h"

namespace bf {

	polynom::polynom(unsigned char n, GF * _field) {
		this->_length = pow(2, n);
		this->_coeff.resize(static_cast<size_t>(this->_length));
	}

	void polynom::set_coeff(bvect32 n, bvect32 coeff) {
		/*if ( arr.size() >= pow(2,n) )
			return false; */
		this->_coeff[n] = coeff;
		//this->_length = pow(2,n);
		//return true;
	}

	unsigned char polynom::get_coeff(bvect32 n) {
		return this->_coeff[n];
	}

	polynom::polynom(const ttable& t) {

	}

	uint32_t polynom::get_length() {
		return this->_length;
	}

	GF * polynom::get_field() {
		return this->_field; 
	}
}