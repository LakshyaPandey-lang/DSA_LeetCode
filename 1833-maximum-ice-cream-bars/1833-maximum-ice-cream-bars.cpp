
class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins) {
        vector<int> freq(100001, 0);

        for (int x : costs) {
            freq[x]++;
        }

        int ans = 0;

        for (int price = 1; price <= 100000; price++) {
            while (freq[price] > 0 && coins >= price) {
                coins -= price;
                ans++;
                freq[price]--;
            }

            if (coins < price) break;
        }

        return ans;
    }
};
