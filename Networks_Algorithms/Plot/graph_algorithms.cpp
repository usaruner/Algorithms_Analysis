#include "graph.h"

int get_diameter(Graph graph)
{
	// TODO
	int num = graph.diameter();
	//std::cout << "num: " << num << std::endl;
	return num;
}

float get_clustering_coefficient(Graph graph)
{
	// TODO
	return graph.cluster(); // remove this line if you implement the function
}

std::map<int, int> get_degree_distribution(Graph graph) 
{
	// TODO
	return graph.degree();
}
