#include "Transaction.h"

Transaction::Transaction()
{
    source = nullptr;
    destination = nullptr;
    coinSrcBlock = nullptr;
}

Transaction::Transaction(
    const std::string& coinID,
    Member* source,
    Member* destination,
    TransactionBlock* coinSrcBlock
)
{
    this->coinID = coinID;
    this->source = source;
    this->destination = destination;
    this->coinSrcBlock = coinSrcBlock;
}

bool Transaction::operator==(const Transaction& other) const
{
    return
        coinID == other.coinID &&
        source == other.source &&
        destination == other.destination &&
        coinSrcBlock == other.coinSrcBlock;
}