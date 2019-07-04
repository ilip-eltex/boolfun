#define LEN 32
#define INT uint32_t
#include "bitslib.hpp"
#include <iostream>
using namespace std;

INT getBit (INT n, INT x) {
	if (n >= LEN)
		return -1;
	return ( (1 << n) & x);
}

bool setBit1 (INT n, INT x) {
	if (n >= LEN) 
		return false;
	x |= (1 << n);
	return true;
}

bool setBit0 (INT n, INT x) {
	if (n >= LEN)
		return false;
	INT *result = &x;
	*result &= ~(1 << n);
	return true;
}

INT getWeight (INT x) {
	
}

bool isodd (INT x) {
	
}

string toBin (INT x) {
	if (x == 0)
		return "0";
	string result = "";
	string s = "";
	for (INT i=LEN-1; i >= 0; i--) 
		s += to_string( (x >> i) & 1 );
	INT j=0;
	while (s[++j] != '1');
	for (INT i=j; i < LEN; result += s[i++]);
	return result;
	
}

int main () {
	INT z; 
	cin >> z;
	cout << toBin(z) << endl;
	setBit0(1,z);
	cout << toBin(z);
	return 0;
}
