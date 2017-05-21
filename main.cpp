#include "random.h"
#include "database.h"
#include <iostream>

//using namespace Database;

void TestGen()
{
    Database::LinkData data;
    data.setKeyNum(5);
    auto test = RandomGen::randUnsgnIntVec(1, 100, 5);
    auto test1 = RandomGen::randUnsgnIntVec(1, 100, 5);
    data.add(test);
    data.add(test1);
    data.print();
}

int main()
{
    TestGen();
    return 0;
}
