#include "bitslib.hpp"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	int z;
	cin >> z;
	cout << toBin(z) << endl;
	setBit0(1,z);
	cout << toBin(z);
	return 0;
}
