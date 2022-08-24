#include <vector>
#include <iostream>
#include <unordered_map>
#include <bits/stdc++.h>


using namespace std;

// twoSum
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> remainders;
    for (int i=0; i< nums.size(); i++) {
        if (remainders.find(target-nums[i]) != remainders.end()) {
            return vector<int> {remainders[target- nums[i]], i};
        }
        remainders[nums[i]] = i;
    }
    return vector<int> {-1, -1};

}

// containsDuplicate
bool containsDuplicate(vector<int>& nums) {
    unordered_map<int, int> dups;
    for (int i; i< nums.size(); i++) { 
        if (dups.count(nums[i])) {
            return true;
        }
        dups[nums[i]] = 1;
    }
    return false;

}

// isAnagram
unordered_map<char, int> counter(string s) {
    unordered_map<char, int> c;
    for (int i=0; i<s.length(); i++) {
        if (c.count(s[i])) {
            c[s[i]] += 1;
        } else {
            c[s[i]] = 1;
        }
    }
    return c;
}

bool isAnagram(string s, string t) { 
    if (s.size() != t.size()) {
        return false;
    }
    unordered_map<char, int> s_count = counter(s);    
    unordered_map<char, int> t_count = counter(t);

    for (auto& key: s_count) {
        if (!t_count.count(key.first)) {
            return false;
        } else if (t_count[key.first] != key.second) {
            return false;
        }
    }   
    return true;
}

// maxProfit
int maxProfit(vector<int>& prices) {
    int min_price = prices[0];
    int max_profit = 0;

    for (int i=0; i<prices.size(); i++) {
        min_price = min(prices[i], min_price);
        max_profit = max(max_profit, prices[i]-min_price);
    }
    return max_profit;
}

bool validParentheses(string s) { 
    unordered_map<char, char> combinations = {{'}', '{'}, {']', '['}, {')', '('}};
    vector<char> stack; 

    for (int i=0; i<s.length(); i++) {
        if (combinations.count(s[i])) {
            if (stack.size() == 0) {
                return false;
            } else if (stack.back() == combinations[s[i]]) {
                stack.pop_back();
            }
        } else {
            stack.push_back(s[i]);
        }
    }
    return stack.size() == 0;
}

int maxSubArray(vector<int>& nums) {
    int current = nums[0];
    int max_number = nums[0];

    for (int i=0; i< nums.size(); i++) {
        current = max(current+ nums[i], nums[i]);
        max_number = max(current, max_number);        
    }
    return max_number;
}

vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> solutions;
    
    for (int i=0; i< nums.size()-3; i++) {
        int target = -nums[i];
        unordered_map<int, int> remainders;

        for (int j=i; j< nums.size(); j++) {
            if (remainders.count(target-nums[j])) {
                solutions.push_back(vector<int> {nums[i], nums[j], nums[remainders[target-nums[j]]]});
                continue;
            }
            remainders[nums[j]] = j;
        }
    }
    set<tuple<int, int, int>> final_solutions;
    
    for (auto sol: solutions) {
        sort(sol.begin(), sol.end());
        tuple<int, int, int> t = {sol[0], sol[1], sol[2]};
        final_solutions.insert(t);
    }

    vector<vector<int>> super_solution;

    for (auto f_sol: final_solutions) {
        super_solution.push_back({get<0>(f_sol), get<1>(f_sol), get<2>(f_sol)});
    }

    return super_solution;
}

//merge Intervals
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<vector<int>> existing;

    for (int i = 0; i<intervals.size(); i++) {
        bool found = false;
        for (int j=0; j<existing.size(); j++) {
            if (existing[j][0] >= intervals[i][0] && existing[j][0] <= intervals[i][1]) {
                existing[j][1] = max(intervals[i][1], existing[j][1]);
                found = true;
                break;
            }
        }
        if (!found) {
            existing.push_back(intervals[i]);
        }
    }
    return existing;

}

bool compareCounters(unordered_map<char, int>& first, unordered_map<char, int>& second) {
    for (auto &pair: first) {
        if (!second.count(pair.first)) {
            return false;
        } else {
            if (pair.second != second[pair.first]) {
                return false;
            }
        }

    }
    return true;
}

