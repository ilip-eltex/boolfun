#include <iostream>
#include "ANF.h"

using namespace std;
using namespace bf;

int main()
{
    ANF anf;
    anf.parse_ANF("x22x4x1 + 5x2x1 + x2x1 + 23 ");
    cout << anf << endl;

    /*
    auto x = anf.getFunction();
    for(int i = 0; i < x[0].size(); ++i)
        cout << (x[0][i]) << endl;

    ttable table(x);
    cout << "iam ok!" << endl;
    anf.getANF(table);
    cout << anf;
 */

    return 0;
}
