#ifndef MAKESEUSS_HPP_
#define MAKESEUSS_HPP_

#include "hashMap.hpp"
#include <string>

class makeSeuss {
    hashMap *ht;
    std::string newfile;
    std::string fn;

public:
    makeSeuss(std::string inputFile, std::string outputFile, bool hash1, bool coll1);
    void processFile();
    void createOutputFile();
    void collisionsPrint();
};

#endif /* MAKESEUSS_HPP_ */
