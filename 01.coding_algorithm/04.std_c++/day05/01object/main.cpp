#include <iostream>
#include "mytime.h"
using namespace std;
int main(){
	Mytime mt1;
	Mytime mt2(12);//有实参，编译器就不认为是声明函数
	//Mytime mt3();//典型错误，编译器认为是声明函数
	Mytime();//创建匿名对象；
	Mytime(1,2,3);//创建匿名对象；

	Mytime *pmt1 = new Mytime;
	Mytime *pmt2 = new Mytime();
	Mytime *pmt3 = new Mytime(1,2,3);
	Mytime *parr = new Mytime[5];
	cout << "delete[] parr" << endl;
	delete[] parr;
	const Mytime mt8;//定义了构造函数可以不手动初始化
	cout << Mytime::g_var << endl;

}
