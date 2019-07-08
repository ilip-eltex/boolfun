#include <GF_simple.h>
#include <Field_polynom_table.h>
#include <privpolynom.h>
#include <cmath>
#include <stdexcept>


using namespace bf;

const int MOD = 0;
const int DIV = 1;
int gen_el_found = 0;//в один момент используем умножение без таблицы, поэтому нужно знать, когда можно использовать таблицу
unsigned int true_order;//пор€док пол€, не степень двойки, а 2^n - 1

bvect32 GFSimple::sum(bvect32 a, bvect32 b)
{
	return (bvect32)(a ^ b);
}

bvect64 GFSimple::sum(bvect64 a, bvect64 b)
{
	return (bvect64)(a ^ b);
}

bvect64 GFSimple::save_x64_multiply(bvect64 a, bvect64 b)
{
	bvect64 c = 0;

	for (int i = 0; i < 32; ++i)
		sum(c, (bvect64)a << ((i * (b >> i) % 2)));

	return mod(c);
}

 //ѕроисходит деление a на b в поле field. «десь режимы
 //                                                    0 - найти MOD
 //                                                    1 - найти DIV
bvect64 GFSimple::div(GFSimple* field, bvect64 a, bvect64 b, int mode)
{
  unsigned char c;
  bvect64 result = 0;
  bvect64 a0 = a;

  while (deg(a0) >= deg(b))
  {
    c = deg(a0) - deg(b);
    set_bit_64(result, c, 1);
    a0 = field->sum(a0, field->save_x64_multiply(b, result));
  }
  if (mode == MOD)
    return a0;
  else
    return result;
}

//“ипичный конструктор
GFSimple::GFSimple(int order)
{
	if (order > 31 || order < 2)
		throw std::invalid_argument("Wrong order!\n");

	true_order = (bvect32)pow(2, order) - 1;

	this->gen_el = get_generating_element();
	this->order = order;
	this->field_polynom = get_polynom_from_table(order);
}

//»щем порождающий элемент
bvect32 GFSimple::get_generating_element()
{
	//генерируем одновременно таблицы степеней и чисел
	deg_to_num = (bvect32*)malloc(true_order * sizeof(bvect32));
	num_to_deg = (bvect32*)malloc(true_order * sizeof(bvect32));

	int was = 0;

	for (bvect32 i = 1; i < true_order; i++)
	{
		memset(num_to_deg, true_order, 0);

		for (bvect32 j = 0; j < true_order; j++)
			if (!num_to_deg[power(i, j)])//ща перепишем
				num_to_deg[power(i, j)] = j;
			else
			{
				was = 1;
				break;
			}

		if (!was)
		{
			for (bvect32 k = 0; k < true_order; k++)
				deg_to_num[num_to_deg[k]] = k;

			gen_el_found = 1;

			return i;
		}
		was = 0;
	}
	throw std::exception("Shit happened in get_generating_element()...");

	return 0;
}

bvect32 GFSimple::mod(bvect64 a)
{
	return (bvect32)div(this, a, field_polynom, MOD);
}

bvect32 GFSimple::multiply(bvect32 a, bvect32 b)
{
	if(gen_el_found)//≈сли таблица доступна
		return deg_to_num[(num_to_deg[a] + num_to_deg[b]) % true_order];
	else
	{
		bvect64 c = 0;

		for (int i = 0; i < 32; ++i)
			sum(c, (bvect64)a << ((i * (b >> i) % 2)));

		return mod(c);
	}
}

//a в степени b
bvect32 GFSimple::power(bvect32 a, bvect32 b)
{
	bvect32 c = a;
	for (size_t i = 1; i < b; i++)
		multiply(c, a);
	
	return c;
}

//¬озвращаетс€ пор€док пол€
unsigned char GFSimple::get_order()
{
	return order;
}
