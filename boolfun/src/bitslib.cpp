#include "bitslib.h"
namespace bf {
	bvect32 getBit(bvect32 n, bvect32 x) {
		/*if (n >= LEN)
			return -1; */
		if (((bvect32)1 << n) & x)
			return 1;
		else
			return 0;
	}

	void setBit1(bvect32 n, bvect32* x) {
		/*if (n >= LEN)
			return false; */
		*x |= (1 << n);
		// return true;
	}

	void setBit0(bvect32 n, bvect32* x) {
		/* if (n >= LEN)
			return false; */
		*x &= ~(1 << n);
		//return true;
	}

	std::string toBin(bvect32 x) {
		if (x == 0)
			return "0"; 
		std::string result = "";
		std::string s = "";
		for (int i = 31; i >= 0; i--) {
			switch ((x >> i) & 1) {
				case 1:
					s += "1";
					break;
				case 0:
					s += "0";
			}
		}

		bvect32 j = 0;
		while (s[++j] != '1');
		for (bvect32 i = j; i < 32; result += s[i++]);
		return result;
	}

	bvect32 getWeight(bvect32 x) {
		bvect32 result = 0;
		while (x != 0) {
			x &= x - 1;
			result++;
		}
		return result;
	}

	bool isodd(bvect32 x) {
		return (getWeight(x) % 2 == 0);
	}
}
