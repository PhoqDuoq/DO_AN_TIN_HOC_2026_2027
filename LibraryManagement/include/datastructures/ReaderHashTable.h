#ifndef READERHASHTABLE_H
#define READERHASHTABLE_H

#include <cstddef>
#include <list>
#include <string>
#include <vector>
#include "Reader.h"

// Hash table quan ly doc gia theo CMND, giai quyet va cham bang separate chaining.
class ReaderHashTable {
public:
    explicit ReaderHashTable(std::size_t bucketCount = 101);

    bool insert(const Reader& reader);
    const Reader* find(const std::string& cmnd) const;
    Reader* find(const std::string& cmnd);
    bool update(const Reader& reader);
    bool remove(const std::string& cmnd);
    void displayAll() const;
    std::vector<Reader> toVector() const;
    void clear();

    std::size_t size() const { return numElements; }
    std::size_t bucketCount() const { return table.size(); }
    std::size_t bucketIndex(const std::string& key) const;

private:
    std::vector<std::list<Reader> > table;
    std::size_t numElements;
};

#endif
