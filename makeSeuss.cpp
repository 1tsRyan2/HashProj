#include "makeSeuss.hpp"
#include "hashMap.hpp"

#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

makeSeuss::makeSeuss(string f1,string f2,bool h1, bool c1) {
	ht = new hashMap(h1,c1);
	newfile = f2;
	fn = f1;
	readFile();
	writeFile();
}
void makeSeuss::readFile() {
	ifstream infile(fn.c_str(), ios::in);
	if (!infile) {
		cerr << "Error: Could not open input file: " << fn << endl;
		return;
	}

	string key = "", value = "";
	infile >> key;

	// Skip BOM if present
	if (!key.empty() && (unsigned char)key[0] == 0xEF) {
		infile >> key;
	}

	ht->first = key;

	while (infile >> value) {
		// Skip non-printable characters
		if (value.empty() || !isprint(value[0])) {
			continue;
		}

		ht->addKeyValue(key, value);
		key = value;
	}

	infile.close();
}

void makeSeuss::writeFile() {
	ofstream outfile(newfile.c_str(),ios::out);

	outfile << ht->first << " ";
	string key = "";
	string value = ht->map[ht->getIndex(ht->first)]->getRandValue();
	int ct = 0;
	int len = 0;
	while (ct < 500 &&  value != "") {
		key = value;
		outfile << key << " ";
		if (len == 11) {
			outfile << "\n";
			len = 0;
		}
		else len++;
		value = ht->map[ht->getIndex(key)]->getRandValue();
		ct ++;
	}
	outfile.close();
}