vector<vector<string>> groupAnagrams(vector<string>& strs) {
    vector<vector<string>> solutions;

    for (int i=0; i<strs.size(); i++) {
        bool found = false;
        for (int j=0; j<solutions.size(); j++) {
            if (strs[i].size() == solutions[j][0].size()) {
                auto current_counter = counter(strs[i]); 
                auto existing_counter = counter(solutions[j][0]);
                if (compareCounters(current_counter, existing_counter)) {
                    solutions[j].push_back(strs[i]);
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            solutions.push_back({strs[i]});
        }
    }
    return solutions;
}

vector<vector<string>> groupAnagrams_fast(vector<string>& strs) {
    unordered_map<string, vector<string>> solutions;

    for (auto &s : strs) {
        string sorted_str = s;
        sort(sorted_str.begin(), sorted_str.end());
        if (solutions.count(sorted_str)) {
            solutions[sorted_str].push_back(s);
        } else {
            solutions[sorted_str] = {s};
        }
    }

    vector<vector<string>> list_solutions;
    for (auto &pair: solutions) {
        list_solutions.push_back(pair.second);
    }
    return list_solutions;

}

// Reverse Linked List
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* reverseList(ListNode* head) {
    ListNode* current = head;
    ListNode* prev = nullptr;

    while (current->next != nullptr) {
        ListNode* temp = current->next;
        current->next = prev;
        prev = current;
        current = temp;
    }

    return current;

}


bool hasCycle(ListNode *head) {
    ListNode* current = head;
    set<ListNode*> reached;

    while (current != nullptr && current->next != nullptr) {
        if (reached.count(current)) {
            return true;
        } else {
            reached.insert(current);
            current = current->next;
        }
    }
    return false;
}

int maxArea(vector<int>& height) {
    int largest_area =0;

    for (int l=0; l<height.size()-1; l++) {
        for (int r=l; r<height.size(); r++) {
            int water_height = min(height[l], height[r]);
            int water_length = r-l;
            largest_area = max(largest_area, water_height * water_length);
        }
    }
    return largest_area;


}

int maxArea_fast(vector<int>& height) {
    int largest_area = 0;

    int l = 0;
    int r = height.size() -1;

    while (l < r) {
        int area = min(height[l], height[r]) * (r-l);
        largest_area = max(area, largest_area);
        if (height[l]<height[r]) {
            l++;
        } else {
            r--;
        }
    }
    return largest_area;
}

// Palindromic Substrings

int countSubstrings_f(string s, int l, int r, int amount) {
    if (l < 0 || r > s.length()-1) {
        return amount;
    }
    if (s[l] == s[r]) {
        return countSubstrings_f(s, l-1, r+1, amount+1); 
    } else {
        return amount;
    }
}

int countSubstrings(string s) {
    int amount = 0;

    for (int i=0; i< s.length(); i++) {
        amount += countSubstrings_f(s, i, i, 0);
        amount += countSubstrings_f(s, i-1, i, 0);
    }
    return amount;
}


int climbStairs_f(int n,  unordered_map<int, int>& sol_dict) {
    if (n <= 2) {
        return n;
    } else {
        if (sol_dict.count(n)) {
            cout << "Here";
            return sol_dict[n];
        }
        int res = climbStairs_f(n-1, sol_dict) + climbStairs_f(n-2, sol_dict);
        sol_dict[n] = res;
        return res;
    }
}

int climbStairs(int n) {
    unordered_map<int, int> sol_dict;
    return climbStairs_f(n, sol_dict);
}

int coinChange_f(vector<int> &coins, int amount, int used) {
    if (amount == 0) {
        return used;
    }
    for (auto c: coins) {
        if (c <= amount) {
            return coinChange_f(coins, amount-c, used+1);
        }
    }
    return -1;
}

int coinChange(vector<int>& coins, int amount) {
    sort(coins.begin(), coins.end(), greater<>());    
    return coinChange_f(coins, amount, 0);    
}

int main() {
    stoll("102");
}