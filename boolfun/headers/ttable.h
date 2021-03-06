#pragma once

#include <vector>
#include "polynom.h"

// Max table length 2^n (n <= 32)
// Max var quanity n (n <= 32)

namespace bf
{
    class polynom;

    class ttable
    {
    public:

        ttable(polynom &p);
        ttable(std::vector<bvect32> values, unsigned int n);

        void set(bvect32 vect, uint32_t index);

        bvect32 get_value(uint32_t index);
        std::vector<bvect32> get_all();
        uint64_t get_length();
        GF *get_field ();

        unsigned int get_output_length();
        unsigned int get_input_length();
        int is_NM_function();

    private:
        std::vector<bvect32> _values;
        uint64_t _length;
        unsigned int _n;
        unsigned int _m;
        GF *_field;

    };
}
