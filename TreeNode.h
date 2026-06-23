#ifndef TREENODE_H
#define TREENODE_H

#include <string>

class TreeNode {
public:

    std::string val;

    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;

    TreeNode();

    explicit TreeNode(const std::string& value);
};

#endif