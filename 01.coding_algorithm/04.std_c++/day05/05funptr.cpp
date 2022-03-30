/*成员函数指针*/
#include <iostream>
using namespace std;
struct Date{
	//注意访问权限
	int year;
	int month;
	int day;
	//提供构造函数
	Date(int year = 0,int month = 0,int day = 0):year(year),month(month),day(day){}
	void showyear(){
		cout << year << "年" << endl;
	}
	void showmonth(){
		cout << month << "月"<<endl;
	}
};
int main(){
	void (Date::*pfun)();//定义一个成员函数指针
	pfun = &Date::showyear;
	Date date(2020,10,1);//创建对象，通过对象调用成员函数
	(date.*pfun)();//调用
	pfun = &Date::showmonth;
	(date.*pfun)();
	Date *date2 = new Date();
	(date2->*pfun)();
}
