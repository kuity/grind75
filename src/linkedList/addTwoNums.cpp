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
Link: https://leetcode.com/problems/add-two-numbers/
Difficulty: medium
Topics: linked list
*/
class Solution {
public:
    ListNode *helper(ListNode* l1, ListNode* l2, bool carry) {
        if (l1 == nullptr && l2 == nullptr && !carry) return nullptr;
        int l1val = l1==nullptr ? 0 : l1->val;
        int l2val = l2==nullptr ? 0 : l2->val;
        int sum = l1val + l2val + carry;
        carry = sum > 9;
        sum = sum > 9 ? sum-10 : sum;

        auto l1nxt = l1 == nullptr ? nullptr : l1->next;
        auto l2nxt = l2 == nullptr ? nullptr : l2->next;

        auto head = new ListNode(sum);
        head->next = helper(l1nxt, l2nxt, carry);
        return head;
    }

    ListNode *addTwoNumbers(ListNode* l1, ListNode* l2) {
        return helper(l1, l2, 0);
    }
};

int main() {
    ListNode *f = new ListNode(2);
    f->next = new ListNode(4);
    f->next->next = new ListNode(3);

    ListNode *g = new ListNode(5);
    g->next = new ListNode(6);
    g->next->next = new ListNode(4);

    Solution *S = new Solution();
    auto ans = S->addTwoNumbers(f, g);
    auto node = ans;
    while (node != nullptr) {
        cout << node->val << ",";
        node = node->next;
    }
    cout << endl;
}
