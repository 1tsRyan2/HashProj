#include "hashMap.hpp"
#include "hashNode.hpp"
#include <iostream>
#include <math.h>
using namespace std;

float hashMap::getLoadFactor() {
    return static_cast<float>(numKeys) / mapSize;
}


hashMap::hashMap(bool hash1, bool coll1) {
    useHash1 = hash1;
    useColl1 = coll1;

    mapSize = 100;
    map = new hashNode*[mapSize];

    for (int i = 0; i < mapSize; i++) {
        map[1] = NULL;
    }
    numKeys = 0;
    first = "";
}
void hashMap::addKeyValue(string k, string v) {
    int index = useHash1 ? calcHash1(k) : calcHash2(k);
    int originalIndex = index;
    int i = 0;

    while (map[index] != NULL) {
        if (map[index]->keyword == k) {
            map[index]->addValue(v);
            return;
        }
        index = coll1 ? coll1(originalIndex, ++i, k) : coll2(originalIndex, ++i, k);
        if (i > mapSize) {
            cout <<"error: map is full or too many keys." << endl;
            return;
        }
    }
    map[index] = new hashNode(k, v);
    numKeys++;

    if (getLoadFactor() > 0.7) {
        reHash();
    }

}
int hashMap::getIndex(string k) {
    int index = useHash1 ? calcHash1(k) : calcHash2(k);
    int originalIndex = index;
    int i = 0;

    while (map[index] != NULL) {
        if (map[index]->keyword == k) {
            return index;
        }
        index = useColl1 ? coll1(originalIndex, ++i, k) : coll2(originalIndex, ++i, k);
    }
    return -1;
}

int hashMap::calcHash2(string k){
}
int hashMap::calcHash1(string k){
}
void hashMap::getClosestPrime() {
}
void hashMap::reHash() {
}
int hashMap::coll1(int h, int i, string k) {
}
int hashMap::coll2(int h, int i, string k) {
}

void hashMap::printMap() {
    cout << "In printMap()" << endl;
    for (int i = 0; i < mapSize; i++) {
        //cout << "In loop" << endl;
        if (map[i] != NULL) {
            cout << map[i]->keyword << ": ";
            for (int j = 0; j < map[i]->currSize;j++) {
                cout << map[i]->values[j] << ", ";
            }
            cout << endl;
        }
    }
}
