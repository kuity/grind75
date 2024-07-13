#include <iostream>

using namespace std;

/*
Link: https://leetcode.com/problems/remove-duplicates-from-an-unsorted-linked-list
Difficulty: Medium
Topics: linked list, hashtable
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
    ListNode* deleteDuplicatesUnsorted(ListNode* head) {
        unordered_map<int, int> M;
        auto node = head;
        while (node != nullptr) {
            M[node->val]++;
            node = node->next;
        }
        ListNode *newHead = head;
        while (newHead && M[newHead->val] > 1) newHead = newHead->next;
        node = newHead;
        while (node && node->next != nullptr) {
            if (M[node->next->val] > 1) node->next = node->next->next;
            else node = node->next;
        }
        return newHead;
    }
};

int main() {
    Solution *S = new Solution();
    int ans;
    cout << "ans is " << ans;
}
