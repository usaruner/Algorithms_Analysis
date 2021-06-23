
#include "project2.h"

void next_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
	int bin = 0;
	free_space.push_back(1.0);
	for (int i = 0; i < (int)items.size(); i++) {
		if (items[i] > free_space[bin]) {
			bin++;
			free_space.push_back(1.0);
		}
		
		free_space[bin] = free_space[bin] - items[i];
		assignment[i] = bin + 1;
	}
}