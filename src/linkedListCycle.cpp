#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
	ListNode *slowPtr = head;
	ListNode *fastPtr = head;

	while(fastPtr != NULL && slowPtr != NULL) {
	    slowPtr = slowPtr->next;
	    fastPtr = fastPtr->next;
	    if (fastPtr != NULL) {
		fastPtr = fastPtr->next;
		if (slowPtr == fastPtr) {
		    return true;
		}
	    }
	}

	return false;
    }
};

int main() {
    ListNode *f = new ListNode(3);
    f->next = new ListNode(2);
    f->next->next = new ListNode(0);
    f->next->next->next = new ListNode(-4);
    f->next->next->next->next = f->next;

    Solution *S = new Solution();
    cout << S->hasCycle(f) << endl;
}
