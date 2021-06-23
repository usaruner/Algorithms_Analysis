#include "ZipTree.h"
#include "project2.h"
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

typedef std::function<void(const std::vector<double>& items, std::vector<int>& assignment, std::vector<double>& free_space)> BIN_FUNCTION;
typedef std::function<std::vector<double>(int)> GET_VECTOR_FUNCTION;
void printV(std::vector <double> const& a) {
	std::cout << "The vector elements are : ";

	for (int i = 0; i < (double)a.size(); i++)
	{
		std::cout << a.at(i) << ' ';
	}
	std::cout << std::endl;
}

static const std::unordered_map<std::string, BIN_FUNCTION> SORT_MAP = {
	{"next_fit", next_fit},
	{"first_fit", first_fit},
	{"first_fit_decreasing", first_fit_decreasing},
	{"best_fit", best_fit},
	{"best_fit_decreasing", best_fit_decreasing},
};

std::vector<double> get_random_vector(int size)
{
	
	int rand1 = rand() % size + 1;
	double rand2 = 0.6*((double)rand()) / ((double)RAND_MAX);
	std::map<int,double> unsortedmap = std::map<int, double>();
	std::vector<int> indexgen = std::vector<int>();
	std::vector<double> randgen = std::vector<double>();
	//generate map[rand1] = rand2
	
	for (int i = 0; i < size; i++) {
		rand1 = rand() % size + 1;
		rand2 = 0.6 * ((double)rand()) / ((double)RAND_MAX);
		unsortedmap[rand1] = rand2;
		indexgen.push_back(rand1);
	}
	

	//sort rand1
	merge_sort(indexgen);
	
	//place via sorted index
	for (int& it : indexgen) {
		randgen.push_back(unsortedmap[it]);
	}
	return randgen;
}

static const std::unordered_map<std::string, GET_VECTOR_FUNCTION> RANDOM_MAP = {
	{"random", get_random_vector},
};

void save_data(const std::string& dir_name, const std::string& file_name, unsigned input_size, double elapsed_time_sum, unsigned num_runs)
{
	std::cout << file_name + ".csv" << std::endl;
	try {
		std::string filename = "C:\\Users\\usaru\\OneDrive\\Desktop\\school\\2021_Spring\\CS165\\HW\\HW2\\plot\\data\\" + file_name + ".csv";
		std::ofstream out;
		out.open(filename, std::ofstream::out | std::ofstream::app);
		if (!out.is_open()) { // use is_open();
			std::cout << "error" << strerror(errno);
		}
		out << input_size << ",";
		out << ((double)elapsed_time_sum / (double)num_runs )<< "," ;
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
			ot.open("C:\\Users\\usaru\\OneDrive\\Desktop\\school\\2021_Spring\\CS165\\HW\\HW2\\plot\\data\\" + file_name + ".csv", std::ofstream::out | std::ofstream::trunc);
			ot.close();
		}
	}
}
double calculatewaste(std::vector<double> sequence, std::vector<double> bins) {

	std::cout <<"size: " << bins.size() <<  "|| ack:" <<  std::accumulate(sequence.begin(), sequence.end(), 0.0) << std::endl;
	return bins.size() - std::accumulate(sequence.begin(), sequence.end(), 0.0);
}
void run_experiment(unsigned min_input_size, unsigned input_size, unsigned num_runs)
{
	std::vector<double> temp = std::vector<double>();
	std::vector<int> assignments(temp.size(), 0);
	std::vector<double> free_space;
	
	//uint64_t num_comparisons_sum = 0;
	double information = 0;
	std::string file_name;
	std::string dir_name;
	for (const auto& rand_gen : RANDOM_MAP) {
		//printV(temp);
		information = 0;
		for (const auto& algorithm : SORT_MAP) {
			information = 0;
			dir_name = algorithm.first;
			file_name = algorithm.first + "_" + rand_gen.first;
			for (int i = 0; i < (int)num_runs; ++i)
			{
				
				temp = rand_gen.second(input_size);
				std::cout << "hello" << std::endl;
				assignments = std::vector<int>(temp.size(), 0);
				free_space = std::vector<double>();
				
				algorithm.second(temp,assignments,free_space); // calling your sort function on the input temp; alter the arguments as needed
				
				information += calculatewaste(temp, free_space);
			}
			save_data(dir_name, file_name, input_size, information, num_runs);
			/*
			try {
				std::cout << "open" << std::endl;
				std::string filename = "C:\\Users\\usaru\\OneDrive\\Desktop\\school\\2021_Spring\\CS165\\HW\\HW2\\plot\\data\\" + file_name + ".csv";
				std::ofstream out;
				out.open(filename, std::ofstream::out | std::ofstream::app);
				if (!out.is_open()) { // use is_open();
					std::cout << "error" << strerror(errno);
				}

				for (int i = 0; i < (double)temp.size(); i++)
				{
					out << temp.at(i) << ",";
				}
				out << "\r\n";
				for (int i = 0; i < (double)free_space.size(); i++)
				{
					out << free_space.at(i) << ",";
				}
				out << "\r\n";
				out.close();
				//std::cout << filename << std::endl;
				std::cout << "close" << std::endl;
			}
			catch (const std::exception& e)
			{
				// catch anything thrown within try block that derives from std::exception
				std::cerr << e.what();
			}
			*/
		}
		
	}
}

void run_experiments(unsigned min_input_size, unsigned max_input_size, double factor, unsigned num_runs)
{

	for (unsigned input_size = min_input_size; input_size <= max_input_size; input_size *= factor)
	{
		
		run_experiment(min_input_size, input_size, num_runs);
		std::cout << "Experiments with input size " << input_size << " for " << num_runs << " runs" << " are done" << std::endl;
	}
}

int main(int argc, char** argv)
{
	std::cout << "hello" << std::endl;
	if (argc > 1 && std::string(argv[1]) == "clear") {
		cleardata();
		
		std::cout << argc << std::endl;
		std::vector<double> randnum = get_random_vector(10);
		std::vector<int> assignments(randnum.size(), 0);
		std::vector<double> free_space;
		printV(randnum);
		next_fit(randnum, assignments, free_space);
		printV(free_space);
		std::cout << "waste" << calculatewaste(randnum, free_space) << std::endl;
		double sum = 0;
		for (double& it : randnum) {
			sum += it;
		}
		std::cout << "sum " << sum << std::endl;
	}
	else if (argc > 1 && argv[1]) {
		std::cout << "hello" << std::endl;
		srand(time(NULL));
		run_experiments(1, atoi(argv[1]), 2, 10);
	}else {
		std::cout << "hello" << std::endl;
		srand(time(NULL));
		run_experiments(1, 80000, 2, 10);
	}
}