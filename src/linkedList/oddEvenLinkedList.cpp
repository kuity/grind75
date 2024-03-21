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
Link: https://leetcode.com/problems/odd-even-linked-list/
Difficulty: medium
Topics: linked list
*/
class Solution {
public:
    void helper(ListNode *node, bool isOdd, ListNode *second) {
        if (node->next != nullptr && node->next->next != nullptr) {
            auto nxt = node->next;
            node->next = node->next->next;
            helper(nxt, !isOdd, second);
            return;
        }
        if (isOdd) node->next = second;
        else {
            node->next->next = second;
            node->next = nullptr;
        }
        return;
    }

    // recursive solution
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr) return head;
        helper(head, true, head->next);
        return head;
    }

    // An iterative solution
    ListNode* oddEvenListIt(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        auto second = head->next;
        auto node = head;
        int count = 0;
        while (node->next != nullptr && node->next->next != nullptr) {
            auto tmp = node->next;
            node->next = node->next->next;
            node = tmp;
            count++;
        }
        if (count%2==0) node->next = second;
        else {
            node->next->next = second;
            node->next = nullptr;
        }
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
    S->oddEvenList(f);
    auto node = f;
    while (node != nullptr) {
        cout << node->val << ",";
        node = node->next;
    }
    cout << endl;
}
