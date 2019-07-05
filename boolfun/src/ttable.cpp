#include "ttable.h"
using namespace std;

ttable::ttable(unsigned char n) {
	this->length = pow(2,n);
	this->_values.reserve( static_cast<size_t>( this->length) );	 
}

bool ttable::set (std::vector<bvect32> arr) {
	if ( arr.size() >= pow(2,n) )
		return false;
	this->_values = arr;
	this->length = pow(2,n);
	return true;
}

bvect32 ttable::get () {
	return this->_values;
} 

ttable::ttable (const polynom &p) {
	vector<unsigned char> coeff = p.get();
	vector<unsigned char> result;
	uint32_t limit = pow(2,coeff)
	for (uint32_t x=0; x < this->length; x++) {
		result[x] = 0;
		for (uint32_t i=0; i < this->length; i++)
			result[x] += coeff[i] * pow(x,i);
	}
	this->_values = result;
}

uint32_t get_length () {
	return this->_length;
}
