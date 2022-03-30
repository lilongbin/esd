#include <iostream>
using namespace std;
class A{
	int *data;
	int mlen;
	public:
	A(int len = 1){
		mlen = len;//记录申请的内存大小
		//在创建对象时中申请内存
		data = new int[len];
		cout << "内存已申请" << endl;
	}
	~A(){//在对象销毁时释放内存
		delete[] data;
		cout << "内存已释放" << endl;
	}
	//写一个拷贝构造函数，完成指针成员的深拷贝
	A(const A& a){
		//给拷贝的对象申请内存
		mlen = a.mlen;
		cout << "在拷贝函数中申请内存" << endl;
		data = new int[a.mlen];
		//把a对象中的data数据拷贝过来
		for(int i = 0;i <= mlen - 1; i++){
			data[i] = a.data[i];
		}
	}//深拷贝就是处理对象的共享内存问题
};
void foo(){
	A a(4);
	//用a对象创建b对象
	A b = a;//拷贝//没有定义深拷贝函数，a和b对共享同一个内存空间，多次释放会出错
}
int main(){
	foo();
	while(1);

}

