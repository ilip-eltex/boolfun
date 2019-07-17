#define bvect32 uint32_t
#define bvect64 uint64_t
#include <cstdint>

namespace bf
{
/////////////// for bvect32 ///////////////////////////////////////////////

    unsigned int get_bit_32(bvect32 x, unsigned int index)
    {
        return (x >> index) & (unsigned) 1;
    }

    void set_bit1_32(bvect32 &x, unsigned int index)
    {
        x |= ((unsigned) 1 << index);
    }

    void set_bit0_32(bvect32 &x, unsigned int index)
    {
        x &= ~((unsigned) 1 << index);
    }

    void set_bit_32(bvect32 &x, unsigned int value, unsigned int index)
    {
        if (value)
            x |= (unsigned) 1 << index;
        else
            x &= ~((unsigned) 1 << index);
    }

    unsigned int get_weight_32(bvect32 x)
    {
        bvect32 result = 0;
        while (x != 0)
        {
            x &= x - 1;
            result++;
        }
        return result;
    }

    bool is_odd_32(bvect32 x)
    {
        x ^= (x >> (unsigned) 16);
        x ^= (x >> (unsigned) 8);
        x ^= (x >> (unsigned) 4);
        x ^= (x >> (unsigned) 2);
        x ^= (x >> (unsigned) 1);
        return (x & (unsigned) 1);
    }

    bvect32 scalar_product_32(bvect32 a, bvect32 b)
    {
        return is_odd_32(a & b);
    }

    unsigned char deg_32(bvect32 a)
    {
        if (a == 0)
            return 0;
		for (int i = 31; i >= 0; --i)
            if ((a >> (unsigned) i) & (unsigned) 1)
                return (unsigned char) i;
        return 0;
    }

//////////////// for bvect64 ///////////////////////////////////////////////

    unsigned int get_bit_64(bvect64 x, unsigned int index)
    {
        return (x >> index) & (unsigned) 1;
    }

    void set_bit1_64(bvect64 &x, unsigned int index)
    {
        x |= (static_cast<bvect64>(1) << index);
    }

    void set_bit0_64(bvect64 &x, unsigned int index)
    {
        x &= ~(static_cast<bvect64>(1) << index);
    }

    void set_bit_64(bvect64 &x, unsigned int value, unsigned int index)
    {
        if (value)
            x |= static_cast<bvect64>(1) << index;
        else
            x &= ~(static_cast<bvect64>(1) << index);
    }

    unsigned int get_weight_64(bvect64 x)
    {
        bvect32 result = 0;
        while (x != 0)
        {
            x &= x - 1;
            result++;
        }
        return result;
    }
	bool is_odd_64(bvect64 x)
    {
        x ^= (x >> (unsigned) 32);
        x ^= (x >> (unsigned) 16);
        x ^= (x >> (unsigned) 8);
        x ^= (x >> (unsigned) 4);
        x ^= (x >> (unsigned) 2);
        x ^= (x >> (unsigned) 1);
        return (x & (unsigned) 1);
    }
    bvect64 scalar_product_64(bvect64 a, bvect64 b)
    {
        return is_odd_64(a & b);
    }

    

    uint32_t power2(uint32_t y)
    {
        return (static_cast<uint32_t>(1) << y);
    }

    unsigned char deg_64(bvect64 a)
    {
        if (a == 0)
            return 0;
		for (int i = 63; i >= 0; --i)
            if ((a >> (unsigned) i) & (unsigned) 1)
                return (unsigned char) i;
        return 0;
    }

}
