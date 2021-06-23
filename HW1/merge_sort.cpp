#include "project1.h"
#include <iostream>
#include "helpers.h"
void merge_sort(std::vector<int>& nums) {
    std::vector<int>  A = std::vector<int>(nums.begin(), nums.end() - nums.size() / 2); // first half
    std::vector<int> B = std::vector<int>(nums.end() - nums.size() / 2, nums.end());    // second half
    if (nums.size() > 1) {
        merge_sort(A); //sort first half
        merge_sort(B); //sort second half
    }
    nums = merge(A, B); //merge and set to num
}

