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
    int keynum, recnum;
    // std::cout << "Size of test cases: ";
    std::cin >> keynum >> recnum;
    // std::cout << "We will randomly generate the test cases";
    Database::LinkData data;
    data.setKeyNum(keynum);
    for (int i = 0; i != recnum; i++) {
        auto temp = RandomGen::randUnsgnIntVec(1, MAX_DATA_NUM, 5);
        data.add(temp);
    }
    // std::cout << "Generated test cases: \n";
    data.print();
    // std::cout << "Running radix sort...\n";
    printSplitForPy();
    clock_t a = clock(), b;
    data.radixSort();
    b = clock();
    data.print();
    // std::cout << "Radix sort run time: " << (double)(b - a) / CLOCKS_PER_SEC << "s\n";
    printSplitForPy();
    std::cout << (double)(b - a) / CLOCKS_PER_SEC;
    printSplitForPy();
    // std::cout << "Running merge sort...\n";
    clock_t c = clock(), d;
    data.mergeSort();
    d = clock();
    data.print();
    // std::cout << "In-place merge sort run time: " << (double)(d - c) / CLOCKS_PER_SEC << "s\n";
    printSplitForPy();
    std::cout << (double)(d - c) / CLOCKS_PER_SEC;
}

int main()
{
    RunAll();
    return 0;
}
