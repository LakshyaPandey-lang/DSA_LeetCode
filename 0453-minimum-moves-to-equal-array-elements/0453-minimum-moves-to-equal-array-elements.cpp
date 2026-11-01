class Solution {
public:
    int minMoves(vector<int>& nums)
    {
        int min = *min_element(nums.begin(), nums.end()), cnt = 0;
        
        for(int i = 0; i < nums.size(); i++)
        {
            cnt += nums[i] - min;
        }
        
        return cnt;
    }
};