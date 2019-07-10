#include <GF.h>
#include <GF_simple.h>

namespace bf
{
    GF *get_field(int order)
    {
        if (order > 31 || order < 2)
            return NULL;
        GF *field = new GFSimple(order);
        return field;
    }
}
