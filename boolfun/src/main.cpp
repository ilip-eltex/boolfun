#include <iostream>
#include "ANF.h"
#include "linear.h"
#include "boolean_utils.h"
#include "polynom.h"
#include "ttable.h"

using namespace std;
using namespace bf;

int main()
{
    GF *field = get_field(5);
    vector<bvect32> values((unsigned) 1 << field->get_order(), 0);

    for(int x = 0; x < (unsigned) 1 << field->get_order(); ++x)
        values[x] = field->power(x, 3);

    ttable table(values, field->get_order());

    cout << is_differentially_uniform(table, 2);


    /*GF* field = get_field(4);
    ttable res = get_trace(*field);
    //for(int i = 0; i < res.get_length(); ++i)
    //    cout << res.get_value(i) << endl;

    cout << is_affine(res) << endl;*/

    //GF* field = get_field(6);
    // ANF anf;
    /*
     GF* field = get_field(6);
    ANF anf;
    auto x = get_trace(*field);
    anf.getANF(x);
    cout << anf;
     */

    /*ANF aff;
    aff.parse_ANF("x1x2+x3x4+x5x6+x7x8+x9x10");
    auto y = aff.getFunction();

   // for(int i = 0;i < y.get_length();i++)
    //    cout << y.get_value(i) << endl;

    cout << get_correlation_immunity(y) <<endl;*/


    /*vector<vector<int>> spec = get_walsh_hadamard_spec(x);
    //cout << spec[0].size() << endl;

    for(int i = 0; i < spec[0].size(); ++i)
        cout << spec[0][i] << endl;
    cout << "---------------------\n";

    cout << get_index_nonlinearity(x) << endl;*/

    //cout << get_hemming_distance(x,y) << endl;
    /*polynom p(field);
    p.set_from_string("3: 5x^7 + 10x^300");
    cout << "n: " << p.get_input_length() << endl;
    cout << "coeffs: ";
    for (uint32_t i=0; i<p.get_length(); i++)
        cout << p.get_coeff(i) << ' ';
    ttable tabletka(p);
    cout << "\n\nTable values: ";
    int temp;
    cin >> temp;
    //cout << tabletka.get_length() << 'y';
    for (uint32_t i=0; i<tabletka.get_length(); i++)
        cout << tabletka.get_value(i) << ' ';
    polynom p2(tabletka);
    cout << "\n\ncoeffs-2: ";
    for (uint32_t i=0; i<p.get_length(); i++)
        cout << p.get_coeff(i) << ' ';*/
    return 0;
}
