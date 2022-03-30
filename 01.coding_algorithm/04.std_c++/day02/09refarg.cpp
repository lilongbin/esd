/*
 * 引用类型做形参可以减少数据的拷贝
 * 简化调用,可以和指针达到一样的效果
 */
#include <iostream>
using namespace std;
void myswap1(int &x, int &y) {
	//引用可以达到指针的效果
	int temp = x;
	x = y;
	y = temp;
}
void printnum(const int &data) {
	//c中加const防止修改变量;
	//c++加const可以防止修改变量,还可以接受常量
	cout << data << endl;
}
int main() {
	int x = 10;
	int y = 20;
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	myswap1(x, y);
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;
	printnum(x);
	printnum(y);
	printnum(100);
}
