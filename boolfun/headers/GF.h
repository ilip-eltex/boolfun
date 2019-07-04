#pragma once

namespace bf
{
  typedef uint32_t bvect32;

  class GF
  {
  public:
    virtual bvect32 sum(bvect32, bvect32) = 0;
    virtual bvect32 mult(bvect32, bvect32) = 0;
  };

  GF* get_field(int n)
  {
    return 0;
  }
}

using bf::bvect32;

class GFSimple : public bf::GF
{
  virtual bvect32 sum(bvect32 a, bvect32 b)
  {
    return a ^ b;
  }
  
  virtual bvect32 mult(bvect32, bvect32)
  {
    return 0;
  }
};