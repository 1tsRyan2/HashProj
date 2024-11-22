#include <iostream>
#include "makeSeuss.hpp"
#include <time.h>
#include <stdlib.h>

using namespace std;
int main() {
	srand(time(NULL));
	makeSeuss voice1("DrSeuss.txt","out1.txt",true,true);
	makeSeuss voice2("DrSeuss.txt","out2.txt",false,true);
	makeSeuss voice3("DrSeuss.txt","out3.txt",true,false);
	makeSeuss voice4("DrSeuss.txt","out4.txt",false,false);
	cout <<  "successfully created";
	return 0;

}
