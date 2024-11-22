#include "hashMap.hpp"
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

hashMap::hashMap(bool hash1, bool coll1) {
    useHash1 = hash1;
    useColl1 = coll1;
    mapSize = 101;
    map = new hashNode*[mapSize];
    for (int i = 0; i < mapSize; i++) {
        map[i] = nullptr;
    }
    numKeys = 0;
    collisionCount1 = 0;
    collisionCount2 = 0;
}

void hashMap::addKeyValue(string key, string value) {
    int index = getIndex(key);
    if (index == -1) {
        reHash();
        index = getIndex(key);
        if (index == -1) {
            std::cerr << "Error: Cannot insert key '" << key << "' after rehashing." << std::endl;
            return;
        }
    }
    if (map[index] == nullptr) {
        map[index] = new hashNode(key, value);
        numKeys++;
    } else if (map[index]->keyword == key) {
        map[index]->addValue(value);
    }

    if ((float)numKeys / mapSize > 0.7) {
        reHash();
    }
}

int hashMap::getIndex(string key) {
    int index = useHash1 ? calcHash(key) : calcHash2(key);
    if (index < 0) index += mapSize;

    int i = 0, originalIndex = index;
    while (map[index] != nullptr && map[index]->keyword != key) {
        if (i == 0) collisionCount1++;
        index = useColl1 ? collisionMethod1(originalIndex, ++i, key)
                         : collisionMethod2(originalIndex, ++i, key);
        collisionCount2++;
        if (i >= mapSize) return -1;
    }
    return index;
}

int hashMap::calcHash(string key) {
    unsigned long hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % mapSize;
}

int hashMap::calcHash2(string key) {
    unsigned long long hash = 0;
    int prime = 31;
    for (char c : key) {
        hash = (hash * prime + c) % mapSize;
    }
    return hash;
}

void hashMap::getClosestPrime() {
    int candidate = mapSize * 2 + 1;
    while (true) {
        bool isPrime = true;
        for (int i = 2; i <= sqrt(candidate); i++) {
            if (candidate % i == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            mapSize = candidate;
            return;
        }
        candidate++;
    }
}

void hashMap::reHash() {
    int oldMapSize = mapSize;
    hashNode **oldMap = map;

    getClosestPrime();
    map = new hashNode*[mapSize];
    for (int i = 0; i < mapSize; i++) map[i] = nullptr;

    numKeys = 0;
    collisionCount1 = 0;
    collisionCount2 = 0;

    for (int i = 0; i < oldMapSize; i++) {
        if (oldMap[i] != nullptr) {
            hashNode *node = oldMap[i];
            addKeyValue(node->keyword, node->values[0]); // Insert into new map
            for (int j = 1; j < node->currSize; j++) {
                addKeyValue(node->keyword, node->values[j]);
            }
        }
    }
    delete[] oldMap;
}

int hashMap::collisionMethod1(int h, int i, string key) {
    return (h + i) % mapSize;
}

int hashMap::collisionMethod2(int h, int i, string key) {
    int step = calcHash(key) % (mapSize - 1) + 1;
    return (h + i * step) % mapSize;
}

void hashMap::collisionsPrint() {
    std::cout << "Initial collisions: " << collisionCount1 << "\n";
    std::cout << "Secondary collisions: " << collisionCount2 << "\n";
}
