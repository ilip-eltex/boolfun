#include "ANF.h"
#include <vector>
#include "bitslib.h"
#include <cmath>

using namespace bf;

void ANF::getANF(ttable& table)
{
    vector<uint64_t> ivec(table.get_length() <= sizeof(uint64_t) ? 1 : table.get_length() / sizeof(uint64_t), 0);
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
    elements.resize((unsigned long long)pow(2, table.get_length()),0);

    if(ivec.size() == 1)
    {
        for (int k = table.get_length() / 2; k >= 1; k /= 2)
        {
            blocks *= 2;
            for (int i = 0; i < blocks - 1; i += 2)
                for (int j = 0; j < k; ++j)
                    set_bit_64(ivec[0], get_bit_64(ivec[0], i*k + j) ^ get_bit_64(ivec[0], (i+1)*k + j), i*k + j);
        }

        for (int l = 0; l < table.get_length(); ++l)
            if(ivec[0] >> (table.get_length() - 1 - l))
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

        for (int l = 0; l < table.get_length(); ++l)
            if(ivec[l / sizeof(uint64_t)] >> (table.get_length() - 1 - (l % sizeof(uint64_t))))
                elements[l] = l;
    }
    transformed = ivec;
    function_table = table;
}

string ANF::toStr(ttable& table)
{

}
string ANF::toStr(bvect32)
{

}
