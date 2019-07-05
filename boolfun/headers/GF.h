#pragma once
#include <cstdint>

namespace bf
{
  typedef uint32_t bvect32;
  typedef uint64_t bvect64;

  class GF
  {
  private:
	  bvect32 h;
	  unsigned char N;
	  virtual bvect32 mod(bvect32) = 0;
  public:
      virtual bvect32 sum(bvect32, bvect32) = 0;
	  virtual bvect32 multiply(bvect32, bvect32) = 0;
	  virtual bvect32 power(bvect32, bvect32) = 0;
	  virtual unsigned char get_order() = 0;
  };

  GF* get_field(int order)
  {
	  if (order > 31 || order < 2)
		  return NULL;
	  GF* field = new GFSimple(order);
	  return field;
  }
}