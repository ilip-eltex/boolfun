#pragma once

#include "GF.h"
#include "ttable.h"
#include <vector>
#include <cmath>

using namespace std;

namespace bf
{
    unsigned int function_weight(ttable& table)
    {
        uint64_t weight = 0;
        for (bvect32 i = 0; i < table.get_length(); ++i)
            weight += table.get_value(i);

        return weight;
    }

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

    vector<int>  walsh_hadamard_spec(ttable& a)
    {
        vector<int> ivec(a.get_length());

        for(int i = 0; i < ivec.size(); ++i)
        {
            if(!a.get_value(i))
                ivec[i] = 1;
            else
                ivec[i] = -1;
        }

        int blocks = 1;
        int tmp;

        for (int k = ivec.size() / 2; k >= 1; k /= 2)
        {
            blocks *= 2;
            for (int i = 0; i < blocks - 1; i += 2)
                for (int j = 0; j < k; ++j)
                {
                    tmp = ivec[i*k + j];
                    ivec[i*k + j] += ivec[(i+1)*k + j];
                    ivec[(i+1)*k + j] = tmp - ivec[(i+1)*k + j];
                }
        }
        return ivec;
    }

    int index_nonlinearity(ttable& a)
    {
        vector<int> b = walsh_hadamard_spec(a);

        int tmp = abs(b[0]);
        for(int i = 0; i < b.size(); ++i)
            if(tmp < abs(b[i]))
                tmp = abs(b[i]);

        return (((unsigned int)1<<(a.get_field()->get_order())) - tmp) / 2;
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

    ttable& get_derivative(ttable& a, bvect32 direction)
    {
        ttable& b = a;

        for (bvect32 i = 0; i < b.get_length(); ++i)
            b.set(b.get_value(i) ^ b.get_value(i ^ direction), i);//f(x) ^ f(x ^ dir)

        return b;
    }
}
