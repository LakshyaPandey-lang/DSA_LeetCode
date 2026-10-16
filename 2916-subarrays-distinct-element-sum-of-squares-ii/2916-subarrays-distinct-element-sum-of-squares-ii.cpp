class Solution {
    static const long long MOD = 1000000007;

    struct Node {
        long long sum = 0;
        long long sq = 0;
        long long lazy = 0;
    };

    vector<Node> tree;
    int n;

    void apply(int node, int l, int r, long long val) {
        long long len = r - l + 1;
        tree[node].sq = (tree[node].sq + 2 * val % MOD * tree[node].sum % MOD
                         + val * val % MOD * len) % MOD;
        tree[node].sum = (tree[node].sum + val * len) % MOD;
        tree[node].lazy = (tree[node].lazy + val) % MOD;
    }

    void push(int node, int l, int r) {
        if (tree[node].lazy == 0 || l == r) return;

        int mid = (l + r) / 2;
        long long val = tree[node].lazy;

        apply(node * 2, l, mid, val);
        apply(node * 2 + 1, mid + 1, r, val);

        tree[node].lazy = 0;
    }

    void update(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return;

        if (ql <= l && r <= qr) {
            apply(node, l, r, 1);
            return;
        }

        push(node, l, r);

        int mid = (l + r) / 2;
        update(node * 2, l, mid, ql, qr);
        update(node * 2 + 1, mid + 1, r, ql, qr);

        tree[node].sum = (tree[node * 2].sum +
                          tree[node * 2 + 1].sum) % MOD;

        tree[node].sq = (tree[node * 2].sq +
                         tree[node * 2 + 1].sq) % MOD;
    }

public:
    int sumCounts(vector<int>& nums) {
        n = nums.size();
        tree.assign(4 * n + 5, Node());

        vector<int> last(100001, 0);
        long long ans = 0;

        for (int i = 1; i <= n; i++) {
            int x = nums[i - 1];
            int p = last[x];

            update(1, 1, n, p + 1, i);

            ans = (ans + tree[1].sq) % MOD;
            last[x] = i;
        }

        return ans;
    }
};