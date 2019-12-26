#include <iostream>
using namespace std;
int main(){
	//flush可以刷缓冲
	cout << "hello " << flush;//可以重定向
	//下面两个不能重定向
	clog << "world ";
	cerr << "test cerr ";
}
