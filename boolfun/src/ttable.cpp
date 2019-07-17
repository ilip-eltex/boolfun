#include "bitslib.h"
#include "ttable.h"

using namespace std;

namespace bf
{

    ttable::ttable(polynom &p, unsigned int n)
    {
        auto field = p.get_field();
        this->_n = p.get_input_length();
        
        vector<bvect32> coeff;
        
		const uint32_t polynom_length = p.get_length(); // aka x-quanity aka coeff-quanity
        for (bvect32 i = 0; i < polynom_length; i++)
            coeff.push_back(p.get_coeff(i));
            
        _values.resize(polynom_length);
		
        for (uint32_t x = 0; x < polynom_length; x++) // Cycle by vectors
            for (uint32_t i = 0; i < polynom_length; i++) // Cycle by coeffs
                _values[x] ^= field->multiply(coeff[i], field->power(x, i));
    }


    ttable::ttable(vector<bvect32> values, unsigned int n)
    {
    	long long int max=-1;
        for (uint64_t i=0; i<values.size(); i++) {
        	if (values[i] > max)
        		max = values[i];
		}
		this->_m = deg_32(max) + 1; 
		this->_values = values;
		this->_n = n; 
    }

    void ttable::set(bvect32 vect, uint32_t index)
    {
        this->_values[index] = vect;
    }

    bvect32 ttable::get_value(uint32_t index)
    {
        return this->_values[index];
    }

    vector<bvect32> ttable::get_all()
    {
        return (this->_values);
    }

    uint64_t ttable::get_length()
    {
        return this->_length;
    }

    int ttable::is_NM_function()
    {
        return (this->_m > 1);
    }

    unsigned int ttable::get_input_length()
    {
        return (this->_n);
    }

    unsigned int ttable::get_output_length()
    {
        return (this->_m);
    }
    
}

