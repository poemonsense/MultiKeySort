#include "database.h"
#include <vector>

namespace Database
{
    inline int intPower(int a, int n)  // return a**n
    {
        int result = 1;
        for (; n > 0; n--)
            result *= a;
        return result;
    }

    inline int getDigit(LinkRecord r, int key, int k)
    {
        return (r.getData(key) / intPower(10, k)) % 10;
    }

    inline int getDigit(int num, int key, int k)
    {
        return (num / intPower(10, k)) % 10;
    }

    inline int getLength(int num)
    {
        int len;
        for (len = 0; num > 0; len++)
            num /= 10;
        return len;
    }
    LinkData &LinkData::mergeSort(int key)
    {
        return *this;
    }

    LinkData &LinkData::mergeSort()
    {
        for (auto i = this->keynum; i != 0; )
            (*this).mergeSort(--i);
        return *this;
    }

    std::vector<std::vector<unsigned>> Distribute(LinkData D, int key, int pos)
    {
        std::vector<std::vector<unsigned>> result(10);
        auto data = D.getData();
        for (int i = D.getHead(); i != -1; i = data[i].getNext())
            result[getDigit(data[i], key, pos)].push_back(i);
        return result;
    }

    void Collect(LinkData &D, std::vector<std::vector<unsigned>> info)
    {
        ;
    }

    LinkData &LinkData::radixSort(int key)
    {
        int numLength = getLength(MAX_DATA_NUM);
        for (int i = keynum - 1; i >= 0; i--) {
            for (int j = 0; j != numLength; j++) {
                auto result = Distribute(*this, keynum, j);
                Collect(*this, result);
            }
        }
        return *this;
    }

    LinkData &LinkData::radixSort()
    {
        for (auto i = this->keynum; i != 0; )
            (*this).radixSort(--i);
        return *this;
    }
}
