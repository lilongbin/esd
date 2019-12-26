#include <iostream>
#include "mytime.h"
using namespace std;
	/*int hour;
	int min;
	int sec;*/
	/*static*/ int Mytime::g_var = 0;
	Mytime::Mytime():hour(0),min(0){
		sec = 0;
	}
	Mytime::Mytime(int hour,int min,int sec):hour(hour),min(min){
		this->sec = sec;
	}
	Mytime::~Mytime(){
		//没有要回收的堆内存
		cout << "析构~Mytime()" << endl;
	}
	Mytime::Mytime(const Mytime& mt){
		cout << "拷贝Mytime(const Mytime&)" << endl;//替换掉默认的拷贝构造
	}
	void Mytime::show(){
		cout << hour << ":" << min << ":" << sec << endl;
	}
	void Mytime::dida(){
		
	}
	void Mytime::run(){}

