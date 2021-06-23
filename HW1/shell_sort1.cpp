#include "project1.h"
#include "helpers.h"
void shell_sort1(std::vector<int>& nums, int size)
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