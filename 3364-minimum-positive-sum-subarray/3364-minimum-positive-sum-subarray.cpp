class Solution {
public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int n = nums.size();
        int sum = INT_MAX;
        bool flag = false;
        for(int i=0; i<n; i++){
            int curr_sum = 0;
            for(int j=i; j<n; j++){
                curr_sum += nums[j];
                if(j-i+1 >= l && j-i+1 <= r && curr_sum > 0){
                    sum = min(sum , curr_sum);
                    flag = true;
                }
            }
        }
        if(flag){
            return sum;
        }
        return -1;
    }
};