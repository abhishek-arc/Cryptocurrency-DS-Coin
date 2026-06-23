#include "../include/Member.h"


#include "../include/Transaction.h"
#include "../include/TransactionBlock.h"
#include "../include/DSCoinHonest.h"
#include "../include/MerkleTree.h"
#include "../include/TreeNode.h"
#include "../include/MissingTransactionException.h"
#include "../include/DSCoinHonest.h"

#include <string>
#include <vector>
using namespace std;

void Member::initiateCoinSend(const string& destUID, DSCoinHonest* DSObj)
{
    auto coinInfo = myCoins.front();

    myCoins.erase(myCoins.begin());

    Member* destination = nullptr;

    // finding the member jisko coin bhejna hai ans assign it a pointer "destination".
    for(Member* m : DSObj->memberList)
    {
        if(m->UID == destUID)
        {
            destination = m;
            break;
        }
    }

    Transaction* tObj = new Transaction();

    tObj->coinID = coinInfo.first;

    tObj->source = this;  // this --> jis member ne ye function call kari hai wo member.

    tObj->destination = destination;

    tObj->coinSrcBlock = coinInfo.second;

    inProcessTrans.push_back(tObj);

    DSObj->pendingTransactions.addTransaction(tObj);
}

void Member::append(const string& coinID, TransactionBlock* tB)
{
    auto newCoin = make_pair(coinID, tB);

    auto it = myCoins.begin();

    while(it != myCoins.end() && it->first < coinID)
    {
        ++it;
    }

    myCoins.insert(it, newCoin);
}

vector<pair<string,string>> Member::queryDocument(int docIdx, MerkleTree& tree)
{
    vector<pair<string, string>> result;

    TreeNode* iter = tree.rootNode;

    int docLocator = tree.numDocs;

    result.insert(result.begin(), {iter->val, ""});

    while(docLocator > 1)
    {
        result.insert(result.begin(), {iter->left->val, iter->right->val});

        docLocator /= 2;

        if(docLocator <= docIdx)
        {
            docIdx -= docLocator;

            iter = iter->right;
        }
        else
        {
            iter = iter->left;
        }
    }

    return result;
}

pair<
    vector<pair<string,string>>,
    vector<pair<string,string>>
>
Member::finalizeCoinSend(Transaction* tObj, DSCoinHonest* DSObj)
{
    TransactionBlock* iter = DSObj->bChain.lastBlock;

    bool found = false;

    int loc = 0;

    while(iter != nullptr)
    {
        for(int i = 0;i < static_cast<int>(iter->trArray.size());i++)
        {
            if(iter->trArray[i] == tObj)
            {
                loc = i;
                found = true;
                break;
            }
        }

        if(found)
        {
            break;
        }

        iter = iter->previous;
    }

    if(iter == nullptr)
    {
        throw MissingTransactionException();
    }

    auto siblingPath = queryDocument(loc,iter->tree);

    vector<pair<string,string>> blockchainProof;

    TransactionBlock* chainIter = DSObj->bChain.lastBlock;

    while(chainIter != iter)
    {
        blockchainProof.insert(
            blockchainProof.begin(),
            {
                chainIter->dgst,
                chainIter->previous->dgst
                + "#"
                + chainIter->trSummary
                + "#"
                + chainIter->nonce
            }
        );

        chainIter = chainIter->previous;
    }

    string init;

    if(iter->previous == nullptr)
    {
        init = BlockChainHonest::START_STRING;
    }
    else
    {
        init = iter->previous->dgst;
    }

    blockchainProof.insert(
        blockchainProof.begin(),
        {
            iter->dgst,
            init
            + "#"
            + iter->trSummary
            + "#"
            + iter->nonce
        }
    );

    blockchainProof.insert(
        blockchainProof.begin(),
        {
            init,
            ""
        }
    );

    for(auto it = inProcessTrans.begin();it != inProcessTrans.end();++it)
    {
        if(*it == tObj)
        {
            inProcessTrans.erase(it);
            break;
        }
    }

    tObj->destination->append(tObj->coinID,iter);

    return {siblingPath,blockchainProof};
    
}


void Member::mineCoin(DSCoinHonest* DSObj)
{
    vector<Transaction*> selected;

    while(selected.size()<static_cast<size_t>(DSObj->bChain.trCount - 1)
    )
    {
        Transaction* t = DSObj->pendingTransactions.removeTransaction();

        bool valid = true;

        for(Transaction* txn : selected)
        {
            if(txn->coinID == t->coinID)
            {
                valid = false;
                break;
            }
        }

        if(valid && DSObj->bChain.lastBlock != nullptr)
        {
            valid = DSObj->bChain.lastBlock->checkTransaction(t);
        }

        if(valid)
        {
            selected.push_back(t);
        }
    }

    Transaction* reward = new Transaction();

    reward->coinID = to_string(stoi(DSObj->latestCoinID) + 1);

    reward->source = nullptr;

    reward->destination = this;

    reward->coinSrcBlock = nullptr;

    selected.push_back(reward);

    TransactionBlock* minedBlock = new TransactionBlock(selected);

    DSObj->bChain.insertBlockHonest(minedBlock);

    append(reward->coinID,minedBlock);

    DSObj->latestCoinID = reward->coinID;
}

void Member::mineCoin(DSCoinMalicious* DSObj)
{

}