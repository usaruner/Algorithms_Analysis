#include "project2.h"
#include "project1.h"
#include "ZipTree.h"
void best_fit_decreasing(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
	std::vector<double> vec = std::vector<double>(items);
	shell_sort1(vec, (int)vec.size());
	best_fit(vec, assignment, free_space);
}
