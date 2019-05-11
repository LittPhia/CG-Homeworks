#include <iostream>
#include "Polynomial.h"

using namespace std;

int main () {
	string name;
	name.assign("P1.txt");

	for (size_t i = 1; i < 6; i++) {
		Polynomial p1(name);
		cout << "TEST FILES : " << name.c_str() << " / ";

		name[1] = '1' + i;
		Polynomial p2 (name);
		cout << name.c_str() << endl;

		Polynomial p3;
		cout << "    P1   |" << p1 << endl
			<< "    P2   |" << p2 << endl;

		p3 = p1 + p2;
		cout << " P1 + P2 |" << p3 << endl;

		p3 = p1 - p2;
		cout << " P1 - P2 |" << p3 << endl;

		p3 = p1 * p2;
		cout << " P1 * P2 |" << p3 << endl;
		cout << endl;
	}
	system ("pause");
	return 0;
}