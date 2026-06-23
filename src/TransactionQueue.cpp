#include "../include/TransactionQueue.h"

TransactionQueue::TransactionQueue()
{
    front = nullptr;
    rear = nullptr;
    numTransactions = 0;
}

TransactionQueue::~TransactionQueue()
{
    while(front != nullptr)
    {
        Node* temp = front;
        front = front->next;

        delete temp;
    }
}

void TransactionQueue::addTransaction(Transaction* transaction)
{
    Node* newNode = new Node(transaction);

    if(front == nullptr)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        newNode->prev = rear;

        rear = newNode;
    }

    numTransactions++;
}

Transaction* TransactionQueue::removeTransaction()
{
    if(front == nullptr)
    {
        throw std::runtime_error("Transaction Queue Empty");
    }

    Node* temp = front;

    Transaction* transaction = temp->data;

    front = front->next;

    if(front != nullptr)
    {
        front->prev = nullptr;
    }
    else
    {
        rear = nullptr;
    }

    delete temp;

    numTransactions--;

    return transaction;
}

int TransactionQueue::size() const
{
    return numTransactions;
}

bool TransactionQueue::empty() const
{
    return numTransactions == 0;
}