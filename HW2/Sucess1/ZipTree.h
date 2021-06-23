#ifndef ZIPTREE_H
#define ZIPTREE_H

#include <time.h> 
#include <cmath>
#include <iostream>
// explanations for public member functions are provided in project2.h
// each file that uses a WAVL tree should #include this file
template <typename KeyType, typename ValType>
class ZipTree
{
public:
	struct BinaryNode {
		BinaryNode* left;
		BinaryNode* right;
		ValType val;
		double max;
		double maxkey;
		KeyType key;
		unsigned rank;
	};
	// DO NOT MODIFY METHOD SIGNATURES BELOW THIS LINE
	ZipTree();
	~ZipTree();
	void eraseAll(BinaryNode* next);
	static unsigned getRandomRank();
	void insert(const KeyType& key, const ValType& val, unsigned rank = getRandomRank());
	void remove(const KeyType& key);
	ValType find(const KeyType& key);
	unsigned getSize();
	int getHeight();
	unsigned getDepth(const KeyType& key);
	// DO NOT MODIFY METHOD SIGNATURES ABOVE THIS LINE
	// define new public methods
	int insert_tree(BinaryNode* tempHead, BinaryNode* iNode);
	void find(const KeyType& key, BinaryNode& node);
	void printTree(BinaryNode* tempHead);
	void printTree();
	int ff_traversal(double val, BinaryNode* tempNode);
	int ffinsert(int& bin,double val);
	int bfinsert(int& bin, double val);
	void replace(double  newVal, BinaryNode* node);
	ValType fixmax(BinaryNode* tempHead);
	int heighthelp(BinaryNode* tempHead);
	double fixmaxkey(BinaryNode* tempHead);
private:
	// define private methods
	int height;
	unsigned sz;
	BinaryNode* head;
	
};

// fill in the definitions for each required member function and for any additional member functions you define


template <typename KeyType, typename ValType>
ZipTree<KeyType, ValType>::ZipTree()
{
	// TODO
	srand(time(0));
	height = 0;
	sz = 0 ;
	head = nullptr;
}

template <typename KeyType, typename ValType>
ZipTree<KeyType, ValType>::~ZipTree()
{
	eraseAll(head);
}

template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::eraseAll(BinaryNode* next) {
	if (next != nullptr) {
		eraseAll(next->left);
		eraseAll(next->right);
		delete next;
	}
}


