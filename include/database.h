#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <stdexcept>
#include <iomanip>
#include <iostream>

// const unsigned MAX_KEY_NUM = 5;
// const unsigned MAX_RECORD_NUM = 10000;

typedef unsigned int KeyType;
const KeyType MAX_DATA_NUM = 256;
const KeyType NUM_BASE = 10;
const int EMPTY_NEXT = -1;

namespace Database
{
    class LinkRecord
    {
        //friend class LinkData;
    public:
        // constructors
        LinkRecord() = default;
        LinkRecord(std::vector<KeyType> data): keys(data) { }
        LinkRecord(std::vector<KeyType> data, int nextVal)
            : keys(data), next(nextVal) { }
        // methods
        std::vector<KeyType> getData() const { return keys; }
        KeyType getData(int n) const { return keys[n]; }
        int getNext() const { return next; }
        LinkRecord &setNext(unsigned pos) { next = pos; return *this; }
        const LinkRecord &print() const;
        LinkRecord &print();
    private:
        std::vector<KeyType> keys;
        int next = EMPTY_NEXT;
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
}


namespace Database
{
    class LinkData
    {
    public:
        // constructors
        LinkData() = default;
        LinkData(int key): keynum(key) { }
        // methods
        int getKeyNum() const { return keynum; }
        int getRecNum() const { return recnum; }
        std::vector<LinkRecord> getData() const { return records; }
        LinkRecord getData(int n) const { return records[n]; }
        KeyType getData(int n, int key) const { return records[n].getData(key); }
        int getHead() const { return head; }
        int getTail() const { return tail; }
        int getMid() const;
        int getMid(int, int) const;
        bool empty() const { return recnum == 0; };
        LinkData &add(std::vector<KeyType>);
        LinkData &setKeyNum(int);
        LinkData &setHead(unsigned);
        LinkData &setNext(unsigned, unsigned);
        const LinkData &print() const;
        LinkData &print();
        LinkData &mergeSort();
        LinkData &mergeSort(int);
        LinkData &radixSort();
        LinkData &radixSort(int);
        std::vector<int> getOrder() const;
        LinkData &setOrder(std::vector<int>);
    private:
        std::vector<LinkRecord> records;   // records
        unsigned keynum = 0;               // number of keys
        unsigned recnum = 0;               // number of records
        int head = -1;
        int tail = EMPTY_NEXT;
        LinkData &mergeSort(int, int, int, std::vector<int> &);
    };

    class multiple_assignments: public std::logic_error {
    public:
        explicit multiple_assignments(const std::string &s): std::logic_error(s) {}
    };

    class index_mismatch: public std::logic_error {
    public:
        explicit index_mismatch(const std::string &s): std::logic_error(s) {}
    };

    inline int LinkData::getMid() const
    {
        return getMid(head, tail);
    }

    inline int LinkData::getMid(int low, int high) const
    {
        int num = 0, pos;
        for (pos = low; pos != high; pos = records[pos].getNext())
            num++;
        num /= 2;
        for (pos = low; num > 0; pos = records[pos].getNext())
            num--;
        return pos;
    }

    inline LinkData &LinkData::setKeyNum(int num)
    {
        keynum = num;
        return *this;
    }

    inline LinkData &LinkData::setHead(unsigned index)
    {
        head = index;
        return *this;
    }

    inline LinkData &LinkData::setNext(unsigned i, unsigned pos)
    {
        records[i].setNext(pos);
        return *this;
    }

    inline LinkData &LinkData::add(std::vector<KeyType> data)
    {
        records.push_back(LinkRecord(data));
        if (head == -1)
            head = tail = 0;
        else {
            records[tail].setNext(recnum);
            tail = recnum;
        }
        recnum++;
        return *this;
    }

    inline LinkData &LinkData::print()
    {
        if (!this->empty())
            for (int i = head; i != EMPTY_NEXT; i = records[i].getNext()){
                records[i].print();
                std::cout << "\n";
            }
        return *this;
    }

    inline const LinkData &LinkData::print() const
    {
        if (!this->empty())
            for (int i = head; i != EMPTY_NEXT; i = records[i].getNext()){
                records[i].print();
                std::cout << "\n";
            }
        return *this;
    }

    inline std::vector<int> LinkData::getOrder() const
    {
        std::vector<int> order;
        if (recnum != 0)
            for (int i = head; i != EMPTY_NEXT; i = records[i].getNext())
                order.push_back(i);
        return order;
    }

    inline LinkData &LinkData::setOrder(std::vector<int> order)
    {
        if (recnum != 0){
            head = order[0];
            tail = order[recnum - 1];
            for (unsigned i = 0; i != recnum - 1; i++)
                records[order[i]].setNext(order[i + 1]);
            records[order[recnum - 1]].setNext(EMPTY_NEXT);
        }
        return *this;
    }

}

#endif // DATABASE_H
