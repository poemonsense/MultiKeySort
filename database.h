#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <stdexcept>
#include <iomanip>
#include <iostream>

// const unsigned MAX_KEY_NUM = 5;
// const unsigned MAX_RECORD_NUM = 10000;

typedef unsigned int KeyType;

namespace Database
{

    class LinkRecord
    {
    public:
        // constructors
        LinkRecord() = default;
        LinkRecord(std::vector<KeyType> data): keys(data) { }
        LinkRecord(std::vector<KeyType> data, int nextVal)
            : keys(data), next(nextVal) { }
        // methods
        std::vector<KeyType> getData() const { return keys; }
        int getNext() const { return next; }
        const LinkRecord &print() const;
        LinkRecord &print();
    private:
        std::vector<KeyType> keys;
        int next = -1;
    };

    inline LinkRecord &LinkRecord::print()
    {
        for (unsigned i = 0; i != keys.size(); i++)
            std::cout << std::setw(3) << keys[i] << "  ";
        return *this;
    }

    inline const LinkRecord &LinkRecord::print() const
    {
        for (unsigned i = 0; i != keys.size(); i++)
            std::cout << std::setw(3) << keys[i] << "  ";
        return *this;
    }

    class LinkData
    {
    public:
        // constructors
        LinkData() = default;
        LinkData(int key): keynum(key) { }
        // methods
        int getKeyNum() const { return keynum; }
        int getRecNum() const { return recnum; }
        LinkData &add(std::vector<KeyType>);
        LinkData &setKeyNum(int num);
        const LinkData &print() const;
        LinkData &print();
        LinkData &mergeSort();
        LinkData &mergeSort(int);
        LinkData &radixSort();
        LinkData &radixSort(int);
    private:
        std::vector<LinkRecord> records;   // records
        unsigned keynum = 0;               // number of keys
        unsigned recnum = 0;               // number of records
    };

    inline LinkData &LinkData::add(std::vector<KeyType> data)
    {
        if (data.size() != keynum)
            throw std::runtime_error("Invalid vector length");
        records.push_back(LinkRecord(data));
        recnum++;
        return *this;
    }

    inline LinkData &LinkData::setKeyNum(int num)
    {
        if (keynum != 0)
            throw std::runtime_error("Keynum can be set only one time");
        keynum = num;
        return *this;
    }

    inline LinkData &LinkData::print()
    {
        for (unsigned i = 0; i != records.size(); i++) {
            records[i].print();
            std::cout << "\n";
        }
        return *this;
    }

    inline const LinkData &LinkData::print() const
    {
        for (unsigned i = 0; i != records.size(); i++) {
            records[i].print();
            std::cout << "\n";
        }
        return *this;
    }

}

#endif // DATABASE_H
