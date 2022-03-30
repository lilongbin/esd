/*
 * const_cast类型转换
 */
#include <iostream>
using namespace std;
int main() {
	const int data = 200;
	//int *pdata = &data;//从类型‘const int*’到类型‘int*’的转换无效
	int *pdata = const_cast <int *>(&data);
	//去掉const修饰
	*pdata = 9527;
	cout << data << endl;	//200
   	//在C++中有const修饰的data,后面用到data的地方直接使用初始值;
	cout << *pdata << endl;	//9527

	volatile const int data1 = 200; //加volatile会在需要时从内存中获取
	int *pdata1 = const_cast <int *>(&data1);
	*pdata1 = 9527;
	cout << data1 << endl;	//9527
	cout << *pdata1 << endl;	//9527
	//reinterpret_cast<类型>(变量)与c语言的强制类型转换一样
}
