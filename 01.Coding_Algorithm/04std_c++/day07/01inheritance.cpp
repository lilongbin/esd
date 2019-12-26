#include <iostream>
using namespace std;
class Animal{
	public:
	string name;
	int age;
	void show(){
		cout << "this is show()" << endl;
	}
};
//Cat类继承自Animal类
class Cat:public Animal{
	public:
	//增加新功能
	void fun(){
		cout << "抓老鼠" << endl;
	}
};
int main(){
	Animal animal;
	animal.name = "test";
	cout << animal.name << endl;
	animal.show();
	cout << sizeof(Cat) << endl;//8
	Cat cat;
	//子类可以复用父类的数据和代码；
	cat.name = "tomcat";
	cat.age = 2;
	cout << cat.name <<":" << cat.age << endl;
	cat.show();
	cat.fun();
}
