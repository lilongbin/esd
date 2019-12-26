/*
 * 第1个C++程序
 */
#include <iostream>
using namespace std;		//可以使用std里面的所有东西(cin/cout/endl);
int main() {
	//目前该大括号折下来的多一些,但不折下来的更牛一些;
	cout << "hello C++" << endl;	//endline换行
	int age;
	cout << "请输入年龄的值:" << endl;
	cin >> age;		//获取用户输入
	cout << "age is " << age << endl;	//输出类型可以自动识别
	//上面的<</>>有没有想shell里面的重定向呢?
	//cin和cout就是输入输出流对象;
	return 0;
}
