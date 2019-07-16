#include "bitslib.h"
#include "ttable.h"

using namespace std;

<<<<<<< HEAD
namespace bf { //FIXME release NM functions!!!
	
	int ttable::is_NM_function () {

	}


	ttable::ttable(polynom &p) {
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
		values.resize (power2(field->get_order());
		               for (uint64_t i=0; i < values.size(); i++)
		               values[i] = 0;
		               uint64_t current_value=0;
		for (uint64_t i=0; i<anf_db.size(); i++) { // container for (containers for bits in values vector
			current_value = 0;
			for (uint64_t j=0; j<anf_db[i].size(); j++) { // anf_db[j] - container for bit number j in values vector
					for (int k=0; k<63; k++) {
						uint32_t temp = this->_values[current_value]
						                set_bit_32(temp, get_bit_32(anf_db[i][j],k),j);
						this->_values[current_value++] = temp;
					}
				}
			}
	}

	ttable::ttable (vector<bvect32>) {

	}

	void ttable::set(bvect32 vect, uint32_t index) {
		this->_values[index] = vect;
	}

	bvect ttable::get_value (uint32_t index) {
		return this->_values[index];
	}

	uint64_t ttable::get_length() {
		return this->_length;
	}

=======
namespace bf //FIXME release NM functions!!!
{
    int ttable::is_NM_function () {
    	
	}

    /*ttable::ttable(GF *field)
    {
        this->_length = power2(static_cast<uint64_t>(field->get_order()));
        this->_values.resize(static_cast<size_t>(this->_length));
    } */

    ttable::ttable(polynom &p)//FIXME release NM functions!!!
    {
        vector<bvect32> coeff;
        const uint32_t polynom_length = p.get_length(); // aka x-quanity aka coeff-quanity
        for (bvect32 i = 0; i < polynom_length; i++)
            coeff.push_back(p.get_coeff(i));
        _values.resize(polynom_length);

        for (uint32_t x = 0; x < polynom_length; x++) // Cycle by vectors
            for (uint32_t i = 0; i < polynom_length; i++) // Cycle by coeffs
                _values[x] += field->multiply(coeff[i], field->power(x, i));
    }

    ttable::ttable(vector< vector<bvect64> > anf_db) // 
    {
        vector<bvect32> values;
        values.resize (power2(field->get_order());
        for (uint64_t i=0; i < values.size(); i++)
        	values[i] = 0;
        uint64_t current_value=0;
		for (uint64_t i=0; i<anf_db.size(); i++) { // container for (containers for bits in values vector
        	current_value = 0;
			for (uint64_t j=0; j<anf_db[i].size(); j++) { // anf_db[j] - container for bit number j in values vector
				for (int k=0; k<63; k++) {
        			uint32_t temp = this->_values[current_value] 
					set_bit_32(temp, get_bit_32(anf_db[i][j],k),j);
					this->_values[current_value++] = temp; 	
				}
			}
		}
    }
    
    ttable::ttable (GF *field, vector<bvect32>) {
    		
	} 

    GF *ttable::get_field()
    {
        return _field;
    }

    void ttable::set(bvect32 vect, uint32_t index)
    {
        this->_values[index] = vect;
    }

    bvect ttable::get_value (uint32_t index)
    {
        return this->_values[index];
    }

    uint64_t ttable::get_length()
    {
        return this->_length;
    }

>>>>>>> master
}
