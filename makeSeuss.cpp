#include "makeSeuss.hpp"
#include <fstream>
#include <iostream>

makeSeuss::makeSeuss(std::string inputFile, std::string outputFile, bool hash1, bool coll1) {
    ht = new hashMap(hash1, coll1);
    newfile = outputFile;
    fn = inputFile;
    processFile();
    createOutputFile();
}

void makeSeuss::processFile() {
    std::ifstream infile(fn.c_str(), std::ios::in);
    std::string key, value;
    if (infile >> key) {
        ht->first = key;
    }
    while (infile >> value) {
        ht->addKeyValue(key, value);
        key = value;
    }
    infile.close();
}

void makeSeuss::createOutputFile() {
    std::ofstream outfile(newfile.c_str(), std::ios::out);
    outfile << ht->first << " ";
    std::string key = ht->first, value;
    int count = 0, lineLength = 0;

    while (count < 500) {
        int index = ht->getIndex(key);
        if (index == -1 || ht->map[index] == nullptr) break;
        value = ht->map[index]->getRandValue();
        if (value.empty()) break;

        outfile << value << " ";
        lineLength++;
        if (lineLength == 11) {
            outfile << "\n";
            lineLength = 0;
        }
        key = value;
        count++;
    }
    outfile.close();
}

void makeSeuss::collisionsPrint() {
    std::cout << "Collisions for " << newfile << ":\n";
    ht->collisionsPrint();
    std::cout << std::endl;
}
