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
        if (table.is_NM_function())
            throw std::invalid_argument("Unsupported NM functions!!!");
    }

    //diff равномерность

    unsigned int get_function_weight(ttable &table)
    {
        check_is_boolean_function(table);

        uint64_t weight = 0;
        for (bvect32 i = 0; i < table.get_length(); ++i)
            weight += table.get_value(i);

        return weight;
    }

    bvect32 get_trace(GF &field)
    {
        bvect32 sum0 = 0;

        for (bvect32 i = 0; i < field.get_order(); ++i)
            field.sum(sum0, field.power((bvect32) 4, i));

        return sum0;
    }

    int is_balanced(ttable &table)
    {
        if (!table.is_NM_function())
        {
            if (get_function_weight(table) == table.get_length() / 2)
                return 1;
            else
                return 0;
        } else
        {
            uint64_t weight = 0;
            for (unsigned int j = 0; j < table.get_output_length(); ++j)
            {
                for (bvect32 i = 0; i < table.get_length(); ++i)
                    weight += (table.get_value(i) >> j) & (unsigned) 1;

                if (weight != table.get_length() / 2)
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

        for (int i = 0; i < ivec.size(); ++i)
        {
            ivec[i].resize(a.get_length());

            for (int l = 0; l < ivec[i].size(); ++l)
            {
                if (!a.get_value(l))
                    ivec[i][l] = 1;
                else
                    ivec[i][l] = -1;
            }

            for (int k = ivec[i].size() / 2; k >= 1; k /= 2)
            {
                blocks *= 2;
                for (int u = 0; u < blocks - 1; u += 2)
                    for (int j = 0; j < k; ++j)
                    {
                        tmp = ivec[i][u * k + j];
                        ivec[i][u * k + j] += ivec[i][(u + 1) * k + j];
                        ivec[i][(u + 1) * k + j] = tmp - ivec[i][(u + 1) * k + j];
                    }
            }
            blocks = 1;
        }

        return ivec;
    }

    ttable &get_derivative(ttable &a, bvect32 direction)
    {
        ttable &b = a;

        for (bvect32 i = 0; i < b.get_length(); ++i)
            b.set(b.get_value(i) ^ b.get_value(i ^ direction), i);//f(x) ^ f(x ^ dir)

        return b;
    }

    void get_GAC_characteristics(ttable &a, unsigned long *sigma, unsigned int *delta)
    {
        check_is_boolean_function(a);

        if (!sigma && !delta)
            return;

        vector<vector<int>> spector(get_walsh_hadamard_spec(a));

        int blocks = 1;
        int tmp;

        for (int i = 0; i < spector.size(); ++i)
        {
            for (int l = 0; l < spector[i].size(); ++l)
                spector[i][l] *= spector[i][l];

            for (int k = spector[i].size() / 2; k >= 1; k /= 2)
            {
                blocks *= 2;
                for (int u = 0; u < blocks - 1; u += 2)
                    for (int j = 0; j < k; ++j)
                    {
                        tmp = spector[i][u * k + j];
                        spector[i][u * k + j] += spector[i][(u + 1) * k + j];
                        spector[i][(u + 1) * k + j] = tmp - spector[i][(u + 1) * k + j];
                    }
            }

            for (int l = 0; l < spector[i].size(); ++l)
                spector[i][l] /= a.get_length();

            if (sigma)
                for (int l = 0; l < spector[i].size(); ++l)
                    (*sigma) += spector[i][l] * spector[i][l];

            if (delta)
            {
                tmp = spector[i][0];

                for (int l = 0; l < spector[i].size(); ++l)
                    if (tmp < spector[i][l])
                        tmp = spector[i][l];

                if ((*delta) < tmp)
                    (*delta) = tmp;
            }

            blocks = 1;
        }
    }

    int get_vector_permutation(ttable &a, int no_ones, int no_zeroes, unsigned int accum)
    {
        if (no_ones == 0)
        {
            for (int i = 0; i < no_zeroes; i++)
                accum <<= (unsigned) 1;

            return is_balanced(get_derivative(a, accum));
        } else if (no_zeroes == 0)
        {
            for (int j = 0; j < no_ones; j++)
            {
                accum <<= (unsigned) 1;
                accum |= (unsigned) 1;
            }

            return is_balanced(get_derivative(a, accum));
        }

        return get_vector_permutation(a, no_ones - 1, no_zeroes, (accum << (unsigned) 1) | (unsigned) 1) &&
               get_vector_permutation(a, no_ones, no_zeroes - 1, accum << (unsigned) 1);
    }

    int is_PC(ttable &a, int k)
    {
        for (int i = 1; i <= k; ++i)
            if (!get_vector_permutation(a, i, a.get_field()->get_order() - i, 0))
                return 0;

        return 1;
    }

    int is_SAC(ttable &a)
    {
        for (unsigned int i = 0; i < a.get_field()->get_order(); ++i)
            if (!is_balanced(get_derivative(a, (unsigned) 1 << i)))
                return 0;
        return 1;
    }

    int get_index_nonlinearity(ttable &a)
    {
        vector<vector<int>> b = get_walsh_hadamard_spec(a);
        int tmp = abs(b[0][0]);

        for (int j = 0; j < b.size(); ++j)
            for (int i = 0; i < b[j].size(); ++i)
                if (tmp < abs(b[j][i]))
                    tmp = abs(b[j][i]);

        return (((unsigned int) 1 << (a.get_field()->get_order())) - tmp) / 2;
    }

    unsigned int get_hemming_distance(ttable &a, ttable &b)
    {
        unsigned int dist = 0;
        for (bvect32 i = 0; i < a.get_length(); ++i)
            dist += (a.get_value(i) != b.get_value(i) ? 1 : 0);

        return dist;
    }
}