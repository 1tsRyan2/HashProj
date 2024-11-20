

#include "hashMap.hpp"
#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;



hashNode::hashNode(string s){
	keyword = s;
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}
hashNode::hashNode(){
	keyword = "";
	values = new string[100];
	valuesSize = 100;
	currSize = 0;
	srand(time(NULL));
}
hashNode::hashNode(string s, string v){
	keyword = s;
	values = new string[100];
	values[0] = v;
	valuesSize = 100;
	currSize = 1;
}
void hashNode::addValue(string v) {
	if (currSize == valuesSize) {
		dblArray();
	}
	values[currSize++] = v;
}
void hashNode::dblArray() {
	valuesSize *= 2;
	string* newValues = new string[valuesSize];
	for (int i = 0; i < currSize; i++) {
		newValues[i] = values[i];
	}
	delete[] values;
	values = newValues;
}
string hashNode::getRandValue() {
	if (currSize =0) return "";
	int randIndex = rand() % currSize;
	return values[randIndex];
}
