#include <math.h>
#include <vector>
#ifndef HELPERS_H
#define HELPERS_H
	void swap(int& A, int& B);
	void sort_with_gaps(std::vector<int>& nums, int gaps, int start);
	void hybrid_sort_helper(std::vector<int>& nums, int Height);
	std::vector<int> merge(std::vector<int>& A, std::vector<int>& B);
	void merge_sort_helper(int start, int end, std::vector<int>& nums);
	void mergeH(int Astart, int Aend, int Bstart, int Bend, std::vector<int>& nums);
	void printV(std::vector <int> const& a);
	int shell_helper(std::vector<int> shell_num, int num_size);
#endif 