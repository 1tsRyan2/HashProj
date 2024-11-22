#include "hashNode.hpp"
#include <cstdlib>

hashNode::hashNode() {
	keyword = "";
	valuesSize = 0;
	currSize = 0;
	values = nullptr;
}

hashNode::hashNode(std::string k) {
	keyword = k;
	valuesSize = 100;
	currSize = 0;
	values = new std::string[valuesSize];
}

hashNode::hashNode(std::string k, std::string v) {
	keyword = k;
	valuesSize = 100;
	currSize = 1;
	values = new std::string[valuesSize];
	values[0] = v;
}

void hashNode::addValue(std::string v) {
	if (currSize >= valuesSize) {
		resizeArray();
	}
	values[currSize++] = v;
}

void hashNode::resizeArray() {
	valuesSize *= 2;
	std::string *newValues = new std::string[valuesSize];
	for (int i = 0; i < currSize; i++) {
		newValues[i] = values[i];
	}
	delete[] values;
	values = newValues;
}

std::string hashNode::getRandValue() {
	return currSize == 0 ? "" : values[rand() % currSize];
}
