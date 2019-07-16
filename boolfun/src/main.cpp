#include <iostream>
#include "GF.h"

using namespace std;
using namespace bf;

int main()
{
    for (int i = 2; i < 16; ++i)
    {
        GF* a = get_field(i);
        cout << i;
    }


    return 0;
}
