#include <iostream>
#include "ANF.h"
#include "linear.h"
#include "boolean_utils.h"

using namespace std;
using namespace bf;

int main()
{
    /*GF* field = get_field(4);
    ttable res = get_trace(*field);
    //for(int i = 0; i < res.get_length(); ++i)
    //    cout << res.get_value(i) << endl;

    cout << is_affine(res) << endl;*/

    ANF anf;
    anf.parse_ANF("x1x2+x3x4+x5x6+x7x8+x9x10");
    cout << anf << endl;
    auto x = anf.getFunction();

    ANF aff;
    aff.parse_ANF("x1+x2+x3+x4+x5+x6+x7+x8+x9+x10");
    auto y = aff.getFunction();

    /*vector<vector<int>> spec = get_walsh_hadamard_spec(x);
    //cout << spec[0].size() << endl;

    for(int i = 0; i < spec[0].size(); ++i)
        cout << spec[0][i] << endl;
    cout << "---------------------\n";

    cout << get_index_nonlinearity(x) << endl;*/

    cout << get_hemming_distance(x,y) << endl;

    return 0;
}
