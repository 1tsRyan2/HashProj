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
        map[i] = nullptr;
    }
    numKeys = 0;
    first = "";
}
void hashMap::addKeyValue(string k, string v) {
    int index = useHash1 ? calcHash1(k) : calcHash2(k);
    int originalIndex = index;
    int i = 0;

    while (map[index] != nullptr) {
        if (map[index]->keyword == k) {
            map[index]->addValue(v);
            return;
        }
        index = useColl1 ? coll1(originalIndex, ++i, k) : coll2(originalIndex, ++i, k);
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

    while (map[index] != nullptr) {
        if (map[index]->keyword == k) {
            return index;
        }
        index = useColl1 ? coll1(originalIndex, ++i, k) : coll2(originalIndex, ++i, k);
    }
    return -1;
}

int hashMap::calcHash2(string k){
    int hash = 0;
    int p = 37;
    int m = mapSize;
    for (int i = 0; i < k.length(); i++) {
        hash = (hash * p + k[i]) % m;
    }
    return hash;
}
int hashMap::calcHash1(string k){
    unsigned int hash = 2166136261; // FNV offset basis
    unsigned int prime = 16777619; // FNV prime
    for (int i = 0; i < k.length(); i++) {
        hash ^= k[i];            // XOR the byte with the hash
        hash *= prime;           // Multiply by the FNV prime
        hash %= mapSize;         // Keep the hash within bounds
    }
    return static_cast<int>(hash); // Cast to int and return
}
void hashMap::getClosestPrime() {
    int candidate = mapSize * 2; // Start with twice the current map size
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
    hashNode** oldMap = map;

    // Step 1: Find the new map size
    getClosestPrime();
    hashNode** newMap = new hashNode*[mapSize];
    for (int i = 0; i < mapSize; i++) {
        newMap[i] = nullptr;
    }

    // Step 2: Rehash all keys from the old map to the new map
    for (int i = 0; i < oldMapSize; i++) {
        if (oldMap[i] != nullptr) {
            hashNode* current = oldMap[i];
            int index = useHash1 ? calcHash1(current->keyword) : calcHash2(current->keyword);
            int originalIndex = index;
            int j = 0;

            while (newMap[index] != nullptr) {
                index = useColl1 ? coll1(originalIndex, ++j, current->keyword) : coll2(originalIndex, ++j, current->keyword);
            }
            newMap[index] = current;
        }
    }

    // Step 3: Update map pointer and size
    delete[] oldMap;
    map = newMap;
}

int hashMap::coll1(int h, int i, string k) {
    return (h + i) % mapSize; // Linear probing: move to the next slot
}
int hashMap::coll2(int h, int i, string k) {
    return (h + i * i) % mapSize; // Quadratic probing: jump by i^2
}

void hashMap::printMap() {
    cout << "In printMap()" << endl;
    for (int i = 0; i < mapSize; i++) {
        //cout << "In loop" << endl;
        if (map[i] != nullptr) {
            cout << map[i]->keyword << ": ";
            for (int j = 0; j < map[i]->currSize;j++) {
                cout << map[i]->values[j] << ", ";
            }
            cout << endl;
        }
    }
}
