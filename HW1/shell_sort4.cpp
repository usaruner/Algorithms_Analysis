#include "project1.h"
#include <iostream>
#include "helpers.h"
void shell_sort4(std::vector<int>& nums, int size) {
    
    int shell_num[] = { 1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001 };
    int gap_size = 0;
    //starting gap size
    for (int gap = size; gap >= 0; gap--)
    {
        gap_size = shell_num[gap];//get gap size
         //every position within the first gap
        for (int i = 0; i < gap_size; i++) 
        {
            //sorts array nums, gap size, starting position i
            sort_with_gaps(nums, gap_size, i);
        }
    }
}