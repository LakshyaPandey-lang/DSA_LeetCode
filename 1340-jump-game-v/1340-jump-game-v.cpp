class Solution {
public:
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        vector<int> dp(n, 0);

        function<int(int)> dfs = [&](int i) -> int {
            if (dp[i] != 0) return dp[i];

            dp[i] = 1;

            for (int j = i + 1; j < n && j <= i + d; j++) {
                if (arr[j] >= arr[i]) break;
                dp[i] = max(dp[i], 1 + dfs(j));
            }

            for (int j = i - 1; j >= 0 && j >= i - d; j--) {
                if (arr[j] >= arr[i]) break;
                dp[i] = max(dp[i], 1 + dfs(j));
            }

            return dp[i];
        };

        int ans = 0;

        for (int i = 0; i < n; i++) {
            ans = max(ans, dfs(i));
        }

        return ans;
    }
};