#include <iostream>
#include "ANF.h"

using namespace std;
using namespace bf;

int main()
{
    ANF anf;
    anf.parse_ANF("21x2x1x3x4 + 5x8x6x4 + 2x8x6x4 + x3x1 + 67 + 32");
    cout << anf;

    return 0;
}
