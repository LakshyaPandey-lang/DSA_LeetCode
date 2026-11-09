
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> count(k, 0);

        priority_queue<pair<int, int>,
                       vector<pair<int, int>>,
                       greater<pair<int, int>>> busy;

        set<int> available;

        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        int n = arrival.size();

        for (int i = 0; i < n; i++) {
            int time = arrival[i];

            while (!busy.empty() && busy.top().first <= time) {
                available.insert(busy.top().second);
                busy.pop();
            }

            if (available.empty()) {
                continue;
            }

            int start = i % k;
            auto it = available.lower_bound(start);

            if (it == available.end()) {
                it = available.begin();
            }

            int server = *it;
            available.erase(it);

            count[server]++;

            busy.push({time + load[i], server});
        }

        int mx = *max_element(count.begin(), count.end());

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == mx) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};
