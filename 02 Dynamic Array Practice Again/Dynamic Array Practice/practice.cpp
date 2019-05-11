#include "dynamic_array.h"
#include <iostream>

using namespace std;

int main() {
	DArray a;

	a.insert(0, 2.1);
	cout << a << endl;

	a.push_back(3.0);
	a.push_back(3.1);
	a.push_back(3.2);
	cout << a << endl;

	a.del(0);
	cout << a << endl;
	a.insert (0, 4.1);
	cout << a << endl;

	// here insert function can automatically expand the size of array if the index exceeds the bound.
	a.insert (10, 7);
	cout << a << endl;

	DArray  acopy = a;
	cout << acopy << endl;

	DArray  acopy2(a);
	cout << acopy2 << endl;

	DArray  acopy3;
	acopy3 = a;
	cout << acopy3 << endl;


	DArray  b;
	b.push_back(21);
	cout << b << endl;
	b.del(0);
	cout << b << endl;
	b.push_back(22);
	b.resize(5);
	cout << b << endl;

	DArray  c;
	c.push_back('a');
	c.push_back('b');
	c.push_back('c');
	c.insert(0, 'd');
	cout << c << endl;

	system("pause");
}