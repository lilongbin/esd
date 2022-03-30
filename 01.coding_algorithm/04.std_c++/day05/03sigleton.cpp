#include <iostream>
using namespace std;
class Singleton{
	private:
	//私有化构造/拷贝构造，防止类外创建
	Singleton(){}//构造
	Singleton(const Singleton& s){}//构造
	//提供静态成员，类外初始化
	static Singleton sig;//静态类型的成员(类型)//加static是在类外初始化，避免递归创建类
	public:
	//提供公开的得到对象的接口
	//使用类型就可以得到对象
	static Singleton& getInstance(){//不能是普通成员函数
		//得到实例
		return sig;
	}
};
Singleton Singleton::sig;//静态成员初始化
int main(){
	Singleton& sig1 = Singleton::getInstance();
	Singleton& sig2 = Singleton::getInstance();
	cout << &sig1 << endl;
	cout << &sig2 << endl;
}
