#include <iostream>
using namespace std;
class A{
	public:
	A(){
		cout << "A()" << endl;
	}
	~A(){
		cout << "~A()" << endl;
	}
	void showA(){
		cout << "showA()"<< endl;
	}
};
//智能指针
//调用自己的对象用.
//调用所管理的对象用->
class myauto_ptr{
	A *data;
	public:
	myauto_ptr(A *data = NULL):data(data){}
	~myauto_ptr(){
		if(data){
			delete data;
			data = NULL;
		}
	}
	void showself(){
		cout << "show auto ptr self"<< endl;
	}
	//const A* & operator->(){//表示引用const类型
	//A* const & operator->(){//注意const位置
	A* operator->(){//重载->
		return data;//取得/返回所管理的对象的地址
	}
	A& operator*(){
		return *data;//取得/返回所管理的对象
	}
};
void foo(){
	A *pa = new A();
	myauto_ptr var_a(pa);//var_a的生命周期是函数的作用期，结束后自动析构
	var_a.showself();
	var_a->showA();//var_a作为一个智能指针对象//需要重载->
	//var_a.operator->()->showA();//上一句的原型，自动优化为上一句
	(*var_a).showA();//var_a作为一个智能指针对象
	(var_a.operator*()).showA();//原型
}
int main(){
	foo();
}

