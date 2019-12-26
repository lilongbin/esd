/*
 * new/delete练习
 */
#include <iostream>
using namespace std;
int main() {
	int var_i;
	int *pi = new int;	//不保证是0;
	*pi = 10;
	int *pi2 = new int (10);	//传入初始值,等价于以上2步;
	cout << *pi2 << endl; //10
	//cout << pi2 << endl; //0x9b28018
	delete pi;
	delete pi2;

	//使用new[]申请5个int的内存,然后赋值,分别输出
	int *parr = new int[5];
	for (int i = 0; i < 5; i++) {
		//parr[i] = i+1;//经典用法,正确,赞!
		// *parr++ = i+1;//典型的错误,动了头指针
		// 先执行p++,但是p的值会在语句结束时才变化;动了指针
		*(parr + i) = i + 1;	//没有动指针;正确用法,赞!
	}
	for (int i = 0; i < 5; i++) {
		cout << parr[i] << " ";
	}
	cout << endl;
	delete[] parr;		//使用delete[]释放掉new[]申请的内存;
	parr = NULL;		//把悬空指针设为空,好习惯;

	union {
		char data[20];	//栈区
		int m;
	};
	cout << "----------------" << endl;
	int *parr2 = new (data) int[5];	//把内存指向data执行的内存
	cout << "data字符串: " << data << endl; //乱码
	cout << "parr2: " << parr2 << endl;
	cout << "(void*)data: " << (void *)data << endl;
	cout << "&m: " << &m << endl;
}
