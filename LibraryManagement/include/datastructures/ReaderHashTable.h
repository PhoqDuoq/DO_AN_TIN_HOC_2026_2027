#ifndef READERHASHTABLE_H
#define READERHASHTABLE_H

#include <vector>
#include <string>
using namespace std;

class Reader;

class ReaderHashTable {
public:
    ReaderHashTable(int capacity = 101);
    ~ReaderHashTable();

    void insert(Reader* reader);
    Reader* find(int id) const;
    bool remove(int id);
    void clear();

private:
    struct Entry {
        int key;
        Reader* value;
        bool used;
    };

    vector<Entry> table;
    int capacity;
    int hash(int id) const;
};

#endif
