
class Solution {
public:
    using ll = long long;

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        vector<array<ll, 4>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = {intervals[i][0], intervals[i][1],
                    intervals[i][2], i};
        }

        sort(a.begin(), a.end());

        vector<int> next(n);
        for (int i = 0; i < n; i++) {
            int l = i + 1, r = n;
            while (l < r) {
                int mid = l + (r - l) / 2;
                if (a[mid][0] > a[i][1])
                    r = mid;
                else
                    l = mid + 1;
            }
            next[i] = l;
        }

        struct State {
            ll score;
            vector<int> ids;
        };

        vector<vector<State>> dp(n + 1, vector<State>(5, {0, {}}));

        auto better = [](const State& x, const State& y) {
            if (x.score != y.score)
                return x.score > y.score;
            return x.ids < y.ids;
        };

        for (int i = n - 1; i >= 0; i--) {
            for (int k = 1; k <= 4; k++) {
                State skip = dp[i + 1][k];
                State take = dp[next[i]][k - 1];

                take.score += a[i][2];
                take.ids.push_back((int)a[i][3]);
                sort(take.ids.begin(), take.ids.end());

                dp[i][k] = better(take, skip) ? take : skip;
            }
        }

        return dp[0][4].ids;
    }
};
