#ifndef HASHMAP_HPP_
#define HASHMAP_HPP_

#include "hashNode.hpp"
#include <string>

class hashMap {
	friend class makeSeuss;
	hashNode **map;
	std::string first;
	int numKeys;
	int mapSize;
	bool useHash1;
	bool useColl1;
	int collisionCount1;
	int collisionCount2;

public:
	hashMap(bool hash1, bool coll1);
	void addKeyValue(std::string key, std::string value);
	int getIndex(std::string key);
	int calcHash(std::string key);
	int calcHash2(std::string key);
	void getClosestPrime();
	void reHash();
	int collisionMethod1(int h, int i, std::string key);
	int collisionMethod2(int h, int i, std::string key);
	void collisionsPrint();
};

#endif /* HASHMAP_HPP_ */
