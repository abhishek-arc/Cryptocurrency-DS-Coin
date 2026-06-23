#ifndef TRANSACTIONQUEUE_H
#define TRANSACTIONQUEUE_H

#include "Transaction.h"
#include <stdexcept>

// doubly linked list.

class TransactionQueue {
private:
    
    struct Node {
        Transaction* data;
        Node* next;
        Node* prev;

        Node(Transaction* t)
            : data(t), next(nullptr), prev(nullptr) {}
    };

    Node* front;
    Node* rear;

    
public:

    int numTransactions;
    
    TransactionQueue();

    ~TransactionQueue();

    void addTransaction(Transaction* transaction);

    Transaction* removeTransaction();

    int size() const;

    bool empty() const;
};

#endif