#include "../include/TreeNode.h"

TreeNode::TreeNode()
{
    val = "";

    parent = nullptr;
    left = nullptr;
    right = nullptr;
}

TreeNode::TreeNode(const std::string& value)
{
    val = value;

    parent = nullptr;
    left = nullptr;
    right = nullptr;
}