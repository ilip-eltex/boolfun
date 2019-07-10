#include "ANF.h"
#include <vector>
#include "bitslib.h"
#include <cmath>
#include <iostream>

using namespace bf;

uint64_t table_length;

void ANF::getANF(ttable& table)
{
    table_length = table.get_length();

    vector<uint64_t> ivec(table_length <= sizeof(uint64_t) ? 1 : table_length / sizeof(uint64_t), 0);
    uint64_t count = 0;

    for(int i = 0; i < ivec.size(); ++i)
    {
        for (int j = 0; j < sizeof(uint64_t) * 8; ++j)
        {
            ivec[i] |= table.get_value(count++);
            ivec[i] <<= 1;
        }
    }
    uint32_t blocks = 1;
    elements.resize((unsigned long long)pow(2, table_length), 0);

    if(ivec.size() == 1)
    {
        for (int k = table_length / 2; k >= 1; k /= 2)
        {
            blocks *= 2;
            for (int i = 0; i < blocks - 1; i += 2)
                for (int j = 0; j < k; ++j)
                    set_bit_64(ivec[0], get_bit_64(ivec[0], i*k + j) ^ get_bit_64(ivec[0], (i+1)*k + j), i*k + j);
        }

        for (int l = 0; l < table_length; ++l)
            if(ivec[0] >> (table_length - 1 - l))
                elements[l] = l;
    }
    else
    {
        for (int k = ivec.size() / 2; k >= 1; k /= 2)
        {
            blocks *= 2;
            for (int i = 0; i < blocks - 1; i += 2)
                for (int j = 0; j < k; ++j)
                    ivec[i*k + j] ^= ivec[(i+1)*k + j];
        }

        for (int l = 0; l < table_length; ++l)
            if(ivec[l / sizeof(uint64_t)] >> (sizeof(uint64_t) - 1 - (l % sizeof(uint64_t))))
                elements[l] = l;
    }
    transformed = ivec;
}

vector<uint64_t> ANF::getFunction()
{
    if(elements.empty())
        throw std::exception();

    uint32_t blocks = 1;

    vector<uint64_t> transformed0(transformed);


    if(transformed0.size() == 1)
        for (int k = table_length / 2; k >= 1; k /= 2)
        {
            blocks *= 2;
            for (int i = 0; i < blocks - 1; i += 2)
                for (int j = 0; j < k; ++j)
                    set_bit_64(transformed0[0], get_bit_64(transformed0[0], i*k + j) ^ get_bit_64(transformed0[0], (i+1)*k + j), i*k + j);
        }
    else
        for (int k = transformed0.size() / 2; k >= 1; k /= 2)
        {
            blocks *= 2;
            for (int i = 0; i < blocks - 1; i += 2)
                for (int j = 0; j < k; ++j)
                    transformed0[i*k + j] ^= transformed0[(i+1)*k + j];
        }

    return transformed0;
}

ostream& operator<< (ostream& stream, ANF& anf)
{
    return stream << anf.toStr();
}

int ANF::deg()
{
    unsigned int maxCount = 0;
    for(int i = 0; i < elements.size(); ++i)
        if(maxCount < get_weight_32(elements[i]))
            maxCount = get_weight_32(elements[i]);

    return maxCount;
}

string ANF::toStr()
{
    if(elements.empty())
        return NULL;
    else
    {
        string anf = "";
        for (int i = 0; i < elements.size(); ++i)
        {
            if(elements[i])
            {
                for (int j = 0; j < sizeof(uint64_t); ++j)
                    if(get_bit_32(elements[i], j))
                        anf += "x" + std::to_string(j);
            }else
                anf += "1";

            if(i != elements.size() - 1)
                anf += " + ";
        }
        return anf;
    }
}
