#include "project1.h"
void merge_sort(std::vector<int>& nums) {
    std::vector<int>  A = std::vector<int>(nums.begin(), nums.end() - nums.size() / 2); // first half
    std::vector<int> B = std::vector<int>(nums.end() - nums.size() / 2, nums.end());    // second half
    if (nums.size() > 1) {
        merge_sort(A); //sort first half
        merge_sort(B); //sort second half
    }
    nums = merge(A, B); //merge and set to num
}
std::vector<int> merge(std::vector<int>& A, std::vector<int>& B) {
    std::vector<int> S = std::vector<int>();
    int i = 0;
    int j = 0;
    while (i < (int)A.size() && j < (int)B.size()) {
        if (A[i] <= B[j]) {
            S.push_back(A[i]);
            i++;
        }
        else {
            S.push_back(B[j]);
            j++;
        }
    }
    while (i < (int)A.size()) {
        S.push_back(A[i]);
        i++;
    }
    while (j < (int)B.size()) {
        S.push_back(B[j]);
        j++;
    }
    return S;
}
void sort_with_gaps(std::vector<double>& nums, int gaps, int start) {
    int swapPos = 0;
    for (int i = start; i < (int)nums.size(); i += gaps) {
        swapPos = 0;
        for (int j = i; j >= 0; j -= gaps) {
            if (j < (int)nums.size() && i != j) {
                if (nums[i - swapPos] > nums[j]) {
                    std::swap(nums[j], nums[i - swapPos]);
                    swapPos += gaps;
                }
                else {
                    break;
                }

            }
        }
    }
}
void shell_sort1(std::vector<double>& nums, int size)
{
    //starting gap size
    for (int gap = (int)nums.size() / 2; gap > 0; gap /= 2)
    {
        //every position within the first gap 
        for (int i = 0; i < gap; i++)
        {
            //sorts array nums, gap size, starting position i
            sort_with_gaps(nums, gap, i);
        }
    }
}