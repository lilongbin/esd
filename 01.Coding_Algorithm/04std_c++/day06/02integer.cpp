#include <iostream>
using namespace std;
class Integer{
	int data;
	public:
	Integer(int data = 0):data(data){}
	// -(负号)
	const Integer operator-(){
		return Integer(-data);//返回一个临时(创建的对象)
	}
	/*const Integer& operator-(){//负号，单目运算
		data = 0 - data;
		return *this;//引用可以减少数据复制,但会改变原数据
	}*/
	const Integer operator-(const Integer& i)const{//减号，双目运算
		//在声明和实现之间加const，否则返回值不能被const对象调用
		//第一个const防止返回值做左值;
		//第二个const防止修改、允许接收const对象；
		//第三个const把函数修饰成const函数，const对象才能调用；
		return Integer(data-i.data);
	}
	// !取反操作符，不是0变成0，是0变成1；
	const Integer operator!()const{
		return Integer(!data);
	}
	friend ostream& operator<<(ostream& os,const Integer& var_i);
	friend istream& operator>>(istream& is,Integer& var_i);
};
ostream& operator<<(ostream& os,const Integer& var_i){
	os << var_i.data;//引用;os就是cout;cout就是os;
	return os;
}
istream& operator>>(istream& is,Integer& var_i){
	return is >> var_i.data;
}
int main(){
	Integer var_a(123);
	Integer var_b(321);
	cout << -var_a << endl;
	cout << (var_a - var_b) << endl;
	cout << ((-var_a) - var_b) << endl;//-var_a是const对象
	cout << !var_b << endl;
	cout << !!var_b << endl;
}
