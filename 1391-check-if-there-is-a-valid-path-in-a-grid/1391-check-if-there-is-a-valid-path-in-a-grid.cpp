class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> vis(m, vector<int>(n, 0));

        vector<vector<pair<int,int>>> dirs(7);

        dirs[1] = {{0,-1}, {0,1}};
        dirs[2] = {{-1,0}, {1,0}};
        dirs[3] = {{0,-1}, {1,0}};
        dirs[4] = {{0,1}, {1,0}};
        dirs[5] = {{0,-1}, {-1,0}};
        dirs[6] = {{0,1}, {-1,0}};

        queue<pair<int,int>> q;
        q.push({0,0});
        vis[0][0] = 1;

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            if (r == m - 1 && c == n - 1)
                return true;

            int type = grid[r][c];

            for (auto [dr, dc] : dirs[type]) {
                int nr = r + dr;
                int nc = c + dc;

                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;

                if (vis[nr][nc])
                    continue;

                bool connected = false;

                for (auto [ndr, ndc] : dirs[grid[nr][nc]]) {
                    if (ndr == -dr && ndc == -dc) {
                        connected = true;
                        break;
                    }
                }

                if (connected) {
                    vis[nr][nc] = 1;
                    q.push({nr, nc});
                }
            }
        }

        return false;
    }
};