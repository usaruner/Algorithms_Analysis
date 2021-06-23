#include "project1.h"
#include "helpers.h"

void shell_sort3(std::vector<int>& nums, int size) {
    int shell_num[] = { 1,2,3,4,6,8,9,12,16,18,24,27,32,36,48,54,64,72,81,96,108,128,144,162,192,216,243,256,288,324,384,432,486,512,576,648,729,768,864,972,1024,1152,1296,1458,1536,1728,1944,2048,2187,2304,2592,2916,3072,3456,3888 };
    int gap_size = 0;
    //starting gap size
    for (int gap = size; gap >= 0; gap--)
    {
        gap_size = shell_num[gap];//get gap size
         //every position within the first gap 
        for (int i = 0; i < gap_size; i++) {
            if (i < (int)nums.size()) 
            {
                //sorts array nums, gap size, starting position i
                sort_with_gaps(nums, gap_size, i);
            }
        }
    }
}