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
};
//设计一个函数，负责两个分数相加
/*const Fraction add(const Fraction& f1,const Fraction& f2){
	return Fraction(f1.x*f2.y+f2.x*f1.y , f1.y*f2.y);
}*/
const Fraction operator+(const Fraction& f1,const Fraction& f2){
	cout << "全局operator+" << endl;
	return Fraction(f1.x*f2.y+f2.x*f1.y , f1.y*f2.y);
}//将函数名add改为operator+即可实现运算符重载；
const Fraction operator-(const Fraction& f1,const Fraction& f2){
	cout << "全局operator-" << endl;
	return Fraction(f1.x*f2.y-f2.x*f1.y , f1.y*f2.y);
}//将函数名add改为operator+即可实现运算符重载；
int main(){
	Fraction fa(1,2);
	fa.show();
	Fraction fb(1,3);
	//调用全局函数让两个分数相加
	//Fraction fc = add(fa,fb);//拷贝
	Fraction fc = fa + fb;
	fc.show();
	fc = fa - fb;
	fc.show();
}
