/*
 * 无名的命名空间
 */
#include <iostream>
using namespace std;
int age = 100;			//全局变量
namespace {			/* 防止跨文件访问 */
	int count = 1001;	//无名的命名空间
}
int main() {
	cout << age << endl;
	cout <<::age << endl;
	cout << count << endl;
	cout <<::count << endl;	//可以向全局一样访问
}
