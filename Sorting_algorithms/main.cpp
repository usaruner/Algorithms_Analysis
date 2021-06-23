#include "project1.h"
#include "helpers.h"
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
typedef std::function<void(std::vector<int>&)> SORT_FUNCTION;
typedef std::function<void(std::vector<int>&,int)> SHELL_SORT_FUNCTION;
typedef std::function<std::vector<int>(int)> GET_VECTOR_FUNCTION;

static const std::unordered_map<std::string, SORT_FUNCTION> SORT_MAP = {

	{"merge_sort", merge_sort},
	{"insertion_sort", insertion_sort},
	{"hybrid_sort1", hybrid_sort1},
	{"hybrid_sort2", hybrid_sort2},
	{"hybrid_sort3", hybrid_sort3},
};
static const std::unordered_map<std::string, SHELL_SORT_FUNCTION> SHELL_SORT_MAP = {
	{"shell_sort1", shell_sort1},
	{ "shell_sort2", shell_sort2},
	{ "shell_sort3", shell_sort3},
	{ "shell_sort4", shell_sort4},
};
int ashell2[] = { 1, 3, 5, 9, 17, 33, 65, 129, 257, 513, 1025, 2049, 4097, 8193, 16385, 32769, 65537, 131073, 262145, 524289 };
int ashell3[] = { 1,2,3,4,6,8,9,12,16,18,24,27,32,36,48,54,64,72,81,96,108,128,144,162,192,216,243,256,288,324,384,432,486,512,576,648,729,768,864,972,1024,1152,1296,1458,1536,1728,1944,2048,2187,2304,2592,2916,3072,3456,3888, 4096, 4374, 4608, 5184, 5832, 6144, 6561, 6912, 7776, 8192, 8748, 9216, 10368, 11664, 12288, 13122, 13824, 15552, 16384, 17496, 18432, 19683, 20736, 23328, 24576, 26244, 27648, 31104, 32768, 34992, 36864, 39366, 41472, 46656, 49152, 52488, 55296, 59049 };
int ashell4[] = { 1, 5, 19, 41, 109, 209, 505, 929, 2161, 3905, 8929, 16001, 36289, 64769, 146305 };
std::vector<int> shell2(ashell2, ashell2 + sizeof(ashell2) / sizeof(int));
std::vector<int> shell3(ashell3, ashell3 + sizeof(ashell3) / sizeof(int));
std::vector<int> shell4(ashell4, ashell4 + sizeof(ashell4) / sizeof(int));

std::vector<int> get_reverse_vector(int size)
{
	std::vector<int> reverse = std::vector<int>();
	for (int i = size; i > 0; i--) {
		reverse.push_back(i);
	}
	return reverse;
}
std::vector<int> get_random_vector(int size)
{
	
	int rand1 = rand() % size + 1;
	int rand2 = rand() % size + 1;
	std::map<int,int> unsortedmap = std::map<int, int>();
	std::vector<int> randgen = std::vector<int>();

	//generate map[rand1] = rand2
	for (int i = 0; i < size; i++) {
		rand1 = rand() % size + 1;
		rand2 = rand() % size + 1;
		unsortedmap[rand1] = rand2;
		randgen.push_back(rand1);
	}

	//sort rand1
	merge_sort(randgen);

	//place via sorted index
	for (int& it : randgen) {
		it = unsortedmap[it];
	}
	return randgen;
}
std::vector<int> get_almost_sorted_vector(int size)
{
	int swaptimes = (int)(2 * log(size));
	//std::cout << swaptimes << std::endl;
	std::vector<int> unsorted = std::vector<int>();
	std::vector<int> A = std::vector<int>();
	std::vector<int> B = std::vector<int>();
	for (int i = 0; i < size; i++) {
		unsorted.push_back(i);
	}

	for (int i = 0; i < swaptimes; i++) {
		A = get_random_vector(size-1);
		B = get_random_vector(size-1);
	}

	for (int i = 0; i < swaptimes; i++) {
		std::swap(unsorted[A[i]], unsorted[B[i]]);
	}
	return unsorted;
}

static const std::unordered_map<std::string, GET_VECTOR_FUNCTION> RANDOM_MAP = {
	{"reverse", get_reverse_vector},
	{"random", get_random_vector},
	{"almost_sorted", get_almost_sorted_vector}
};

