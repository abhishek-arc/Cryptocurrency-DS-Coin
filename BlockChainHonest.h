#ifndef BLOCKCHAINHONEST_H
#define BLOCKCHAINHONEST_H

#include <string>

class TransactionBlock;

class BlockChainHonest {

public:

    int trCount;

    static const std::string START_STRING;

    TransactionBlock* lastBlock;

    BlockChainHonest();

    void insertBlockHonest(TransactionBlock* newBlock);
};

#endif