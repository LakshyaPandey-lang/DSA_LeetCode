class Solution {
public:
    struct Node {
        int prod;
        int cnt[5];

        Node() {
            prod = 1;
            for (int i = 0; i < 5; i++)
                cnt[i] = 0;
        }
    };

    int n, k;
    vector<int> seg;

    vector<array<int, 5>> count;
    
    Node merge(Node L, Node R) {
        Node res;

        res.prod = (L.prod * R.prod) % k;

        for (int r = 0; r < k; r++)
            res.cnt[r] += L.cnt[r];

        for (int r = 0; r < k; r++) {
            int nr = (L.prod * r) % k;
            res.cnt[nr] += R.cnt[r];
        }

        return res;
    }

    vector<Node> tree;

    void build(int p, int l, int r, vector<int>& nums) {
        if (l == r) {
            tree[p].prod = nums[l] % k;
            tree[p].cnt[nums[l] % k] = 1;
            return;
        }

        int mid = (l + r) / 2;

        build(p * 2, l, mid, nums);
        build(p * 2 + 1, mid + 1, r, nums);

        tree[p] = merge(tree[p * 2], tree[p * 2 + 1]);
    }

    void update(int p, int l, int r, int idx, int val) {
        if (l == r) {
            tree[p] = Node();
            tree[p].prod = val % k;
            tree[p].cnt[val % k] = 1;
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(p * 2, l, mid, idx, val);
        else
            update(p * 2 + 1, mid + 1, r, idx, val);

        tree[p] = merge(tree[p * 2], tree[p * 2 + 1]);
    }

    Node query(int p, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tree[p];

        int mid = (l + r) / 2;

        if (qr <= mid)
            return query(p * 2, l, mid, ql, qr);

        if (ql > mid)
            return query(p * 2 + 1, mid + 1, r, ql, qr);

        Node L = query(p * 2, l, mid, ql, qr);
        Node R = query(p * 2 + 1, mid + 1, r, ql, qr);

        return merge(L, R);
    }

    vector<int> resultArray(vector<int>& nums, int k,
                            vector<vector<int>>& queries) {
        this->k = k;
        n = nums.size();

        tree.assign(4 * n + 5, Node());

        build(1, 0, n - 1, nums);

        vector<int> result;

        for (auto &q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            update(1, 0, n - 1, index, value);

            Node res = query(1, 0, n - 1, start, n - 1);

            result.push_back(res.cnt[x]);
        }

        return result;
    }
};