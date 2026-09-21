class Solution {
public:
    long long getPos(int x, int y, int side) {
        if (y == 0)
            return x;
        if (x == side)
            return side + y;
        if (y == side)
            return 3LL * side - x;
        return 4LL * side - y;
    }

    bool possible(vector<long long>& pos, int n, int k, long long perimeter, long long d) {
        vector<long long> a(2 * n);

        for (int i = 0; i < n; i++) {
            a[i] = pos[i];
            a[i + n] = pos[i] + perimeter;
        }

        vector<int> nxt(2 * n, 2 * n);

        int j = 0;

        for (int i = 0; i < 2 * n; i++) {
            if (j < i + 1)
                j = i + 1;

            while (j < 2 * n && a[j] - a[i] < d)
                j++;

            nxt[i] = j;
        }

        for (int start = 0; start < n; start++) {
            int cur = start;
            bool ok = true;

            for (int cnt = 1; cnt < k; cnt++) {
                cur = nxt[cur];

                if (cur >= start + n) {
                    ok = false;
                    break;
                }
            }

            if (ok && a[start + n] - a[cur] >= d)
                return true;
        }

        return false;
    }

    int maxDistance(int side, vector<vector<int>>& points, int k) {
        int n = points.size();
        long long perimeter = 4LL * side;

        vector<long long> pos;

        for (auto &p : points) {
            pos.push_back(getPos(p[0], p[1], side));
        }

        sort(pos.begin(), pos.end());

        long long low = 0;
        long long high = 2LL * side;

        while (low < high) {
            long long mid = low + (high - low + 1) / 2;

            if (possible(pos, n, k, perimeter, mid))
                low = mid;
            else
                high = mid - 1;
        }

        return (int)low;
    }
};