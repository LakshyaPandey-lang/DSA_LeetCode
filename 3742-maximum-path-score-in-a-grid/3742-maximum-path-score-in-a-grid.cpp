
class Solution {
public:
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dp(n, vector<int>(k + 1, -1));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                vector<int> curr(k + 1, -1);

                int val = grid[i][j];
                int cost = (val == 0 ? 0 : 1);

                if (i == 0 && j == 0) {
                    curr[0] = 0;
                } else {
                    for (int c = cost; c <= k; c++) {
                        int best = -1;

                        if (i > 0 && dp[j][c - cost] != -1) {
                            best = max(best, dp[j][c - cost]);
                        }

                        if (j > 0 && dp[j - 1][c - cost] != -1) {
                            best = max(best, dp[j - 1][c - cost]);
                        }

                        if (best != -1) {
                            curr[c] = best + val;
                        }
                    }
                }

                dp[j] = curr;
            }
        }

        return *max_element(dp[n - 1].begin(), dp[n - 1].end());
    }
};