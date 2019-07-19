#pragma once

#include "bitslib.h"
#include "GF.h"
#include "ttable.h"

#include <vector>
#include <string>

using namespace std;

namespace bf
{
    class ANF
    {
    private:
        vector<uint32_t> coeff;
        int input_size;
        int empty_table = 1;
    public:
        virtual void             getANF(ttable& table);
        virtual ttable           getFunction();
        virtual string           to_str();
        virtual int              deg();
        virtual void             parse_ANF(string arg);
    };

    ostream& operator<< (ostream& stream, ANF& anf);
}
