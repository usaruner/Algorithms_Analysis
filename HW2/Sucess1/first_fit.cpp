#include "project2.h"
#include "ZipTree.h"
void first_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
	int bin = 0;
	int assign;
	ZipTree<int, double> tree;
	for (int i = 0; i < (int)items.size(); i++) {
		assign = tree.ffinsert(bin, items[i]);
		assignment[i] = assign;
	}
	//std::cout << "hello";
	for (int i = 0; i < (int)tree.getSize(); i++) {
		double d = tree.find(i);
		//std::cout << "done" << std::endl;
		free_space.push_back(d);
	}
	//tree.printTree();
}