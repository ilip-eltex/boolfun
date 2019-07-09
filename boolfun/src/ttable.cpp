#include "ttable.h"
using namespace std;
namespace bf {
	
	ttable::ttable(unsigned char n) {
		this->_length = power2(n);
		this->_values.resize(static_cast<size_t>(this->_length));
	}

	bool ttable::set(bvect32 vect, uint32_t index) {
		this->_values[index] = vect;
		return true;
	}

	bvect32 ttable::get_value(uint32_t index) {
		return this->_values[index];
	}
	
	ttable::ttable (const polynom& p) {
			vector<unsigned char> coeff;
			const uint32_t polynom_length = p.get_length(); // aka x-quanity aka coeff-quanity
			for (bvect32 i = 0; i < polynom_length; i++) 
				coeff.push_back( p.get_coeff(i) );
			vector<unsigned char> result; 
			result.resize(polynom_length);
			for (uint32_t x = 0; x < polynom_length; x++) // Cycle by vectors
				for (uint32_t i = 0; i < polynom_length; i++) // Cycle by coeffs
						result[x] += coeff[i] * pow(x, i);
			this->_values = result;
	}
	
	uint32_t ttable::get_length() {
		return this->_length;
	}
	
}
