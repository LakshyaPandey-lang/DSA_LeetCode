
class Solution {
public:
    long long maximumScore(vector<vector<int>>& grid) {
        int n = grid.size();

        vector<vector<long long>> pref(
            n, vector<long long>(n + 1, 0)
        );

        for (int j = 0; j < n; j++) {
            for (int i = 0; i < n; i++) {
                pref[j][i + 1] =
                    pref[j][i] + grid[i][j];
            }
        }

        if (n == 1) return 0;

        const long long NEG = LLONG_MIN / 4;

        vector<vector<long long>> dp(
            n + 1, vector<long long>(n + 1, NEG)
        );

        for (int a = 0; a <= n; a++) {
            for (int b = 0; b <= n; b++) {
                dp[a][b] =
                    pref[0][max(a, b)] - pref[0][a];
            }
        }

        for (int j = 1; j < n - 1; j++) {
            vector<vector<long long>> ndp(
                n + 1, vector<long long>(n + 1, NEG)
            );

            for (int b = 0; b <= n; b++) {
                vector<long long> left(n + 1);
                vector<long long> right(n + 2, NEG);

                long long best = NEG;

                for (int a = 0; a <= n; a++) {
                    best = max(best, dp[a][b]);
                    left[a] = best;
                }

                for (int a = n; a >= 0; a--) {
                    long long gain =
                        pref[j][max(a, b)] - pref[j][b];

                    right[a] = max(
                        right[a + 1],
                        dp[a][b] + gain
                    );
                }

                for (int c = 0; c <= n; c++) {
                    long long gain =
                        pref[j][max(b, c)] - pref[j][b];

                    long long option1 = left[c] + gain;
                    long long option2 = right[c + 1];

                    ndp[b][c] = max(option1, option2);
                }
            }

            dp = move(ndp);
        }

        long long ans = 0;

        for (int a = 0; a <= n; a++) {
            for (int b = 0; b <= n; b++) {
                long long gain =
                    pref[n - 1][max(a, b)]
                    - pref[n - 1][b];

                ans = max(ans, dp[a][b] + gain);
            }
        }

        return ans;
    }
};