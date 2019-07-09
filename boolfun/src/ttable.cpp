#include "ttable.h"
using namespace std;
namespace bf {
	ttable::ttable(unsigned char n) {
    this->_length = (1 << n);
		this->_values.resize(static_cast<size_t>(this->_length));
  }

	bool ttable::set(bvect32 vect, uint32_t index) {
		this->_values[index] = vect;
		return true;
	}

	bvect32 ttable::get_value(uint32_t index) {
		return this->_values[index];
	}

	ttable::ttable(const polynom& p) { 
    // здесь не работает
    /*
		vector<unsigned char> coeff;
		for (bvect32 i = 0; i < p.get_length(); i++) {
			coeff.push_back(p->get_coeff(i));
		}
		vector<unsigned char> result;
		uint32_t limit = pow(2, coeff.size());
			for (uint32_t x = 0; x < this->length; x++) {
				//result[x] = 0;
				for (uint32_t i = 0; i < this->length; i++)
					result[x] += coeff[i] * pow(x, i);
			}
		this->_values = result;
    */
	}

	uint32_t ttable::get_length() {
		return this->_length;
	}
}
