#include <iostream>
#include "ANF.h"

using namespace std;
using namespace bf;

int main()
{
    ANF anf;
    anf.parse_ANF("x1x2 + 32x2x32 + 4x1x2x3 + x1x3 + x1 + 9x3 + x2 + 65537 + x3 + 7x2 + 7x2");
    cout << anf << endl;
    auto x = anf.getFunction();
    //for(int i = 0; i < x.get_length(); ++i)
     //   cout << x.get_value(i) << endl;

    anf.getANF(x);
    cout << anf << endl;

    //с константами проблемы

    /*auto x = anf.getFunction();
    for(int i = 0; i < x[0].size(); ++i)
        cout << (x[0][i]) << endl;

    ttable table(x);
    cout << "iam ok!" << endl;
    anf.getANF(table);
    cout << anf;
 */

    return 0;
}
