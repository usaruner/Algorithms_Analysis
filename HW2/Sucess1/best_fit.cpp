#include "project2.h"
#include "ZipTree.h"
void best_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
	int bin = 0;
	int assign;
	ZipTree<int,double> tree;
	for (int i = 0; i < (int)items.size(); i++) {
		assign = tree.bfinsert(items[i], bin);
		std::cout << "done" << (int)free_space.size() << " vs " << assign << std::endl;
		if ((int)free_space.size() + 1 >= assign) {
			free_space.push_back(1.0);
		}
		free_space[assign - 1] = free_space[assign - 1] - items[i];

		assignment[i] = assign;
	}
	//tree.printTree();
}