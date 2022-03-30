/*
 * 构造函数重载
 */
#include <iostream>
using namespace std;
class A {
	public:
		//构造函数重载
		A() {
			cout << "A()" << endl;
		}
		A(int a) {
			cout << "A(int): " << a << endl;
		}
		A(int a, double b) {
			cout << "A(int, double): " << a << ", " << b << endl;
		}
};
int main() {
	A var_a; //创建了一个对象
	A var_b(1); //创建了一个对象
	A var_c(2); //创建了一个对象
	A var_d(1, 2.5); //创建了一个对象
	A *var_e = new A();	//在堆区创建
	A *var_f = new A(1);
	delete var_e;
	delete var_f;
	//A var_c(); //错误,与A var_a不同;
	//A var_c(); //系统默认为是函数声明;不会创建对象
}
