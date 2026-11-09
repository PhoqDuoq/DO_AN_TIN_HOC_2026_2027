#ifndef READERHASHTABLE_H
#define READERHASHTABLE_H

#include <vector>
#include <string>
#include <list>
using namespace std;

#include "../models/Reader.h"

/**
 * Hash table for managing Readers (độc giả) using separate chaining.
 * Key: CMND (string).
 */
class ReaderHashTable {
public:
    explicit ReaderHashTable(size_t bucketCount = 101);
    ~ReaderHashTable();

    // Insert a new reader. Returns false if CMND already exists.
    bool insert(const Reader& reader);

    // Find a reader by CMND. Returns nullptr if not found.
    const Reader* find(const string& cmnd) const;
    Reader* find(const string& cmnd);

    // Update existing reader (identified by CMND). Returns false if not found.
    bool update(const Reader& reader);

    // Remove reader by CMND. Returns false if not found.
    bool remove(const string& cmnd);

    // Display all readers.
    void displayAll() const;

    // Clear the entire table.
    void clear();

    size_t size() const { return numElements; }

private:
    // Simple polynomial rolling hash for strings.
    size_t hash(const string& key) const;

    vector< list<Reader> > table; // each bucket is a list of Readers
    size_t numElements;
};

#endif // READERHASHTABLE_H
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
