#include <iostream>
using namespace std;
class A {
	const int a; //const修饰的变量只能在定义时初始化;
	int &b; //定义引用必须初始化;
	//const或引用类型成员,需要在构造函数调用之前初始化参数列表；
	public:
	//构造函数的初始化参数列表在构造函数参数列表之后,实现体之前,以冒号开头;
	A(int pa, int pb):a(pa), b(pb) {
		//参数要保证生命期
		//pb是普通变量,用完就消失,所有后面b的值没有保留创建时传入的值;
		//a = pa; //const变量不可再赋值;
		//b = pb;
	}
   	void show() {
		cout << a << "," << b << endl;
	}
};
int main() {
	int x = 100, y = 200;
	A a(100, 200);
	a.show(); //100, 200
	A b(300, 500);
	a.show(); //100, 500;a.show()的结果受到干扰
}
