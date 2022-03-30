#include <iostream>
using namespace std;
//前置声明
//Animal声明和全局函数的声明
class Animal;//声明的时候不用{}，不然就是实现
void showAnimal(Animal *a);//声明里面比较经典的套路
class Animal{
	string name;
	int age;
	public:
	Animal(string name = "",int age = 0){
		//name = name;
		this->name = name;//指定前一个是成员变量，后一个是参数；
		this->age = age;
	}
	void modname(const string& name){
		this->name = name;
	}
	string& getname(){//不加const别人可以通过该函数该改name，加const不可以改那name
		return name;
	}
	void show(){
		showAnimal(this);//需要声明
		innershow(this);
		cout << name << "," << age << endl;
	}
	Animal *getself1(){//返回指针
		age++;
		return this;
	}
	Animal getself2(){//返回对象的值
		age++;
		return *this;
	}
	Animal& getself3(){//返回引用
		age++;
		return *this;
	}
	void innershow(Animal *a){
		cout << a->name << endl;
	}
};
void showAnimal(Animal *a){
	cout << a->getname() << endl;
}
int main(){
	Animal animal1("test",1);
	animal1.show();
	animal1.modname("test2");
	animal1.show();
	//
	Animal animal("test1",1);
	cout << "showAnimal(&animal) ";
	showAnimal(&animal);//this的第三种用途this做函数参数;&animal就是this
	animal.show();//test1,1
	//animal.getself2().getself2();//值传递，最后一个getself2返回的是一个临时对象
	//animal.show();//test1,2
	animal.getself3().getself3();//返回的不是临时对象
	animal.show();//test1,3
	animal.getself1()->getself1();//返回的不是临时对象
	animal.show();//test1,5
}

