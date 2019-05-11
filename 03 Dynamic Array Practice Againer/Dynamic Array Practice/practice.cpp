#include "dynamic_array.h"
#include <iostream>

using namespace std;

int main () {
	DArray<double> a;
	a.insert(0, 2.1);
	cout << a << endl;

	a.push_back(3.0);
	a.push_back(3.1);
	a.push_back(3.2);
	cout << a << endl;

	a.del(0);
	cout << a << endl;
	a.insert(0, 4.1);
	cout << a << endl;

	DArray<double> acopy = a;  //此处用到了拷贝构造函数
	cout << acopy << endl;

	DArray<double> acopy2 (a);  //该语句等同于上面的语句，都是初始化
	cout << acopy2 << endl;

	DArray<double> acopy3;
	acopy3 = a;					//此处用到了赋值操作符号"="的重载
	cout << acopy3 << endl;


	DArray<int> b;
	b.push_back(21);
	cout << b << endl;
	b.del(0);
	cout << b << endl;
	b.push_back(22);
	b.resize(5);
	cout << b << endl;

	DArray<char> c;
	c.push_back('a');
	c.push_back('b');
	c.push_back('c');
	c.insert(0, 'd');
	cout << c << endl;

	system ("pause");
	return 0;
}