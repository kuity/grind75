#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/remove-nth-node-from-end-of-list/
Difficulty: medium
Topics: linked list, two pointers
*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        auto node = head;
        auto remove = head;
        for (auto i=0; i<n; i++) node = node->next;

        ListNode *prev = nullptr;
        while (node != nullptr) {
            prev = remove;
            remove = remove->next;
            node = node->next;
        }

        // In this case, head of list to be removed
        if (prev == nullptr) return head->next;

        prev->next = remove->next;
        return head;
    }
};

int main() {
    ListNode *f = new ListNode(1);
    f->next = new ListNode(2);
    f->next->next = new ListNode(3);
    f->next->next->next = new ListNode(4);
    f->next->next->next->next = new ListNode(5);
    Solution *S = new Solution();
    auto ans = S->removeNthFromEnd(f, 2);
    auto node = ans;
    while (node != nullptr) {
        cout << node->val << ",";
        node = node->next;
    }
    cout << endl;

    f = new ListNode(1);
    f->next = new ListNode(2);
    f->next->next = new ListNode(3);
    ans = S->removeNthFromEnd(f, 3);
    node = ans;
    while (node != nullptr) {
        cout << node->val << ",";
        node = node->next;
    }
    cout << endl;

    f = new ListNode(1);
    ans = S->removeNthFromEnd(f, 1);
    node = ans;
    while (node != nullptr) {
        cout << node->val << ",";
        node = node->next;
    }
    cout << endl;
}
