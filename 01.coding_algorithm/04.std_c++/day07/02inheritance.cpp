#include <iostream>
using namespace std;
class Animal{
	public:
	string name;
	int age;
	void show(){
		cout << "this is show()Animal" << endl;
	}
};
class Dog:public Animal{
	public:
	//增加新功能
	void fun(){
		cout << "摇尾巴" << endl;
	}
};
int main(){
	Animal animal;
	animal.name = "animal";
	cout << animal.name << endl;
	animal.show();
	Dog dog;
	dog.name = "dog";
	dog.age = 2;
	cout << dog.name << ":" << dog.age << endl;
	dog.show();
	dog.fun();
}
