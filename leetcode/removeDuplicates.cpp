#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        // if(!nums.empty()){
        //     vector<int>::iterator it = nums.begin();
        //     for(;it!=nums.end()-1;++it){
        //         if(*it==*(it+1)){
        //             nums.erase(it);
        //             --it;
        //         }
        //     }
        // }
        
        // if(!nums.empty()){
        //     for(int i=0;i<nums.size()-1;i++){
        //         cout << "size="<<nums.size() << " i=" << i << endl;
        //         if(nums.at(i)==nums.at(i+1)){
        //             nums.erase(nums.begin() + i);
        //             --i;
        //         }
        //     }
        // }
        
        if(!nums.empty()){
            nums.erase(unique(nums.begin(), nums.end()), nums.end());
        }
        return nums.size();
    }
};

int main(){
    int result = 0;
    vector<int> nums = {};
    Solution lame; 
    
    result = lame.removeDuplicates(nums);

    cout << "result = " << result << endl;
    
    for(int i=0;i<nums.size();i++){
        cout << nums.at(i) << " ";
        if(i==nums.size()-1){
            cout << endl;
        }
    }
    return 0;
}