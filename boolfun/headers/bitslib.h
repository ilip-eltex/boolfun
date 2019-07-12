#pragma once
#include <GF.h>

namespace bf
{
    unsigned int get_bit_32(bvect32, unsigned int);
    void set_bit1_32(bvect32&, unsigned int);
    void set_bit0_32(bvect32&, unsigned int);
    void set_bit_32(bvect32&, unsigned int, unsigned int);
    unsigned int get_weight_32(bvect32);
    bool is_odd_32(bvect32);
    bvect32 scalar_product(bvect32, bvect32);
    unsigned char deg(bvect32);
    unsigned int get_bit_64(bvect64, unsigned int);
    void set_bit1_64(bvect64&, unsigned int);
    void set_bit0_64(bvect64&, unsigned int);
    void set_bit_64(bvect64&, unsigned int, unsigned int);
    unsigned int get_weight_64(bvect64);
    bool is_odd_64(bvect64);
    bvect64 scalar_product(bvect64, bvect64);
    uint32_t power2(uint32_t);
    unsigned char deg(bvect64);
}

