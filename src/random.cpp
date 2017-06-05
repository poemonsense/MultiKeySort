#include "random.h"
#include <vector>

namespace RandomGen
{
    std::vector<unsigned> randUnsgnIntVec(int low, int high, int length)
    {
        std::vector<unsigned> ret;
        for (int i = 0; i != length; i++)
            ret.push_back(randUnsgnInt(low, high));
        return ret;
    }

    unsigned int *randUnsgnIntArray(int low, int high, int length)
    {
        unsigned int *ret = new unsigned int[length];
        for (int i = 0; i != length; i++)
            ret[i] = randUnsgnInt(low, high);
        return ret;
    }
}

