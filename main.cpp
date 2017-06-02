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
    // func 0: randomly generate, print it out
    // func 1: randomly generate, do not print it out
    // func 2: manually generate, print it out
    int func, keynum, recnum;
    std::cin >> func >> keynum >> recnum;
    std::vector<unsigned> priority;
    unsigned key;
    for (int i = 0; i != keynum; i++){
        std::cin >> key;
        priority.push_back(key);
    }
    Database::LinkData data;
    data.setKeyNum(keynum);
    for (int i = 0; i != recnum; i++){
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
        data.add(temp);
    }
    if (func == 0 || func == 3){
        data.print();
        printSplitForPy();
    }

    clock_t a, b;

    /* Testing radixSort_LSD */
    a = clock();
    data.radixSort_LSD(priority);
    b = clock();
    if (func == 0 || func == 3){
        data.print();
        printSplitForPy();
    }
    data.resetOrder();
    std::cout << (double)(b - a) / CLOCKS_PER_SEC;
    printSplitForPy();

    /* Testing radixSort_MSD */
    a = clock();
    data.radixSort_MSD(priority);
    b = clock();
    if (func == 0 || func == 3){
        data.print();
        printSplitForPy();
    }
    data.resetOrder();
    std::cout << (double)(b - a) / CLOCKS_PER_SEC;
    printSplitForPy();

    /* Testing mergeSort_LSD */
    a = clock();
    data.mergeSort_LSD(priority);
    b = clock();
    if (func == 0 || func == 3){
        data.print();
        printSplitForPy();
    }
    data.resetOrder();
    std::cout << (double)(b - a) / CLOCKS_PER_SEC;
    printSplitForPy();

    /* Testing mergeSort_MSD */
    a = clock();
    data.mergeSort_MSD(priority);
    b = clock();
    if (func == 0 || func == 3){
        data.print();
        printSplitForPy();
    }
    std::cout << (double)(b - a) / CLOCKS_PER_SEC;

}

int main()
{
    RunAll();
    return 0;
}
