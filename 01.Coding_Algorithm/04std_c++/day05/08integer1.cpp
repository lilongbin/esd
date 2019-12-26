#include <iostream>
using namespace std;
class Integer{
	int data;
	public:
	Integer(int data = 0):data(data){}
	void show(){
		cout << "data = " << data << endl;
	}
	
	// i1.operator+(i2)
	/*const Integer operator+(const Integer& i2){
		cout << "mem operator+" << endl;
		return Integer(this->data+i2.data);//this->在此可以省略
	}*/
	//把全局函数请到类内做朋友，但不是成员;
	//以友元的身份声明;//把实现放进来也可以,但是点不地道吧
	private://对下面的友元函数没用，因为下面的友元函数不是类内的成员
	//声明operator是Integer类型的友元
	friend const Integer operator+(const Integer& i1,const Integer& i2);
	friend const Integer operator*(const Integer& i1,const Integer& i2);
	friend const bool operator==(const Integer& i1,const Integer& i2);
	
};
const Integer operator+(const Integer& i1,const Integer& i2){
		cout << "调用operator+" << endl;//
		return Integer(i1.data+i2.data);
}
const Integer operator*(const Integer& i1,const Integer& i2){
		cout << "调用operator*" << endl;//
		return Integer(i1.data*i2.data);
}
const bool operator==(const Integer& i1,const Integer& i2){
		cout << "调用operator==" << endl;//
		return i1.data==i2.data;
}

int main(){
	Integer a(10);
	Integer b(10);
	Integer c = a + b;
	c.show();
	c = a * b;
	c.show();
	cout << (a==b) << endl;
}
