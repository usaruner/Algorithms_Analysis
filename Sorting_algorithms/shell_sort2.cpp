#include "project1.h"
#include "helpers.h"

void shell_sort2(std::vector<int>& nums, int size){
    int shell_num[] = { 1, 3, 5, 9, 17, 33, 65, 129, 257, 513, 1025, 2049, 4097, 8193, 16385, 32769, 65537, 131073, 262145, 524289 };
    int gap_size = 0;
    //starting gap size
    for (int gap = size; gap >= 0; gap--)
    {
        gap_size = shell_num[gap]; //get gap size
        //every position within the first gap 
        for (int i = 0; i < gap_size; i++) 
        {
            //sorts array nums, gap size, starting position i
            sort_with_gaps(nums, gap_size, i);
        }
    }
}