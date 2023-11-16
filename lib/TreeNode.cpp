#include "TreeNode.h"
#include <iostream>

using namespace std;

void printPreOrder(TreeNode* root) {
    if (!root) return;          // If current node is nullptr, just return

    cout << root->val << " ";  // Print the current node's value
    printPreOrder(root->left);   // Recursively print the left subtree
    printPreOrder(root->right);  // Recursively print the right subtree
}

