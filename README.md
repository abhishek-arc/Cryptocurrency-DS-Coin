# DSCoin: A Cryptocurrency and Blockchain Simulation

## Overview

DSCoin is a simplified cryptocurrency system inspired by Bitcoin. The project implements core blockchain concepts including transaction verification, block creation, Merkle trees, cryptographic hashing, and ownership transfer.

The system supports secure transaction processing through a blockchain structure while maintaining transaction integrity using cryptographic techniques.

## Features

- Blockchain-based transaction storage
- Merkle Tree construction for transaction verification
- Secure hashing using Cryptographic Random Functions (CRF)
- Transaction queue management
- Block mining and insertion
- Member wallet and ownership tracking
- Moderator-controlled initialization of the currency system
- Support for honest blockchain maintenance

## Project Structure

```
DSCOIN_FINAL/
│
├── include/
│   ├── BlockChainHonest.h
│   ├── CRF.h
│   ├── DSCoinHonest.h
│   ├── Member.h
│   ├── MerkleTree.h
│   ├── MissingTransactionException.h
│   ├── Moderator.h
│   ├── Transaction.h
│   ├── TransactionBlock.h
│   ├── TransactionQueue.h
│   └── TreeNode.h
│
├── src/
│   ├── BlockChainHonest.cpp
│   ├── CRF.cpp
│   ├── Member.cpp
│   ├── MerkleTree.cpp
│   ├── Moderator.cpp
│   ├── Transaction.cpp
│   ├── TransactionBlock.cpp
│   ├── TransactionQueue.cpp
│   ├── TreeNode.cpp
│   └── main.cpp
│
└── README.md
```

## Core Components

### Transaction
Represents the transfer of a coin between members.

### Transaction Queue
Stores pending transactions waiting to be mined into a block.

### Transaction Block
Contains a fixed number of transactions along with:
- Previous block hash
- Merkle root
- Block digest

### Merkle Tree
Used to efficiently verify transaction integrity within a block.

### Blockchain
Maintains an ordered sequence of transaction blocks linked through cryptographic hashes.

### Member
Represents a user in the DSCoin network and maintains coin ownership information.

### Moderator
Initializes the system and distributes initial coins among members.

### CRF
Provides cryptographic hash functionality used throughout the blockchain.

## Technologies Used

- C++
- Object-Oriented Programming
- Data Structures
  - Linked Lists
  - Queues
  - Trees
- Blockchain Concepts
- Merkle Trees
- Cryptographic Hashing

## Compilation

Using g++:

```bash
g++ -Iinclude src/*.cpp -o dsc
```

## Run

```bash
./dsc
```

(Windows)

```bash
dsc.exe
```

## Learning Outcomes

This project helped in understanding:

- Blockchain architecture
- Cryptographic hash functions
- Merkle tree construction
- Transaction verification
- Secure distributed ledger concepts
- Object-oriented design in C++

## Author

Abhishek Patel
IIT Delhi