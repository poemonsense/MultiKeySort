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
    // func 0: randomly generate, print the database
    // func 1: randomly generate, do not print the database
    // func 2: manually generate, print the database
    int func, keynum, recnum;
    std::cin >> func >> keynum >> recnum;
    Database::LinkData data1, data2, data3, data4;
    data1.setKeyNum(keynum);
    data2.setKeyNum(keynum);
    data3.setKeyNum(keynum);
    data4.setKeyNum(keynum);
    for (int i = 0; i != recnum; i++) {
        std::vector<unsigned> temp;
        if (func == 3){
            unsigned x;
            for (int j = 0; j != keynum; j++){
                std::cin >> x;
                temp.push_back(x);
            }
        }
        else
            temp = RandomGen::randUnsgnIntVec(1, Database::MAX_DATA_NUM, keynum);
        data1.add(temp);
        data2.add(temp);
        data3.add(temp);
        data4.add(temp);
    }
    if (func == 0 || func == 3){
        data1.print();
        printSplitForPy();
    }

    clock_t a = clock(), b;
    data1.radixSort_LSD();
    b = clock();
    if (func == 0 || func == 3){
        data1.print();
        printSplitForPy();
    }

    std::cout << (double)(b - a) / CLOCKS_PER_SEC;
    printSplitForPy();

    a = clock();
    data2.radixSort_MSD();
    b = clock();
    if (func == 0 || func == 3){
        data2.print();
        printSplitForPy();
    }

    std::cout << (double)(b - a) / CLOCKS_PER_SEC;
    printSplitForPy();

    a = clock();
    data3.mergeSort_LSD();
    b = clock();
    if (func == 0 || func == 3){
        data3.print();
        printSplitForPy();
    }

    std::cout << (double)(b - a) / CLOCKS_PER_SEC;
    printSplitForPy();

    a = clock();
    data4.mergeSort_MSD();
    b = clock();
    if (func == 0 || func == 3){
        data4.print();
        printSplitForPy();
    }

    std::cout << (double)(b - a) / CLOCKS_PER_SEC;
}

int main()
{
    RunAll();
    return 0;
}
