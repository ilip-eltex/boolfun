#include "bitslib.hpp"

int getBit (int n, int x) {
	if (n >= STD_LEN)
		return -1;
	return ( (x >> (n - 1)) & 0x1 );
}

bool setBit1 (int n, int x) {
	if (n >= STD_LEN) 
		return false;
	x or (1 << n);
	return true;
}

bool setBit0 (int n, int x) {
	if (n >= STD_LEN)
		return false;
	x xor ( (1 << n) and x );
	return true;
}

int getWeight (int x) {
	
}

bool isodd (int x) {
	
}

string toBin (int x) {
	if (x == 0)
		return "0";
	string result = "";
	string s = "";
	for (int i=STD_LEN-1; i >= 0; i--) 
		s += to_string( (x >> i) & 1 );
	int j=0;
	while (s[++j] != '1');
	for (int i=j; i < STD_LEN; result += s[i++]);
	return result;
	
}
