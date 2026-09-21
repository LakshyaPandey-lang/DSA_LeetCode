class Solution {
public:
    vector<long long> resultArray(vector<int>& nums, int k) {
        vector<long long> ans(k, 0);
        vector<long long> dp(k, 0);

        for (int num : nums) {
            vector<long long> ndp(k, 0);

            int cur = num % k;

            ndp[cur]++;

            for (int r = 0; r < k; r++) {
                int newRem = (r * cur) % k;
                ndp[newRem] += dp[r];
            }

            dp = ndp;

            for (int r = 0; r < k; r++) {
                ans[r] += dp[r];
            }
        }

        return ans;
    }
};