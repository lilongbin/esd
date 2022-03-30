/*
 * struct.cpp
 */
#include <iostream>
using namespace std;
struct Emp {
};
// 定义一个日期类型的结构体:年月日,在结构体中提供显示日期的函数
struct Date {
	//数据
	int year;
	int month;
	int day;
	//代码在代码区
	void showDate() {	//在同一个作用域,可以省略参数的传递;
		cout << year << "年" << month << "月" << day << "日" << endl;
	}
   	//结构体和函数形式上是一体的,存储在不同的区;c++编译器会自动处理
};
void showDate(Date * date) {
	cout << date->year << "年"
	    << date->month << "月" << date->day << "日" << endl;
}
int main() {
	cout << "空结构体大小:" << sizeof(Emp) << endl;
	Emp emp;		//c++中可以省略struct关键字
	cout << "空结构体对象大小:" << sizeof(emp) << endl;
	/*构建日期对象,表现日期对象 */
	Date date = { 2015, 07, 12 };
	showDate(&date);	//传参的方式;
	date.year = 2015;	//访问成员变量
	date.showDate();	//调用成员函数;
}
