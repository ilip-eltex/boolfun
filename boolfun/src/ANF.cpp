#include <vector>
#include <cmath>
#include <iostream>
#include "ANF.h"

namespace bf
{
    uint64_t table_length;

    void gen_ANF_for_boolean_function(ttable &table, unsigned int bit_vector, vector<uint32_t> &elements0,
                                      vector<uint64_t> &transformed0)
    {
        table_length = table.get_length();

        vector<uint64_t> ivec(table_length <= sizeof(uint64_t) ? 1 : table_length / sizeof(uint64_t), 0);
        uint64_t count = 0;

        for (int i = 0; i < ivec.size(); ++i)
        {
            for (int j = 0; j < sizeof(uint64_t) * 8; ++j)
            {
                ivec[i] |= (table.get_value(count++) >> bit_vector) & (unsigned) 1;
                ivec[i] <<= (unsigned) 1;
            }
        }
        uint32_t blocks = 1;
        elements0.resize(table_length, 0);

        if (ivec.size() == 1)
        {
            for (int k = table_length / 2; k >= 1; k /= 2)
            {
                blocks *= 2;
                for (int i = 0; i < blocks - 1; i += 2)
                    for (int j = 0; j < k; ++j)
                        set_bit_64(ivec[0], get_bit_64(ivec[0], i * k + j) ^ get_bit_64(ivec[0], (i + 1) * k + j),
                                   i * k + j);
            }

            for (int l = 0; l < table_length; ++l)
                if (ivec[0] >> (table_length - 1 - l))
                    elements0[l] = l;
        } else
        {
            for (int k = ivec.size() / 2; k >= 1; k /= 2)
            {
                blocks *= 2;
                for (int i = 0; i < blocks - 1; i += 2)
                    for (int j = 0; j < k; ++j)
                        ivec[i * k + j] ^= ivec[(i + 1) * k + j];
            }

            for (int l = 0; l < table_length; ++l)
                if (ivec[l / sizeof(uint64_t)] >> (sizeof(uint64_t) - 1 - (l % sizeof(uint64_t))))
                    elements0[l] = l;
        }
        transformed0 = ivec;
    }

    void ANF::getANF(ttable &table)//FIXME чекай индексы
    {
        if (!table.is_NM_function())
        {
            transformed.resize(1);
            gen_ANF_for_boolean_function(table, 0, elements, transformed[0]);
        } else
        {
            vector<vector<uint32_t>> elements0;

            coeff.resize(table_length);
            elements0.resize(table.get_output_length());
            transformed.resize(table.get_output_length());
            elements.resize(table_length, 0);

            for (int i = 0; i < table.get_output_length(); ++i)
                gen_ANF_for_boolean_function(table, (unsigned) i, elements0[i], transformed[i]);

            for (int k = 0; k < (unsigned long long) pow(2, table_length); ++k)
                for (int j = 0; j < table.get_output_length(); ++j)
                {
                    coeff[k] |= (unsigned) (elements0[j][k] > 0 ? 1 : 0);
                    coeff[k] <<= (unsigned) 1;

                    if (!elements[k])
                        elements[k] = k;
                }
        }
    }

    vector<vector<uint64_t>> ANF::getFunction()
    {
        if (elements.empty())
            throw std::exception();

        uint32_t blocks = 1;
        vector<vector<uint64_t>> transformed0(transformed.size());

        for (int i = 0; i < transformed.size(); ++i)
        {
            transformed0[i] = transformed[i];

            if (transformed0[i].size() == 1)
                for (int k = table_length / 2; k >= 1; k /= 2)
                {
                    blocks *= 2;
                    for (int i0 = 0; i0 < blocks - 1; i0 += 2)
                        for (int j = 0; j < k; ++j)
                            set_bit_64(transformed0[i][0], get_bit_64(transformed0[i][0], i0 * k + j) ^
                                                           get_bit_64(transformed0[i][0], (i0 + 1) * k + j), i0 * k + j);
                }
            else
                for (int k = transformed0[i].size() / 2; k >= 1; k /= 2)
                {
                    blocks *= 2;
                    for (int i0 = 0; i0 < blocks - 1; i0 += 2)
                        for (int j = 0; j < k; ++j)
                            transformed0[i0][i0 * k + j] ^= transformed0[i0][(i0 + 1) * k + j];
                }
            blocks = 1;
        }
        return transformed0;
    }

    ostream &operator<<(ostream &stream, ANF &anf)
    {
        return stream << anf.to_str();
    }

    int ANF::deg()
    {
        if (elements.empty())
            throw std::exception();

        unsigned int maxCount = 0;

        for (int i = 0; i < elements.size(); ++i)
            if (maxCount < get_weight_32(elements[i]))
                maxCount = get_weight_32(elements[i]);

        return maxCount;
    }

