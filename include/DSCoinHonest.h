#ifndef DSCOINHONEST_H
#define DSCOINHONEST_H

#include <string>
#include <vector>

#include "TransactionQueue.h"
#include "BlockChainHonest.h"
using namespace std;

class Member;

class DSCoinHonest {

public:

    TransactionQueue pendingTransactions;

    BlockChainHonest bChain;

    vector<Member*> memberList;

    string latestCoinID;
};

#endif