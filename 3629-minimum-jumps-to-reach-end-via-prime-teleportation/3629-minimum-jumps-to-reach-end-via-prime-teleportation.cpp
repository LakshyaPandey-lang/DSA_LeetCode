class Solution {
public:
    int minJumps(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 0;

        int maxVal = *max_element(nums.begin(), nums.end());

        vector<bool> isPrime(maxVal + 1, true);
        isPrime[0] = isPrime[1] = false;

        for (int i = 2; i * i <= maxVal; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= maxVal; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        vector<vector<int>> indices(maxVal + 1);

        for (int i = 0; i < n; i++) {
            int x = nums[i];

            for (int p = 2; p * p <= x; p++) {
                if (x % p == 0) {
                    indices[p].push_back(i);

                    while (x % p == 0)
                        x /= p;
                }
            }

            if (x > 1)
                indices[x].push_back(i);
        }

        vector<int> dist(n, -1);
        vector<bool> usedPrime(maxVal + 1, false);

        queue<int> q;
        q.push(0);
        dist[0] = 0;

        while (!q.empty()) {
            int i = q.front();
            q.pop();

            if (i == n - 1)
                return dist[i];

            if (i + 1 < n && dist[i + 1] == -1) {
                dist[i + 1] = dist[i] + 1;
                q.push(i + 1);
            }

            if (i - 1 >= 0 && dist[i - 1] == -1) {
                dist[i - 1] = dist[i] + 1;
                q.push(i - 1);
            }

            int x = nums[i];

            if (isPrime[x] && !usedPrime[x]) {
                usedPrime[x] = true;

                for (int j : indices[x]) {
                    if (dist[j] == -1) {
                        dist[j] = dist[i] + 1;
                        q.push(j);
                    }
                }
            }
        }

        return -1;
    }
};