    int get_token(string arg, unsigned int &index, uint32_t &elem)
    {
        while (arg[index] != 'x' && !(arg[index] - '0' > 0 && arg[index] - '0' < 10))
        {
            if (index == arg.length())
                return -3;

            if (arg[index] != ' ' && arg[index] != '+' && !(arg[index] - '0' > 0 && arg[index] - '0' < 10))
                return -1;
            else if (arg[index] == '+')
                return -2;

            index++;
        }
        cout << arg[index];

        if (arg[index] - '0' > 0 && arg[index] - '0' < 10)
        {
            unsigned int a = arg[index] - '0';
            index++;
            while (arg[index] - '0' > 0 && arg[index] - '0' < 10 && index++ < arg.length())
                a = a * 10 + (arg[index - 1] - '0');

            elem = a;
            if (index <= arg.length() && (arg[index] == ' ' || arg[index] == '+'))
                return 0;
            else if (index < arg.length() && arg[index] == 'x')
                return 1;
            else
            {
                cout << arg[index] << endl;
                return -1;
            }
        } else
        {
            if (index == arg.length() - 1)
            {
                cout << "dadw" << endl;
                return -1;
            }
            else
            {
                unsigned int a = arg[index + 1] - '0';
                index+=2;
                while (arg[index] - '0' > 0 && arg[index] - '0' < 10 && index++ < arg.length())
                    a = a * 10 + (arg[index - 1] - '0');

                elem = a;

                return 2;
            }
        }
    }

    void ANF::parse_ANF(string arg)
    {
        int fill = 1;
        int br = 0;
        int maxDeg = 0;
        unsigned int index = 0;
        unsigned int lastCoeff = 0;
        unsigned int lastX = 0;
        int writeElem = 0;
        uint32_t elem;

        while (true)
        {
            cout << "da";
            if (fill)
            {
                elements.resize(elements.size() + 1);
                fill = 0;
            }

            switch (get_token(arg, index, elem))
            {
                case -3:
                    if (!elements.empty())
                        throw std::invalid_argument("bad string!0");
                    else
                        if(!writeElem)
                        {
                            br = 1;
                            break;
                        }
                case -2:
                    fill = 1;

                    if(!writeElem)
                        throw std::invalid_argument("bad string!1");

                    if(!lastCoeff)
                        lastCoeff = 1;

                    if(elements.size() <= lastX)
                        elements.resize(lastX + 1);

                    if(!elements[lastX])
                        elements[lastX] = lastX;
                    else
                    {
                        coeff[lastX] ^= lastCoeff;
                        if(!coeff[lastX])
                        {
                            elements[lastX] = 0;
                            for (int j = 0; j < transformed.size(); ++j)
                                transformed[j][lastX] = 0;
                            break;
                        }
                    }

                    for (int j = 0; j < transformed.size(); ++j)
                        transformed[j][lastX] |= lastCoeff >> (unsigned)(transformed.size() - 1 - j);

                    coeff[lastX] = lastCoeff;

                    writeElem = 0;
                    lastX = 0;
                    lastCoeff = 0;
                    break;
                case -1:
                    throw std::invalid_argument("bad string!2");
                case 0:
                    if (elements.empty())
                        elements.resize(1);
                    if (coeff.empty())
                        coeff.resize(1);

                    elements[0] = 0;
                    coeff[0] = elem;
                    break;
                case 1://coeff of x
                    if (elem)
                    {
                        lastCoeff = elem;
                        writeElem = 1;

                        if (elem != 1)
                        {
                            if(transformed.size() < deg_32(elem))
                            {
                                int size = transformed.size();
                                transformed.resize(deg_32(elem));
                                for (int i = size + 1; i < transformed.size(); ++i)
                                    transformed[i].resize(1 << maxDeg);
                            }
                        }
                    }
                    break;
                case 2://x index
                    if(maxDeg < elem)
                    {
                        maxDeg = elem;
                        for (int i = 0; i < transformed.size(); ++i)
                            transformed[i].resize(1 << maxDeg, 0);

                        coeff.resize(1 << maxDeg);
                    }

                    writeElem = 1;

                    lastX |= (unsigned int) ((unsigned)1 << (elem - 1));
                    break;
            }
            if (br)
                break;
        }
    }

    string ANF::to_str()
    {
        if (elements.empty())
            return NULL;
        else
        {
            string anf = "";
            for (int i = 0; i < elements.size(); ++i)
            {
                if (elements[i])
                {
                    if (!coeff.empty())
                        anf += std::to_string(coeff[i]);

                    for (int j = 0; j < sizeof(uint32_t); ++j)
                        if (get_bit_32(elements[i], j))
                            anf += "x" + std::to_string(j + 1);
                } else if (i == 0 && transformed.size() == 1)
                    anf += "1";
                else if (i == 0 && transformed.size() > 1)
                    anf += std::to_string(coeff[0]);

                if (i != elements.size() - 1)
                    anf += " + ";
            }
            return anf;
        }
    }
}

