class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans;
        for(int i = 0; i < n; i++){
            int num = nums[i] > 0 ? nums[i] : -nums[i];
            if(nums[num-1]>0){
                nums[num-1] = -nums[num-1];
            }else{
                ans.push_back(num);
            }
        }
        return ans;
    }
};
