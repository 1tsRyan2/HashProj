#include "makeSeuss.hpp"
#include <cstdlib>
#include <ctime>

int main() {
	srand(time(NULL));

	makeSeuss seuss1("DrSeuss.txt", "Seussout1.txt", true, true);
	seuss1.collisionsPrint();

	makeSeuss seuss2("DrSeuss.txt", "Seussout2.txt", true, false);
	seuss2.collisionsPrint();

	makeSeuss seuss3("DrSeuss.txt", "Seussout3.txt", false, true);
	seuss3.collisionsPrint();

	makeSeuss seuss4("DrSeuss.txt", "Seussout4.txt", false, false);
	seuss4.collisionsPrint();

	return 0;
}
