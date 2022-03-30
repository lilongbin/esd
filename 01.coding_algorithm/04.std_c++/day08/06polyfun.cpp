#include <iostream>
using namespace std;
class Animal{
	public:
	virtual void show(){
		cout << "this is Animal show()" << endl;
	}
	void run(){
		cout << "this is Animal run()" << endl;
	}
};
class Dog:public Animal{
	public:
	//函数重写，必须提供相同的函数名和参数列表；返回值必须相同；
	void show(){//其实是个虚函数，不需要加virtual，一虚则全虚
		cout << "this is Dog show()" << endl;
	}
	void run(){//run()函数不是虚函数，但与父类同名，所以这是名字隐藏
		cout << "this is Dog run()" << endl;
	}
};
int main(){
	Animal *pa = new Animal();//括号可以不加；
	/*Animal*/
	pa->show();
	pa->run();
	pa = new Dog();
	/*virtual show() Dog*/
	pa->show();//虚函数
	/*Animal*/
	pa->run();//普通函数
}
