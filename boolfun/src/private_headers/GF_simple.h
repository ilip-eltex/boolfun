#pragma once
#include <GF.h>

namespace bf 
{
	class GFSimple :public GF
	{
	private:
		bvect32 field_polynom;
		bvect32 gen_el;
		bvect32* num_to_deg;//Массив отображения число - степень попрождающего элемента
		bvect32* deg_to_num;//Массив отображения степень порождающего элемента - число
		unsigned char order;
		virtual bvect32 mod(bvect32);
		virtual bvect32 get_generating_element();
	public:
		virtual bvect32 sum(bvect32, bvect32);
		virtual bvect32 multiply(bvect32, bvect32);
		virtual bvect32 power(bvect32, bvect32);
		virtual unsigned char get_order();
		GFSimple(int order);
	};
}
