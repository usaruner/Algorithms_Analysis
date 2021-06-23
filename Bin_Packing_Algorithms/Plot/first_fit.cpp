#include "project2.h"
#include "ZipTree.h"
void first_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
	/*
	int bin = 0;
	int assign;
	free_space = std::vector<double>((int)items.size(), 1);
	ZipTree<int, double> tree;
	for (int i = 0; i < (int)items.size(); i++) {
		assign = tree.ffinsert(bin, items[i]);
		assignment[i] = assign;
		if (std::fabs(free_space[assign - 1] - items[i]) < 0.00001) {
			free_space[assign - 1] = 0;
		}
		else {
			free_space[assign - 1] = free_space[assign - 1] - items[i];
		}
	}
	if ((int)free_space.size() > 3) {
		while (*(free_space.end() - 1) == 1) {
			free_space.pop_back();
		}
	}
	*/
	//std::cout << "hello";
	//tree.printTree();
	free_space.push_back(1);
	bool needbin = true;
	for (int i = 0; i < (int)items.size(); i++) {
		needbin = true;
		for (int j = 0; j < (int)free_space.size(); j++) {
			//std::cout << "item[" << i << "] <= bin[" << j << "] = " << items[i] << " vs " << free_space[j] << std::endl;
			if (items[i] < free_space[j] || std::fabs(items[i] - free_space[j]) < 0.000001) {
				if (std::fabs(items[i] - free_space[j]) < 0.000001) {
					free_space[j] = 0;
					assignment[i] = j + 1;
					needbin = false;
					break;
				}
				else {
					free_space[j] -= items[i];
					assignment[i] = j + 1;
					needbin = false;
					break;
				}
			}
		}
		if (needbin) {
			free_space.push_back(1);
			free_space[free_space.size()-1] -= items[i];
			assignment[i] = free_space.size();
		}
	}
}