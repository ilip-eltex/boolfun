#include "bitslib.h"
#include "ttable.h"

using namespace std;

namespace bf {

	ttable::ttable (polynom &p) {
		auto field = p.get_field();
		vector<bvect32> coeff;
		const uint32_t polynom_length = p.get_length(); // aka x-quanity aka coeff-quanity
		for (bvect32 i = 0; i < polynom_length; i++)
			coeff.push_back(p.get_coeff(i));
		_values.resize(polynom_length);

		for (uint32_t x = 0; x < polynom_length; x++) // Cycle by vectors
			for (uint32_t i = 0; i < polynom_length; i++) // Cycle by coeffs
				_values[x] += field->multiply(coeff[i], field->power(x, i));
	}

	ttable::ttable (vector< vector<bvect64> > anf_db) {
		vector<bvect32> values;
		values.resize (anf_db[0].size());
		for (uint64_t i=0; i < values.size(); i++)
			values[i] = 0;
		uint64_t current_value=0;
		for (uint64_t i=0; i<anf_db.size(); i++) { // container for (containers for bits in values vector
			current_value = 0;
			for (uint64_t j=0; j<anf_db[i].size(); j++) { // anf_db[j] - container for bit number j in values vector
				for (int k=0; k<63; k++) {
					uint32_t temp = this->_values[current_value];
					set_bit_32(temp, get_bit_32(anf_db[i][j],k),j);
					this->_values[current_value++] = temp;
				}
			}
		}

	}

	ttable::ttable (vector<bvect32> values) {
		this->_values = values;
	}

	void ttable::set(bvect32 vect, uint32_t index) {
		this->_values[index] = vect;
	}

	bvect32 ttable::get_value (uint32_t index) {
		return this->_values[index];
	}

	vector<bvect32> ttable::get_all() {
		return (this->_values);
	}

	uint64_t ttable::get_length() {
		return this->_length;
	}

	int ttable::is_NM_function () {
		return (this->_m > 1);
	}

	int ttable::get_input_length() {
		return (this->_n);
	}

	int ttable::get_output_length() {
		return (this->_m);
	}

}

