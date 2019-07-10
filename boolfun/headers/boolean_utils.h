#ifndef BOOLFUN_EXE_BOOLEAN_UTILS_H
#define BOOLFUN_EXE_BOOLEAN_UTILS_H

#include "GF.h"
#include "ttable.h"

namespace bf
{
    bvect32 trace(GF* field);
    ttable*   get_derivative(ttable& a, bvect32 direction);

    unsigned int function_weight(ttable& table);
    unsigned int hemming_distance(ttable& a, ttable& b);
    int scalar_product(bvect32 a, bvect32 b);
    int walsh_hadamard_coef(ttable& a, bvect32 b);
    int walsh_hadamard_coef(ttable& a, bvect32 b);
    bvect32 walsh_hadamard_sup(ttable& a);// возвращает вектор, у которого максимальный коэффициент уолша адамара

    int is_balanced(ttable& table);
}

#endif
