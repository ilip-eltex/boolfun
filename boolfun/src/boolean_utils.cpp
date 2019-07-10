#include "boolean_utils.h"
#include <cmath>

using namespace bf;

bvect32 trace(GF *field)
{
    bvect32 sum0 = 0;

    for (bvect32 i = 0; i < field->get_order(); ++i)
        field->sum(sum0, field->power((bvect32) 4, i));

    return sum0;
}

unsigned int function_weight(ttable64& table)
{
    uint64_t weight = 0;
    for (bvect64 i = 0; i < table.get_length(); ++i)
        weight += table.get_value(i);

    return weight;
}

int is_balanced(ttable64& table)
{
    if(function_weight(table) == table.get_length() / 2)
        return 1;
    else
        return 0;
}

int is_balanced(ttable& table)
{
    if (function_weight(table) == table.get_length() / 2)
        return 1;
    else
        return 0;
}



unsigned int function_weight(ttable& table)
{
    uint64_t weight = 0;
    for (bvect32 i = 0; i < table.get_length(); ++i)
        weight += table.get_value(i);

    return weight;
}

unsigned int hemming_distance(ttable64& a, ttable64& b)
{
    unsigned int dist = 0;
    for (bvect64 i = 0; i < a.get_length(); ++i)
        dist += a.get_value(i) ^ b.get_value(i);

    return dist;
}

unsigned int hemming_distance(ttable& a, ttable& b)
{
    unsigned int dist = 0;
    for (bvect32 i = 0; i < a.get_length(); ++i)
        dist += a.get_value(i) ^ b.get_value(i);

    return dist;
}

int scalar_product(bvect64 a, bvect64 b)
{
    return is_odd_64(a & b);
}

int scalar_product(bvect32 a, bvect32 b)
{
    return is_odd_32(a & b);
}

ttable*   get_derivative(ttable& a, bvect32 direction)
{

}

ttable64* get_derivative(ttable64& a, bvect32 direction)
{

}