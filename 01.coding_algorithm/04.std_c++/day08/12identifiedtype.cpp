#include <iostream>
#include <typeinfo>
using namespace std;
class Animal{
	public:
	virtual void run(){
		cout << "animal run" << endl;
	}
};
class Dog:public Animal{
	public:
	void run(){
		cout << "dog run " << endl;
	}
	void dogfun(){
		cout << "dog special function" <<endl;
	}
};
class Cat:public Animal{
	public:
	void run(){
		cout << "cat jump" << endl;
	}
	void catfun(){
		cout << "cat special function" << endl;
	}
};
class Fish:public Animal{
	public:
	void run(){
		cout << "fish is swimming" << endl;
	}
};
void showAnimal(Animal *animal){
	//体现多态
	animal->run();
	//把具体的类型识别出来
	/*if(dynamic_cast<Dog*>(animal)){
		((Dog*)(animal))->dogfun();
	}
	else if(dynamic_cast<Cat*>(animal)){
		((Cat*)(animal))->catfun();
	}*/
	if(typeid(*animal) == typeid(Dog)){
		//#include <typeinfo>
		((Dog*)(animal))->dogfun();
	}
	else if(typeid(*animal) == typeid(Cat)){
		((Cat*)(animal))->catfun();
	}
}
int main(){
	//Animal *pa = new Dog();
	Animal *pa = new Cat();//转换失败，不是Dog类型
	/*如果转换成功pd为非空，如果转换失败pd为空*/
	Dog *pd = dynamic_cast<Dog*>(pa);
	cout << "pd = "<< pd << endl;
	showAnimal(pa);
	pa = new Dog();
	showAnimal(pa);
	pa = new Fish();
	showAnimal(pa);
}
