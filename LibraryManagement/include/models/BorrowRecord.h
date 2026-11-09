#ifndef BORROW_RECORD_H
#define BORROW_RECORD_H

#include <string>
using namespace std;

class BorrowRecord {
public:
    BorrowRecord();
    BorrowRecord(int borrowId, int bookId, int readerId, const string& borrowDate, const string& dueDate);

    int getBorrowId() const;
    int getBookId() const;
    int getReaderId() const;
    string getBorrowDate() const;
    string getDueDate() const;

    void setBorrowId(int borrowId);
    void setBookId(int bookId);
    void setReaderId(int readerId);
    void setBorrowDate(const string& borrowDate);
    void setDueDate(const string& dueDate);

private:
    int borrowId;
    int bookId;
    int readerId;
    string borrowDate;
    string dueDate;
};

#endif
