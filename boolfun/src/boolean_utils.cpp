#include <iostream>

#include "boolean_utils.h"
#include "bitslib.h"
#include "GF.h"
#include "GF_simple.h"

using namespace std;

namespace bf
{
    void check_is_boolean_function(ttable &table)
    {
        if(table.is_NM_function())
            throw std::invalid_argument("Unsupported NM functions!!!");
    }

    //diff равномерность

    unsigned int get_function_weight(ttable &table)
    {
        check_is_boolean_function(table);

        uint64_t weight = 0;
        for(bvect32 i = 0; i < table.get_length(); ++i)
            weight += table.get_value(i);

        return weight;
    }

    ttable get_trace(GF &field)
    {
        vector<bvect32> values((unsigned) 1 << field.get_order(), 0);

        bvect32 temp;
        for(uint64_t j = 1; j < values.size(); j++)
        {
            temp = 0;
            for(uint64_t a = 0; a < field.get_order(); a++)
                temp ^= field.power(j, (unsigned) 1 << a);

            values[j] = temp;
        }
        ttable table(values, field.get_order());

        return table;
    }

    int is_balanced(ttable &table)
    {
        if(!table.is_NM_function())
        {
            if(get_function_weight(table) == table.get_length() / 2)
                return 1;
            else
                return 0;
        } else
        {
            uint64_t weight = 0;
            for(unsigned int j = 0; j < table.get_output_length(); ++j)
            {
                for(bvect32 i = 0; i < table.get_length(); ++i)
                    weight += (table.get_value(i) >> j) & (unsigned) 1;

                if(weight != table.get_length() / 2)
                    return 0;

                weight = 0;
            }
            return 1;
        }
    }

    vector<vector<int>> get_walsh_hadamard_spec(ttable &a)
    {
        int blocks = 1;
        int tmp;

        vector<vector<int>> ivec(a.get_output_length());

        for(int i = 0;i < ivec.size();i++)
        {
            ivec[i].resize(a.get_length());

            for(int l = 0; l < ivec[i].size(); ++l)
            {
                if(!a.get_value(l))
                    ivec[i][l] = 1;
                else
                    ivec[i][l] = -1;
            }

            for(int k = ivec[i].size() / 2; k >= 1; k /= 2)
            {
                blocks *= 2;
                for(int u = 0; u < blocks - 1; u += 2)
                    for(int j = 0; j < k; ++j)
                    {
                        tmp = ivec[i][u * k + j];
                        ivec[i][u * k + j] += ivec[i][(u + 1) * k + j];//FIXME
                        ivec[i][(u + 1) * k + j] = tmp - ivec[i][(u + 1) * k + j];
                    }
            }
            blocks = 1;
        }

        return ivec;
    }

    ttable get_derivative(ttable &a, bvect32 direction)
    {
        auto b = ttable(a);

        for(bvect32 i = 0; i < b.get_length(); ++i)
            b.set(a.get_value(i) ^ a.get_value(i ^ direction), i);//f(x) ^ f(x ^ dir)

        return b;
    }

    void get_GAC_characteristics(ttable &a, unsigned long *sigma, unsigned int *delta)
    {
        if(!sigma && !delta)
            return;

        vector<vector<int>> spector(get_walsh_hadamard_spec(a));

        int blocks = 1;
        int tmp;

        for(int e = 0;e < spector.size();e++)
        {
            for(int o = 0;o < spector[e].size();o++)
                spector[e][o] *= spector[e][o];

            for(int k = spector[e].size() / 2; k >= 1; k /= 2)
            {
                blocks *= 2;
                for(int u = 0; u < blocks - 1; u += 2)
                    for(int j = 0; j < k; ++j)
                    {
                        tmp = spector[e][u * k + j];
                        spector[e][u * k + j] += spector[e][(u + 1) * k + j];
                        spector[e][(u + 1) * k + j] = tmp - spector[e][(u + 1) * k + j];
                    }
            }

            for(int o = 0;o < spector[e].size();o++)
                spector[e][o] /= a.get_length();

            if(sigma)
                for(int o = 0;o < spector[e].size();o++)
                    (*sigma) += spector[e][o] * spector[e][o];

            if(delta)
            {
                tmp = spector[e][1];

                for(int i = 2;i < spector[e].size();i++)
                    if(tmp < spector[e][i])
                        tmp = spector[e][i];

                if((*delta) < tmp)
                    (*delta) = tmp;
            }

            blocks = 1;
        }
    }

    int get_vector_permutation(ttable &a, int no_ones, int no_zeroes, unsigned int accum)
    {
        if(no_ones == 0)
        {
            for(int i = 0; i < no_zeroes; i++)
                accum <<= (unsigned) 1;

            auto table = get_derivative(a, accum);
            return is_balanced(table);
        } else if(no_zeroes == 0)
        {
            for(int j = 0; j < no_ones; j++)
            {
                accum <<= (unsigned) 1;
                accum |= (unsigned) 1;
            }
            auto table = get_derivative(a, accum);
            return is_balanced(table);
        }

        return get_vector_permutation(a, no_ones - 1, no_zeroes, (accum << (unsigned) 1) | (unsigned) 1) &&
               get_vector_permutation(a, no_ones, no_zeroes - 1, accum << (unsigned) 1);
    }

    int is_PC(ttable &a, int k)
    {
        for(int i = 1; i <= k; ++i)
            if(!get_vector_permutation(a, i, a.get_input_length() - i, 0))
                return 0;

        return 1;
    }

    int is_SAC(ttable &a)
    {
        for(unsigned int i = 0; i < a.get_input_length(); ++i)
        {
            auto table = get_derivative(a, (unsigned) 1 << i);
            if(!is_balanced(table))
                return 0;
        }

        return 1;
    }

    int get_index_nonlinearity(ttable &a)
    {
        vector<vector<int>> b = get_walsh_hadamard_spec(a);
        int tmp = abs(b[0][0]);

        for(auto el : b)
            for(auto el1 : el)
                if(tmp < abs(el1))
                    tmp = abs(el1);

        return (((unsigned) 1 << (unsigned) (a.get_input_length())) - tmp) / 2;
    }

    unsigned int get_hemming_distance(ttable &a, ttable &b)
    {
        unsigned int dist = 0;
        for(bvect32 i = 0; i < a.get_length(); ++i)
            dist += (a.get_value(i) != b.get_value(i) ? 1 : 0);

        return dist;
    }
}