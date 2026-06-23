#include "DSCoinHonest.h"
#include "Moderator.h"
#include "Member.h"
#include "TransactionBlock.h"
#include "Transaction.h"
#include "TransactionQueue.h"
#include "BlockChainHonest.h"

#include <iostream>

int main()
{
    DSCoinHonest ds;

    ds.bChain.trCount = 4;

    //--------------------------------------------------
    // Create Members
    //--------------------------------------------------

    Member* alice = new Member();
    Member* bob = new Member();
    Member* charlie = new Member();

    alice->UID = "Alice";
    bob->UID = "Bob";
    charlie->UID = "Charlie";

    ds.memberList.push_back(alice);
    ds.memberList.push_back(bob);
    ds.memberList.push_back(charlie);

    //--------------------------------------------------
    // Initialize DSCoin
    //--------------------------------------------------

    Moderator mod;

    mod.initializeDSCoin(&ds, 12);

    std::cout << "\n========== INITIALIZATION ==========\n";

    std::cout << "Latest Coin ID : "
              << ds.latestCoinID
              << "\n";

    std::cout << "Last Block Digest : "
              << ds.bChain.lastBlock->dgst
              << "\n";

    std::cout << "Last Block Nonce : "
              << ds.bChain.lastBlock->nonce
              << "\n";

    //--------------------------------------------------
    // Check Wallets
    //--------------------------------------------------

    std::cout << "\nAlice Coins:\n";
    for(auto& coin : alice->myCoins)
        std::cout << coin.first << " ";

    std::cout << "\n\nBob Coins:\n";
    for(auto& coin : bob->myCoins)
        std::cout << coin.first << " ";

    std::cout << "\n\nCharlie Coins:\n";
    for(auto& coin : charlie->myCoins)
        std::cout << coin.first << " ";

    std::cout << "\n";

    //--------------------------------------------------
    // Create Transactions
    //--------------------------------------------------

    alice->initiateCoinSend(
        "Bob",
        &ds
    );

    Transaction* aliceTx =
        alice->inProcessTrans[0];

    std::cout
        << "\n========== AFTER ALICE SEND ==========\n";

    std::cout
        << "Alice Wallet Size : "
        << alice->myCoins.size()
        << "\n";

    std::cout
        << "Pending Transactions : "
        << ds.pendingTransactions.size()
        << "\n";

    bob->initiateCoinSend(
        "Charlie",
        &ds
    );

    charlie->initiateCoinSend(
        "Alice",
        &ds
    );

    std::cout
        << "\nPending Transactions : "
        << ds.pendingTransactions.size()
        << "\n";

    //--------------------------------------------------
    // Mine Block
    //--------------------------------------------------

    alice->mineCoin(&ds);

    std::cout
        << "\n========== AFTER MINING ==========\n";

    std::cout
        << "Latest Coin ID : "
        << ds.latestCoinID
        << "\n";

    std::cout
        << "New Last Block Digest : "
        << ds.bChain.lastBlock->dgst
        << "\n";

    std::cout
        << "New Last Block Nonce : "
        << ds.bChain.lastBlock->nonce
        << "\n";

    std::cout
        << "Pending Transactions : "
        << ds.pendingTransactions.size()
        << "\n";

    std::cout
        << "\nAlice Coins After Mining:\n";

    for(auto& coin : alice->myCoins)
        std::cout << coin.first << " ";

    std::cout << "\n";

    //--------------------------------------------------
    // Digest Check
    //--------------------------------------------------

    std::cout
        << "\nDigest Prefix = "
        << ds.bChain.lastBlock->dgst.substr(0,4)
        << "\n";

    if(ds.bChain.lastBlock->dgst.substr(0,4) == "0000")
    {
        std::cout
            << "Mining Successful\n";
    }
    else
    {
        std::cout
            << "Mining Failed\n";
    }

    //--------------------------------------------------
    // Finalize Coin Transfer
    //--------------------------------------------------

    std::cout
        << "\n========== BEFORE FINALIZE ==========\n";

    std::cout
        << "Alice inProcess size : "
        << alice->inProcessTrans.size()
        << "\n";

    std::cout
        << "Bob wallet size : "
        << bob->myCoins.size()
        << "\n";

    auto proofs =
        alice->finalizeCoinSend(
            aliceTx,
            &ds
        );

    //--------------------------------------------------
    // Check Finalization
    //--------------------------------------------------

    std::cout
        << "\n========== AFTER FINALIZE ==========\n";

    std::cout
        << "Alice inProcess size : "
        << alice->inProcessTrans.size()
        << "\n";

    std::cout
        << "Bob wallet size : "
        << bob->myCoins.size()
        << "\n";

    //--------------------------------------------------
    // Bob Wallet
    //--------------------------------------------------

    std::cout
        << "\nBob Coins:\n";

    for(auto& coin : bob->myCoins)
    {
        std::cout
            << coin.first
            << " ";
    }

    std::cout << "\n";

    //--------------------------------------------------
    // Merkle Proof
    //--------------------------------------------------

    std::cout
        << "\n===== MERKLE PROOF =====\n";

    std::cout
        << "Size : "
        << proofs.first.size()
        << "\n";

    for(auto& p : proofs.first)
    {
        std::cout
            << "("
            << p.first
            << ", "
            << p.second
            << ")\n";
    }

    //--------------------------------------------------
    // Blockchain Proof
    //--------------------------------------------------

    std::cout
        << "\n===== BLOCKCHAIN PROOF =====\n";

    std::cout
        << "Size : "
        << proofs.second.size()
        << "\n";

    for(auto& p : proofs.second)
    {
        std::cout
            << "("
            << p.first
            << ", "
            << p.second
            << ")\n";
    }

    //--------------------------------------------------
    // Verify Bob received coin 100000
    //--------------------------------------------------

    bool found = false;

    for(auto& coin : bob->myCoins)
    {
        if(coin.first == "100000")
        {
            found = true;
            break;
        }
    }

    std::cout
        << "\nCoin Transfer Verified : "
        << (found ? "YES" : "NO")
        << "\n";

    return 0;
}