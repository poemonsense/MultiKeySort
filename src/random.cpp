#include "random.h"
#include <iostream>
#include <vector>
#include <random>
#include <ctime>

namespace RandomGen
{
    unsigned int randUnsgnInt(int low, int high)
    {
        static std::default_random_engine e(time(0));
        std::uniform_int_distribution<unsigned> u(low, high);
        return u(e);
    }

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

