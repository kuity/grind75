#include <iostream>
#include <queue>
using namespace std;

/*
Link: https://leetcode.com/problems/design-hit-counter/
Difficulty: Medium
Topics: array, binary search, design, queue, data stream
*/
class HitCounter {
    // {timestamp, numHits}
    queue<pair<int, int>> tracker;
    int totalHits;

public:
    HitCounter() {
        totalHits = 0;
    }

    void cleanTracker(int timestamp) {
        auto cutoff = timestamp - 300;
        while (!tracker.empty()) {
            auto f = tracker.front();
            if (f.first <= cutoff) {
                totalHits -= f.second;
                tracker.pop();
            } else break;
        }
    }
    
    void hit(int timestamp) {
        // cout << "hit " << timestamp << endl;
        if (tracker.size() == 0) {
            tracker.push({timestamp, 1});
            totalHits++;
        } else {
            pair<int, int> &last = tracker.back();
            if (last.first == timestamp) last.second++;
            else tracker.push({timestamp, 1});
            totalHits++;
        }
    }
    
    int getHits(int timestamp) {
        // cout << "gethit " << timestamp << endl;
        cleanTracker(timestamp);
        return totalHits;
    }
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */

int main() {
    HitCounter* obj = new HitCounter();
    int ans;
    obj->hit(1);
    obj->hit(2);
    obj->hit(3);
    obj->hit(3);
    ans = obj->getHits(4);
    cout << "hits at 4 is " << ans << endl;
    obj->hit(300);
    ans = obj->getHits(300);
    cout << "hits at 300 is " << ans << endl;
    ans = obj->getHits(301);
    cout << "hits at 301 is " << ans << endl;
    ans = obj->getHits(301);
    cout << "hits at 301 is " << ans << endl;
}
