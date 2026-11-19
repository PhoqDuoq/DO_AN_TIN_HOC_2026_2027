#include "ReaderHashTable.h"

#include <iostream>

using namespace std;

ReaderHashTable::ReaderHashTable(size_t bucketCount)
    : table(bucketCount == 0 ? 1 : bucketCount), numElements(0) {}

size_t ReaderHashTable::bucketIndex(const string& key) const {
    // Polynomial rolling hash; unsigned arithmetic has defined wraparound.
    size_t value = 0;
    for (unsigned char ch : key) {
        value = value * 31u + ch;
    }
    return value % table.size();
}

bool ReaderHashTable::insert(const Reader& reader) {
    if (reader.CMND.empty() || reader.fullName.empty() || find(reader.CMND)) return false;
    table[bucketIndex(reader.CMND)].push_back(reader);
    ++numElements;
    return true;
}

const Reader* ReaderHashTable::find(const string& cmnd) const {
    if (cmnd.empty()) return nullptr;
    const list<Reader>& chain = table[bucketIndex(cmnd)];
    for (list<Reader>::const_iterator it = chain.begin(); it != chain.end(); ++it) {
        if (it->CMND == cmnd) return &*it;
    }
    return nullptr;
}

Reader* ReaderHashTable::find(const string& cmnd) {
    if (cmnd.empty()) return nullptr;
    list<Reader>& chain = table[bucketIndex(cmnd)];
    for (list<Reader>::iterator it = chain.begin(); it != chain.end(); ++it) {
        if (it->CMND == cmnd) return &*it;
    }
    return nullptr;
}

bool ReaderHashTable::update(const Reader& reader) {
    Reader* existing = find(reader.CMND);
    if (!existing || reader.fullName.empty()) return false;
    *existing = reader;
    return true;
}

bool ReaderHashTable::remove(const string& cmnd) {
    if (cmnd.empty()) return false;
    list<Reader>& chain = table[bucketIndex(cmnd)];
    for (list<Reader>::iterator it = chain.begin(); it != chain.end(); ++it) {
        if (it->CMND == cmnd) {
            chain.erase(it);
            --numElements;
            return true;
        }
    }
    return false;
}

void ReaderHashTable::displayAll() const {
    if (numElements == 0) {
        cout << "Danh sach doc gia dang rong.\n";
        return;
    }
    cout << "\n" << "CMND | Ho ten | Email | Dien thoai | Loai the\n";
    cout << "---------------------------------------------------------------\n";
    for (size_t i = 0; i < table.size(); ++i) {
        for (list<Reader>::const_iterator it = table[i].begin(); it != table[i].end(); ++it) {
            cout << it->CMND << " | " << it->fullName << " | " << it->email << " | "
                 << it->phone << " | " << it->cardType << "\n";
        }
    }
}

vector<Reader> ReaderHashTable::toVector() const {
    vector<Reader> readers;
    readers.reserve(numElements);
    for (size_t i = 0; i < table.size(); ++i)
        for (list<Reader>::const_iterator it = table[i].begin(); it != table[i].end(); ++it)
            readers.push_back(*it);
    return readers;
}

void ReaderHashTable::clear() {
    for (size_t i = 0; i < table.size(); ++i) table[i].clear();
    numElements = 0;
}
