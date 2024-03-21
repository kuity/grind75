#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
Link: https://leetcode.com/problems/swap-nodes-in-pairs/
Difficulty: medium
Topics: hashtable, linked list, two pointers
*/
class Solution {
public:
    // Iterative solution
    ListNode* swapPairsIt(ListNode* head) {
        auto node = head;
        ListNode *prev;
        if (head != nullptr) head = head->next;
        while (node != nullptr && node->next != nullptr) {
            auto nxt = node->next;
            node->next = nxt->next;
            nxt->next = node;

            auto tmp = node;
            node = node->next;
            if (prev != nullptr) prev->next = nxt;
            prev = tmp;
        }

        return head;
    }

    // Recursive solution
    ListNode* swapPairs(ListNode* head) {
        if (head != nullptr && head->next != nullptr) {
            auto nxt = head->next;
            head->next = swapPairs(nxt->next);
            nxt->next = head;
            return nxt;
        }
        return head;
    }
};

int main() {
    Solution *S = new Solution();
    ListNode *f = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4))));
    ListNode *g = S->swapPairs(f);
    auto node = g;
    while (node != nullptr) {cout << node->val << ","; node = node->next;}
    cout << endl;

    f = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5)))));
    g = S->swapPairs(f);
    node = g;
    while (node != nullptr) {cout << node->val << ","; node = node->next;}
    cout << endl;

    f = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, new ListNode(5, new ListNode(6))))));
    g = S->swapPairs(f);
    node = g;
    while (node != nullptr) {cout << node->val << ","; node = node->next;}
    cout << endl;
}
