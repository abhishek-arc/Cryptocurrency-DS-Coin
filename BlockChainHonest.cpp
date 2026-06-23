#include "BlockChainHonest.h"
#include "TransactionBlock.h"
#include "CRF.h"

const std::string
BlockChainHonest::START_STRING = "DSCoin";

BlockChainHonest::BlockChainHonest()
{
    trCount = 0;
    lastBlock = nullptr;
}

void BlockChainHonest::insertBlockHonest(TransactionBlock* newBlock)
{
    CRF obj(64);

    std::string previousDigest;

    if(lastBlock == nullptr)
    {
        previousDigest = START_STRING;

        newBlock->previous = nullptr;
    }
    else
    {
        previousDigest = lastBlock->dgst;

        newBlock->previous = lastBlock;
    }

    long long nonceValue = 1000000000LL;

    while(true)
    {
        std::string nonce =
            std::to_string(nonceValue);

        std::string digest =
            obj.Fn(
                previousDigest
                + "#"
                + newBlock->trSummary
                + "#"
                + nonce
            );

        if(digest.substr(0,4) == "0000")
        {
            newBlock->nonce = nonce;
            newBlock->dgst = digest;

            break;
        }

        nonceValue++;
    }

    lastBlock = newBlock;
}