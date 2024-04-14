#include "TreeNode.h"
#include <iostream>

using namespace std;

void printPreOrder(TreeNode* root) {
    if (!root) { return; }
    cout << root->val << " ";  // Print the current node's value
    printPreOrder(root->left);   // Recursively print the left subtree
    printPreOrder(root->right);  // Recursively print the right subtree
}

void printLevelOrder(TreeNode* root) {
    if (root == nullptr) return;
    vector<TreeNode *> children = {root};
    while (!children.empty()) {
        int sz = children.size();
        vector<TreeNode *> childrenNew;
        for (auto i=0; i<sz; i++) {
            auto child = children[i];
            if (child == nullptr) {
                cout << "null ";
                continue;
            }
            cout << child->val << " ";
            childrenNew.push_back(child->left);
            childrenNew.push_back(child->right);
        }
        children = childrenNew;
    }
}

