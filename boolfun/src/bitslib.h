#pragma once

#include <string>
#include <GF.h>


bvect32 getBit(bvect32 n, bvect32 x);
void setBit1(bvect32 n, bvect32* x);
void setBit0(bvect32 n, bvect32* x);
std::string toBin(bvect32 x);
bvect32 getWeight(bvect32 x);
bool isodd(bvect32 x);
