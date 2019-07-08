#pragma once
#include <GF.h>

namespace bf 
{
	class GFSimple: public GF
	{
	protected:
		virtual bvect32 mod(bvect32);
		virtual bvect32 get_generating_element();
		virtual bvect64 sum(bvect64, bvect64);
	public:
		virtual bvect32 sum(bvect32, bvect32);
		virtual bvect32 multiply(bvect32, bvect32);
		virtual bvect32 power(bvect32, bvect32);
		virtual unsigned char get_order();
		GFSimple(int order);
	};
}
