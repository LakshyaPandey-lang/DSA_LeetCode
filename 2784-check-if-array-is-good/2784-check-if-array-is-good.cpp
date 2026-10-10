class Solution {
public:
    bool isGood(vector<int>& nums) {
        int n = nums.size() - 1;

        if (n < 1) return false;

        vector<int> freq(n + 1, 0);

        for (int x : nums) {
            if (x < 1 || x > n) return false;
            freq[x]++;
        }

        for (int i = 1; i < n; i++) {
            if (freq[i] != 1) return false;
        }

        return freq[n] == 2;
    }
};