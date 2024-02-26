#include <unordered_map>
#include <iostream>
#include <queue>

using namespace std;

/*
Link: https://leetcode.com/problems/task-scheduler
Difficulty: Medium
Topics: Heap, Hashtable, Greedy
*/
class Solution {
public:
    // In this approach I simulate the actual task scheduler using a max heap
    // and a hashmap to store the last run timestep of each task
    // This way, able to check whether the stipulated cooldown is done before adding
    // a task from the wait queue back into the run queue
    int leastInterval(vector<char>& tasks, int n) {
        // First, figure out the frequency of each task
        unordered_map<char, int> F;
        for (auto c: tasks) F[c]++;

        // The maxheap containing frequency of each task because always wanna schedule highest freq first
        priority_queue<pair<char, int>, vector<pair<char, int>>, 
            function<bool(pair<char, int>, pair<char, int>)> 
        > Q1 ( 
            F.begin(), F.end(),
            [](const pair<char, int> &a, const pair<char, int> &b) {
                return a.second < b.second;
        });

        // Track the last run timestep for each task
        unordered_map<char, int> tracker;

        // A separate queue to keep tasks on "cooldown"
        queue<pair<char, int>> Q2;
        int timestep = 0;

        while (!Q1.empty() || !Q2.empty()) {
            // If possible to put a waiting task back into running Q, do it
            if (!Q2.empty()) {
                auto nextTask = Q2.front();
                auto T = nextTask.first;

                // if CD is done put task into run Q
                if (tracker.find(T) != tracker.end()) {
                    if (tracker[T] + n < timestep) {
                        Q1.push(nextTask);
                        Q2.pop();
                    }
                }  else {
                    Q1.push(nextTask);
                    Q2.pop();
                }
            }

            // Run a task and put into wait queue
            if (!Q1.empty()) {
                auto nextRun = Q1.top();
                // cout << "Running " << nextRun.first << " at timestep " << timestep << endl;
                nextRun.second--;
                tracker[nextRun.first] = timestep;
                Q1.pop();
                if (nextRun.second > 0) Q2.push(nextRun);
                timestep++;
            } 

            // Check need to wait how long
            else {
                auto waitTask = Q2.front();
                auto cd = tracker[waitTask.first] +(n+1) - timestep;
                timestep += cd;
            }
        }
        return timestep;
    }


    // Solution taken from leetcode 
    // Because only the least time possible is needed in the output
    // we don't really need to simulate the full process
    // After optimization, it is really just a calculation problem
    //
    // Why this calculation works
    // We can divide this into 2 cases
    // Either the cooldown n matters, or it doesn't matter
    // Assuming it doesn't matter, then simply ans = size(tasks)
    // Assuming it does matter, then ans > size(tasks)
    // So we don't really care which case it is, at the end we just need to return
    // max(size(tasks), X), where X is the calculation considering n
    //
    // Regarding X, now we know we should always prioritize the task with the highest frequency
    // Suppose this task is A
    // Considering the cooldown, the NEXT time we can run task A is in n+1 time steps
    // Because we take 1 time step to run A then we wait n time steps
    // Then at the very least, this cycle MUST repeat Freq(A)-1 times 
    // Now, if A is the only task with frequency = Freq(A), then we add 1 for the final time 
    // A has to run, then we are done
    // Whatever other tasks have lesser frequency, thus they can fit into the cooldown period
    // Oh but what if they cannot fit into the cooldown period? 
    // Then this situation will fit into case 2 above
    // Now, what if there exists B with Freq(B) == Freq(A)
    // Then, we simply add 1 for each T where Freq(T) = Freq(A) 
    int leastIntervalMath(vector<char>& tasks, int n) {
        // First, figure out the frequency of each task
        unordered_map<char, int> F;
        int maxFreq = 0;
        for (auto c: tasks) { F[c]++; if (F[c] > maxFreq) maxFreq = F[c]; }

        int ans = (maxFreq-1) * (n+1);
        for (auto kv: F) if (kv.second == maxFreq) ans++;
        return max(ans, int(tasks.size()));
    }
};

int main() {
    Solution *S = new Solution();
    vector<char> tasks = {'A','A','A','B','B','B'};
    auto ans = S->leastIntervalMath(tasks, 2);
    cout << "Answer is : " << ans << endl;

    tasks = {'A','A','A','A','A','A','B','C','D','E','F','G'};
    ans = S->leastIntervalMath(tasks, 2);
    cout << "Answer is : " << ans << endl;
}
