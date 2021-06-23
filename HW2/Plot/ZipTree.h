#ifndef ZIPTREE_H
#define ZIPTREE_H
#include "keytype.h"
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
		ValType  max;
		KeyType maxkey;
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
	BinaryNode* zip(BinaryNode* x, BinaryNode* y);
	BinaryNode* removehelper(const KeyType& key, BinaryNode* next);
	void find(const KeyType& key, BinaryNode& node);
	void printTree(BinaryNode* tempHead);
	void printTree();
	int ff_traversal(double val, BinaryNode* tempNode);
	int ffinsert(int& bin,double val);
	int bfinsert(int& bin, KeyType val);
	void replace(double  newVal, BinaryNode* node);
	ValType fixmax(BinaryNode* tempHead);
	int heighthelp(BinaryNode* tempHead);
	KeyType fixmaxkey(BinaryNode* tempHead);
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
	srand(2);
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
	//printTree(head);
	if (tempHead != nullptr) {
		leftval = 0;
		rightval = 0;
		if (tempHead->left == nullptr && tempHead->right == nullptr) {
			tempHead->max = tempHead->val;
			return tempHead->val;
		}
		if (tempHead->left != nullptr) {
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
		return tempHead->max;
	}
	return -1;
}
template <typename KeyType, typename ValType>
KeyType ZipTree<KeyType, ValType>::fixmaxkey(BinaryNode* tempHead) {
	KeyType leftkey;
	KeyType rightkey;
	//std::cout << "fixed call:" << std::endl;
	//printTree(tempHead);
	if (tempHead != nullptr) {
		if (tempHead->left == nullptr && tempHead->right == nullptr) {
			tempHead->maxkey = tempHead->key;
			//std::cout << "maxcheckR: " << tempHead->key << std::endl;
			//std::cout << "head" << std::endl;
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
					return tempHead->key;
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
					return tempHead->key;
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
		return tempHead->maxkey;
	}
	return head->key;
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
	//std::cout << "point1" << std::endl;
	while (curr != nullptr && (rank < curr->rank || (rank == curr->rank && key > curr->key))) {
		prev = curr;
		if (key < curr->key) {
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}
		//std::cout << "point1" << std::endl;
	}
	//std::cout << "point2" << std::endl;
	if (curr == head ) {
		head = newNode;
		//std::cout << "point1" << std::endl;
	}
	else if (key < prev->key) {
		prev->left = newNode;
		//std::cout << "point2" << std::endl;
	}
	else {
		prev->right = newNode;
		//std::cout << "point3" << std::endl;
	}
	
	if (curr == nullptr) {
		std::cout << newNode->key << std::endl;
		newNode->left = nullptr;
		newNode->right = nullptr;
		if (head != nullptr) {
			fixmax(head);
			
			fixmaxkey(head);
		}
		//std::cout << "point3" << std::endl;
		return;
		//
	}
	if (key < curr->key) {
		newNode->right = curr;
	}
	else {
		newNode->left = curr;
	}
	prev = newNode;
	//std::cout << "point4" << std::endl;

	//	std::cout << "point1" << std::endl;
	BinaryNode* fix = prev;
	while (curr != nullptr) {
		//std::cout << "curr" << curr->key << std::endl;
		//std::cout << "key" << std::endl;
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
	//std::cout << "point6" << std::endl;

	//std::cout << "insert" << std::endl;
	if (head != nullptr) {
		fixmax(head);
		//std::cout << "point7" << std::endl;
		fixmaxkey(head);
	}
	//std::cout << "point8" << std::endl;

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
typename ZipTree<KeyType, ValType>::BinaryNode* ZipTree<KeyType, ValType>::zip(BinaryNode* x, BinaryNode* y) {
	if (x == nullptr) {
		return y;
	}
	if (y == nullptr) {
		return x;
	}
	if (x->rank < y->rank) {
		y->left = zip(x, y->left);
		return y;
	}
	else {
		x->right = zip(x->right, y);
		return x;
	}
}
template <typename KeyType, typename ValType>
typename ZipTree<KeyType, ValType>::BinaryNode* ZipTree<KeyType, ValType>::removehelper(const KeyType& key, BinaryNode* next) {
	if (key == next->key) {
		return zip(next->left, next->right);
	}
	if (key < next->key) {
		if (key == next->left->key) {
			next->left = zip(next->left->left, next->left->right);
		}
		else {
			removehelper(key, next->left);
		}
	}
	else {
		if (key == next->right->key) {
			next->right = zip(next->right->left, next->right->right);
		}
		else {
			removehelper(key, next->right);
		}
	}
	return next;
}
template <typename KeyType, typename ValType>
void ZipTree<KeyType, ValType>::remove(const KeyType& key)
{
	sz--;
	
	/*if (head != nullptr) {
		removehelper(key, head);
	}*/
	
	BinaryNode* curr = head;
	BinaryNode* prev = head;
	//std::cout << "done" << std::endl;
	//std::cout << "curr addr" << curr->key << "  key addr " << key << std::endl;
	while (curr->key != key) {
		prev = curr;
		if (key < curr->key) {
			curr = curr->left;
		}
		else {
			curr = curr->right;
		}
		
	}
	std::cout << "done" << std::endl;
	BinaryNode* leftnode = curr->left;
	BinaryNode* rightnode = curr->right;
	BinaryNode* x = curr;
	if (leftnode == nullptr) {
		curr = rightnode;
	}
	else if (rightnode == nullptr) {
		curr = leftnode;
	}
	else if (leftnode->rank > rightnode->rank) {
		curr = leftnode;
	}
	else {
		curr = rightnode;
	}
	//std::cout << "head" << head->key << " vs " << x->key << "bool:" << (head == x) << std::endl;
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
	
	if (x != nullptr) {
		//std::cout << "remove x: key: " << x->key << " val " << x->val << std::endl;
		delete x;
	}
	
	if (head != nullptr) {
		//std::cout << "fix" << std::endl;
		fixmax(head);
		//std::cout << "fixk" << std::endl;
		fixmaxkey(head);
		//std::cout << "fixkend" << std::endl;
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
int ZipTree<KeyType, ValType>::bfinsert(int& bin, KeyType val) {

	BinaryNode* next = head;
	BinaryNode* prev = head;
	bool stop = false;
	if (head == nullptr) {
		//std::cout << "in " << 1 - val << std::endl;
		insert(keytype{ 1 ,-1 } - val, bin++);
	}
	else {
		//printTree(head);
		while (next != nullptr && stop == false) {
			//std::cout << "prev: " << prev->key << "next: " << next->key << std::endl;
			prev = next;
			/*if (next->left != nullptr) {
				std::cout << next->key << "(next->left->maxkey > val || std::fabs(next->left->maxkey - val) < 0.000001)" << next->left->maxkey << " > " << val << " || " << std::fabs(next->left->maxkey - val) << "\n equal: " << std::fabs(next->left->maxkey - val) << " B: " << (next->left->maxkey > val || std::fabs(next->left->maxkey - val) < 0.001) << std::endl;
			}
			if (next->right != nullptr) {
				std::cout << next->key <<"(next->right->maxkey > val || std::fabs(next->right->maxkey - val) < 0.000001)" << next->right->maxkey << " > " << val << " || " << std::fabs(next->right->maxkey - val) <<"\n equal: " << std::fabs(next->right->maxkey - val) << " B: "<< (next->right->maxkey > val || std::fabs(next->right->maxkey - val) < 0.001) << std::endl;
			}*/
			if (next->key >= val && next->left != nullptr && next->left->maxkey >= val ) {
				next = next->left;
			}else if (next->key <= val  && next->right != nullptr && next->right->maxkey >= val ) {
				next = next->right;
			}else {
				stop = true;
			}
		}
		if (prev != nullptr){
			//std::cout << "prev: " << prev->key << "val: " << val << std::endl;
		}
		if (prev != nullptr && prev->key >= val ) {
			KeyType tempkey = prev->key;
			ValType tempval = prev->val;
			if (tempkey == val) {
				//std::cout << "1";
				remove(prev->key);
			}else {
				//std::cout << "2";
				remove(prev->key);
				//std::cout << "5";
				insert(tempkey - val, tempval);
				//insert(tempkey - val, tempval);
			}
			std::cout << tempval + 1;
			return tempval + 1;
		}
		else {
			std::cout << keytype{ 1 ,-1 } - val;
			insert(keytype{ 1 ,-1 } - val, bin++);
		}
	}
	return bin;
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
	return -1;
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
