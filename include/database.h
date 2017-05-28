#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <stdexcept>
#include <iomanip>
#include <iostream>

namespace Database
{

    typedef unsigned int KeyType;
    const KeyType MAX_DATA_NUM = 256;
    const KeyType NUM_BASE = 10;
    const int EMPTY_NEXT = -1;

    class LinkRecord
    {
        //friend class LinkData;
    public:
        // constructors
        LinkRecord() = default;
        LinkRecord(const std::vector<KeyType> &data): keys(data) { }
        LinkRecord(const std::vector<KeyType> &data, int nextVal)
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
        for (auto out: keys)
            std::cout << std::setw(3) << out << "  ";
        return *this;
    }

    inline const LinkRecord &LinkRecord::print() const
    {
        for (auto out: keys)
            std::cout << std::setw(3) << out << "  ";
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
        int getHead() const { return head; }
        int getTail() const { return tail; }
        int getMid() const;
        int getMid(int, int) const;
        bool empty() const { return recnum == 0; };
        LinkData &add(const std::vector<KeyType> &);
        LinkData &setKeyNum(int);
        LinkData &setHead(unsigned);
        LinkData &setNext(unsigned, unsigned);
        const LinkData &print() const;
        LinkData &print();
        LinkData &mergeSort_LSD();
        LinkData &mergeSort_MSD();
        LinkData &mergeSort(int);
        LinkData &radixSort_LSD();
        LinkData &radixSort_MSD();
        LinkData &radixSort(int);
        std::vector<int> getOrder() const;
        LinkData &setOrder(const std::vector<int> &);
    private:
        std::vector<LinkRecord> records;   // records
        unsigned keynum = 0;               // number of keys
        unsigned recnum = 0;               // number of records
        int head = -1;
        int tail = EMPTY_NEXT;
        LinkData &mergeSort(int, int, int, std::vector<int> &);
        LinkData &radixSort(int, int, int, std::vector<int> &);
        LinkData &sort_MSD(int);
        KeyType getData(int n, int key) const { return records[n].getData(key); }
    };

    inline int LinkData::getMid() const
    {
        return getMid(head, tail);
    }

    inline int LinkData::getMid(int low, int high) const
    {
        std::vector<int> order;
        if (recnum != 0){
            unsigned short finish = 0;
            int left, right;
            for (int i = head, num = 0; i != EMPTY_NEXT && finish != 2; i = records[i].getNext(), num++){
                order.push_back(i);
                if (i == low){
                    left = num;
                    finish++;
                }
                if (i == high){
                    right = num;
                    finish++;
                }
            }
            if (finish != 2)
                return -1;
            else
                return order[(right + left) / 2];
        }
        else
            return -1;
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

    inline LinkData &LinkData::add(const std::vector<KeyType> &data)
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

    inline LinkData &LinkData::setOrder(const std::vector<int> &order)
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
