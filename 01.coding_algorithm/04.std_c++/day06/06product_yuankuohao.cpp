#include <iostream>
using namespace std;
class Product{
	int count;
	double price;
	public:
	Product(int count = 0,double price = 0):count(count),price(price){}
	//重载()运算符，完成函数对象的功能
	double operator()(int c,double p){
		return c * p;//返回总价
	}
	//重载()运算符，完成类型转换的功能
	//int operator()(){}编译器不能与上面的功能区分
	operator int (){//int放operator后面，参数不需要
		return count;
	}
	operator double(){
		return price;
	}
};
int main(){
	Product apple;
	//把对象当函数来用
	cout << apple(4,4888.5) << endl;//把()当成函数使用
	cout << apple(4,2188.0) << endl;
	Product product(10,1.85);
	cout << (int)product << endl;//显示10
	cout << (double)product << endl;//显示1.85
}
