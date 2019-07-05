#include <GF_simple.h>
#include <Binary.h>
#include <Field_polynom_table.h>
#include <Polynom.h>
#include <cmath>
#include <stdexcept>


using namespace bf;

const int MOD = 0;
const int DIV = 1;
int gen_el_found = 0;//� ���� ������ ���������� ��������� ��� �������, ������� ����� �����, ����� ����� ������������ �������
unsigned int true_order;//������� ����, �� ������� ������, � 2^n - 1

//�������� �����������
GFSimple::GFSimple(int order)
{
	if (order > 31 || order < 2)
		throw std::invalid_argument("Wrong order!\n");

	true_order = (bvect32)pow(2, order) - 1;

	this->gen_el = get_generating_element();
	this->order = order;
	this->field_polynom = get_polynom_from_table(order);
}

//���� ����������� �������
bvect32 GFSimple::get_generating_element()
{
	//���������� ������������ ������� �������� � �����
	deg_to_num = (bvect32*)malloc(true_order * sizeof(bvect32));
	num_to_deg = (bvect32*)malloc(true_order * sizeof(bvect32));

	int was = 0;

	for (size_t i = 1; i < true_order; i++)
	{
		memset(num_to_deg, true_order, 0);

		for (size_t j = 0; j < true_order; j++)
			if (!num_to_deg[power(i, j)])//�� ���������
				num_to_deg[power(i, j)] = j;
			else
			{
				was = 1;
				break;
			}

		if (!was)
		{
			for (size_t k = 0; k < true_order; k++)
				deg_to_num[num_to_deg[k]] = k;

			gen_el_found = 1;

			return i;
		}
		was = 0;
	}
}

bvect32 GFSimple::mod(bvect32 a)
{
	return (bvect32)div(this, a, field_polynom, MOD);
}

bvect32 GFSimple::sum(bvect32 a, bvect32 b)
{
	return (bvect32)(a ^ b);
}

bvect32 GFSimple::multiply(bvect32 a, bvect32 b)
{
	if(gen_el_found)//���� ������� ��������
		return deg_to_num[(num_to_deg[a] + num_to_deg[b]) % true_order];
	else
	{
		bvect64 c = 0;

		for (int i = 0; i < 32; ++i)
			sum(c, a << (((b >> i) % 2)));

		return mod(c);
	}
}

//a � ������� b
bvect32 GFSimple::power(bvect32 a, bvect32 b)
{
	bvect32 c = a;
	for (size_t i = 1; i < b; i++)
		multiply(c, a);
	
	return c;
}

//������������ ������� ����
unsigned char GFSimple::get_order()
{
	return order;
}

//���������� ������� a �� b � ���� field. ����� ������
//                                                    0 - ����� MOD
//                                                    1 - ����� DIV
static bvect64 div(GF* field, bvect64 a, bvect64 b, int mode)
{
	unsigned char c;
	bvect64 result = 0;
	bvect32 a0 = a;

	while (deg(a0) >= deg(b))
	{
		c = deg(a0) - deg(b);
		set_bit_64(&result, c, 1);
		a0 = field->sum(a0, field->multiply(b, result));
	}
	if (mode == MOD)
		return a0;
	else
		return result;
}