template <typename KeyType, typename ValType>
unsigned ZipTree<KeyType, ValType>::getRandomRank()
{
	// TODO
	int rank = 0;
	while (rand() % 2 == 1) {
		rank++;
	}
	return rank;
}
template <typename KeyType, typename ValType>
int ZipTree<KeyType, ValType>::insert_tree(BinaryNode* tempHead, BinaryNode* iNode) {
	int height = 0;
	if (tempHead->key > iNode->key) {
		if (tempHead->left != nullptr) {
			return insert_tree(tempHead->left, iNode) + 1;
		}
		else {
			tempHead->left = iNode;
			return 1;
		}
	}
	if (tempHead->key <= iNode->key) {
		if (tempHead->right != nullptr) {
			return insert_tree(tempHead->right, iNode) + 1;
		}
		else {
			tempHead->right = iNode;
			return 1;
		}
	}
	return height;
}
template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::printTree(BinaryNode* tempHead) {
	if (tempHead != nullptr) {
		std::cout << " VAL: " << tempHead->val << " RANK: " << tempHead->rank << " KEY: " << tempHead->key << " MAX: " << tempHead->max << " MAXK: " << tempHead->maxkey << std::endl;
	}
	if (tempHead->left != nullptr) {
		std::cout << " LEFT: " << std::endl;
		printTree(tempHead->left);
	}
	if (tempHead->right != nullptr) {
		std::cout << " RIGHT: " << std::endl;
		printTree(tempHead->right);
	}
}
template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::printTree() {
	BinaryNode* tempHead = head;
	if (tempHead != nullptr) {
		std::cout << " VAL: " << tempHead->val << " RANK: " << tempHead->rank << " KEY: " << tempHead->key << " MAX: " << tempHead->max << " MAXK: " << tempHead->maxkey << std::endl;
	}
	if (tempHead->left != nullptr) {
		std::cout << " LEFT: " << std::endl;
		printTree(tempHead->left);
	}
	if (tempHead->right != nullptr) {
		std::cout << " RIGHT: " << std::endl;
		printTree(tempHead->right);
	}
}
template <typename KeyType, typename ValType>
ValType ZipTree<KeyType, ValType>::fixmax(BinaryNode* tempHead) {
	ValType leftval;
	ValType rightval;
	//std::cout << "maxcheck:" << std::endl;
	//printTree(tempHead);
	if (tempHead != nullptr) {
		if (tempHead->left == nullptr && tempHead->right == nullptr) {
			tempHead->max = tempHead->val;

			return tempHead->val;
		}
		if(tempHead->left != nullptr){
			leftval = fixmax(tempHead->left);
			if (tempHead->right == nullptr) {
				if (leftval > tempHead->val) {
					tempHead->max = leftval;
					return tempHead->max;
				}
				else {
					tempHead->max = tempHead->val;
					return tempHead->max;
				}
				
			}
		}
		if (tempHead->right != nullptr) {
			rightval = fixmax(tempHead->right);
			if (tempHead->left == nullptr) {
				if (rightval > tempHead->val) {
					tempHead->max = rightval;
					return tempHead->max;
				}
				else {
					tempHead->max = tempHead->val;
					return tempHead->max;
				}
			}
		}
		if (leftval >= rightval) {
			tempHead->max = leftval;
			return tempHead->max;
		}
		else {
			tempHead->max = rightval;
			return tempHead->max;
		}
	}
	return tempHead->max;
}
template <typename KeyType, typename ValType>
double ZipTree<KeyType, ValType>::fixmaxkey(BinaryNode* tempHead) {
	double leftkey;
	double rightkey;
	//std::cout << "maxcheck:" << std::endl;
	//printTree(tempHead);
	if (tempHead != nullptr) {
		if (tempHead->left == nullptr && tempHead->right == nullptr) {
			tempHead->maxkey = tempHead->key;
			//std::cout << "maxcheck: " << tempHead->key << std::endl;
			return tempHead->key;
		}
		if (tempHead->left != nullptr) {
			leftkey = fixmaxkey(tempHead->left);
			if (tempHead->right == nullptr) {
				if (leftkey > tempHead->key) {
					tempHead->maxkey = leftkey;
					return tempHead->maxkey;
				}
				else {
					tempHead->maxkey = tempHead->key;
					return tempHead->maxkey;
				}

			}
		}
		if (tempHead->right != nullptr) {
			rightkey = fixmaxkey(tempHead->right);
			if (tempHead->left == nullptr) {
				if (rightkey > tempHead->key) {
					tempHead->maxkey = rightkey;
					return tempHead->maxkey;
				}
				else {
					tempHead->maxkey = tempHead->key;
					return tempHead->maxkey;
				}
			}
		}
		if (leftkey >= rightkey) {
			tempHead->maxkey = leftkey;
			return tempHead->maxkey;
		}
		else {
			tempHead->maxkey = rightkey;
			return tempHead->maxkey;
		}
	}
	return tempHead->maxkey;
}
template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::insert(const KeyType& key, const ValType& val, unsigned rank)
{
	// TODO
	sz++;
	//create NODE
	BinaryNode* newNode = new BinaryNode();
	newNode->val = val;
	newNode->rank = rank;
	newNode->key = key;
	newNode->max = val;
	BinaryNode* curr = head;
	BinaryNode* prev = head;
	while (curr != nullptr && (rank < curr->rank || (rank == curr->rank && key > curr->key))) {
		prev = curr;
		if (key < curr->key) {
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}
	}
	if (curr == head ) {
		head = newNode;
	}
	else if (key < prev->key) {
		prev->left = newNode;
	}
	else {
		prev->right = newNode;
	}

	if (curr == nullptr) {
		newNode->left = nullptr;
		newNode->right = nullptr;
		return;
	}
	if (key < curr->key) {
		newNode->right = curr;
	}
	else {
		newNode->left = curr;
	}
	prev = newNode;
	//	std::cout << "point1" << std::endl;
	BinaryNode* fix = prev;
	while (curr != nullptr) {
		
		fix = prev;
		if (curr->key < key) {
			while (curr != nullptr && curr->key <= key) {
				prev = curr;
				curr = curr->right;
			}
		}
		else {
			while (curr != nullptr && curr->key >= key) {
				prev = curr;
				curr = curr->left;
			}
		}
		//std::cout << "point2" << std::endl;
		if (fix->key > key || (fix == newNode && prev->key > key)) {
			fix->left = curr;
		}
		else {
			fix->right = curr;
		}
		
	}
	
	fixmax(head);
	fixmaxkey(head);

	//find rank spot, put remainer fix in place 
	/*	
	if (head == nullptr) {
		head = newNode;
		return;
	}else {
		
		if (newNode->rank > place->rank) {
			if (newNode->key < place->key) {
				newNode->right = place;
			}
			else if (newNode->key >= place->key) {
				newNode->left = place;
			}
			head = newNode;
			height++;
		}
		else {
			while (place != nullptr && place->rank >= newNode->rank) {
				//std::cout << "prevplace" << prevplace->key << std::endl;
				//std::cout << "place" << place->key << std::endl;
				//std::cout << "newNode" << newNode->key << std::endl;
				
				if (newNode->key < place->key) {
					if (place != nullptr && place->rank == newNode->rank) {
						
						newNode->right = place;
						prevplace->left = place->left;
						place->left = nullptr;
						newNode->left = nullptr;
						place = prevplace->left;
						//printTree(prevplace);
						break;
					}
					else {
						prevplace = place;
						place = place->left;
					}
				}
				else if (newNode->key >= place->key) {
					prevplace = place;
					place = place->right;
				}
				maxheight++;
			}
			
			place = prevplace;
			BinaryNode* moveNode = place;
			if (newNode->key < place->key) {
				moveNode = place->left;
				place->left = newNode;
			}
			else if (newNode->key >= place->key) {
				moveNode = place->right;
				place->right = newNode;
			}
			place = moveNode;
			int local_height = 0;
			int temp = 0;
			if (place != nullptr) {
				//printTree(place);
			}
			//printTree(newNode);
			while (place != nullptr) {
				moveNode = place;
				//std::cout << "hello";
				if (newNode->key < place->key) {
					place = place->left;
					moveNode->left = nullptr;
					//std::cout << "hello";
					temp = insert_tree(newNode, moveNode);
					//std::cout << "hello";
				}
				else if (newNode->key >= place->key) {
					place = place->right;
					moveNode->right = nullptr;
					temp = insert_tree(newNode, moveNode);
				}
				if (temp > local_height) {
					local_height = temp;
				}
				//std::cout << "place" << place->key << std::endl;
			}
			if (height < maxheight + local_height) {
				height = maxheight + local_height;
			}
		}
		//printTree(head);
	}
	*/
}

