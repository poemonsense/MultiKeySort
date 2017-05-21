#ifndef RANDOMGEN
#define RANDOMGEN

#include <vector>
namespace RandomGen
{
    unsigned int randUnsgnInt(int low, int high);
    std::vector<unsigned> randUnsgnIntVec(int low, int high, int length);
    unsigned int *randUnsgnIntArray(int low, int high, int length);
    //void TestRandom();
}

#endif // RANDOMGEN
