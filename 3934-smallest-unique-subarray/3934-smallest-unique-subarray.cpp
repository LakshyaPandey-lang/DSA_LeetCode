
class Solution {
public:
    using ll = long long;

    static const int MOD1 = 1000000007;
    static const int MOD2 = 1000000009;
    static const int BASE = 911382323;

    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();

        vector<ll> p1(n + 1, 0), p2(n + 1, 0);
        vector<ll> pow1(n + 1, 1), pow2(n + 1, 1);

        for (int i = 0; i < n; i++) {
            ll x = nums[i] + 1LL;

            p1[i + 1] = (p1[i] * BASE + x) % MOD1;
            p2[i + 1] = (p2[i] * BASE + x) % MOD2;

            pow1[i + 1] = (pow1[i] * BASE) % MOD1;
            pow2[i + 1] = (pow2[i] * BASE) % MOD2;
        }

        auto check = [&](int len) -> bool {
            unordered_map<unsigned long long, int> mp;
            mp.reserve(2 * n);

            for (int i = 0; i + len <= n; i++) {
                ll h1 = (p1[i + len] -
                         p1[i] * pow1[len] % MOD1 + MOD1) % MOD1;

                ll h2 = (p2[i + len] -
                         p2[i] * pow2[len] % MOD2 + MOD2) % MOD2;

                unsigned long long key =
                    (static_cast<unsigned long long>(h1) << 32) |
                    static_cast<unsigned int>(h2);

                mp[key]++;
            }

            for (auto &it : mp) {
                if (it.second == 1) {
                    return true;
                }
            }

            return false;
        };

        int left = 1, right = n;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (check(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        return left;
    }
};
