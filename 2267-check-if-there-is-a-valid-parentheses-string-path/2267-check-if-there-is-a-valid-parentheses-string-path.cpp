class Solution {
public:
    int m, n;
    int dp[101][101][201];

    bool dfs(int i, int j, int balance, vector<vector<char>>& grid) {
        if (i >= m || j >= n || balance < 0)
            return false;

        balance += (grid[i][j] == '(') ? 1 : -1;

        if (balance < 0 || balance > (m + n - 2 - i - j))
            return false;

        if (i == m - 1 && j == n - 1)
            return balance == 0;

        if (dp[i][j][balance] != -1)
            return dp[i][j][balance];

        bool ans = dfs(i + 1, j, balance, grid) ||
                   dfs(i, j + 1, balance, grid);

        return dp[i][j][balance] = ans;
    }

    bool hasValidPath(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();

        if (grid[0][0] == ')' ||
            grid[m - 1][n - 1] == '(' ||
            (m + n - 1) % 2 != 0)
            return false;

        memset(dp, -1, sizeof(dp));

        return dfs(0, 0, 0, grid);
    }
};