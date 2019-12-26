/*
 * 类与对象的模拟
 */
#include <iostream>
#include <string>
using namespace std;
struct Dog {
	//特征(属性)
	string dogno; //只保存一个指向字符串首地址的指针;
	string name; //大小为4字节,64位为8字节;
	int weight;
	int age;
	//行为(方法)
	void play() {
		cout << name << "逗你开心" << endl;
	}
   	void show() {
		cout << name << ":" << age << "月" << weight << "Kg" << endl;
	}
	void fun() {
		cout << name << "在看家" << endl;
	}
};
int main() {
	Dog dog1; //创建结构体变量;
	dog1.name = "wangcai";
	dog1.age = 2;
	dog1.weight = 10;
	dog1.dogno = "bj001";
	cout << sizeof(Dog) << endl;	//16
	cout << sizeof(dog1) << endl;	//16
	dog1.play();
	dog1.show();
	dog1.fun();
}
