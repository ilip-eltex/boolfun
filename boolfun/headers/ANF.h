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
    public:
        virtual void             getANF(ttable& table) = 0;
        virtual vector<uint64_t> getFunction() = 0;
        virtual string           to_str() = 0;
        virtual int              deg() = 0;
    };

    ostream& operator<< (ostream& stream, ANF& anf);
}



#endif
