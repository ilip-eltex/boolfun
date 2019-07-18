#include "ANF.h"
#include "ttable.h"
#include <vector>

namespace bf
{
    void ANF::getANF(ttable& table)
    {
        coeff.resize(table.get_length());
        input_size = table.get_input_length();

        for(bvect32 i = 0; i < table.get_length(); ++i)
        {
            coeff[i] = table.get_value(i);
            if(coeff[i])
                empty_table = 0;
        }

        uint32_t blocks = 1;

        for(int k = coeff.size() / 2; k >= 1; k /= 2)
        {
            blocks *= 2;
            for(int i = 0; i < blocks - 1; i += 2)
                for(int j = 0; j < k; ++j)
                    coeff[(i + 1) * k + j] ^= coeff[i * k + j];
        }
    }

    ttable ANF::getFunction()
    {
        if(coeff.empty())
            throw std::exception();

        if(empty_table)
        {
            vector<bvect32> copy((unsigned)1 << (unsigned)input_size, 0);
            ttable table(copy, input_size);
            return table;
        }

        vector<bvect32> copy(coeff);

        uint32_t blocks = 1;

        for(int k = copy.size() / 2; k >= 1; k /= 2)
        {
            blocks *= 2;
            for(int i = 0; i < blocks - 1; i += 2)
                for(int j = 0; j < k; ++j)
                    copy[(i + 1) * k + j] ^= copy[i * k + j];
        }

        ttable table(copy, input_size);
        return table;
    }

    ostream &operator<<(ostream &stream, ANF &anf)
    {
        return stream << anf.to_str();
    }

    int ANF::deg()
    {
        if(coeff.empty())
            throw std::exception();

        unsigned int maxCount = 0;

        for(int i = 0;i < coeff.size();i++)
            if(coeff[i] && maxCount < get_weight_32(i))
                maxCount = get_weight_32(i);

        return maxCount;
    }

    int get_token(string arg, unsigned int &index, uint32_t &elem)
    {
        while(arg[index] != 'x' && !isdigit(arg[index]))
        {
            if(index == arg.length())
                return -3;

            if(arg[index] != ' ' && arg[index] != '+' && !isdigit(arg[index]))
                return -1;
            else if(arg[index] == '+')
            {
                index++;
                return -2;
            }

            index++;
        }

        int exp = 10;

        if(isdigit(arg[index]))
        {
            unsigned int a = arg[index] - '0';
            index++;
            while(isdigit(arg[index]) && index < arg.length())
                a = a * exp + (arg[index++] - '0');

            elem = a;
            if(index == arg.length() || (index < arg.length() && (arg[index] == ' ' || arg[index] == '+')))
                return 0;
            else if(index < arg.length() && arg[index] == 'x')
                return 1;
            else
                return -1;
        } else
        {
            if(index == arg.length() - 1)
                return -1;
            else
            {
                unsigned int a = 0;
                index++;
                while(isdigit(arg[index]) && index < arg.length())
                    a = a * exp + (arg[index++] - '0');

                elem = a;


                return 2;
            }
        }
    }

    void ANF::parse_ANF(string arg)
    {
        if(arg.empty())
            throw std::invalid_argument("empty string!");

        int br = 0;
        int maxDeg = 0;
        unsigned int index = 0;
        unsigned int lastCoeff = 0;
        unsigned int lastX = 0;
        int writeElem = 0;
        uint32_t elem;
        int lastOp = 0;
        int counter = 0;

        while(true)
        {
            switch(get_token(arg, index, elem))
            {
                case -3:
                    if(lastOp == -2)
                        throw std::invalid_argument("bad string!");
                    if(!writeElem)
                    {
                        br = 1;
                        break;
                    }
                    lastOp = -3;
                case -2:
                    if(lastOp != -3)
                        lastOp = -2;
                    if(!writeElem)
                        throw std::invalid_argument("bad string!");

                    if(coeff[lastX] && lastCoeff)
                    {
                        coeff[lastX] ^= lastCoeff;
                        lastCoeff = coeff[lastX];
                        if(!lastCoeff)
                            counter--;
                    }

                    if(lastCoeff)
                    {
                        coeff[lastX] = lastCoeff;
                        counter++;
                    }

                    writeElem = 0;
                    lastX = 0;
                    lastCoeff = 0;
                    break;
                case -1:
                    throw std::invalid_argument("bad string!");
                case 0:
                    lastOp = 0;

                    if(coeff.empty())
                        coeff.resize(1);

                    writeElem = 1;

                    lastCoeff = elem;
                    lastX = 0;
                    break;
                case 1:
                    lastOp = 1;
                    if(elem)
                    {
                        lastCoeff = elem;
                        writeElem = 1;
                    }
                    break;
                case 2:
                    lastOp = 2;
                    if(elem == 0)
                        throw std::invalid_argument("zero x index!");
                    if(elem > 31)
                        throw std::invalid_argument("x index more than 31!");

                    if(!lastCoeff)
                        lastCoeff = 1;

                    if(maxDeg < elem)
                    {
                        maxDeg = elem;
                        input_size = maxDeg;
                        coeff.resize((unsigned)1 << (unsigned)maxDeg);
                    }
                    writeElem = 1;

                    lastX |= (unsigned int) ((unsigned) 1 << (elem - 1));
                    break;
            }
            if(br)
                break;
        }
        if(counter)
            empty_table = 0;
    }

    string ANF::to_str()
    {
        if(coeff.empty())
            return nullptr;

        if(empty_table)
            return "0";

        string anf;
        int was = 0;

        for(int i = coeff.size() - 1; i >= 0; --i)
        {
            if(coeff[i])
            {
                if(!was)
                    was = 1;
                else
                    anf += " + ";

                if(coeff[i] != 1 || i == 0)
                    anf += std::to_string(coeff[i]);

                for(int j = 0; j < sizeof(uint32_t) * 8; ++j)
                    if(get_bit_32(i, j))
                        anf += "x" + std::to_string(j + 1);
            }
        }
        return anf;
    }
}
