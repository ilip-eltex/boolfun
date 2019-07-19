#include <iostream>

#include "boolean_utils.h"
#include "bitslib.h"
#include "GF.h"
#include "GF_simple.h"
#include "ANF.h"
#include "linear.h"
#include <cstring>

using namespace std;

namespace bf
{
    void full_analysis(ttable &table)
    {
        cout << "Check information..." << endl <<
                "Is vector function: " + (string)(table.is_NM_function() ? "yes" : "no") << endl <<
                "Argument vector size: " + std::to_string(table.get_input_length()) << endl <<
                "Result vector size: " + std::to_string(table.get_output_length()) << endl <<
                "Function weight: " + (string)(!table.is_NM_function() ? std::to_string(get_function_weight(table)) : "unsupported for vector functions!") << endl <<
                "Is balanced: " + (string)(is_balanced(table) ? "yes" : "no") << endl <<
                "Index of nonlinearity: " + std::to_string(get_index_nonlinearity(table)) << endl <<
                "Correlation immunity: " + std::to_string(get_correlation_immunity(table)) << endl <<
                "Satisfies the SAC: " + (string)(is_SAC(table) ? "yes" : "no") << endl <<
                "Is linear: " + (string)(is_affine(table) ? "yes" : "no") << endl <<
                "Is affine: " + (string)(is_linear(table) ? "yes" : "no") << endl <<
                "Is bent-function: " + (string)(is_bent_function(table) ? "yes" : "no") << endl;
        unsigned int delta = 0;
        unsigned long sigma = 0;
        get_GAC_characteristics(table, &sigma, &delta);
        cout << "The GAC characteristics: sigma - " + std::to_string(sigma) + (string)(", delta - ") + std::to_string(delta) << endl <<
                "ANF of this function: ";
        ANF anf;
        anf.getANF(table);
        cout << anf << endl;
        cout << "The degree of the function: " + std::to_string(anf.deg()) << endl;
    }

    int is_bent_function(ttable &table)
    {
        if(table.get_input_length() & (unsigned)1)
            return 0;

        string anf_linear;
        for(int i = 1; i < table.get_input_length() + 1; ++i)
            anf_linear += "x" + std::to_string(i) + (string)(i == table.get_input_length() ? "" : "+");

        ANF anf;
        anf.parse_ANF(anf_linear);
        auto b = anf.getFunction();

        return get_hemming_distance(table, b) == (((unsigned)1 << (table.get_input_length() - 1)) - ((unsigned)1 << ((table.get_input_length() / 2) - 1)));
    }

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
            for(uint64_t a = 0; a < field.get_order(); a++){
            temp ^= field.power(j, ((unsigned) 1 << a));
            }
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

    unsigned int get_correlation_immunity(ttable &table)
    {
        check_is_boolean_function(table);

        unsigned int corr = table.get_input_length();
        vector<vector<int>> spec = get_walsh_hadamard_spec(table);

        for(unsigned int i = 1; i < spec[0].size(); ++i)
            if(spec[0][i] && get_weight_32(i) - 1 < corr)
                corr = get_weight_32(i) - 1;

        return corr;
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
                        ivec[i][u * k + j] += ivec[i][(u + 1) * k + j];
                        ivec[i][(u + 1) * k + j] = tmp - ivec[i][(u + 1) * k + j];
                    }
            }
            blocks = 1;
        }

        return ivec;
    }

    int is_differentially_uniform(ttable table, unsigned char delta)
    {
        vector<uint32_t> array((unsigned)1 << table.get_output_length(), 0);
        vector<uint32_t> array1((unsigned)1 << table.get_input_length(), 0);

        uint32_t max;
        for(int a = 1; a < (unsigned)1 << table.get_input_length(); ++a)
        {
            ttable der = get_derivative(table, a);

            for(int x = 0; x < (unsigned) 1 << table.get_input_length(); ++x)
                array[der.get_value(x)]++;

            max = array[0];
            for(int i = 1; i < array.size(); ++i)
                if(array[i] > max)
                    max = array[i];

            array1[a] = max;
            memset(array.data(), 0, ((unsigned)1 << table.get_output_length()) * sizeof(bvect32));
        }
        max = array1[0];
        for(int i = 1; i < array1.size(); ++i)
            if(array1[i] > max)
                max = array1[i];

        return delta >= max;
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