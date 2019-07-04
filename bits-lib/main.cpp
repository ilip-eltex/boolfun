#define LEN 32
#define INT uint32_t
#include <iostream>
#include <string>
using namespace std;

INT getBit (INT n, INT x) {
	if (n >= LEN)
		return -1;
	if ( ( (INT)1 << n ) & x) 
	    return 1;
	else 
	    return 0;
}

bool setBit1 (INT n, INT *x) {
	if (n >= LEN) 
		return false;
	*x |= (1 << n);
	return true;
}

bool setBit0 (INT n, INT *x) {
	if (n >= LEN)
		return false;
	*x &= ~(1 << n);
	return true;
}

string toBin (INT x) {
	if (x == 0)
		return "0";
	string result = "";
	string s = "";
	for (int i=LEN-1; i >= 0; i--) {
	   switch ( (x >> i) & 1) {
	       case 1: s += '1'; break;
	       case 0: s += '0';
	   }
	}
		
	INT j=0;
	while (s[++j] != '1');
	for (INT i=j; i < LEN; result += s[i++]);
	return result;
}

INT getWeight (INT x) {
	INT result=0;
	while (x != 0) {
	    x &= x-1;
	    result++;
	}
	return result;
}

bool isodd (INT x) {
	
}

int main () {
	INT z; 
	cin >> z;
	const string l = toBin(z);
	cout << l << endl;
	cout << getWeight(z) << ' ';
	return 0;
}
