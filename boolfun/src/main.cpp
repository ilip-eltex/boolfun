#include <ANF.h>
#include <iostream>

using namespace bf;
using namespace std;

int main()
{
	ANF a;
	a.parse_ANF("30x0x1x3 + 13x2x1 + 3x0x3 + 29");
	cout << a.to_str();

    return 0;
}
