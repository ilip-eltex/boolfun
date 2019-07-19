#pragma once

#include "GF.h"
#include "ttable.h"
#include <vector>
#include <cmath>

using namespace std;

namespace bf
{
    unsigned int get_function_weight(ttable&);
    ttable get_trace(GF&);
    int is_balanced(ttable&);
    vector<vector<int>> get_walsh_hadamard_spec(ttable&);
    ttable get_derivative(ttable&, bvect32);
    void get_GAC_characteristics(ttable&, unsigned long*, unsigned int*);
    int is_PC(ttable&, int);
    int is_SAC(ttable&);
    int get_index_nonlinearity(ttable&);
    unsigned int get_hemming_distance(ttable&, ttable&);
    int is_differentially_uniform(ttable, unsigned char);
    unsigned int get_correlation_immunity(ttable &table);
    void full_analysis(ttable &table);
    int is_bent_function(ttable &table);
}