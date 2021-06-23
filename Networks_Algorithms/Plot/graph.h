#ifndef GRAPH_H
#define GRAPH_H
#include <map>
#include <vector>
#include "node.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <stdlib.h>    
#include <time.h> 
class Graph 
{
	public:
		// DO NOT MODIFY MEMBERS BELOW THIS LINE
        int get_num_nodes(); 						// get number of nodes
        int get_num_edges(); 						// get number of edges
        std::vector<Node> get_neighbors(Node u); 	// return neighbors of u 
        std::map<int, Node> get_id_to_node_map(); 	// allows lookup of nodes from ids
		// DO NOT MODIFY MEMBERS ABOVE THIS LINE
		std::map<int, Node> vectorMap;
		std::map<Node, std::vector<Node>> edgeMap;
		int numNodes;
		// declare any constructors, members, and member functions you may want to use
		Graph() {
			vectorMap = std::map<int, Node>();
			edgeMap = std::map<Node, std::vector<Node>>();
			numNodes = 0;
		}
		Graph(int num_nodes, std::vector<int> u, std::vector<int> v) {
			srand(time(NULL));
			vectorMap = std::map<int, Node>();
			edgeMap = std::map<Node, std::vector<Node>>();
			numNodes = num_nodes;
			Node* uNode;
			Node* vNode;
			
			
			for (int i = 0; i < (int)u.size(); i++) {
				if (vectorMap.find(u[i]) == vectorMap.end()) {
					uNode = new Node(u[i]);
					vectorMap.insert(std::make_pair(u[i], *uNode));
					edgeMap.insert(std::make_pair(*uNode, std::vector<Node>()));
					//std::cout << "created Node" << u[i] << std::endl;
				}
				if (vectorMap.find(v[i]) == vectorMap.end()) {
					vNode = new Node(v[i]);
					vectorMap.insert(std::make_pair(v[i], *vNode));
					edgeMap.insert(std::make_pair(*vNode, std::vector<Node>()));
					//std::cout << "created Node" << v[i] << std::endl;
				}
				uNode = &vectorMap[u[i]];
				vNode = &vectorMap[v[i]];
				if (std::find(edgeMap[*uNode].begin(), edgeMap[*uNode].end(), *vNode) == edgeMap[*uNode].end()) {
					edgeMap[*uNode].push_back(*vNode);
				}
				if (std::find(edgeMap[*vNode].begin(), edgeMap[*vNode].end(), *uNode) == edgeMap[*vNode].end()) {
					edgeMap[*vNode].push_back(*uNode);
				}
				//std::cout << "i :" << i<< std::endl;
			}
			/*for (auto elem : vectorMap)
			{
				std::cout << elem.first << ", " <<elem.second << "\n";
			}
			for (auto vec : edgeMap)
			{
				for (auto elem : vec.second)
				{
					std::cout << vec.first.id << " -> " << elem.id << "\n";
				}
			}
			*/
		}
		// implement any newly declared member functions in graph.cpp
		std::pair<Node,int> BFS_diameter(std::pair<Node, int> info, std::vector<Node>& visited) {
			std::pair<Node, int> temp;
			std::pair<Node, int> currtemp;
			std::pair<Node, int> max = info;
			std::queue<std::pair<Node, int>> que;
			que.push(info);
			while (!que.empty()) {
				temp = que.front();
				que.pop();
				for (auto e : edgeMap[temp.first]) {
					if (std::find(visited.begin(), visited.end(), e) == visited.end()) {
						currtemp = std::make_pair(e, temp.second + 1);
						visited.push_back(currtemp.first);
						que.push(currtemp);
						//std::cout << ", to " << currtemp.first << " (" << currtemp.second << ") ";
						if (currtemp.second > max.second) {
							max = currtemp;
						}
					}
				}
			}

			return max;
		}
		int diameter() {
			std::vector<Node> visited = std::vector<Node>();
			std::pair<Node, int> info;
			int d = 0;
			int start_index = rand() % numNodes + 1;
			Node next = Node(start_index);
			int numtesting;
			if (numNodes / 100 > 1) {
				numtesting = 20;
			}
			else {
				numtesting = numNodes;
			}
			std::cout << "[D] testing num: " << numtesting;
			for (int i = 0; i < numtesting; i++)
			{
				//std::cout << "node" << next;
				visited.clear();
				visited.push_back(next);
				info = BFS_diameter(std::make_pair(next,0), visited);
				next = info.first;
			}
			//std::cout << std::endl;
			return info.second;
		}
		float cluster() {
			std::map<Node, bool> H = std::map<Node, bool>();
			std::vector<Node> L = std::vector<Node>();
			std::map<Node, int> Dv = std::map<Node, int>();
			std::map<int, std::vector<Node>> D = std::map<int, std::vector<Node>>();
			std::map<Node, std::vector<Node>> Nv = std::map<Node, std::vector<Node>>();
			int k = 0;
			int i = 0;
			int newpos;
			int degree;
			int twoEdge = 0;
			Node tempNode;

			for (auto n : edgeMap) {
				degree = n.second.size();
				twoEdge += degree * (degree - 1) / 2;
			}

			//TRIANGLES
			for (auto vec : edgeMap)
			{
				H.insert(std::make_pair(vec.first, false));
				Dv.insert(std::make_pair(vec.first,vec.second.size()));
				D[vec.second.size()].push_back(vec.first);
				Nv.insert(std::make_pair(vec.first, std::vector<Node>()));
			}

			for (int n = 0; n < numNodes; n++) {
				i = 0;
				while (D[i].empty() && (i < numNodes)) {
					i++;
				}
				if (i >= numNodes) {
					break;
				}
				if (k < i) {
					k = i;
				}
				tempNode = D[i].back();
				H[tempNode] = true;
				L.insert(L.begin(), tempNode);
				D[i].pop_back();
				for (auto ele : edgeMap[tempNode]) {
					if (H[ele] == false) {
						newpos = Dv[ele];
						D[newpos].erase(std::remove(D[newpos].begin(), D[newpos].end(), ele), D[newpos].end());
						D[newpos--].push_back(ele);
						Nv[tempNode].push_back(ele);
					}
				}
				/*
				std::cout << "\nK: " << k << std::endl;
				for (auto v : D) {
					std::cout << "int: " << v.first << " L:";
					for (auto n : v.second) {
						std::cout << ", " << n;
					}
					std::cout << std::endl;
				}
				std::cout << std::endl;
				for (auto h : H) {
					std::cout << "Node: " << h.first << " bool:" << h.second;
				}
				for (auto v : Dv) {
					std::cout << "Node: " << v.first << " int:" << v.second;
				}
				std::cout << std::endl;
				for (auto v : Nv) {
					std::cout << "Node: " << v.first << " L:";
					for (auto n : v.second) {
						std::cout << ", " << n;
					}
					std::cout << std::endl;
				}
				for (auto n : L) {
					std::cout << "Node: " << n;
				}
				std::cout << std::endl;
				*/
			}
			//couunting triangles
			int numT=0;
			for (auto vec : L)
			{
				/*std::cout << "BNODE" << " : ";
				for (auto u : Nv[vec]) {
					std::cout << u << " , ";
				}
				std::cout << "\n\n";
				std::cout << vec << " : ";
				*/
				std::vector<Node> Bnode = Nv[vec];
				//std::cout << Bnode.size() << " : ";
				for (auto u : Bnode) {
					for (auto v : Bnode) {
						if (u != v) {
							for (auto n : edgeMap[u]) {
								if (n == v) {
									//std::cout << "(" << u << ", " << v << "), ";
									numT++;
									break;
								}
							}
						}
					}
				}
				std::cout << std::endl;
			}
			numT = numT / 2;
			//std::cout << "two edges" << twoEdge << std::endl;
			//std::cout << "triangle" << numT  << std::endl;
			//std::cout << "cNum" << 3.0 * ((double)numT) / (double)twoEdge << std::endl;
			return 3.0*((double)numT)/ (double)twoEdge;
		}

		std::map<int, int> degree() {
			std::map<int, int>degMap = std::map<int, int>();
			for (auto n : edgeMap) {
				degMap[n.second.size()]++;
			}
			return degMap;
		}
};

#endif
