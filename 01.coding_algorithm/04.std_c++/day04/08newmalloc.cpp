#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
class Date{
	public:
	Date(){
		cout << "构造函数Date()" << endl;
	}
	~Date(){
		cout << "析构函数~Date()" << endl;
	}

};
class Person{
	string name;
	int age;
	Date birth;//Date类型的成员变量
	public:
	Person(){
		cout << "构造函数Person()" << endl;
	}
	~Person(){
		cout << "析构函数~Person()" << endl;
	}
};
int main(){
	Person *p = static_cast<Person*>(malloc(sizeof(Person)));
	free(p);//不会调用析构函数；
	Person *pnew = new Person();//new可以自动调用构造函数，自动进行类型转换，自动构建成员
	delete pnew;//会自动调用析构函数；
	//注意调用析构函数时的顺序与创建构造函数时相反
}
