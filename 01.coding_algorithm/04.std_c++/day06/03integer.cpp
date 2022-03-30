#include <iostream>
using namespace std;
class Integer{
	int data;
	public:
	Integer(int data = 0):data(data){}
	const Integer operator-(const Integer& i)const{//减号，双目运算
		//在声明和实现之间加const，否则返回值不能被const对象调用
		//第一个const防止返回值做左值;
		//第二个const防止修改、允许接收const对象；
		//第三个const把函数修饰成const函数，const对象才能调用；
		return Integer(data-i.data);
	}
	// ++  默认前++  ++var_a
	Integer& operator++(){//如果不希望别人连续使用前++，就加const
		++data;
		return *this;
	}
	//后++,后++的结果是一个临时的结果
	Integer operator++(int){//哑元
		/*data++;
		return Integer(data-1);*/
		return Integer(data++);
	}
	//实现前--
	Integer& operator--(){
		data--;
		return *this;
	}
	//实现后--
	Integer operator--(int){
		return Integer(data--);
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
	Integer var_b(1);
	cout <<"++var_a : "<< ++var_a << endl;
	cout <<"++var_a : "<< ++var_a << endl;
	cout <<"var_b++ : "<< var_b++ << endl;//1
	cout <<"var_b   : "<< var_b << endl;//2
	cout << var_b.operator++() << endl;//3//前++
	//cout << var_b.operator++(int) << endl;//错误
	cout << var_b.operator++(0) << endl;//后++
	cout <<"var_b    : "<< var_b << endl;
	cout <<"--var_b  : "<< --var_b << endl;
	cout <<"var_b--  : "<< var_b-- << endl;
	cout <<"var_b    : "<< var_b << endl;
}
