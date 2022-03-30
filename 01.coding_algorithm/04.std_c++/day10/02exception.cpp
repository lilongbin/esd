#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
void foo(){
	srand(time(NULL));
	int num = rand() % 4;
	if(num == 0){
		cout << "程序正常执行" << endl;
	}else if(num == 1){
		int x = 1;
		//异常中的局部变量与普通的局部变量不同，会保持到异常处理
		throw x;
	}else if(num == 2){
		throw "2.1";
	}else{
		throw 3.5;
	}
	cout << "foo continue" << endl;
}
int main(){
	cout << "main start" << endl;
	/*捕获异常*/
	try{
		foo();
	}catch(int e){
		cout << "int e = " << e << endl;
	}catch(double e){
		cout << "double e ="<< e  << endl;
	}catch(const char* e){
		cout << "const char* e = " << e << endl;
	}catch(...){
		cout << "app have exception" << endl;
	}
	cout << "app continue" << endl;
}
