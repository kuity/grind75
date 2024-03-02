#include <iostream>
#include <set>
#include <stack>
#include "../../lib/TreeNode.h"

using namespace std;

/*
Link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/
Difficulty: Medium
Topics: tree, dfs, binary tree
*/
class Solution {
public:
    stack<TreeNode *> parents;
    stack<TreeNode *> n1parents;
    stack<TreeNode *> n2parents;
    set<int> toFind;

    // How do we keep track of the "parents"?
    // A parent is "done" when both its children is "done"
    // We can know this when a recursive function returns
    // When a node incurs its children, push itself on the parent stack
    // After done, pop itself off the stack 
    void traverse(TreeNode* N) {
        if (toFind.size() == 0) {
            return;
        }

        parents.push(N);
        if (toFind.find(N->val) != toFind.end()) {
            if (toFind.size() == 2) {
                n1parents = parents;
                toFind.erase(N->val);
            } else if (toFind.size() == 1) {
                n2parents = parents;
                return;
            }
        } 

        if (N->left != nullptr) {
            traverse(N->left);
        }
        if (N->right != nullptr) {
            traverse(N->right);
        }
        parents.pop();
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        parents = {};
        n1parents = {};
        n2parents = {};
        toFind = {};
        toFind.insert(p->val);
        toFind.insert(q->val);
        traverse(root);
        set<TreeNode *> n1set;
        while(!n1parents.empty()) {
            n1set.insert(n1parents.top());
            n1parents.pop();
        }
        while(!n2parents.empty()) {
            if (n1set.find(n2parents.top()) != n1set.end()) {
                return n2parents.top();
            }
            n2parents.pop();
        }
        return nullptr;
    }
};

int main() {
    TreeNode *q = new TreeNode(4);
    TreeNode *p = new TreeNode(5, new TreeNode(6), 
                 new TreeNode(2, new TreeNode(7), q));
    TreeNode *t1 = new TreeNode(3, p, 
                    new TreeNode(1, new TreeNode(0), new TreeNode(8)));
    printPreOrder(t1);
    cout << endl;
    Solution *S = new Solution();
    auto ans = S->lowestCommonAncestor(t1, p, q);
    cout << "lca is " << ans->val << endl;

    q = new TreeNode(5, new TreeNode(6), 
             new TreeNode(2, new TreeNode(7), new TreeNode(4)));
    p = new TreeNode(1, new TreeNode(0), new TreeNode(8));
    t1 = new TreeNode(3, p, q);
    ans = S->lowestCommonAncestor(t1, p, q);
    cout << "lca is " << ans->val << endl;
}
