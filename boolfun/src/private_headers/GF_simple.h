#pragma once
#include "GF.h"

namespace bf 
{
	class GFSimple: public GF
	{
	protected:
		virtual bvect32 mod(bvect64);
		virtual bvect32 get_generating_element();
		virtual bvect64 sum(bvect64, bvect64);
		virtual bvect64 save_x64_multiply(bvect64, bvect64);
		virtual bvect64 div(GFSimple* field, bvect64 a, bvect64 b, int mode);
	public:
        virtual bvect32 sum(bvect32, bvect32);
		virtual bvect32 multiply(bvect32, bvect32);
		virtual bvect32 power(bvect32, bvect32);
		virtual unsigned char get_order();
		GFSimple(int order);
		~GFSimple();
	};
}
