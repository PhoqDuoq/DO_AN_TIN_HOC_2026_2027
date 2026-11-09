#include "Reader.h"

Reader::Reader() : id(0), name(""), phone("") {}

Reader::Reader(int id, const string& name, const string& phone)
    : id(id), name(name), phone(phone) {}

int Reader::getId() const { return id; }
string Reader::getName() const { return name; }
string Reader::getPhone() const { return phone; }

void Reader::setId(int id) { this->id = id; }
void Reader::setName(const string& name) { this->name = name; }
void Reader::setPhone(const string& phone) { this->phone = phone; }
