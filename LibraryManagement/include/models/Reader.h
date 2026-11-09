#ifndef READER_H
#define READER_H

#include <string>
using namespace std;

class Reader {
public:
    Reader();
    Reader(int id, const string& name, const string& phone);

    int getId() const;
    string getName() const;
    string getPhone() const;

    void setId(int id);
    void setName(const string& name);
    void setPhone(const string& phone);

private:
    int id;
    string name;
    string phone;
};

#endif
