#include "polynom.h"

using namespace std;

polynom::polynom(unsigned char n) {
	this->_length = pow(2,n);
	this->_coeff.reserve( static_cast<size_t>( this->length) );	 
}

bool polynom::set (std::vector<bvect32> arr) {
	if ( arr.size() >= pow(2,n) )
		return false;
	this->_values = arr;
	this->_length = pow(2,n);
	return true;
}

bvect32 polynom::get_coeffs () {
	return this->_coeff;
} 

polynom::polynom (const ttable &t) {
	
}

uint32_t get_length () {
	return this->_length;
}
