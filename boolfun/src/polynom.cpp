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

	polynom::polynom(const ttable &t, GF * field) {
		this->_length = t->get_length();
		this->_coeff.resize( static_cast<size_t>(this->_length) );
		this->set_coeff(0,t.get_value(0));
		vector<bvect32> values;
		const uint32_t tlen = tlen;
		for (uint32_t i=0; i < tlen; i++) 
			values.push_back( t.get_value(i) )
		for (uint_32 coeffq = 0; coeffq < this->_length; coeffq++) 
			for (uint32 valuesq=0; valuesq < tlen; valuesq++)
				this->set_coeff( coeffq, ( t->get_value(valuesq) * field->power(valuesq,(tlen - i - 1)) ) );
				 
	}

	uint32_t polynom::get_length() {
		return this->_length;
	}

	GF * polynom::get_field() {
		return this->_field; 
	}
}

