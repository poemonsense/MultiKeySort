#ifndef RANDOMGEN
#define RANDOMGEN

#include <vector>
#include <random>
#include <ctime>

namespace RandomGen
{
    static std::default_random_engine e(time(0));
    unsigned int randUnsgnInt(int low, int high);
    std::vector<unsigned> randUnsgnIntVec(int low, int high, int length);
    unsigned int *randUnsgnIntArray(int low, int high, int length);

    inline unsigned int randUnsgnInt(int low, int high)
    {
        std::uniform_int_distribution<unsigned> u(low, high);
        return u(RandomGen::e);
    }
}

#endif // RANDOMGEN
