#include <iostream>
using namespace std;
class Integer{
	int data;
	public:
	Integer(int data = 0):data(data){}
	void show(){
		cout << "data = " << data << endl;
	}
	bool operator==(const Integer& i2){
		cout << "mem operator" << endl;
		return data==i2.data;
	}	
	private://对下面的友元函数没用，因为下面的友元函数不是类内的成员
	friend const Integer operator+(const Integer& i1,const Integer& i2);
	friend const Integer operator*(const Integer& i1,const Integer& i2);
	//friend void operator<<(ostream& os,Integer i2);
	friend ostream& operator<<(ostream& os,const Integer& i2);
	
};
const Integer operator+(const Integer& i1,const Integer& i2){
	cout << "调用operator+" << endl;//
	return Integer(i1.data+i2.data);
}
const Integer operator*(const Integer& i1,const Integer& i2){
	cout << "调用operator*" << endl;//
	return Integer(i1.data*i2.data);
}
//全局形式的输出运算符
/*void operator<<(ostream& os,Integer i2){
	cout << i2.data ;
}*/
ostream& operator<<(ostream& os,const Integer& i2){
	/* os << i2.data ;
	return os; */
	//os即cout的别名
	return os << i2.data;//简化写法
}

int main(){
	Integer a(10);
	Integer b(10);
	Integer c = a + b;
	c.show();
	c = a * b;
	c.show();
	cout << (a==b) << endl;
	cout << c << endl;
	cout << a*b << endl;
}
