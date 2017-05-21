#include "random.h"
#include "database.h"
#include <iostream>
#include <ctime>

//using namespace Database;

void TestGen()
{
    Database::LinkData data;
    data.setKeyNum(5);
    for (int i = 0; i != 4; i++) {
        auto temp = RandomGen::randUnsgnIntVec(1, 256, 5);
        data.add(temp);
    }
    clock_t a = clock(), b;
    data.print();
    b = clock();
    std::cout << "Run time:" << (double)(b - a) / CLOCKS_PER_SEC << "s" << std::endl;
}

int main()
{
    TestGen();
    return 0;
}
