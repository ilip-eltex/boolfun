#include <cmath>
#include <exception>
#include <cstring>
#include <stdexcept>
#include <iostream>

#include "GF_simple.h"
#include "Field_polynom_table.h"

namespace bf
{
    GFSimple::~GFSimple() = default;

    //Типичный конструктор
    GFSimple::GFSimple(int order)
    {
        if (order > 31 || order < 2)
            throw std::invalid_argument("Wrong order!\n");

        true_order = (bvect32)pow(2, order);
        //std::cout << gen_el_found << std::endl;

        this->order = order;
        this->field_polynom = get_polynom_from_table(order);
        //std::cout << this->field_polynom << std::endl;
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

    bvect64 GFSimple::save_x64_multiply(bvect64 a, bvect64 b)
    {
        bvect64 c = 0;

        for (unsigned int i = 0; i < 64; ++i)
            if((b >> i) & (unsigned)1)
                c = sum(c, (bvect64)a << i);

        return c;
    }

    //Происходит деление a на b в поле field. Здесь режимы
    //                                                    0 - найти MOD
    //                                                    1 - найти DIV
    bvect64 GFSimple::div(GFSimple* field, bvect64 a, bvect64 b, int mode)
    {
        unsigned char c;
        bvect64 result = 0;
        bvect64 a0 = a;

        while (deg(a0) >= deg(b))
        {
            //std::cout << (int)deg(a0) << ' ' << (int)deg(b) << std::endl;
            c = deg(a0) - deg(b);
            set_bit_64(result, 1, c);
            a0 = field->sum(a0, b << c);
        }
        if (mode == 0)
            return a0;
        else
            return result;
    }

    //Ищем порождающий элемент
    bvect32 GFSimple::get_generating_element()
    {
        //генерируем одновременно таблицы степеней и чисел
        deg_to_num.resize(true_order);
        num_to_deg.resize(true_order);

        int was = 0;

        for (bvect32 i = 1; i < true_order; i++)
        {
            memset(num_to_deg.data(), 0, true_order * sizeof(bvect32));

            for (bvect32 j = 0; j < true_order; j++)
            {
                //std::cout << i << " " << j << " " << power(i, j) << std::endl;
                if (!num_to_deg[power(i, j)])
                    num_to_deg[power(i, j)] = j;
                else
                {
                    was = 1;
                    break;
                }
            }
            //std::cout << "------" << std::endl;

            if (!was)
            {
                std::cout << " - " << i << std::endl;
                for (bvect32 k = 0; k < true_order; k++)
                    deg_to_num[num_to_deg[k]] = k;

                gen_el_found = 1;

                return i;
            }
            was = 0;
        }
        throw std::exception();
    }

    bvect32 GFSimple::mod(bvect64 a)
    {
        return (bvect32)div(this, a, (bvect64)field_polynom, 0);
    }

    bvect32 GFSimple::multiply(bvect32 a, bvect32 b)
    {
        if(gen_el_found)//Если таблица доступна
            return deg_to_num[(num_to_deg[a] + num_to_deg[b]) % (true_order - 1)];
        else
        {
            bvect64 c = 0;

            for (unsigned int i = 0; i < 32; ++i)
                if((b >> i) & (unsigned)1)
                    c = sum(c, (bvect64)a << i);

            //std::cout << "awd" << c << std::endl;

            return mod(c);
        }
    }

    //a в степени b
    bvect32 GFSimple::power(bvect32 a, bvect32 b)
    {
        if(b == 0)
            return 1;

        bvect32 c = a;
        for (size_t i = 1; i < b; i++)
            c = multiply(c, a);

        //std::cout << c<< std::endl;

        return c;
    }

    //Возвращается порядок поля
    unsigned char GFSimple::get_order()
    {
        return order;
    }
}