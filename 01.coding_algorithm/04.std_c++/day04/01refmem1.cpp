#include <iostream>
using namespace std;
class A{
	int& ma;
	public:
	A(int& pa):ma(pa){
	}
	int& getma(){
		return ma;	
	}
};
int main(){
	int x = 200;
	A oa(x);//参数改为引用类型，可以保证不出问题
	cout << oa.getma() << endl;
	cout << oa.getma() << endl;
}
