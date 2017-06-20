#include "random.h"
#include "database.h"
#include <iostream>
#include <chrono>

void printSplitForPy()
{
    std::cout << "*";
}

void RunAll()
{
    // func 0: randomly generate, print it out
    // func 1: randomly generate, do not print it out
    // func 2: manually generate, print it out
    // func 3: for .exe test
    int func;
    std::cin >> func;
    if (func == 0) {
        int keynum, recnum;
        std::cin >> keynum >> recnum;
        std::vector<unsigned> priority;
        unsigned key;
        for (int i = 0; i != keynum; i++){
            std::cin >> key;
            priority.push_back(key);
        }
        Database::MyDatabase data;
        data.setKeyNum(keynum);
        for (int i = 0; i != recnum; i++){
            std::vector<unsigned> temp;
            temp = RandomGen::randUnsgnIntVec(1, Database::MAX_DATA_NUM, keynum);
            data.add(temp);
        }
        data.print();
        printSplitForPy();
        auto a = std::chrono::steady_clock::now();
        /* Testing radixSort_LSD */
        data.radixSort_LSD(priority);
        auto b = std::chrono::steady_clock::now();
        data.print();
        printSplitForPy();
        data.resetOrder();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0;
        printSplitForPy();
        /* Testing radixSort_MSD */
        a = std::chrono::steady_clock::now();
        data.radixSort_MSD(priority);
        b = std::chrono::steady_clock::now();
        data.print();
        printSplitForPy();
        data.resetOrder();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0;
        printSplitForPy();
        /* Testing mergeSort_LSD */
        a = std::chrono::steady_clock::now();
        data.mergeSort_LSD(priority);
        b = std::chrono::steady_clock::now();
        data.print();
        printSplitForPy();
        data.resetOrder();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0;
        printSplitForPy();
        /* Testing mergeSort_MSD */
        a = std::chrono::steady_clock::now();
        data.mergeSort_MSD(priority);
        b = std::chrono::steady_clock::now();
        data.print();
        printSplitForPy();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0;
    }
    else if (func == 1) {
        int keynum, recnum;
        std::cin >> keynum >> recnum;
        std::vector<unsigned> priority;
        unsigned key;
        for (int i = 0; i != keynum; i++){
            std::cin >> key;
            priority.push_back(key);
        }
        Database::MyDatabase data;
        data.setKeyNum(keynum);
        for (int i = 0; i != recnum; i++){
            std::vector<unsigned> temp;
            temp = RandomGen::randUnsgnIntVec(1, Database::MAX_DATA_NUM, keynum);
            data.add(temp);
        }
        auto a = std::chrono::steady_clock::now();
        /* Testing radixSort_LSD */
        data.radixSort_LSD(priority);
        auto b = std::chrono::steady_clock::now();
        data.resetOrder();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0;
        printSplitForPy();
        /* Testing radixSort_MSD */
        a = std::chrono::steady_clock::now();
        data.radixSort_MSD(priority);
        b = std::chrono::steady_clock::now();
        data.resetOrder();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0;
        printSplitForPy();
        /* Testing mergeSort_LSD */
        a = std::chrono::steady_clock::now();
        data.mergeSort_LSD(priority);
        b = std::chrono::steady_clock::now();
        data.resetOrder();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0;
        printSplitForPy();
        /* Testing mergeSort_MSD */
        a = std::chrono::steady_clock::now();
        data.mergeSort_MSD(priority);
        b = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0;
    }
    else if (func == 2){
        int keynum, recnum;
        std::cin >> keynum >> recnum;
        std::vector<unsigned> priority;
        unsigned key;
        for (int i = 0; i != keynum; i++){
            std::cin >> key;
            priority.push_back(key);
        }
        Database::MyDatabase data;
        data.setKeyNum(keynum);
        for (int i = 0; i != recnum; i++){
            std::vector<unsigned> temp;
            if (func == 2){
                unsigned x;
                for (int j = 0; j != keynum; j++){
                    std::cin >> x;
                    temp.push_back(x);
                }
            }
            data.add(temp);
        }
        data.print();
        printSplitForPy();
        auto a = std::chrono::steady_clock::now();
        /* Testing radixSort_LSD */
        data.radixSort_LSD(priority);
        auto b = std::chrono::steady_clock::now();
        data.print();
        printSplitForPy();
        data.resetOrder();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0;
        printSplitForPy();
        /* Testing radixSort_MSD */
        a = std::chrono::steady_clock::now();
        data.radixSort_MSD(priority);
        b = std::chrono::steady_clock::now();
        data.print();
        printSplitForPy();
        data.resetOrder();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0;
        printSplitForPy();
        /* Testing mergeSort_LSD */
        a = std::chrono::steady_clock::now();
        data.mergeSort_LSD(priority);
        b = std::chrono::steady_clock::now();
        data.print();
        printSplitForPy();
        data.resetOrder();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0;
        printSplitForPy();
        /* Testing mergeSort_MSD */
        a = std::chrono::steady_clock::now();
        data.mergeSort_MSD(priority);
        b = std::chrono::steady_clock::now();
        data.print();
        printSplitForPy();
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0;
    }
    else if (func == 3){
        std::cout << "In-place Multi-key Sort Demonstration\n";
        std::cout << "Developers: Xu Yinan, Zhang Yuanhang, Li Xie\n\n";
        std::cout << "Enter keynum: ";
        int keynum, recnum;
        std::cin >> keynum;
        std::cout << "Enter recnum: ";
        std::cin >> recnum;
        std::cout << "Enter priority in range [0, " << (keynum - 1) << "]: ";
        std::vector<unsigned> priority;
        unsigned key;
        for (int i = 0; i != keynum; i++){
            std::cin >> key;
            priority.push_back(key);
        }
        std::cout << "\nGenerating random data...";
        Database::MyDatabase data;
        data.setKeyNum(keynum);
        for (int i = 0; i != recnum; i++){
            std::vector<unsigned> temp;
            temp = RandomGen::randUnsgnIntVec(1, Database::MAX_DATA_NUM, keynum);
            data.add(temp);
        }
        std::cout << "Completed! \nPrint the generated data (y or Y)? ";
        char s;
        std::cin >> s;
        if (s == 'y' || s == 'Y')
            data.print();
        /* Testing radixSort_LSD */
        std::cout << "\nRunning LSD Radix Sort...";
        auto a = std::chrono::steady_clock::now();
        data.radixSort_LSD(priority);
        auto b = std::chrono::steady_clock::now();
        std::cout << "Completed! \nTime usage: ";
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0 << " s\n";
        std::cout << "Print the sorted data (y or Y)? ";
        std::cin >> s;
        if (s == 'y' || s == 'Y')
            data.print();
        data.resetOrder();
        /* Testing radixSort_MSD */
        std::cout << "\nRunning MSD Radix Sort...";
        a = std::chrono::steady_clock::now();
        data.radixSort_MSD(priority);
        b = std::chrono::steady_clock::now();
        std::cout << "Completed! \nTime usage: ";
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0 << " s\n";
        std::cout << "Print the sorted data (y or Y)? ";
        std::cin >> s;
        if (s == 'y' || s == 'Y')
            data.print();
        data.resetOrder();
        /* Testing mergeSort_LSD */
        std::cout << "\nRunning LSD Merge Sort...";
        a = std::chrono::steady_clock::now();
        data.mergeSort_LSD(priority);
        b = std::chrono::steady_clock::now();
        std::cout << "Completed! \nTime usage: ";
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0 << " s\n";
        std::cout << "Print the sorted data (y or Y)? ";
        std::cin >> s;
        if (s == 'y' || s == 'Y')
            data.print();
        data.resetOrder();
        /* Testing mergeSort_MSD */
        std::cout << "\nRunning MSD Merge Sort...";
        a = std::chrono::steady_clock::now();
        data.mergeSort_MSD(priority);
        b = std::chrono::steady_clock::now();
        std::cout << "Completed! \nTime usage: ";
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count() / 1000.0 << " s\n";
        std::cout << "Print the sorted data (y or Y)? ";
        std::cin >> s;
        if (s == 'y' || s == 'Y')
            data.print();
        data.resetOrder();
        std::cout << "\nDemonstration finished!\n";
        std::cout << "For further analysis, run the provided Python script. \nThanks. \n";
    }
}

int main()
{
    RunAll();
    return 0;
}
