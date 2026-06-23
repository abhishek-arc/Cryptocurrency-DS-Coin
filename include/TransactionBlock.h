#ifndef TRANSACTIONBLOCK_H
#define TRANSACTIONBLOCK_H

#include <vector>
#include <string>

#include "Transaction.h"
#include "MerkleTree.h"

class TransactionBlock {

public:

    std::vector<Transaction*> trArray;

    TransactionBlock* previous;

    MerkleTree tree;

    std::string trSummary;

    std::string nonce;

    std::string dgst;

    TransactionBlock(const std::vector<Transaction*>& transactions);

    bool checkTransaction(Transaction* t);
};

#endif