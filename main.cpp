#include "random.h"
#include "database.h"
#include <iostream>
#include <chrono>

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

    auto a = std::chrono::steady_clock::now();
    /* Testing radixSort_LSD */
    data.radixSort_LSD(priority);
    auto b = std::chrono::steady_clock::now();
    if (func == 0 || func == 3){
        data.print();
        printSplitForPy();
    }
    data.resetOrder();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0;
    printSplitForPy();

    /* Testing radixSort_MSD */
    a = std::chrono::steady_clock::now();
    data.radixSort_MSD(priority);
    b = std::chrono::steady_clock::now();
    if (func == 0 || func == 3){
        data.print();
        printSplitForPy();
    }
    data.resetOrder();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0;
    printSplitForPy();

    /* Testing mergeSort_LSD */
    a = std::chrono::steady_clock::now();
    data.mergeSort_LSD(priority);
    b = std::chrono::steady_clock::now();
    if (func == 0 || func == 3){
        data.print();
        printSplitForPy();
    }
    data.resetOrder();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0;
    printSplitForPy();

    /* Testing mergeSort_MSD */
    a = std::chrono::steady_clock::now();
    data.mergeSort_MSD(priority);
    b = std::chrono::steady_clock::now();
    if (func == 0 || func == 3){
        data.print();
        printSplitForPy();
    }
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0;

}

int main()
{
    RunAll();
    return 0;
}
