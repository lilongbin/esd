/*
 * 函数返回引用类型并做左值
 */
#include <iostream>
using namespace std;
// int &ret_val() {
int ret_val() {
	int i = 10;
	cout << "&i = " << &i << endl;
	return i;
	// 返回值为普通变量类型时,会把返回值放入一个临时空间然后赋值给调用者提供的存储空间;
	// i -> tmp -> 调用者准备的空间;
	// 返回值为引用类型时直接使用返回的的变量所对应的存储空间供调用者使用;
	// i -> [i] -> 调用者准备的空间;[i]即不开辟一个新的临时空间;
	// 如果i是局部变量,这在函数返回时释放,调用者使用的是一个非法的空间;
}
// int getmax(int x, int y) {
//	 return x > y ? x : y; //返回的是值
// }
int &getmax(int &x, int &y) {
	return x > y ? x : y;	//返回的是值
}
int &getnum() {
	//int temp = 100; //局部变量,不能返回对局部变量的引用
	static int temp = 100;
	return temp;
}
int main() {
	int i = ret_val();
	cout << "&tmp = " << sizeof(ret_val()) << endl;
	int x = 10;
	int y = 123;
	int var_res = getmax(x, y);
	cout << "getmax(x, y)= " << var_res << endl;	//123
	getmax(x, y) = 456;
	cout << "x = " << x << endl;
	cout << "y = " << y << endl;	//456
	int &var_res1 = getnum(); //var_res1是temp的引用
	cout << var_res1 << endl;
}
