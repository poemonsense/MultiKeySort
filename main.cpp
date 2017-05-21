#include "random.h"
#include "database.h"
#include <iostream>
#include <ctime>

void TestGen()
{
    std::cout << "5 Keys, 10000 test records with integer values in range [1, " << MAX_DATA_NUM << "]\n";
    Database::LinkData data;
    data.setKeyNum(5);
    for (int i = 0; i != 10000; i++) {
        auto temp = RandomGen::randUnsgnIntVec(1, MAX_DATA_NUM, 5);
        data.add(temp);
    }
    clock_t a = clock(), b;
    data.radixSort();
    b = clock();
    // data.print();
    std::cout << "Radix sort run time: " << (double)(b - a) / CLOCKS_PER_SEC << "s" << std::endl;
    clock_t c = clock(), d;
    data.mergeSort();
    d = clock();
    // data.print();
    std::cout << "In-place merge sort run time: " << (double)(d - c) / CLOCKS_PER_SEC << "s" << std::endl;
}

int main()
{
    TestGen();
    return 0;
}
