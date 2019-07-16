#include <iostream>
#include "ANF.h"

using namespace std;
using namespace bf;

int main()
{
    ANF anf;
    anf.parse_ANF("x0x1x3x4 + x3x1 + 1");
    cout << anf;

    return 0;
}
