#include "helpers.h"
#include "project1.h"
#include <iostream>
#include <math.h>
void printV(std::vector <int> const& a) {
    std::cout << "The vector elements are : ";

    for (int i = 0; i < (int)a.size(); i++)
    {
        std::cout << a.at(i) << ' ';
    }
    std::cout << std::endl;
}

//simiple swap
/*void swap(int& A, int& B) {
    int temp = A;
    A = B;
    B = temp;
}*/
int shell_helper(std::vector<int> shell_num, int num_size) {
    int pos_max = 0;
    //find largest number
    int i = 0;
    for (auto it = shell_num.begin(); it != shell_num.end(); it++) {
        i++;
        if (*it > num_size) {
            pos_max = i;
            break;
        }
    }
    std::cout << pos_max << std::endl;
    return pos_max;
}
//sort vector num, gap size, starting index
void sort_with_gaps(std::vector<int>& nums, int gaps, int start) {
    int swapPos = 0;
    for (int i = start; i < (int)nums.size(); i += gaps) {
        swapPos = 0;
        for (int j = i; j >= 0; j -= gaps) {
            if (j < (int)nums.size() && i != j) {
                if (nums[i - swapPos] < nums[j]) {
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

// A + B = sort(AB) from slides
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

void mergeH(int Astart, int Aend, int Bstart, int Bend, std::vector<int>& nums) {
    int i = Astart;
    int j = Bstart;
    //std::cout << Astart << ", "<< Aend <<" to "  << Bstart << ", " << Bend << std::endl;
    while (i <= (int)Aend && j <= (int)Bend) {
        //std::cout << nums[j] << " <= " << nums[i] << std::endl;
        if (nums[j] <= nums[i]) {
            nums.insert(nums.begin() + i, *(nums.begin() + j ));
            nums.erase(nums.begin() + j + 1);
            i++;
            j++;
            Aend++;
        }
        else {
            i++;
        }
    }
    //printV(nums);   
}

void merge_sort_helper(int start, int end, std::vector<int>& nums) {
    int size = (end - start);
    int Astart = start;
    int Aend = start + size/2;
    int Bstart = start + size/2 + 1;
    int Bend = Bstart + size/2;
    if (Bstart >= (int)nums.size()) {
        Bstart = nums.size() - 1;
    }
    if (Bend >= (int)nums.size()) {
        Bend = nums.size() - 1;
    }
    if (Astart >= (int)nums.size()) {
        Astart = nums.size() - 1;
    }
    if (Aend >= (int)nums.size()) {
        Aend = nums.size() - 1;
    }
    if (size > 1 ) {
        merge_sort_helper(Astart,Aend, nums); //sort first half
        merge_sort_helper(Bstart, Bend , nums); //sort second half
    }
    //std::cout << size << std::endl;
    //std::cout << Astart << ", " << Aend << " to " << Bstart << ", " << Bend << std::endl;
    mergeH(Astart, Aend, Bstart, Bend, nums); //merge and set to num
}

//just need the H (from slides)
void hybrid_sort_helper(std::vector<int>& nums, int Height) {
    if ((int)nums.size() > Height) {

        std::vector<int>  A = std::vector<int>(nums.begin(), nums.end() - nums.size() / 2);
        std::vector<int> B = std::vector<int>(nums.end() - nums.size() / 2, nums.end());
        hybrid_sort_helper(A, Height);
        hybrid_sort_helper(B, Height);
        nums = merge(A, B);
    }
    else {
        insertion_sort(nums);
    }
}