#include "BorrowRecord.h"

BorrowRecord::BorrowRecord() : borrowId(0), bookId(0), readerId(0), borrowDate(""), dueDate("") {}

BorrowRecord::BorrowRecord(int borrowId, int bookId, int readerId, const string& borrowDate, const string& dueDate)
    : borrowId(borrowId), bookId(bookId), readerId(readerId), borrowDate(borrowDate), dueDate(dueDate) {}

int BorrowRecord::getBorrowId() const { return borrowId; }
int BorrowRecord::getBookId() const { return bookId; }
int BorrowRecord::getReaderId() const { return readerId; }
string BorrowRecord::getBorrowDate() const { return borrowDate; }
string BorrowRecord::getDueDate() const { return dueDate; }

void BorrowRecord::setBorrowId(int borrowId) { this->borrowId = borrowId; }
void BorrowRecord::setBookId(int bookId) { this->bookId = bookId; }
void BorrowRecord::setReaderId(int readerId) { this->readerId = readerId; }
void BorrowRecord::setBorrowDate(const string& borrowDate) { this->borrowDate = borrowDate; }
void BorrowRecord::setDueDate(const string& dueDate) { this->dueDate = dueDate; }
