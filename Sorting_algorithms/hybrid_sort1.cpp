#include "project1.h"
#include <math.h>
#include "helpers.h"
#include<iostream>
void hybrid_sort1(std::vector<int>& nums) 
{
    double H = pow((double)nums.size(), (double)(0.5));
    if (H < 1) 
	{
        H = 1;
    }
	std::cout << "hybrid3: " << H << std::endl;
	if ((int)nums.size() > H) {
		std::vector<int>  A = std::vector<int>(nums.begin(), nums.end() - nums.size() / 2);
		std::vector<int> B = std::vector<int>(nums.end() - nums.size() / 2, nums.end());
		hybrid_sort_helper(A, H);
		hybrid_sort_helper(B, H);
        nums = merge(A, B);
	}
	else {
		insertion_sort(nums);
	}
}
