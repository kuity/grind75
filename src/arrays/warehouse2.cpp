#include <iostream>
#include <vector>

using namespace std;

/*
Link: https://leetcode.com/problems/put-boxes-into-the-warehouse-ii/description
Difficulty: Medium
Topics: array, greedy, sorting
*/
class Solution {
public:
    // Greedy approach that try to fit the biggest boxes first
    // And keep 2 pointers for left and right of warehouse
    // This works because we can change the insert order of the boxes
    int maxBoxesInWarehouse(vector<int>& boxes, vector<int>& warehouse) {
        int left = 0;
        int right = warehouse.size()-1;
        sort(boxes.begin(), boxes.end(), greater<int>());
        int ans = 0;
        int index = 0;
        while (left <= right && index < boxes.size()) {
            if (boxes[index] <= warehouse[left]) {
                index++;
                left++;
                ans++;
            } else if (boxes[index] <= warehouse[right]) {
                index++;
                right--;
                ans++;
            } else {
                index++;
            }
        }
        return ans;
    }
};

int main() {
    Solution *S = new Solution();
    vector<int> boxes;
    vector<int> warehouse;
    int ans;

    boxes = {1,2,2,3,4};
    warehouse = {3,4,1,2};
    ans = S->maxBoxesInWarehouse(boxes, warehouse);
    cout << "ans is " << ans << endl;

    boxes = {3,5,5,2};
    warehouse = {2,1,3,4,5};
    ans = S->maxBoxesInWarehouse(boxes, warehouse);
    cout << "ans is " << ans << endl;
}
