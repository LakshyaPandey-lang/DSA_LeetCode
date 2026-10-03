class Solution {
public:
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();

        vector<int> suf(n);
        vector<int> ans(n, -1);

        suf[n - 1] = nums[n - 1];

        for (int i = n - 2; i >= 0; i--) {
            suf[i] = min(nums[i], suf[i + 1]);
        }

        int mx = 0;

        for (int i = 0; i < n; i++) {
            mx = max(mx, nums[i]);

            if (i == n - 1 || mx <= suf[i + 1]) {
                int j = i;

                while (j >= 0 && ans[j] == -1) {
                    ans[j] = mx;
                    j--;
                }
            }
        }

        return ans;
    }
};