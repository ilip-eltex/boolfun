#include <GF.h>
#pragma once

namespace bf 
{
	class GFSimple :public GF
	{
	private:
		bvect32 field_polynom;
		unsigned char order;
		virtual bvect32 mod(bvect32);
	public:
		virtual bvect32 sum(bvect32, bvect32);
		virtual bvect32 multiply(bvect32, bvect32);
		virtual bvect32 power(bvect32, bvect32);
		virtual unsigned char get_order();
		GFSimple(int order);
	};
}
