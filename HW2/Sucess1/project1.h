#include <vector>

//REQUIREMENTS:
//each sort should be implemented in its own file of the same name e.g. insertion_sort.cpp
//each file should #include this header file
//no file should use anything outside of the C++ standard library
//functions should be tested using g++ in a linux environment
//each function should modify the input vector so that it is sorted upon completion
#ifndef PROJECT1_H
#define PROJECT1_H
void swap(double& A, double& B);
void shell_sort1(std::vector<double>& nums, int i);
void sort_with_gaps(std::vector<double>& nums, int gaps, int start);
#endif 
