#ifndef DATABASE_H
#define DATABASE_H

#include <vector>

namespace Database
{
    typedef unsigned int KeyType;
    const KeyType MAX_DATA_NUM = 999;
    const KeyType NUM_BASE = 10;
    const int EMPTY_NEXT = -1;
}

namespace Database
{
    class MyRecord
    {
    public:
        // constructors
        MyRecord() = default;
        MyRecord(const std::vector<KeyType> &data): keys(data) { }
        MyRecord(const std::vector<KeyType> &data, int nextVal)
            : keys(data), next(nextVal) { }
        // methods
        std::vector<KeyType> getData() const { return keys; }
        KeyType getData(int n) const { return keys[n]; }
        int getNext() const { return next; }
        MyRecord &setNext(unsigned pos) { next = pos; return *this; }
        MyRecord &setData(unsigned n, KeyType d) { keys[n] = d; return *this; }
        const MyRecord &print() const;
        MyRecord &print();
    private:
        std::vector<KeyType> keys;
        int next = EMPTY_NEXT;
    };
}


namespace Database
{
    class MyDatabase
    {
    public:
        // constructors
        MyDatabase() = default;
        MyDatabase(int key): keynum(key) { }
        // methods
        int getKeyNum() const { return keynum; }
        int getRecNum() const { return recnum; }
        std::vector<MyRecord> getData() const { return records; }
        MyRecord getData(int n) const { return records[n]; }
        int getHead() const { return head; }
        int getTail() const { return tail; }
        int getMid() const;
        int getMid(int, int) const;
        bool empty() const { return recnum == 0; }
        MyDatabase &add(const std::vector<KeyType> &);
        MyDatabase &setKeyNum(int);
        const MyDatabase &print() const;
        MyDatabase &print();
        MyDatabase &mergeSort_LSD();
        MyDatabase &mergeSort_MSD();
        MyDatabase &mergeSort(unsigned);
        MyDatabase &mergeSort_LSD(const std::vector<unsigned> &);
        MyDatabase &mergeSort_MSD(const std::vector<unsigned> &);
        MyDatabase &radixSort_LSD();
        MyDatabase &radixSort_MSD();
        MyDatabase &radixSort(unsigned);
        MyDatabase &radixSort_LSD(const std::vector<unsigned> &);
        MyDatabase &radixSort_MSD(const std::vector<unsigned> &);
        std::vector<int> getOrder() const;
        MyDatabase &setOrder(const std::vector<int> &);
        MyDatabase &resetOrder();
    private:
        std::vector<MyRecord> records;   // records
        unsigned keynum = 0;               // number of keys
        unsigned recnum = 0;               // number of records
        int head = -1;
        int tail = -1;

        MyDatabase &mergeSort(unsigned, int, int, std::vector<int> &);
        MyDatabase &radixSort(unsigned, int, int, std::vector<int> &);
        MyDatabase &sort_MSD(int);
        MyDatabase &sort_MSD(int, const std::vector<unsigned> &);
        KeyType getData(int n, int key) const { return records[n].getData(key); }
    };

    inline MyDatabase &MyDatabase::setKeyNum(int num)
    {
        keynum = num;
        return *this;
    }

    inline MyDatabase &MyDatabase::add(const std::vector<KeyType> &data)
    {
        records.push_back(MyRecord(data));
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
