
class Solution {
public:
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        const int MOD = 1e9 + 7;
        int n = edges.size() + 1;
        int LOG = 20;

        vector<vector<int>> adj(n + 1);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<vector<int>> up(LOG, vector<int>(n + 1, 0));
        vector<int> depth(n + 1, 0);
        vector<int> parent(n + 1, 0);

        queue<int> q;
        q.push(1);
        parent[1] = 1;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (v == parent[u]) continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                up[0][v] = u;

                q.push(v);
            }
        }

        for (int j = 1; j < LOG; j++) {
            for (int i = 1; i <= n; i++) {
                up[j][i] = up[j - 1][up[j - 1][i]];
            }
        }

        auto lca = [&](int u, int v) {
            if (depth[u] < depth[v]) swap(u, v);

            int diff = depth[u] - depth[v];

            for (int j = 0; j < LOG; j++) {
                if (diff & (1 << j)) {
                    u = up[j][u];
                }
            }

            if (u == v) return u;

            for (int j = LOG - 1; j >= 0; j--) {
                if (up[j][u] != up[j][v]) {
                    u = up[j][u];
                    v = up[j][v];
                }
            }

            return up[0][u];
        };

        vector<long long> power2(n + 1, 1);

        for (int i = 1; i <= n; i++) {
            power2[i] = (power2[i - 1] * 2) % MOD;
        }

        vector<int> ans;

        for (auto &query : queries) {
            int u = query[0];
            int v = query[1];

            int ancestor = lca(u, v);

            int d = depth[u] + depth[v] - 2 * depth[ancestor];

            if (d == 0) {
                ans.push_back(0);
            } else {
                ans.push_back(power2[d - 1]);
            }
        }

        return ans;
    }
};
