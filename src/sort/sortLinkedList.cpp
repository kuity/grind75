#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

/*
Link: https://leetcode.com/problems/sort-list/description/
Difficulty: Medium
Topics: linked list, two pointers, sorting, merge sort, divide and conquer
*/
class Solution {
public:
    // Find the middle, split into 2 lists, sort both
    // then merge the 2 sorted lists
    ListNode* sortList(ListNode* head) {
        //If List Contain a Single or 0 Node
        if(head == NULL || head ->next == NULL) return head;
        
        ListNode *temp = NULL;
        ListNode *slow = head;
        ListNode *fast = head;
        
        // 2 pointer appraoach / turtle-hare Algorithm (Finding the middle element)
        while(fast !=  NULL && fast -> next != NULL) {
            temp = slow;
            slow = slow->next;          //slow increment by 1
            fast = fast ->next ->next;  //fast incremented by 2
        }   
        temp -> next = NULL;            //end of first left half
        
        ListNode* l1 = sortList(head);    //left half recursive call
        ListNode* l2 = sortList(slow);    //right half recursive call
        return mergelist(l1, l2);         //mergelist Function call
    }
    
    //MergeSort Function O(n*logn)
    ListNode* mergelist(ListNode *l1, ListNode *l2) {
        ListNode *ptr = new ListNode(0);
        ListNode *curr = ptr;
        
        while(l1 != NULL && l2 != NULL) {
            if(l1->val <= l2->val) {
                curr -> next = l1;
                l1 = l1 -> next;
            } else {
                curr -> next = l2;
                l2 = l2 -> next;
            }
            curr = curr ->next;
        }
        
        if(l1 != NULL) {
            curr -> next = l1;
            l1 = l1->next;
        }
        
        if(l2 != NULL) {
            curr -> next = l2;
            l2 = l2 ->next;
        }
        
        return ptr->next;
    }
};

int main() {
    ListNode *f = new ListNode(-1);
    f->next = new ListNode(5);
    f->next->next = new ListNode(3);
    f->next->next->next = new ListNode(4);
    f->next->next->next->next = new ListNode(0);
    Solution *S = new Solution();
    auto ans = S->sortList(f);
    auto node = ans;
    while (node != nullptr) {
        cout << node->val << ",";
        node = node->next;
    }
    cout << endl;
}
