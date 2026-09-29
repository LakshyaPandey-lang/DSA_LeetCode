
class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<long long, 4>> a;
        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        sort(a.begin(), a.end(), [](auto& x, auto& y) {
            return x[1] < y[1];
        });

        vector<long long> ends(n);
        for (int i = 0; i < n; i++) {
            ends[i] = a[i][1];
        }

        struct State {
            long long weight = 0;
            vector<int> indices;
        };

        vector<vector<State>> dp(5, vector<State>(n + 1));

        for (int k = 1; k <= 4; k++) {
            for (int i = 1; i <= n; i++) {
                dp[k][i] = dp[k][i - 1];

                long long l = a[i - 1][0];
                long long w = a[i - 1][2];
                int idx = a[i - 1][3];

                int p = lower_bound(
                    ends.begin(),
                    ends.begin() + i - 1,
                    l
                ) - ends.begin();

                State candidate = dp[k - 1][p];
                candidate.weight += w;

                candidate.indices.insert(
                    lower_bound(
                        candidate.indices.begin(),
                        candidate.indices.end(),
                        idx
                    ),
                    idx
                );

                if (candidate.weight > dp[k][i].weight ||
                    (candidate.weight == dp[k][i].weight &&
                     candidate.indices < dp[k][i].indices)) {
                    dp[k][i] = candidate;
                }
            }
        }

        return dp[4][n].indices;
    }
};