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
        virtual void             getANF(ttable& table);
        virtual vector<uint64_t> getFunction();
        virtual string           to_str();
        virtual int              deg();
        virtual void             parse_ANF(string arg);
    };

    ostream& operator<< (ostream& stream, ANF& anf);
}



#endif
