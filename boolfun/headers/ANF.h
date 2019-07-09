#ifndef BOOLFUN_EXE_ANF_H
#define BOOLFUN_EXE_ANF_H

#include "GF.h"
#include <string>
#include "ttable.h"
#include <vector>

using namespace std;

namespace bf
{
    class ANF
    {
    private:
        vector<uint32_t> elements;
        vector<uint64_t> transformed;
        ttable& function_table;
    public:
        virtual void    getANF(ttable& table) = 0;
        virtual bvect32 getFunction() = 0;
        virtual string  toStr() = 0;
    };

    ostream& operator<< (ostream& stream, ANF& anf);
}



#endif
