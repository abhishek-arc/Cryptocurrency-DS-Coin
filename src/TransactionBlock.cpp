#include "../include/TransactionBlock.h"

TransactionBlock::TransactionBlock(const std::vector<Transaction*>& transactions)
{
    trArray = transactions;

    previous = nullptr;

    trSummary = tree.build(trArray);

    dgst = "";

    nonce = "";
}


bool TransactionBlock::checkTransaction(Transaction* t)
{
    TransactionBlock* src = t->coinSrcBlock;

    bool found = false;

    if(src != nullptr)
    {
        for(Transaction* txn : src->trArray)
        {
            if(
                txn != nullptr &&
                txn->coinID == t->coinID &&
                txn->destination == t->source
            )
            {
                found = true;
                break;
            }
        }

        if(!found)
        {
            return false;
        }
    }

    int totalCoinID = 0;

    for(Transaction* txn : trArray)
    {
        if(txn != nullptr && txn->coinID == t->coinID)
        {
            totalCoinID++;
        }
    }

    if(totalCoinID > 1)
    {
        return false;
    }

    TransactionBlock* current = previous;
    TransactionBlock* dest = t->coinSrcBlock;

    while(current != dest)
    {
        for(Transaction* txn : current->trArray)
        {
            if(
                txn != nullptr &&
                txn->coinID == t->coinID
            )
            {
                return false;
            }
        }

        current = current->previous;
    }

    return true;
}