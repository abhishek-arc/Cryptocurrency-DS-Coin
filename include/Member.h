#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include <utility>
using namespace std;

class Transaction;
class TransactionBlock;
class DSCoinHonest;
class DSCoinMalicious;
class MerkleTree;

class Member {

public:

    string UID;

    vector<pair<string,TransactionBlock*>> myCoins;

    vector<Transaction*> inProcessTrans;

    void initiateCoinSend(const string& destUID,DSCoinHonest* DSObj);

    void append(const string& coinID, TransactionBlock* tB);

    vector<pair<string, string>> queryDocument(int docIdx, MerkleTree& tree);

    pair<
        vector<pair<string,string>>,
        vector<pair<string,string>>
    >
    finalizeCoinSend(Transaction* tObj, DSCoinHonest* DSObj);

    void mineCoin(DSCoinHonest* DSObj);

    void mineCoin(DSCoinMalicious* DSObj);
};

#endif