#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class Member;
class TransactionBlock;

class Transaction {
public:

    std::string coinID;

    Member* source;
    Member* destination;

    TransactionBlock* coinSrcBlock;

    // Constructor
    Transaction();

    Transaction(
        const std::string& coinID,
        Member* source,
        Member* destination,
        TransactionBlock* coinSrcBlock
    );

    // Equality operator : to check whether two transaction dtype are equal or not.
    bool operator==(const Transaction& other) const;
};

#endif