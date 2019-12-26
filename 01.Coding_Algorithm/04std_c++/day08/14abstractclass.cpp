#include <iostream>
using namespace std;
class Animal{
	public:
	Animal(){
		cout << "Animal()" << endl;
	}
	void show(){
		cout << "Animal show()" << endl;
	}
	/*纯虚函数*/
	virtual void run()=0;//纯虚函数
};
class Dog:public Animal{
	public:
	void run(){//实现了纯虚函数，当前类不再是抽象类
		//如果不实现纯虚函数，则当前类也是抽象类	
	}
};
int main(){
	//Animal animal;//抽象类不能实例化
	Dog dog;
}
