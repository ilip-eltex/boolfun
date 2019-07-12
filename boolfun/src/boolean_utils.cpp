#include "boolean_utils.h"

namespace bf
{
    unsigned int get_function_weight(ttable &table)
    {
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
        if (get_function_weight(table) == table.get_length() / 2)
            return 1;
        else
            return 0;
    }

    vector<int> get_walsh_hadamard_spec(ttable &a)
    {
        vector<int> ivec(a.get_length());

        for (int i = 0; i < ivec.size(); ++i)
        {
            if (!a.get_value(i))
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
                    tmp = ivec[i * k + j];
                    ivec[i * k + j] += ivec[(i + 1) * k + j];
                    ivec[(i + 1) * k + j] = tmp - ivec[(i + 1) * k + j];
                }
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

    void get_GAC_characteristics(ttable& a, unsigned long* sigma, unsigned int* delta)
    {
        if(!sigma && !delta)
            return;

        vector<int> spector(get_walsh_hadamard_spec(a));

        for(int l = 0; l < spector.size(); ++l)
            spector[l] *= spector[l];

        int blocks = 1;
        int tmp;

        for (int k = spector.size() / 2; k >= 1; k /= 2)
        {
            blocks *= 2;
            for (int i = 0; i < blocks - 1; i += 2)
                for (int j = 0; j < k; ++j)
                {
                    tmp = spector[i * k + j];
                    spector[i * k + j] += spector[(i + 1) * k + j];
                    spector[(i + 1) * k + j] = tmp - spector[(i + 1) * k + j];
                }
        }

        for(int l = 0; l < spector.size(); ++l)
            spector[l] /= a.get_length();

        if(sigma)
            for(int l = 0; l < spector.size(); ++l)
                (*sigma) += spector[l] * spector[l];

        if(delta)
        {
            tmp = spector[0];

            for(int l = 0; l < spector.size(); ++l)
                if(tmp < spector[l])
                    tmp = spector[l];

            (*delta) = tmp;
        }
    }

    int get_vector_permutation(ttable &a, int no_ones, int no_zeroes, unsigned int accum)
    {
        if(no_ones == 0)
        {
            for (int i = 0; i < no_zeroes; i++)
                accum <<= (unsigned)1;

            return is_balanced(get_derivative(a, accum));
        } else if(no_zeroes == 0)
        {
            for (int j = 0; j < no_ones; j++)
            {
                accum <<= (unsigned)1;
                accum |=  (unsigned)1;
            }

            return is_balanced(get_derivative(a, accum));
        }

        return get_vector_permutation(a, no_ones - 1, no_zeroes, (accum << (unsigned) 1) | (unsigned) 1) &&
               get_vector_permutation(a, no_ones, no_zeroes - 1, accum << (unsigned) 1);
    }

    int is_PC(ttable &a, int k)
    {
        for (int i = 1; i <= k; ++i)
            if(!get_vector_permutation(a, i, a.get_field()->get_order() - i, 0))
                return 0;

        return 1;
    }

    int is_SAC(ttable &a)
    {
        for (unsigned int i = 0; i < a.get_field()->get_order(); ++i)
            if (!is_balanced(get_derivative(a, (unsigned)1 << i)))
                return 0;
        return 1;
    }

    int get_index_nonlinearity(ttable &a)
    {
        vector<int> b = get_walsh_hadamard_spec(a);

        int tmp = abs(b[0]);
        for (int i = 0; i < b.size(); ++i)
            if (tmp < abs(b[i]))
                tmp = abs(b[i]);

        return (((unsigned int) 1 << (a.get_field()->get_order())) - tmp) / 2;
    }

    unsigned int get_hemming_distance(ttable &a, ttable &b)
    {
        unsigned int dist = 0;
        for (bvect32 i = 0; i < a.get_length(); ++i)
            dist += a.get_value(i) ^ b.get_value(i);

        return dist;
    }
}