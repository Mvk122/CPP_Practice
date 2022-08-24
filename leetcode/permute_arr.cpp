#include <vector>
#include <iostream>
#include <unordered_map>
#include <bits/stdc++.h>

using namespace std;

void permute_arr_f(vector<int> current, vector<int> remainder, vector<vector<int>> & result) {
    if (remainder.size() == 0) {
        result.push_back(current);
    } else {
        for (int i=0; i<remainder.size(); i++) {
            auto temp = current;
            temp.push_back(remainder[i]);

            auto new_remainder = vector<int>(remainder.begin(), remainder.begin() + i);
            new_remainder.insert(new_remainder.end(), remainder.begin()+ i + 1, remainder.end());
            permute_arr_f(temp, new_remainder, result);
        }
    }
}

vector<vector<int>> permute_arr(vector<int> &nums) {
    vector<vector<int>> result = {};
    vector<int> current = {};
    permute_arr_f(current, nums, result);
    return result;
}

int main() {
    vector<int> nums = {1,2,3};
    return 0;
}