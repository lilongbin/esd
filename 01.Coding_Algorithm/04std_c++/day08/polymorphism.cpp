/*****************************************
 * Copyright (C) 2018 * Ltd. All rights reserved.
 * 
 * File name   : polymorphism.cpp
 * Author      : longbin
 * Created date: 2018-08-06 10:49:11
 * Description : 
 *
 *******************************************/

#include <iostream>
using namespace std;

class BasicClass {
	public:
		BasicClass() { cout << "Basic Class init" <<endl; }
		virtual void work() { cout << "Basic Class working" <<endl; }
		virtual ~BasicClass() { cout << "Basic Class deinit" <<endl; }
};

class SubClass: public BasicClass {
	public:
		SubClass() { cout << "\tSub Class init" <<endl; }
		virtual void work() { cout << "\tSub Class working" <<endl; }
		virtual ~SubClass() { cout << "\tSub Class deinit" <<endl; }
};

class SubSubClass: public SubClass {
	public:
		SubSubClass() { cout << "\t\tSub-Sub Class init" <<endl; }
		virtual void work() { cout << "\t\tSub-Sub Class working" <<endl; }
		~SubSubClass() { cout << "\t\tSub-Sub Class deinit" <<endl; }
};

/* 当调用how2Work()函数时表现多态性，根据入参不同调用不同的方法 */
/* 如果父类没有声明为virtual即没有实现多态，传入子类对象时就不会调用子类的方法 */
void how2Work(BasicClass *base)
{
	base->work();
}

int main(void)
{
#ifdef CASE1
	BasicClass *person = NULL;
	person = new BasicClass();
	person->work();
	delete person;
	person = NULL;

	person = new SubClass();
	person->work();
	delete person;
	person = NULL;

	person = new SubSubClass();
	person->work();
	delete person;
	person = NULL;
	/* 虽然都是person->work()结果却有不同的表现 */
#else
	/* 多态的使用最多的是下面这种方式 */
	BasicClass bc;
	SubClass sc;
	SubSubClass ssc;

	how2Work(&bc);
	how2Work(&sc);
	how2Work(&ssc);
#endif

	return 0;
}

