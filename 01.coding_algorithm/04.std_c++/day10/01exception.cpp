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
		throw 1;
	}else if(num == 2){
		throw "2.1";
	}else{
		throw 3.5;
	}
	cout << "foo continue" << endl;
}
int main(){
	foo();
	cout << "app continue" << endl;
}
