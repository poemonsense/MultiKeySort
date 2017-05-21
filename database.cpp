#include "database.h"

namespace Database
{
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

    LinkData &LinkData::radixSort(int key)
    {
        return *this;
    }

    LinkData &LinkData::radixSort()
    {
        for (auto i = this->keynum; i != 0; )
            (*this).radixSort(--i);
        return *this;
    }
}
