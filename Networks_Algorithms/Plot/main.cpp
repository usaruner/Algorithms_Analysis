
#include "project3.h"
#include "project1.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <fstream>
#include <iostream>
#include <locale.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <cstdio>
#include <map>
#include <time.h> 
#include <errno.h>
#include <cstring>
#include <numeric>
#include <math.h> 


static const std::unordered_map<std::string, int> SORT_MAP = {
	{"diameter",1},
	{"cluster",2},
	{"degree",3}
};
static const std::unordered_map<std::string, int> RANDOM_MAP = {
	{"random", 0},
};
std::vector <std::pair<int, int>> get_random_vector(int n, double p)
{
	std::vector<std::pair<int, int>> edge;
	int v = 1;
	double w = -1;
	double randProb;
	while (v < n) {
		randProb = ((double)rand()) / ((double)RAND_MAX);
		w = w + 1 + (log(1 - randProb) / log(1 - p));
		while (w >= v && v < n) {
			w = w - v; 
			v++;
		}
		if (v < n) {
			edge.push_back(std::make_pair(v, w));
		}
	}	
	return edge;
}


void save_data(const std::string& dir_name, const std::string& file_name, std::string data)
{
	std::cout << file_name + ".csv" << std::endl;
	try {
		std::string filename = "C:\\Users\\usaru\\OneDrive\\Desktop\\school\\2021_Spring\\CS165\\HW\\HW3\\plot\\data\\" + file_name + ".csv";
		std::ofstream out;
		out.open(filename, std::ofstream::out | std::ofstream::app);
		if (!out.is_open()) { // use is_open();
			std::cout << "error" << strerror(errno);
		}
		out << data;
		out << "\r\n";
		out.close();
		//std::cout << filename << std::endl;
	}
	catch (const std::exception& e)
	{
		// catch anything thrown within try block that derives from std::exception
		std::cerr << e.what();
	}
}

void cleardata() {
	std::string file_name;
	std::string dir_name;
	for (const auto& rand_gen : RANDOM_MAP) {
		for (const auto& algorithm : SORT_MAP) {
			file_name = algorithm.first + "_" + rand_gen.first;
			std::ofstream ot;
			ot.open("C:\\Users\\usaru\\OneDrive\\Desktop\\school\\2021_Spring\\CS165\\HW\\HW3\\plot\\data\\" + file_name + ".csv", std::ofstream::out | std::ofstream::trunc);
			ot.close();
		}
	}
}

void run_experiment(unsigned min_input_size, unsigned input_size, unsigned num_runs)
{
	std::vector<std::pair<int, int>> temp = std::vector<std::pair<int, int>>();
	std::vector<int> u = std::vector<int>();
	std::vector<int> v = std::vector<int>();
	std::map<int, int> infomap;
	std::string info;
	std::string file_name;
	std::string dir_name;
	Graph testGraph;
	for (const auto& rand_gen : RANDOM_MAP) {
		for (const auto& algorithm : SORT_MAP) {
			std::cout << "in fors" << std::endl;
			dir_name = algorithm.first;
			file_name = algorithm.first + "_" + rand_gen.first;
			temp = get_random_vector(input_size, 2*(log(input_size)) / input_size);
			std::cout << "random" << input_size << std::endl;
			for (auto& i : temp) {
				u.push_back(i.first);
				v.push_back(i.second);
			}
			testGraph = Graph(input_size, u, v);
			/*
			if (algorithm.second == 1) {
				info = std::to_string(input_size) + ", " + std::to_string(testGraph.diameter());
				save_data(dir_name, file_name, info);
			}
			else if (algorithm.second == 2) {
				info = std::to_string(input_size) + ", " + std::to_string(testGraph.cluster());
				save_data(dir_name, file_name, info);
			}
			*/
			if (algorithm.second == 3) {
				infomap = testGraph.degree();
				for (auto n : infomap) {
					info = std::to_string(n.first) + ", " + std::to_string(n.second);
					save_data(dir_name, file_name, info);
				}
			}
			
			
		}
		
	}
}

void run_experiments(unsigned min_input_size, unsigned max_input_size, double factor, unsigned num_runs)
{
	/*
	for (unsigned input_size = min_input_size; input_size <= max_input_size; input_size *= factor)
	{
		run_experiment(min_input_size, input_size, num_runs);
		std::cout << "Experiments with input size " << input_size << " for " << num_runs << " runs" << " are done" << std::endl;
	}
	*/
	run_experiment(min_input_size, 1000, 10);
	run_experiment(min_input_size, 10000, 10);
	run_experiment(min_input_size, 100000, 10);
}

int main(int argc, char** argv)
{
	std::cout << "hello" << std::endl;
	if (argc > 1 && std::string(argv[1]) == "clear") {
		cleardata();

	}
	else if (argc > 1 && argv[1]) {
		std::cout << "hello" << std::endl;
		srand(time(NULL));
		run_experiments(1, atoi(argv[1]), 2, 10);
	}else {
		std::cout << "hello" << std::endl;
		srand(time(NULL));
		run_experiments(64, 80000, 2, 10);
	}
}