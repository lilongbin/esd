/*
 * 引用的本质就是变量(所对应存储空间)的别名
 */
#include <iostream>
using namespace std;
void swap(int &ia, int &ib) {
	//定义函数用于交换两个变量的值,参数为引用类型;
	//形参a和b与实参a和b是一回事,并没有为形参a和b重新分配存储空间;
	int t;
	t = ia, ia = ib, ib = t; //交换两个参数的值;
	cout << &ia << ", " << &ib << endl;
	// ia和a对应同一个存储空间;
	// ib和b对应同一个存储空间;
}
int main() {
	int a = 1, b = 2;
	cout << &a << ", " << &b << endl;
	swap(a, b); //a,b的值将被交换;a==2,b==1;
	//只在函数声明定义时指定参数为引用类型,调用正常使用参数本身;
	//引用和变量对应同一块存储空间
	int &ref1 = a;
	int &ref2 = a;
	int &ref3 = ref1;
	cout << a << " " << ref1 << " " << ref2 << " " << ref3 << " " << endl;
	cout << &a << " " << &ref1 << " " << &ref2 << " " << &ref3 << " " << endl;
	// a,ref1,ref2,ref3都对应同一个存储空间,都是某个存储位置的别名;
	return 0;
}
