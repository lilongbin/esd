#include <iostream>
using namespace std;
class Dog{
	public:
	int age;
	static int dogcount;
	static void show(){
		//static中不可以访问非static中，因为static的生成时间早
		cout << /*age << */ dogcount <<"show()" << endl;
	}
	void dogshow(){
		//非static类型可以访问static类型，static类型生成时间比较早；
		show();
	}
};
int Dog::dogcount ;//类外初始化，全局自动初始化为0；
int main(){
	Dog::show();
	cout << Dog::dogcount << endl;
	Dog dog1;
	dog1.dogcount = 1;
	Dog::show();
	Dog dog2;
	dog2.dogcount = 2;
	dog1.show();
}
