#include "MerkleTree.h"
#include "Member.h"
#include "TransactionBlock.h"

MerkleTree::MerkleTree()
{
    rootNode = nullptr;
    numDocs = 0;
}


void MerkleTree::nodeInit(
    TreeNode* node,
    TreeNode* left,
    TreeNode* right,
    TreeNode* parent,
    const std::string& value
)
{
    node->left = left;
    node->right = right;
    node->parent = parent;
    node->val = value;
}


std::string MerkleTree::getString(Transaction* tr)
{
    CRF obj(64);

    std::string value = tr->coinID;

    if(tr->source == nullptr)
        value += "#Genesis";
    else
        value += "#" + tr->source->UID;

    value += "#" + tr->destination->UID;

    if(tr->coinSrcBlock == nullptr)
        value += "#Genesis";
    else
        value += "#" + tr->coinSrcBlock->dgst;

    return obj.Fn(value);
}

std::string MerkleTree::build(const std::vector<Transaction*>& transactions)
{
    CRF obj(64);

    numDocs = transactions.size();

    std::queue<TreeNode*> q;

    for(Transaction* tr : transactions)
    {
        TreeNode* node = new TreeNode();

        std::string value = getString(tr);

        nodeInit(
            node,
            nullptr,
            nullptr,
            nullptr,
            value
        );

        q.push(node);
    }

    while(q.size() > 1)
    {
        TreeNode* left = q.front();
        q.pop();

        TreeNode* right = q.front();
        q.pop();

        TreeNode* parent = new TreeNode();

        std::string parentHash =
            obj.Fn(
                left->val +
                "#" +
                right->val
            );

        nodeInit(
            parent,
            left,
            right,
            nullptr,
            parentHash
        );

        left->parent = parent;
        right->parent = parent;

        q.push(parent);
    }

    rootNode = q.front();

    return rootNode->val;
}