void save_data(const std::string& dir_name, const std::string& file_name, unsigned input_size, uint64_t elapsed_time_sum, unsigned num_runs)
{

	try {
		std::string filename = "C:\\Users\\usaru\\OneDrive\\Desktop\\school\\2021_Spring\\CS165\\HW\\HW1\\data\\" + dir_name + "\\" + file_name + ".csv";
		std::ofstream out;
		out.open(filename, std::ofstream::out | std::ofstream::app);
		if (!out.is_open()) { // use is_open();
			std::cout << "error" << strerror(errno);
		}
		out << input_size << ",";
		out << static_cast<uint64_t>(round(elapsed_time_sum / num_runs)) << "," ;
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
		file_name = rand_gen.first;
		for (const auto& algorithm : SORT_MAP) {
			dir_name = algorithm.first;
			std::ofstream ot;
			ot.open("C:\\Users\\usaru\\OneDrive\\Desktop\\school\\2021_Spring\\CS165\\HW\\HW1\\data\\" + dir_name + "\\" + file_name + ".csv", std::ofstream::out | std::ofstream::trunc);
			ot.close();
		}
		for (const auto& algorithm : SHELL_SORT_MAP) {
			dir_name = algorithm.first;
			std::ofstream ot;
			ot.open("C:\\Users\\usaru\\OneDrive\\Desktop\\school\\2021_Spring\\CS165\\HW\\HW1\\data\\" + dir_name + "\\" + file_name + ".csv", std::ofstream::out | std::ofstream::trunc);
			ot.close();
		}
	}
}
void run_experiment(unsigned min_input_size, unsigned input_size, unsigned num_runs)
{
	std::vector<int> temp = std::vector<int>();
	//uint64_t num_comparisons_sum = 0;
	uint64_t  elapsed_time_sum = 0;
	std::string file_name;
	std::string dir_name;
	int index_shell = 0;
	for (const auto& rand_gen : RANDOM_MAP) {
		//printV(temp);
		file_name = rand_gen.first;
		for (const auto& algorithm : SORT_MAP) {
			dir_name = algorithm.first;
			elapsed_time_sum = 0;
			for (int i = 0; i < (int)num_runs; ++i)
			{
				temp = rand_gen.second(input_size);
				auto start_time = std::chrono::steady_clock::now();

				algorithm.second(temp); // calling your sort function on the input temp; alter the arguments as needed

				auto end_time = std::chrono::steady_clock::now();
				elapsed_time_sum += std::chrono::nanoseconds(end_time - start_time).count();
			}
			save_data(dir_name, file_name, input_size, elapsed_time_sum, num_runs);
		}
		for (const auto& algorithm : SHELL_SORT_MAP) {
			dir_name = algorithm.first;
			elapsed_time_sum = 0;

			for (int i = 0; i < (int)num_runs; ++i)
			{
				temp = rand_gen.second(input_size);
				if (algorithm.first == "shell_sort2") {
					index_shell = shell_helper(shell2, input_size);
				}else if (algorithm.first == "shell_sort3") {
					index_shell = shell_helper(shell3, input_size);
				}else if (algorithm.first == "shell_sort4") {
					index_shell = shell_helper(shell4, input_size);
				}
				else {
					index_shell = 1;
				}
				auto start_time = std::chrono::steady_clock::now();
				algorithm.second(temp,index_shell); // calling your sort function on the input temp; alter the arguments as needed

				auto end_time = std::chrono::steady_clock::now();
				elapsed_time_sum += std::chrono::nanoseconds(end_time - start_time).count();
			}
			save_data(dir_name, file_name, input_size, elapsed_time_sum, num_runs);
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
	if (argc > 1) {
		cleardata();
		std::cout << argc << std::endl;
	}
	else {
		srand(time(NULL));
		int size = 20;
		std::vector<int> al_sorted = get_random_vector(size);
		printV(al_sorted);
		hybrid_sort3(al_sorted);
		printV(al_sorted);
		al_sorted = get_random_vector(size);
		insertion_sort(al_sorted);
		printV(al_sorted);
		//run_experiments(1, 20000, 2, 10);
	}
}