#include <iostream>
#include <cstring>
using namespace std;
/*多态的底层实现原理*/
class Animal{
	public:
	virtual void fun(){
		cout << "Animal fun 很抽象" << endl;
	}
	virtual void show(){
		cout << "Animal show 很抽象" << endl;
	}
};//一个类型对应一张虚函数表，虚函数表中存放虚函数的地址
class Dog:public Animal{
	public:
	void fun(){
		cout << "Dog fun 看家" << endl;
	}
	void show(){
		cout << "Dog show 汪汪叫" << endl;
	}
};
class Cat:public Animal{
	public:
	void fun(){
		cout << "Cat fun 抓老鼠" << endl;
	}
	void show(){
		cout << "Cat show 喵喵" << endl;
	}
};
int main(){
	/*每个类型都有自己的虚函数表，同类型的对象共享一张虚表*/
	Animal animal;
	int *ptr = reinterpret_cast<int*>(&animal);//类型中存放着虚函数表的地址
	cout << hex << *ptr << endl;
	Dog doga;
	ptr = reinterpret_cast<int*>(&doga);
	cout << hex << *ptr << endl;
	Dog dogb;
	ptr = reinterpret_cast<int*>(&dogb);
	cout << hex << *ptr << endl;
	Cat cat;
	ptr = reinterpret_cast<int*>(&cat);
	cout << hex << *ptr << endl;
	/*创建三个对象，满足多态的条件*/
	Animal *dogOne = new Dog();
	Animal *dogTwo = new Dog();
	Animal *cata = new Cat();
	dogOne->fun();
	dogTwo->fun();
	/*把cata对应内存的前四个字节覆盖掉dogOne对应的内存的前4个字节(虚表地址)*/
	cout << "------" << endl;
	memcpy(dogOne,cata,4);//需要添加string.h的头文件
	dogOne->fun();//狗拿耗子
	dogTwo->fun();

}
