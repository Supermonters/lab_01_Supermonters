#include <chrono>
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
      std::set<vector<int>> currset;
        for(int i =0;i<nums.size();++i){
          for(int j =i+1;j<nums.size();++j){
            for(int k=j+1;k<nums.size();++k){
              if(((nums[i]+nums[j]+nums[k])==0)){
                std::vector<int> curr = {nums[i],nums[j],nums[k]};
                sort(curr.begin(),curr.end());
                currset.insert(curr);
              }
            }
          }
        }
        return vector<vector<int>>(currset.begin(), currset.end());
    }
};

int main() {
    Solution sol;
    // Data sizes: you can extend this up to 8000. 
    // If n = 8000 is too slow, adjust the max size (e.g., to 4000) and note this in your report.
    vector<int> testSizes = {100,200,400,800, 1600, 3200, 4000};
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(-1000, 1000);

    cout.setf(ios::fixed);
    
    for (auto n : testSizes) {
        vector<int> nums;
        // Ensure at least one valid triplet is included if n >= 3.
        if (n >= 3) {
            int a = dis(gen), b = dis(gen);
            while (a + b == 0) {
                a = dis(gen);
                b = dis(gen);
            }
            // Insert a valid triplet: [-a, -b, a+b] whose sum is 0.
            nums.push_back(-a);
            nums.push_back(-b);
            nums.push_back(a + b);
        }
        // Fill the rest of the array with random values.
        while (nums.size() < n) {
            nums.push_back(dis(gen));
        }
        // Shuffle to randomize the location of the valid triplet.
        shuffle(nums.begin(), nums.end(), gen);
        
        // Repeat the test 5 times to get an average time.
        double total_time_ms = 0.0;
        for (int i = 0; i < 5; i++) {
            auto start = chrono::high_resolution_clock::now();
            auto triplets = sol.threeSum(nums);
            auto end = chrono::high_resolution_clock::now();
            auto duration_us = chrono::duration_cast<chrono::microseconds>(end - start);
            double time_taken_ms = duration_us.count() / 1000.0;  // convert to milliseconds
            total_time_ms += time_taken_ms;
        }
        double avg_time_ms = total_time_ms / 5.0;  // Find the average time taken.

        // Format and output the results.
        cout << "n = " << setw(5) << n 
             << " | Found " << setw(5) << sol.threeSum(nums).size() << " triplets"
             << " | Time: ";
        if (avg_time_ms < 1.0) {
            cout << setw(6) << setprecision(2) << total_time_ms*100  << " microsec" << endl;
        } else {
            cout << setw(6) << setprecision(2) << avg_time_ms << " ms" << endl;
        }
    }
    return 0;
}
