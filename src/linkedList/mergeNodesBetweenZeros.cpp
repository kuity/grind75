#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/merge-nodes-in-between-zeros
Difficulty: Medium
Topics: linked list, simulation
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
    ListNode* mergeNodes(ListNode* head) {
        auto node = head;
        auto v = node->val;
        while(node->next != nullptr) {
            if (node->next->val != 0) {
                v += node->next->val;
                node->next = node->next->next;
            } else {
                node->val = v;
                if (node->next->next == nullptr) node->next = nullptr;
                else {
                    node = node->next;
                    v = node->val;
                }
            }
        }
        return head;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    cout << "ans is " << ans;
}
