#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "bitslib.h"
#include "GF.h"

// Max polynom length 2^n (n <= 32)
// Max var quanity n (n <= 32)

namespace bf
{
    class ttable;

    class polynom
    { // over field type

    public:
        polynom(GF *field);
        polynom(ttable &t, GF *field);
        void set_coeff(uint32_t index, bvect32 coeff);
        bvect32 get_coeff(uint32_t index);
        uint32_t get_length();
        GF *get_field();
        bool set_from_string(const std::string &s);

    private:
        std::vector<bvect32> _coeff;
        uint32_t _length;
        GF *_field;

    };

}
