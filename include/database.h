#ifndef DATABASE_H
#define DATABASE_H

#include <vector>

namespace Database
{
    typedef unsigned int KeyType;
    const KeyType MAX_DATA_NUM = 256;
    const KeyType NUM_BASE = 10;
    const int EMPTY_NEXT = -1;
}

namespace Database
{
    class LinkRecord
    {
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
        LinkRecord &setData(unsigned n, KeyType d) { keys[n] = d; return *this; }
        const LinkRecord &print() const;
        LinkRecord &print();
    private:
        std::vector<KeyType> keys;
        int next = EMPTY_NEXT;
    };
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
        bool empty() const { return recnum == 0; }
        LinkData &add(const std::vector<KeyType> &);
        LinkData &setKeyNum(int);
        LinkData &setHead(unsigned);
        LinkData &setNext(unsigned, unsigned);
        const LinkData &print() const;
        LinkData &print();
        LinkData &mergeSort_LSD();
        LinkData &mergeSort_MSD();
        LinkData &mergeSort(int);
        LinkData &mergeSort_LSD(const std::vector<unsigned> &);
        LinkData &mergeSort_MSD(const std::vector<unsigned> &);
        LinkData &radixSort_LSD();
        LinkData &radixSort_MSD();
        LinkData &radixSort(int);
        LinkData &radixSort_LSD(const std::vector<unsigned> &);
        LinkData &radixSort_MSD(const std::vector<unsigned> &);
        std::vector<int> getOrder() const;
        LinkData &setOrder(const std::vector<int> &);
        LinkData &resetOrder();
    private:
        std::vector<LinkRecord> records;   // records
        unsigned keynum = 0;               // number of keys
        unsigned recnum = 0;               // number of records
        int head = -1;
        int tail = EMPTY_NEXT;

        LinkData &mergeSort(int, int, int, std::vector<int> &);
        LinkData &radixSort(int, int, int, std::vector<int> &);
        LinkData &sort_MSD(int);
        LinkData &sort_MSD(int, const std::vector<unsigned> &);
        KeyType getData(int n, int key) const { return records[n].getData(key); }
    };

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
}

#endif // DATABASE_H
