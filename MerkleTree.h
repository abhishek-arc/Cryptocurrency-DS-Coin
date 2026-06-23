#ifndef MERKLETREE_H
#define MERKLETREE_H

#include <string>
#include <vector>
#include <queue>

#include "TreeNode.h"
#include "Transaction.h"
#include "CRF.h"

class MerkleTree {
public:

    TreeNode* rootNode;
    int numDocs;

    MerkleTree();

    std::string getString(Transaction* tr);

    std::string build(
        const std::vector<Transaction*>& transactions
    );

private:

    void nodeInit(TreeNode* node, TreeNode* left, TreeNode* right, 
                TreeNode* parent,const std::string& value);
};

#endif