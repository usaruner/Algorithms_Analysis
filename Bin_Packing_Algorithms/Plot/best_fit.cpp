#include "project2.h"
#include "ZipTree.h"
#include <iostream>
#include <vector>
#include "keytype.h"


void best_fit(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space) {
	/*
	int bin = 0;
	int static assign;
	ZipTree<keytype,int> tree;
	free_space = std::vector<double>((int)items.size(), 1);
	assignment.reserve((int)items.size());
	
	for (int i = 0; i < (int)items.size(); i++) {
		assign = tree.bfinsert(bin, keytype{items[i],i});
		assignment[i] = assign;
		//std::cout << "free_space[" << assign - 1 << "] = " << free_space[assign-1] << " - " << items[i] << " = " << free_space[assign - 1] - items[i] << std::endl;
		if (std::fabs(free_space[assign - 1] - items[i]) < 0.00001) {
			free_space[assign - 1] = 0;
		}
		else {
			free_space[assign - 1] = free_space[assign - 1] - items[i];
		}
}
	//std::cout << "ENDOF"<< *(free_space.end()-1) << std::endl;
	
	if ((int)free_space.size() > 3) {
		while (*(free_space.end() - 1) == 1) {
			free_space.pop_back();
		}
	}
	//tree.printTree();
	*/
	free_space.push_back(1);
	bool needbin = true;
	double bestfit = 1;
	int bestfitindex = 0;
	for (int i = 0; i < (int)items.size(); i++) {
		needbin = true;
		bestfit = 1;
		bestfitindex = 0;
		for (int j = 0; j < (int)free_space.size(); j++) {
			if (items[i] < free_space[j] || std::fabs(items[i] - free_space[j]) < 0.000001) {
				if (std::fabs(items[i] - free_space[j]) < 0.000001) {
					bestfit = 0;
					bestfitindex = j;
					needbin = false;
					break;
				}
				else {
					//std::cout << "new:" << (free_space[j] - items[i]) << "best: " <<(bestfit) << std::endl;
					if (free_space[j] - items[i] < bestfit) {
						bestfit = free_space[j] - items[i];
						bestfitindex = j;
						needbin = false;
					}
				}
			}
		}
		if (needbin) {
			free_space.push_back(1);
			free_space[free_space.size() - 1] -= items[i];
			assignment[i] = free_space.size();
			//std::cout << "new bin insert " <<( 1- items[i] )<< " into bin " << free_space.size()<< std::endl;
		}
		else {
			free_space[bestfitindex] = bestfit;
			assignment[i] = bestfitindex+1;
			//std::cout << "insert " << bestfit << " into bin " << bestfitindex+1 << std::endl;
		}
	}
}