#include "database.h"
#include <vector>

namespace Database
{
    inline int intPower(int a, int n)
    {
        int result = 1;
        for (; n > 0; n--)
            result *= a;
        return result;
    }

    inline int getDigit(LinkRecord r, int key, int k)
    {
        return (r.getData(key) / intPower(NUM_BASE, k)) % NUM_BASE;
    }

    inline int getDigit(int num, int key, int k)
    {
        return (num / intPower(NUM_BASE, k)) % NUM_BASE;
    }

    inline int getLength(int num)
    {
        int len;
        for (len = 0; num > 0; len++)
            num /= NUM_BASE;
        return len;
    }

    LinkData &LinkData::mergeSort(int key)
    {
        /* TO BE COMPLETED */
        return *this;
    }

    LinkData &LinkData::mergeSort()
    {
        for (auto i = this->keynum; i != 0; )
            (*this).mergeSort(--i);
        return *this;
    }

    std::vector<std::vector<int>> Distribute(LinkData D, int key, int pos)
    {
        std::vector<std::vector<int>> result(NUM_BASE);
        std::vector<LinkRecord> data = D.getData();
        for (int i = D.getHead(); i != EMPTY_TAIL; i = data[i].getNext()){
            //std::cout << i << "qqq" << data[i].getData(key) << " asad" << key << std::endl;
            result[getDigit(data[i], key, pos)].push_back(i);
        }
        return result;
    }

    void Collect(LinkData &D, std::vector<std::vector<int>> info)
    {
        int previous;
        for (int i = 0; i != NUM_BASE; i++)
            if (info[i].size() > 0) {
                D.setHead(info[i][0]);
                previous = info[i][0];
                info[i].erase(info[i].begin());
                break;
            }
        for (int i = 0; i != NUM_BASE; i++) {
            for (unsigned j = 0; j != info[i].size(); j++) {
                D.setNext(previous, info[i][j]);
                previous = info[i][j];
            }
        }
        D.setNext(previous, EMPTY_TAIL);
    }

    LinkData &LinkData::radixSort(int key)
    {
        int numLength = getLength(MAX_DATA_NUM);
        for (int i = keynum - 1; i >= 0; i--) {
            for (int j = 0; j != numLength; j++) {
                auto result = Distribute(*this, i, j);
                Collect(*this, result);
            }
        }
        return *this;
    }

    LinkData &LinkData::radixSort()
    {
        if (this->recnum != 0)
            for (auto i = this->keynum; i != 0; )
                (*this).radixSort(--i);
        return *this;
    }
}
