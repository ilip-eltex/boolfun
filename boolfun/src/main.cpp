#include <iostream>
#include "ANF.h"

using namespace std;
using namespace bf;

int main()
{
    ANF anf;
    anf.parse_ANF("x1x2x3 + x2x3 + x1 + 1");
    cout << anf << endl;

    ttable table(anf.getFunction());
    cout << "iam ok!" << endl;
    anf.getANF(table);
    cout << anf;

    return 0;
}
