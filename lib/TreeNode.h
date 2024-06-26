#ifndef TREENODE_H
#define TREENODE_H

// Definition of the struct
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void printPreOrder(TreeNode* root);
void printLevelOrder(TreeNode* root);

#endif 
