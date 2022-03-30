#include <iostream>
using namespace std;
class Animal{
	public:
	virtual void show(){
		cout << "this is Animal show()" << endl;
	}
	virtual void run(){
		cout << "this is Animal run()" << endl;
	}
	void fun(){
		cout << "Animal fun" << endl;
	}
};
class Dog:public Animal{
	public:
	void show(){//函数重写
		cout << "this is Dog show()" << endl;
	}
	void run(){//函数重写
		cout << "this is Dog run()" << endl;
	}
	void fun(){//名字隐藏
		cout << "Dog fun" << endl;
	}
};
class Fish:public Animal{
	public:
	void show(){
		cout << "this is Fish show()" << endl;
	}
	void run(){
		cout << "this is fish run()" << endl;
	}
};
void showAnimal(Animal* animal){
	animal->show();
	animal->run();
}
Animal* getAnimal(string type){
	/*对象制造工厂*/
}
int main(){
	Dog dog;
	Fish fish;
	showAnimal(&dog);
	showAnimal(&fish);
}
