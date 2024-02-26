#include <iostream>
#include <unordered_map>

using namespace std;

class TimeMap {
private:
    unordered_map<string, vector<pair<int, string>>> M;

public:
    TimeMap() {
        M = {};
    }

    int findNearest(int ts, vector<pair<int, string>> &v) {
        int left = 0;
        int right = v.size() - 1;
        int mid, midnum;

        while (left <= right) {
            mid = left + (right - left) / 2;
            midnum = v[mid].first;
            if (midnum == ts) {
                return mid;
            } else if (midnum < ts) {
                left = mid+1;
            } else {
                right = mid-1;
            }
        }

        // At this juncture, L > R
        // If we always want to return the bigger number, then return L
        // If we always want to return the smaller number, then return R
        return right;
    }

    void set(string key, string value, int timestamp) {
        if (M.find(key) == M.end()) {
            M[key] = {{timestamp, value}};
        } else {
            M[key].push_back({timestamp, value});
        }
    }
    
    string get(string key, int timestamp) {
        if (M.find(key) == M.end()) {
            return "";
        } else {
            auto index = findNearest(timestamp, M[key]);
            if (index < 0) {
                return "";
            }
            return M[key][index].second;
        }
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
int main() {
    string ans;
    TimeMap* obj = new TimeMap();
    obj->set("foo", "bar", 1);
    ans = obj->get("foo", 1);
    cout << "Get 1 returns " << ans << endl;
    ans = obj->get("foo", 3);
    cout << "Get 3 returns " << ans << endl;
    obj->set("foo", "bar2", 4);
    ans = obj->get("foo", 4);
    cout << "Get 4 returns " << ans << endl;
    ans = obj->get("foo", 5);
    cout << "Get 5 returns " << ans << endl;
}
