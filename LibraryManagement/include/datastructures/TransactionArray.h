#ifndef TRANSACTIONARRAY_H
#define TRANSACTIONARRAY_H

#include <string>
#include <vector>
using namespace std;

struct Transaction {
    int id;
    string type;
    string description;
    string timestamp;
};

class TransactionArray {
public:
    TransactionArray();
    ~TransactionArray();

    void addTransaction(const Transaction& transaction);
    void removeTransaction(int id);
    const vector<Transaction>& getTransactions() const;
    void clear();

private:
    vector<Transaction> transactions;
};

#endif
