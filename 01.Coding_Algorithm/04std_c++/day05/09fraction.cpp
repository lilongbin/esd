#include <iostream>
using namespace std;
struct Fraction{
	int x;
	int y;
	public:
	Fraction(int x = 0,int y = 1):x(x),y(y){}
};
//设计一个分数的输出
ostream& operator<<(ostream& os,const Fraction& f){
	return os << f.x << "/" << f.y;
}
//设计一个分数的输入函数iostream& cin
/*istream& operator>>(istream& is,Fraction f){//要用引用类型，且不能加const
	return is >> f.x >> f.y;
}*/
istream& operator>>(istream& is,Fraction& f){
	return is >> f.x >> f.y;
}


int main(){
	Fraction f(1,3);
	cout << "请输入分子 分母" << endl;
	cin >> f;
	cout << f << endl;
}
