
class Solution {
public:
    int assignEdgeWeights(vector<vector<int>>& edges) {
        const int MOD = 1e9 + 7;
        int n = edges.size() + 1;

        vector<vector<int>> adj(n + 1);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> depth(n + 1, -1);
        queue<int> q;

        q.push(1);
        depth[1] = 0;

        int maxDepth = 0;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            for (int v : adj[u]) {
                if (depth[v] == -1) {
                    depth[v] = depth[u] + 1;
                    maxDepth = max(maxDepth, depth[v]);
                    q.push(v);
                }
            }
        }

        long long ans = 1;

        for (int i = 0; i < maxDepth - 1; i++) {
            ans = (ans * 2) % MOD;
        }

        return ans;
    }
};
