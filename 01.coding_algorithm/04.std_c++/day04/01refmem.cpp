#include <iostream>
using namespace std;
class A{
	int& ma;
	public:
	A(int pa):ma(pa){
	}
	int& getma(){
		return ma;	
	}
};
int main(){
	A oa(200);
	cout << oa.getma() << endl;//两次结果会有所不同
	cout << oa.getma() << endl;//pa的值已释放
}
