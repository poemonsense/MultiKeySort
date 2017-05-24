#include "random.h"
#include "database.h"
#include <iostream>
#include <ctime>

void printSplitForPy()
{
    std::cout << "Python";
}

void RunAll()
{
    int func, keynum, recnum;
    std::cin >> func >> keynum >> recnum;
    Database::LinkData data1, data2;
    data1.setKeyNum(keynum);
    data2.setKeyNum(keynum);
    if (func == 0){
        for (int i = 0; i != recnum; i++) {
            auto temp = RandomGen::randUnsgnIntVec(1, MAX_DATA_NUM, 5);
            data1.add(temp);
            data2.add(temp);
        }
    }
    if (func == 0){
        data1.print();
        printSplitForPy();
    }
    clock_t a = clock(), b;
    data1.radixSort();
    b = clock();
    if (func == 0){
        data1.print();
        printSplitForPy();
    }
    std::cout << (double)(b - a) / CLOCKS_PER_SEC;
    printSplitForPy();
    clock_t c = clock(), d;
    data2.mergeSort();
    d = clock();
    if (func == 0){
        data2.print();
        printSplitForPy();
    }
    std::cout << (double)(d - c) / CLOCKS_PER_SEC;
}

int main()
{
    RunAll();
    return 0;
}
