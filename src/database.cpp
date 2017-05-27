#include "database.h"
#include <vector>
#include <stack>
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
            mergeSort(key, low, mid, order);
            mergeSort(key, mid + 1, high, order);
            int i = low, j = mid + 1, len = high - low + 1;
            std::vector<int> sub;
            while (i <= mid || j <= high){
                if (i <= mid && j <= high) {
                    if (getData(order[i], key) <= getData(order[j], key))
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
        auto order = getOrder();
        mergeSort(key, 0, recnum - 1, order);
        setOrder(order);
        return *this;
    }

    LinkData &LinkData::mergeSort_LSD()
    {
        for (auto i = keynum; i != 0; )
            mergeSort(--i);
        return *this;
    }

    LinkData &LinkData::mergeSort_MSD()
    {
        return sort_MSD(0);
    }

    LinkData &LinkData::radixSort(int key, int low, int high, std::vector<int> &order)
    // radix sort in range(order[low], order[high])
    // sort by changing vector order
    // a helper function
    {
        int numLength = getLength(MAX_DATA_NUM);
        for (int pos = 0; pos != numLength; pos++) {
            // distribution part
            std::vector<std::vector<int>> collect(NUM_BASE);
            for (int i = low; i <= high; i++){
                auto rec = order[i];
                collect[getDigit(getData(rec, key), pos)].push_back(rec);
            }
            // collection part
            unsigned i = low;
            for (auto col: collect)
                for (auto pos: col)
                    order[i++] = pos;
        }
        return *this;
    }

    LinkData &LinkData::radixSort(int key)
    // radix sort according to keys[key]
    {
        auto order = getOrder();
        radixSort(key, 0, recnum - 1, order);
        setOrder(order);
        return *this;
    }

    LinkData &LinkData::radixSort_LSD()
    // LSD radix sort
    {
        for (auto i = keynum; i != 0; )
            radixSort(--i);
        return *this;
    }

    LinkData &LinkData::radixSort_MSD()
    // MSD radix sort
    {
        return sort_MSD(1);
    }

    LinkData &LinkData::sort_MSD(int type)
    // type == 0: merge sort
    // type == 1: radix sort
    {
        if (keynum != 0){
            auto order = getOrder();
            std::stack<int> from, to;
            from.push(order[0]);
            to.push(order[recnum - 1]);
            for (unsigned i = 0; (!from.empty()) && i != keynum; i++){
                while (!from.empty()){
                    if (type == 0)
                        mergeSort(i, from.top(), to.top(), order);
                    else if (type == 1)
                        radixSort(i, from.top(), to.top(), order);
                    from.pop();
                    to.pop();
                }
                // update regions of recursion
                unsigned low = 0;
                for (unsigned j = 0; j != recnum; j++)
                    if (j == recnum - 1 && j != low){
                        from.push(low);
                        to.push(j);
                    }
                    else if (j != recnum - 1){
                        auto left = getData(order[j], i), right = getData(order[j + 1], i);
                        if (left != right){
                            if (j != low){
                                from.push(low);
                                to.push(j);
                            }
                            low = j + 1;
                        }
                    }
            }
            setOrder(order);
        }
        return *this;
    }
}
