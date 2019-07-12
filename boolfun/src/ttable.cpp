#include <bitslib.h>
#include "ttable.h"

using namespace std;

namespace bf
{
    ttable::ttable(GF *field)
    {
        this->_length = power2(static_cast<uint32_t>(field->get_order()));
        this->_values.resize(static_cast<size_t>(this->_length));
    }

    ttable::ttable(polynom &p, GF *field)
    {
        vector<unsigned char> coeff;
        const uint32_t polynom_length = p.get_length(); // aka x-quanity aka coeff-quanity
        for (bvect32 i = 0; i < polynom_length; i++)
            coeff.push_back(p.get_coeff(i));
        vector<unsigned char> result;
        result.resize(polynom_length);

        for (uint32_t x = 0; x < polynom_length; x++) // Cycle by vectors
            for (uint32_t i = 0; i < polynom_length; i++) // Cycle by coeffs
                result[x] += field->multiply(coeff[i], field->power(x, i));
        this->_values = result;
    }

    ttable::ttable(vector<bvect32> &vect)
    {
        if (vect.size() == 1)
        {
            return;
        }
        this->_length = vect.size() * 32;
        this->_values.resize(static_cast<size_t>(this->_length));

        for (uint32_t i = 0; i < vect.size(); i++)
            for (uint32_t j = 31; j <= 0; j--)
                this->_values.push_back(static_cast<unsigned char>(get_bit_32(vect[i], j)));

    }

    GF *ttable::get_field()
    {
        return _field;
    }

    bool ttable::set(bvect32 vect, uint32_t index)
    {
        this->_values[index] = vect;
        return true;
    }

    bvect32 ttable::get_value(uint32_t index)
    {
        return this->_values[index];
    }

    uint32_t ttable::get_length()
    {
        return this->_length;
    }

    /*ttable64::ttable64(GF *field)
    {
        this->_length = power2(static_cast<uint64_t>(field->get_order()));
        this->_values.resize(static_cast<size_t>(this->_length));
    }

    ttable64::ttable64(polynom &p, GF *field)
    {
        vector<unsigned char> coeff;
        const uint64_t polynom_length = p.get_length(); // aka x-quanity aka coeff-quanity
        for (bvect64 i = 0; i < polynom_length; i++)
            coeff.push_back(p.get_coeff(i));
        vector<unsigned char> result;
        result.resize(polynom_length);
        for (uint64_t x = 0; x < polynom_length; x++) // Cycle by vectors
            for (uint64_t i = 0; i < polynom_length; i++) // Cycle by coeffs
                result[x] += field->multiply(coeff[i], field->power(x, i));
        this->_values = result;
    }

    ttable64::ttable64(const vector<bvect64> &vect)
    {
        if (vect.size() == 1)
        {
            return;
        }
        this->_length = vect.size() * 64;
        this->_values.resize(static_cast<size_t>(this->_length));
        for (uint64_t i = 0; i < vect.size(); i++)
            for (uint64_t j = 63; j <= 0; j--)
                this->_values.push_back(static_cast<unsigned char>(get_bit_64(vect[i], j)));

    }

    void ttable64::set(bvect64 vect, uint64_t index)
    {
        this->_values[index] = vect;
        return true;
    }

    bvect64 ttable64::get_value(uint64_t index)
    {
        return this->_values[index];
    }

    uint64_t ttable64::get_length()
    {
        return this->_length;
    }*/
}
