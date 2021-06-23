#ifndef NODE_H
#define NODE_H
#include <vector>
#include <iostream>
class Node {
	public:
		// DO NOT MODIFY MEMBERS BELOW THIS LINE 
		bool operator==(const Node& other) const {return id == other.id;} 	// used for comparing two nodes, already implemented	
		int id; 															// uniquely identifies a node (no two nodes have the same id).    															// id must be set in the constructor and thereafter not modified
		Node(){}															// don't use this constructor, implement another one that accepts node id as an argument 
		// DO NOT MODIFY MEMBERS ABOVE THIS LINE 

		
	// you should declare a constructor/any other members you need

		Node(int i ){
			id = i;
		}
		bool operator!=(const Node& other) const { return id != other.id; }
		bool operator<(const Node& other) const { return id < other.id; }
		bool operator<=(const Node& other) const { return id <= other.id; }
		bool operator>(const Node& other) const { return id > other.id; }
		bool operator>=(const Node& other) const { return id >= other.id; }
		friend std::ostream& operator<<(std::ostream& os, const Node& other) {
			os << other.id;
			return os;
		}
	// implement any newly declared member functions in node.cpp
	
};

#endif
