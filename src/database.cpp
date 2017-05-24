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

    inline int getDigit(int num, int k)
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

    LinkData &LinkData::mergeSort(int key, int low, int high, std::vector<int> &order)
    {
        if (low < high) {
            int mid = (low + high) / 2;
            this->mergeSort(key, low, mid, order);
            this->mergeSort(key, mid + 1, high, order);
            int i = low, j = mid + 1, len = high - low + 1;
            std::vector<int> sub;
            while (i <= mid || j <= high){
                if (i <= mid && j <= high) {
                    if (this->getData(order[i], key) <= this->getData(order[j], key))
                        sub.push_back(order[i++]);
                    else
                        sub.push_back(order[j++]);
                }
                else if (i <= mid)
                    sub.push_back(order[i++]);
                else
                    sub.push_back(order[j++]);
            }
            for (i = 0; i != len; i++)
                order[low + i] = sub[i];
        }
        return *this;
    }

    LinkData &LinkData::mergeSort(int key)
    {
        auto order = this->getOrder();
        this->mergeSort(key, 0, recnum - 1, order);
        this->setOrder(order);
        return *this;
    }

    LinkData &LinkData::mergeSort()
    {
        for (auto i = this->keynum; i != 0; )
            (*this).mergeSort(--i);
        return *this;
    }

    LinkData &LinkData::radixSort(int key)
    {
        auto order = this->getOrder();
        int numLength = getLength(MAX_DATA_NUM);
        for (int pos = 0; pos != numLength; pos++) {
            // distribute part
            std::vector<std::vector<int>> collect(NUM_BASE);
            for (auto rec: order)
                collect[getDigit(this->getData(rec, key), pos)].push_back(rec);
            // collect part
            unsigned i = 0;
            for (auto col: collect)
                for (auto pos: col)
                    order[i++] = pos;
        }
        this->setOrder(order);
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
