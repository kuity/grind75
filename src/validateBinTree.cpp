#include <iostream>
#include <stack>
#include <tuple>
#include <limits>
#include "../lib/TreeNode.h"

using namespace std;

class Solution {
public:
    bool isValidBST(TreeNode* root) {
	long upperLim = long(numeric_limits<int>::max()) + 1;
	long lowerLim = long(numeric_limits<int>::min()) - 1;

	stack<tuple<TreeNode *, long, long>> remain;
	remain.push(make_tuple(root, lowerLim, upperLim));
	while (!remain.empty()) {
	    tuple<TreeNode *, long, long> nxt = remain.top();
	    TreeNode * nxtNode = get<0>(nxt);
	    remain.pop();
	    if (nxtNode != nullptr) {
		long lower = get<1>(nxt);
		long upper = get<2>(nxt);
		long myVal = nxtNode->val;
		if (!(myVal > lower && myVal < upper)) { return false; }
		remain.push(make_tuple(nxtNode->left, lower, myVal));
		remain.push(make_tuple(nxtNode->right, myVal, upper));
	    } 
	}
	return true;
    }
};

int main() {
    Solution *S = new Solution();
    TreeNode *t1 = new TreeNode(5, 
			new TreeNode(1), 
			new TreeNode(4, new TreeNode(3), new TreeNode(6)));
    printPreOrder(t1);
    cout << "isValidBST = " << S->isValidBST(t1) << endl;
    TreeNode *t2 = new TreeNode(2, new TreeNode(1), new TreeNode(3));
    printPreOrder(t2);
    cout << "isValidBST = " << S->isValidBST(t2) << endl;
    TreeNode *t3 = new TreeNode(5, 
			new TreeNode(4), 
			new TreeNode(6, new TreeNode(3), new TreeNode(7)));
    printPreOrder(t3);
    cout << "isValidBST = " << S->isValidBST(t3) << endl;
}