template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::remove(const KeyType& key)
{
	sz--;
	
	BinaryNode* curr = head;
	BinaryNode* prev = head;
	while (curr->key != key) {
		prev = curr;
		if (key < curr->key) {
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}
	}
	
	BinaryNode* leftnode = curr->left;
	BinaryNode* rightnode = curr->right;
	BinaryNode* x = curr;
	if (leftnode == nullptr) {
		curr = rightnode;
	}
	else if (rightnode == nullptr) {
		curr = leftnode;
	}
	else if (leftnode->rank >= rightnode->rank) {
		curr = leftnode;
	}
	else {
		curr = rightnode;
	}
	
	if (head == x) {
		head = curr;
	}
	else if(key < prev->key){
		prev->left = curr;
	}
	else {
		prev->right = curr;
	}
	
	while (leftnode != nullptr && rightnode != nullptr) {
		
		if (leftnode->rank >= rightnode->rank) {

			while (leftnode != nullptr && leftnode->rank >= rightnode->rank) {
				prev = leftnode;
				leftnode = leftnode->right;
			}
			prev->right = rightnode;
		}
		else {
			
			while (rightnode != nullptr && leftnode->rank < rightnode->rank) {
				prev = rightnode;
				rightnode = rightnode->left;
			}
			prev->left = leftnode;
		}
	}
	
	delete x;
	if (head != nullptr) {
		fixmax(head);
		fixmaxkey(head);
	}
}

