#include <iostream>
using namespace std;
//通用模板
template<typename T1,typename T2>
class Dual{
	public:
	static void printType(void){
		cout << "Dual<T1,T2>"<<endl;
	}
};
//针对第2个参数取short的局部特化
template<typename T>
class Dual<T,short>{//类型局部特化
	public:
	static void printType(void){
		cout << "Dual<T,short>" <<endl;
	}
};
//针对两个类型参数取相同类型的局部特化
template<typename T>
class Dual<T,T>{
	public:
	static void printType(void){
		cout << "Dual<T,T>" << endl;
	}
};
//针对两个类型参数取某种类型的指针的局部特化
template<typename T1,typename T2>
class Dual<T1*,T2*>{
	public:
	static void printType(void){
		cout << "Dual<T1*,T2*>" <<endl;
	}
};
//针对两个类型参数取相同类型指针的局部特化版本
template<typename T>
class Dual<T*,T*>{
	public:
	static void printType(void){
		cout << "Dual<T*,T*>" << endl;
	}
};
//针对两个类型参数取某种类型数组的局部特化
template<typename T1,typename T2>
class Dual<T1[],T2[]>{
	public:
	static void printType(void){
		cout << "Dual<T1[],T2[]>" << endl;
	}
};

int main(){
	Dual<int,char>::printType();
	Dual<int,short>::printType();
	Dual<int,int>::printType();
	Dual<int*,char*>::printType();
	Dual<int*,int*>::printType();
	Dual<int[],char[]>::printType();
	//歧义candidates
	return 0;
}
