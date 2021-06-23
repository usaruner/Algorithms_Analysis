#include "project2.h"
#include "project1.h"
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
void first_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
    std::vector<double> vec = std::vector<double>(items);
    shell_sort1(vec,(int)vec.size());
    first_fit(vec, assignment, free_space);
}