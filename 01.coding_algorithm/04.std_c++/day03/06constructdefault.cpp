/*
 * 构造函数参数默认值
 */
#include <iostream>
using namespace std;
class A {
	public:
		//构造函数也拥有函数参数默认值的特性
		//使用默认值可以减少构造函数的个数
		A(int a = 0, double b = 0) {
			cout << "A(int, double): " << a << ", " << b << endl;
		}
};
int main() {
	A *var_a = new A();	//在堆区创建
	A *var_b = new A(1);
	delete var_a;
	delete var_b;
}
