#include <iostream>
using namespace std;
struct Fraction{
	int x;
	int y;
	public:
	Fraction(int x = 0,int y = 1):x(x),y(y){}
	void show(){
		cout << x << "/" << y << endl;
	}
	//成员形式的+号运算符
	const Fraction operator+(const Fraction& f2){
		cout << "mem operator+" << endl;
		return Fraction(x*f2.y+y*f2.x,y*f2.y);	
	}
};
//设计一个函数，负责两个分数相加
const Fraction operator+(const Fraction& f1,const Fraction& f2){
	cout << "全局 operator+" << endl;
	return Fraction(f1.x*f2.y+f2.x*f1.y , f1.y*f2.y);
}
int main(){
	Fraction fa(1,2);
	fa.show();
	Fraction fb(1,3);
	//调用全局函数让两个分数相加
	//Fraction fc = add(fa,fb);//拷贝
	Fraction fc = fa + fb;
	fc.show();
}
