#ifndef HASHNODE_HPP_
#define HASHNODE_HPP_

#include <string>

class hashNode {
public:
	std::string keyword;
	std::string *values;
	int currSize;
	int valuesSize;

	hashNode();
	hashNode(std::string k);
	hashNode(std::string k, std::string v);
	void addValue(std::string v);
	void resizeArray();
	std::string getRandValue();
};

#endif /* HASHNODE_HPP_ */
