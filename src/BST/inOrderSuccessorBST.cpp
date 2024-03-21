#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
Link: https://leetcode.com/problems/inorder-successor-in-bst/description/
Difficulty: Medium
Topics: Tree, BST, DFS, Binary Tree
*/
class Solution {
public:
    TreeNode* findSuccessor(TreeNode* n, int v) {
        if (v <= n->val && n->left != nullptr) return findSuccessor(n->left, v);
        if (v > n->val && n->right != nullptr) return findSuccessor(n->right, v);
        return n;
    }

    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if (root->val == p->val) {
            if (root->right != nullptr) return findSuccessor(root->right, p->val);
            else return nullptr;
        }

        else if (root->val < p->val) {
            return inorderSuccessor(root->right, p);
        }

        // if (root->val > p->val)
        else {
            auto ret = inorderSuccessor(root->left, p);
            if (ret == nullptr) return root;
            return ret;
        }
    }
};

int main() {
    Solution *S = new Solution();
    TreeNode *y = new TreeNode(6);
    TreeNode *x = new TreeNode(5, 
			new TreeNode(3, 
			    new TreeNode(2, new TreeNode(1), nullptr), 
			    new TreeNode(4)), 
			y
    );

    auto ans = S->inorderSuccessor(x, y);
    cout << "successor is " << ans << endl;
}
