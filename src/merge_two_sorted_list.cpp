#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
	cout << "Hello World" << endl;

	ListNode *head;
	ListNode *one;
	ListNode *two;
	ListNode *tmp;

	if (list1->val > list2->val) {
	    head = list2;
	    one = list2;
	    two = list1;
	} else {
	    head = list1;
	    one = list1;
	    two = list2;
	}

	while (one->next != nullptr) {
	    if (one->next->val > two->val) {
		tmp = one->next;
		one->next = two;
		one = one->next;
		two = tmp;
	    } else {
		one = one->next;
	    }
	}

	one->next = two;
	return head;
    }

    static void printList(ListNode* l) {
	while(l != nullptr) {
	    cout << to_string(l->val) << ",";
	    l = l->next;
	}
	cout << endl;
    }
};

int main() {
    ListNode *list1 = new ListNode(1, new ListNode(2, new ListNode(4)));
    ListNode *list2 = new ListNode(1, new ListNode(3, new ListNode(4)));
    Solution *S = new Solution();
    Solution::printList(list1);
    Solution::printList(list2);
    ListNode *combined = S->mergeTwoLists(list1, list2);
    Solution::printList(combined);
}
