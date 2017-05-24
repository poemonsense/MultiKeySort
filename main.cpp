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
    Database::LinkData data;
    data.setKeyNum(keynum);
    if (func == 0){
        for (int i = 0; i != recnum; i++) {
            auto temp = RandomGen::randUnsgnIntVec(1, MAX_DATA_NUM, 5);
            data.add(temp);
        }
    }
    if (func == 0){
        data.print();
        printSplitForPy();
    }
    clock_t a = clock(), b;
    data.radixSort();
    b = clock();
    if (func == 0){
        data.print();
        printSplitForPy();
    }
    std::cout << (double)(b - a) / CLOCKS_PER_SEC;
    printSplitForPy();
    clock_t c = clock(), d;
    data.mergeSort();
    d = clock();
    if (func == 0){
        data.print();
        printSplitForPy();
    }
    std::cout << (double)(d - c) / CLOCKS_PER_SEC;
}

int main()
{
    RunAll();
    return 0;
}
