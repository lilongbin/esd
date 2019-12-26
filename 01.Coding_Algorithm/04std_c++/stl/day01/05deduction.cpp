#include <iostream>
#include <typeinfo>
using namespace std;
template<typename T>
void foo(T const& x,T const& y){
	cout << typeid (x).name() << ' ' << typeid(y).name() << endl;
}
template<typename R,typename T>
R bar(T const& t){
	R r;
	cout << typeid(t).name() << ' ' << typeid(r).name() << endl;
	return r;
}
int main(void){
	//通过隐式推断去实例化函数模板
	int a,b;
	foo(a,b);//编译器推断出T是int
	double c,d;
	foo(c,d);
	char e[256],f[256];
	foo(e,f);
	string g,h;
	foo(g,h);
	//隐式推断不允许隐式类型转换
	//foo(a,c);//error
	//但是可以显式类型转换
	foo(a,static_cast<int>(c));
	foo(static_cast<double>(a),c);
	//或者显式的实例化函数模板
	foo<int>(a,c);//类型不用再猜了，这样就可以隐式类型转换了
	foo<double>(a,c);//
	int i;
	double j;
	//返回类型不能隐式推断
	i = bar<int,double>(j);
	i = bar<int>(j);
	return 0;
}
