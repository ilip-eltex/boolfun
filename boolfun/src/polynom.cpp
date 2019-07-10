#include "polynom.h"

namespace bf {

	polynom::polynom (GF * field) {
		this-_length = power2 ( static_cast<uint32_t>(field->get_order()) );
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
					this->set_coeff( coeffq, ( field->multiply( t->get_value(valuesq), field->power(valuesq,(tlen - i - 1)) ) ) );

	}

	uint32_t polynom::get_length() {
		return this->_length;
	}

	GF * polynom::get_field() {
		return this->_field;
	}
	
	polynom64::polynom64 (GF * field) {
		this-_length = power2 ( static_cast<uint64_t>(field->get_order()) );
		this->_coeff.resize( static_cast<size_t>(this->_length) );
	}


	void polynom64::set_coeff(uint64_t index, bvect64 coeff) {
		this->_coeff[index] = coeff;
	}

	unsigned char polynom64::get_coeff(uint64_t index) {
		return this->_coeff[index];
	}

	polynom64::polynom64 (const ttable &t, GF * field) {
		this->_length = t->get_length();
		this->_coeff.resize( static_cast<size_t>(this->_length) );
		this->set_coeff(0,t.get_value(0));
		vector<bvect64> values;
		const uint64_t tlen = tlen;
		for (uint64_t i=0; i < tlen; i++)
			values.push_back( t.get_value(i) )
			for (uint_64 coeffq = 0; coeffq < this->_length; coeffq++)
				for (uint64 valuesq=0; valuesq < tlen; valuesq++)
					this->set_coeff( coeffq, ( field->multiply( t->get_value(valuesq), field->power(valuesq,(tlen - i - 1)) ) ) );

	}

	uint64_t polynom64::get_length() {
		return this->_length;
	}

	GF * polynom::get_field() {
		return this->_field;
	}
	
}

