#include <iostream>
using namespace std;
class Integer{
	int data;
	public:
	Integer(int data = 0):data(data){}
	// i1.operator+(i2)
	const Integer operator+(const Integer& i2){
		return Integer(data+i2.data);//返回一个新构造的匿名对象
	}
	const Integer& operator-=(const Integer& b){
		data -= b.data;
		return *this;
		//return Integer(data);//错误,新构造了一个匿名的对象
	}
	const Integer& operator*=(const Integer& b){//返回值与参数类型不同，不可连续运算
		data *= b.data;
		return *this;
	}
	friend ostream& operator<<(ostream& os,const Integer& var_i);
	friend istream& operator>>(istream& is,Integer& var_i);
	//重载运算符 += // a.operator+= (b)
	friend const Integer& operator+=(Integer& a,const Integer& b);
};
ostream& operator<<(ostream& os,const Integer& var_i){
	os << var_i.data;//引用;os就是cout;cout就是os;
	return os;
}
istream& operator>>(istream& is,Integer& var_i){
	return is >> var_i.data;
}
const Integer& operator+=(Integer& a,const Integer& b){
	a.data += b.data;
	return a;
}
int main(){
	Integer var_a(123);
	Integer var_b(321);
	//cout << var_a + var_b << endl;
	cout << "请输入两个整数" << endl;
	cin >> var_a >> var_b ;
	cout << var_a + var_b << endl;
	cout << (var_a += var_b) << endl;
	cout << (var_a -= var_b) << endl;
	cout << (var_a *= var_b) << endl;

}
