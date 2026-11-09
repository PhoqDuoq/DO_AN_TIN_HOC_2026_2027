#include "ReaderHashTable.h"

#include "Reader.h"

ReaderHashTable::ReaderHashTable(int capacity) : capacity(capacity) {
    table.resize(capacity);
    for (auto& entry : table) {
        entry.key = -1;
        entry.value = nullptr;
        entry.used = false;
    }
}

ReaderHashTable::~ReaderHashTable() {
    clear();
}

int ReaderHashTable::hash(int id) const {
    return id % capacity;
}

void ReaderHashTable::insert(Reader* reader) {
    if (!reader) return;
    int index = hash(reader->getId());
    while (table[index].used && table[index].key != reader->getId()) {
        index = (index + 1) % capacity;
    }
    table[index].key = reader->getId();
    table[index].value = reader;
    table[index].used = true;
}

Reader* ReaderHashTable::find(int id) const {
    int index = hash(id);
    while (table[index].used) {
        if (table[index].key == id) {
            return table[index].value;
        }
        index = (index + 1) % capacity;
    }
    return nullptr;
}

bool ReaderHashTable::remove(int id) {
    int index = hash(id);
    while (table[index].used) {
        if (table[index].key == id) {
            table[index].value = nullptr;
            table[index].key = -1;
            table[index].used = false;
            return true;
        }
        index = (index + 1) % capacity;
    }
    return false;
}

void ReaderHashTable::clear() {
    for (auto& entry : table) {
        entry.key = -1;
        entry.value = nullptr;
        entry.used = false;
    }
}
