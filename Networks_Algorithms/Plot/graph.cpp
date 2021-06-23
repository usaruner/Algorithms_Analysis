#include "graph.h"

Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v){
	// TODO
	return Graph(num_nodes, u, v);
}

int Graph::get_num_nodes() {
	// TODO
	return numNodes; // remove this line if you implement the function
}

int Graph::get_num_edges() {
	// TODO
	int size = 0;
	for (const auto& pair : edgeMap) {
		size += pair.second.size();
	}
	return size/2;
}

std::vector<Node> Graph::get_neighbors(Node u) {
	// TODO
	std::cout << "get " << u <<std::endl;
	for (auto elem : edgeMap[u])
	{
		std::cout <<  elem.id << ",";
	}
	std::cout << std::endl;
	return edgeMap[u];
}

std::map<int, Node> Graph::get_id_to_node_map(){
	// TODO
	return *(new std::map<int, Node>(vectorMap));
}

