/*
 * 构造函数的初始化参数列表
 */
#include <iostream>
using namespace std;
class A {
	const int a;
	int &b;
	//const或引用类型成员,需要在构造函数调用之前初始化参数列表；
	public:
	//构造函数的初始化参数列表
	//放在构造函数参数列表之后,实现体之前,以冒号开头；
	A(int pa, int &pb):a(pa), b(pb) {
		//定义pb为引用类型可解决b的值消失的问题;
		//参数要保证生命期
		//b是引用类型,所以参数列表中pb也要定义为引用类型;
	}
   	void show() {
		cout << a << ", " << b << endl;
	}
};
int main() {
	int x = 100, y = 200;
	A a(x, y);
	a.show();
	int x1 = 300, y1 = 500;
	A b(x1, y1);
	a.show();		//构造函数只在创建对象的时候自动调用一次
	b.show();
}
