/*
 * static中构造this访问普通成员
 */
#include <iostream>
using namespace std;
class A{
	public:
	/*
	 * static void show(){
	 *     play();//不可以直接访问
	 * }
	 */
	/* 线程封装的雏形 */
	static void show(A *mythis){
		mythis->play();
	}
	void play(){
		cout << "this is play()" << endl;
	}
};
int main(){
	A a;
	//A::show();//错误：没有对象无法调用成员函数‘void A::play()’
	A::show(&a);
}
