#include "project1.h"
#include <iostream>
#include <cmath>


void printVec(std::vector<int>& nums) {
    for (std::vector<int>::iterator it = nums.begin(); it < nums.end(); it++) {
        std::cout << *(it) << ", ";
    }
    std::cout << std::endl;
}

void insertion_sort(std::vector<int>& nums) {
    int swapPos = 0;
    for (auto i = 0; i < (int)(nums.size()); i++) {
        swapPos = 0;
        for (auto j = i - 1; j >= 0; j--) {
            if (nums[j] <= nums[i]) {
                swapPos = j + 1;
                break;
            }
        }
        //insertsion/delete
        nums.insert(nums.begin() + swapPos, *(nums.begin() + i));
        nums.erase(nums.begin() + i + 1);
    }

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
void merge_sort(std::vector<int>& nums) {
    std::vector<int>  A = std::vector<int>(nums.begin(), nums.end() - nums.size() / 2);
    std::vector<int> B = std::vector<int>(nums.end() - nums.size() / 2, nums.end());
    std::cout << nums.size();
    if (nums.size() > 1) {
        try {
            merge_sort(A);
        }
        catch (...) {
            std::cout << "fail" << nums.size();
            printVec(A);
            std::cout << "\n";
        }
        //merge_sort(B);
        printVec(A);
        printVec(B);
    }
    nums = merge(A, B);
}
void swap(int& A, int& B) {
    int temp = A;
    A = B;
    B = temp;
}
void sort_with_gaps(std::vector<int>& nums, int gaps, int start) {
    int swapPos = 0;
    
    for (int i = start; i < (int)nums.size(); i+=gaps) {
        swapPos = 0;
        for (int j = i ; j >= 0; j-=gaps) {
            if (j < (int)nums.size() && i != j) {
                //std::cout << "num[" << j << "]" << nums[j] << " < " << "num[" << i << "]" << nums[i - swapPos] << std::endl;
                if (nums[i - swapPos] < nums[j]) {
                    //std::cout << "swapped" << std::endl;
                    swap(nums[j], nums[i-swapPos]);
                    swapPos+=gaps;
                }
            }
        }
    }
    
    for (int i = start; i < (int)nums.size(); i += gaps) {
        std::cout << nums[i] << ", ";
    }
    std::cout << std::endl;
    
}
void shell_sort1(std::vector<int>& nums)
{

    for (int gap = (int)nums.size() / 2; gap > 0; gap /= 2)
    {
        std::cout << "GAP:" << gap << std::endl;
        for (int i = 0; i < gap; i++) {
            sort_with_gaps(nums, gap, i);
        }
        printVec(nums);
    }
    std::cout << std::endl;
}
void shell_sort2(std::vector<int>& nums) {
    std::cout << "GAP start:" << log2(nums.size()) << std::endl;
    int gap_size = 0;
    for (int gap = log2((int)nums.size()); gap > 0; gap--)
    {   
        gap_size = pow(2, gap) + 1;
        std::cout << "GAP:" << gap_size << std::endl;
        for (int i = 0; i < gap; i++) {
            if (i < (int)nums.size()) {
                sort_with_gaps(nums, gap_size, i);
            }
        }
        printVec(nums);
    }
    std::cout << std::endl;
}
void shell_sort3(std::vector<int>& nums) {
    int shell_num[] = { 1, 2, 3, 4, 6, 8, 9, 12, 16, 18, 24, 27, 32, 36, 48, 54, 64, 72, 81, 96, 108, 128, 144, 162, 192, 216, 243, 256 };
    int pos_max = 0;
    for (int i = 0; i < (int)(sizeof(shell_num) / sizeof(shell_num[0])); i++) {
        if (shell_num[i] > (int)nums.size()) {
            pos_max = i - 1;
            break;
        }
    }
    int gap_size = 0;
    for (int gap = pos_max; gap > 0; gap--)
    {
        gap_size = shell_num[gap];
        //std::cout << "GAP:" << gap_size << std::endl;
        for (int i = 0; i < gap; i++) {
            if (i < (int)nums.size()) {
                sort_with_gaps(nums, gap_size, i);
            }
        }
        printVec(nums);
    }
    std::cout << std::endl;
}
void shell_sort4(std::vector<int>& nums) {
    int shell_num[] = {1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905 };
    int pos_max = 0;
    for (int i = 0; i < (int)(sizeof(shell_num) / sizeof(shell_num[0])); i++) {
        if (shell_num[i] > (int)nums.size()) {
            pos_max = i - 1;
            break;
        }
    }
    int gap_size = 0;
    for (int gap = pos_max; gap > 0; gap--)
    {
        gap_size = shell_num[gap];

        //std::cout << "GAP:" << gap_size << std::endl;
        for (int i = 0; i < gap; i++) {
            if (i < (int)nums.size()) {
                sort_with_gaps(nums, gap_size, i);
            }
        }
        printVec(nums);
    }
    std::cout << std::endl;
}
/*
void hybrid_sort1(std::vector<int>& nums);
void hybrid_sort2(std::vector<int>& nums);
void hybrid_sort3(std::vector<int>& nums);
*/