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
        vector<uint32_t> elements;
        vector<vector<uint64_t>> transformed;
    public:
        virtual void             getANF(ttable& table);
        virtual vector<vector<uint64_t>> getFunction();
        virtual string           to_str();
        virtual int              deg();
        virtual void             parse_ANF(string arg);
    };

    ostream& operator<< (ostream& stream, ANF& anf);
}