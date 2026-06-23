#include "../include/Moderator.h"

#include "../include/Member.h"
#include "../include/Transaction.h"
#include "../include/TransactionBlock.h"

#include <vector>
#include <string>
using namespace std;

void Moderator::initializeDSCoin(DSCoinHonest* DSObj,int coinCount)
{
    Member* moderator = new Member();

    moderator->UID = "Moderator";

    vector<Transaction*> allTransactions;

    for(int i = 0; i < coinCount; i++)
    {
        Transaction* txn = new Transaction();

        txn->coinID = to_string(100000 + i);

        txn->source = moderator;

        txn->destination = DSObj->memberList[i % DSObj->memberList.size()];

        txn->coinSrcBlock = nullptr;

        allTransactions.push_back(txn);
    }

    int trCount = DSObj->bChain.trCount;

    for(int start = 0; start < coinCount; start += trCount)
    {
        vector<Transaction*> blockTransactions;

        for(int j = start;j < start + trCount;j++)
        {
            blockTransactions.push_back(allTransactions[j]);
        }

        TransactionBlock* block = new TransactionBlock(blockTransactions);

        DSObj->bChain.insertBlockHonest(block);

        for(Transaction* txn :blockTransactions)
        {
            txn->destination->append(txn->coinID,block);
        }
    }

    DSObj->latestCoinID =to_string(100000 + coinCount - 1);
}