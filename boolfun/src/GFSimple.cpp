#include <exception>
#include <cstring>
#include <stdexcept>

#include "GF_simple.h"
#include "Field_polynom_table.h"

namespace bf
{
    GFSimple::~GFSimple() = default;

    //�������� �����������
    GFSimple::GFSimple(int order)
    {
        if (order > 31 || order < 2)
            throw std::invalid_argument("Wrong order!\n");

        true_order = (bvect32)((unsigned)1 << (unsigned)order);

        this->order = order;
        this->field_polynom = get_polynom_from_table(order);
        this->gen_el = get_generating_element();
    }

    bvect64 GFSimple::sum(bvect64 a, bvect64 b)
    {
        return (bvect64)(a ^ b);
    }

    bvect32 GFSimple::sum(bvect32 a, bvect32 b)
    {
        return (bvect64)(a ^ b);
    }

    //���������� ������� a �� b � ���� field. ����� ������
    //                                                    0 - ����� MOD
    //                                                    1 - ����� DIV
    bvect64 GFSimple::div(bvect64 a, bvect64 b, int mode)
    {
        if(b == field_polynom)
        {
            unsigned char c;
            bvect64 result = 0;
            bvect64 a0 = a;

            while (deg_64(a0) >= deg_64(b))
            {
                c = deg_64(a0) - deg_64(b);
                set_bit_64(result, 1, c);
                a0 = sum(a0, b << c);
            }
            if (mode == 0)
                return a0;
            else
                return result;
        }else
        {
            if(mode == 0)
                return 0;
            else
            {
                if(num_to_deg[a] - num_to_deg[b] < 0)
                    return deg_to_num[true_order - 1 + (num_to_deg[a] - num_to_deg[b])];
                else
                    return deg_to_num[num_to_deg[a] - num_to_deg[b]];
            }
        }
    }

    //���� ����������� �������
    bvect32 GFSimple::get_generating_element()
    {
        if(gen_el_found)
            return gen_el;

        //���������� ������������ ������� �������� � �����
        deg_to_num.resize(true_order);
        num_to_deg.resize(true_order);

        int was = 0;

        for (bvect32 i = 1; i < true_order; i++)
        {
            memset(num_to_deg.data(), 0, true_order * sizeof(bvect32));

            for (bvect32 j = 0; j < true_order; j++)
                if (!num_to_deg[power(i, j)])
                {
                    if(j != true_order - 1)
                        num_to_deg[power(i, j)] = j;
                }
                else
                {
                    was = 1;
                    break;
                }


            if (!was)
            {
                for (bvect32 k = 0; k < true_order; k++)
                    deg_to_num[k] = power(i, k);

                gen_el_found = 1;

                return i;
            }
            was = 0;
        }
        throw std::exception();
    }

    bvect32 GFSimple::mod(bvect64 a)
    {
        return (bvect32)div(a, (bvect64)field_polynom, 0);
    }

    bvect32 GFSimple::multiply(bvect32 a, bvect32 b)
    {
        if(!a || !b)
            return 0;

        if(gen_el_found)
            return deg_to_num[(num_to_deg[a] + num_to_deg[b]) % (true_order - 1)];
        else
        {
            bvect64 c = 0;

            for (unsigned int i = 0; i < 32; ++i)
                if((b >> i) & (unsigned)1)
                    c = sum(c, (bvect64)a << i);

            return mod(c);
        }
    }

    //a � ������� b
    bvect32 GFSimple::power(bvect32 a, bvect32 b)
    {
        if(b == 0)
            return 1;

        bvect32 c = a;
        for (size_t i = 1; i < b; i++)
            c = multiply(c, a);

        return c;
    }

    //������������ ������� ����
    unsigned char GFSimple::get_order()
    {
        return order;
    }
}