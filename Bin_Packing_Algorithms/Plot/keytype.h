#ifndef KEYTYPE_H
#define KEYTYPE_H
#include <cmath>
#include <iostream>
struct keytype {
	double key;
	int keyID;

	keytype operator++() {
		key++;
		return (*this);
	}
	keytype operator-(keytype other) {
		if (std::fabs(key - other.key) < 0.000001) {
			key = 0;
		}
		else {
			key = key - other.key;
		}
		if (keyID < other.keyID) {
			keyID =other.keyID;
		}
		return (*this);
	}
	bool operator==(keytype other)const {
		return (std::fabs(key - other.key) < 0.000006 && keyID == other.keyID);
	}
	bool operator>=(keytype other)const {
		return std::fabs(key - other.key) < 0.000006 || key > other.key;
	}
	bool operator<=(keytype other)const {
		return std::fabs(key - other.key) < 0.000006 || key < other.key;
	}
	bool operator>(keytype other)const {
		return !(std::fabs(key - other.key) < 0.000006) && key > other.key;
	}
	bool operator<(keytype other)const {
		return !(std::fabs(key - other.key) < 0.000006) && key < other.key;
	}
	bool operator!=(keytype other)const {
		return !(std::fabs(key - other.key) < 0.000006 && keyID == other.keyID);
	}
	friend std::ostream& operator<<(std::ostream& os, const keytype& other){
		os << "key: " << other.key << " ID: " << other.keyID ;
		return os;
	}
};
#endif