#include "TransactionArray.h"

#include <algorithm>
using namespace std;

TransactionArray::TransactionArray() = default;

TransactionArray::~TransactionArray() = default;

void TransactionArray::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
}

void TransactionArray::removeTransaction(int id) {
    auto it = remove_if(transactions.begin(), transactions.end(),
        [id](const Transaction& t) { return t.id == id; });
    transactions.erase(it, transactions.end());
}

const vector<Transaction>& TransactionArray::getTransactions() const {
    return transactions;
}

void TransactionArray::clear() {
    transactions.clear();
}
