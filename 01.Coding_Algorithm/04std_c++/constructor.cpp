/*****************************************
 * Copyright (C) 2018 * Ltd. All rights reserved.
 * 
 * File name   : constructor.cpp
 * Author      : longbin
 * Created date: 2018-08-22 14:49:49
 * Description : 
 *
 *******************************************/

#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

class Basic{
	public:
		Basic()
		{
			cout << "Basic()" << endl;
		}
		~Basic()
		{
			cout << "~Basic" << endl;
		}
};

class SubClass: public Basic {
	public:
		int i;
		SubClass():i(geti())
		{
			cout << " SubClass()" << endl;
		}
		int geti() {
			cout << " geti() -- init param list" << endl;
			return 1;
		}
		~SubClass()
		{
			cout << " ~SubClass()" << endl;
		}
};

class Implement{
	public:
		int element;
		Implement(int ele=0)
		{
			cout << "  Implement() begin" << endl;
			/* 指针类型声明,不会生成对象也不会调用构造 */
			cout << "  *psc1 begin" << endl;
			SubClass *psc1; // just create a pointer type variable
			cout << "  *psc1 end" << endl;

			cout << "  psc2 begin" << endl;
			/* 首先调用父类构造即Basic() */
			/* 然后执行初始化参数列表即geti() */
			/* 然后调用自己的无参构造函数即SubClass() */
			SubClass psc2;  // create a instance of SubClass
			cout << "  psc2 end" << endl;
			element = ele;
			cout << "  Implement() end" << endl;
		}
		~Implement()
		{
			cout << " ~Implement(): " << element << endl;
		}
};

void func(Implement im)
{
	im.element = 1;
	cout << "func(Implement im)" << endl;
}

int main() {
	Implement(5); /* 临时对象在当前语句结束时就释放 */
	cout << "##################" << endl;
/*
 *   Implement() begin
 *   *psc1 begin
 *   *psc1 end
 *   psc2 begin
 * Basic()
 *  geti() -- init param list
 *  SubClass()
 *   psc2 end
 *   Implement() end
 *  ~SubClass()
 * ~Basic
 *  ~Implement(): 5
 * ##################
 */
	Implement imp(0); /* 局部变量函数结束时释放 */
	cout << "##################" << endl;
/*
 *   Implement() begin
 *   *psc1 begin
 *   *psc1 end
 *   psc2 begin
 * Basic()
 *  geti() -- init param list
 *  SubClass()
 *   psc2 end
 *   Implement() end
 *  ~SubClass()
 * ~Basic
 * ##################
 */
	func(imp);
	cout << "main return 0" << endl;
	return 0;
}

/*
 * func(Implement im)
 *  ~Implement(): 1
 * main return 0
 *  ~Implement(): 0
 */

