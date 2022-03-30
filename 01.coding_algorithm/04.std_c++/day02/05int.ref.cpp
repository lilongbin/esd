/*
 * 引用的定义
 */
#include <iostream>
using namespace std;
int main() {
	// int &ref; //错误,定义引用必须初始化;
	int i = 9527;
	int &refi = i;		//refi是i的引用/别名;
	//再定义一个i变量的引用
	int &refi2 = i;
	// int &refi2 = refi; //也可以
	cout << i << " " << refi << " " << refi2 << endl;
	cout << "修改一个值" << endl;
	refi = 12345;
	cout << i << " " << refi << " " << refi2 << endl;

	//验证引用的终生服务理念
	int j = 10086;		//读'钩'
	refi = j;		//把变量j的值赋值给引用refi,而不是引用j;这就是终生服务;
	//理解引用的本质就是为变量的别名,在使用时就是那个变量,
	//本语句就跟i = j;赋值语句是一回事;
	cout << "-----------" << endl;
	cout << refi << endl;	//10086
	j = 100;
	cout << j << endl;	//100
	cout << refi << endl;	//10086
}
