#include "GF_simple.h"
#include "Polynom.h"
#include "Binary.h"
using namespace bf;

const int MOD = 0;
const int DIV = 1;

bvect32 GFSimple::mod(bvect32 a)
{
	return (bvect32)div(this, a, h, MOD);
}

bvect32 GFSimple::sum(bvect32 a, bvect32 b)
{
	return (bvect32)(a ^ b);
}

bvect32 GFSimple::multiply(bvect32 a, bvect32 b)
{
	bvect64 c = 0;

	for (int i = 0; i < 32; ++i)
		sum(c, a << (((b >> i) % 2)));

	return mod(c);
}

//a в степени b
bvect32 GFSimple::power(bvect32 a, bvect32 b)
{
	bvect32 c = a;
	for (size_t i = 1; i < b; i++)
		multiply(c, a);
	
	return c;
}

unsigned char GFSimple::getN()
{
	return N;
}

//ѕроисходит деление a на b в поле field
static bvect64 div(GF* field, bvect64 a, bvect64 b, int mode)
{
	unsigned char c;
	bvect64 result = 0;
	bvect32 a0 = a;

	while (deg(a0) >= deg(b))
	{
		c = deg(a0) - deg(b);
		setBit64(&result, c, 1);
		a0 = field->sum(a0, field->multiply(b, result));
	}
	if (mode == MOD)
		return a0;
	else
		return result;
}