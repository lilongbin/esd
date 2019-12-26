#include <iostream>
using namespace std;
class Animal{
	public:
	string name;
	int age;
	void show(){
		cout << "this is Animal.show()" << endl;
	}
};
//另一种代码复用和功能扩展的方式
//组合技术
//这种技术非常优秀，但推广晚于继承10年，继承已占相当地位
//有大量的代码是用组合技术实现的；耦合度低
//软件设计的目标：高内聚，低耦合；
class Dog{
	private:
	Animal animal;
	public:
	void show(){
		animal.show();
	}
	//扩展新功能
	void fun(){
		cout << "看家" << endl;
	}
};
int main(){
	Dog dog;
	//dog.animal.name = "wangcai";
	//dog.animal.show();
	dog.show();
	dog.fun();
}