template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::replace(double  newVal, BinaryNode* node) {
	KeyType oldkey = node->key;
	remove(node->key);
	insert(oldkey, newVal);
	
}
template <typename KeyType, typename ValType>
int ZipTree<KeyType, ValType>::ffinsert(int& bin, double val) {
	
	BinaryNode* next = head;
	bool stop = false;
	if (head == nullptr) {
		insert(bin++, 1 - val);
	}
	else {
		//printTree();
		while (next != nullptr && stop == false) {
			if (next->left != nullptr && (std::fabs((next->left->max) - val) < 0.00001 || next->left->max > val)) {
				//std::cout << "next->left->max >= val" << next->left->max << " >= " << val << " : " << std::fabs((next->left->max) - val) << (std::fabs((next->left->max) - val) < 0.0001) << std::endl;
				next = next->left;
			}
			else if( (next->val < val && !(std::fabs(next->val - val) < 0.00001)) && next->right != nullptr){
				//std::cout << "next->val < val:" << next->val << " < " << val << ": bool:" << ((next->val) < val) << std::endl;
				next = next->right;
			}
			else {
				stop = true;
			}
		}
		//printTree(head);
		
		if (next != nullptr && (val < next->val || std::fabs((next->val) - val) < 0.0001)) {
			KeyType temp = next->key;
			if (std::fabs(next->val - val) < 0.000001) {
				replace(0, next);
			}
			else {
				replace(next->val - val, next);
			}
			return temp + 1;
		}
		else {
			insert(bin++,1 - val);
		}
		//printTree(head);
	}
	return bin;
}
template <typename KeyType, typename ValType>
int ZipTree<KeyType, ValType>::bfinsert(int& bin, double val) {
	template <typename KeyType, typename ValType>
	int ZipTree<KeyType, ValType>::bfinsert(double val, int& bin) {

		BinaryNode* next = head;
		bool stop = false;
		if (head == nullptr) {
			insert((1.0 - val), bin++);
			std::cout << "hello?" << std::endl;
		}
		else {
			double min = next->key;
			printTree();
			std::cout << "------------------------------------------------------- \n";
			while (next != nullptr && stop == false) {

				if (next->left != nullptr && (std::fabs((next->key) - val) < 0.00001 || next->key > val)) {
					//std::cout << "next->left->max >= val" << next->left->max << " >= " << val << " : " << std::fabs((next->left->max) - val) << (std::fabs((next->left->max) - val) < 0.0001) << std::endl;
					next = next->left;
				}
				else if ((next->right != nullptr && next->key < val)) {
					//std::cout << "next->val < val:" << next->val << " < " << val << ": bool:" << ((next->val) < val) << std::endl;
					next = next->right;
				}
				else {
					stop = true;
				}
				if (next != nullptr && min > next->key && (next->key > val || std::fabs((next->key) - val) < 0.00001)) {
					min = next->key;
				}
			}

			if (next != nullptr && (val < next->val || std::fabs((next->val) - val) < 0.0001)) {
				ValType oldval = next->val;
				if (std::fabs(next->val - val) < 0.000001) {
					remove(min);
					insert(0, oldval);
				}
				else {
					remove(min);
					insert(min - val, oldval);
				}
				std::cout << min << oldval << std::endl;
				return oldval;
			}
			else {
				insert(1 - val, bin++);
				return bin;
			}
			//printTree(head);

		}

		return bin;
	}
}
template <typename KeyType, typename ValType>
ValType ZipTree<KeyType, ValType>::find(const KeyType& key)
{
	// TODO
	

	BinaryNode* next = head;

	while (next != nullptr) {
		//std::cout << "\nnext" << next->key << std::endl;
		//std::cout << "key" << key << std::endl;
		//printTree(next);
		//printTree(next);
		if(next->key == key) {
			return next->val;
		}
		if (next->key < key) {
			next = next->right;
		}else if (next->key > key) {
			next = next->left;
		}
	}
	return next->val;
}

template <typename KeyType, typename ValType>
unsigned ZipTree<KeyType, ValType>::getSize()
{
	// TODO
	return sz; // remove this line when you implement this function
}
template <typename KeyType, typename ValType>
int ZipTree<KeyType, ValType>::heighthelp(BinaryNode* tempHead) {
	int lef = 0;
	int rig = 0;
	if (tempHead != nullptr)
	{
		if (tempHead->left != nullptr) {
			lef = heighthelp(tempHead->left) + 1;
		}
		if (tempHead->right != nullptr) {
			rig = heighthelp(tempHead->right) + 1;
		}
		if (lef > rig) {
			return lef;
		}
		else {
			return rig;
		}
	}
	return  0;
}
template <typename KeyType, typename ValType>
int ZipTree<KeyType, ValType>::getHeight()
{
	// TODO
	return heighthelp(head); // remove this line when you implement this function
}

template <typename KeyType, typename ValType>
unsigned ZipTree<KeyType, ValType>::getDepth(const KeyType& key)
{
	// TODO
	BinaryNode* next = head;
	unsigned depth = 0;
	//std::cout << "target " << key << std::endl;
	while (next != nullptr) {
		//std::cout << "start " << next->key << std::endl;
		//printTree(next);
		if (next->key == key) {
			//std::cout << ", " << next->key << std::endl;
			return depth;
		}
		if (next->key < key) {
			//std::cout << ", L: " << next->key;
			next = next->right;
			depth++;
		}
		if (next->key > key) {
			//std::cout << ", R: " << next->key;
			next = next->left;
			depth++;
		}
	}
	//std::cout << std::endl;
	return depth;
}

#endif
