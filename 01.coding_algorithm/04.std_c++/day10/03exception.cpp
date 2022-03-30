#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
void   foo()//throw()
		throw(int,double,const char*){
    srand(time(NULL));
		int  num=rand()%4;
		if(0==num){
		    cout << "程序正常执行" << endl;
		}else if(1==num){
				int  x=1;
		    throw x;
		}else if(2==num){
		    throw "2.1"; 
		}else if(3==num){
		    throw 3.5;
		}
		cout << "foo continue" << endl;
}
int main(){
		cout << "main start" << endl;
		/* 捕获异常 */
    try{
        foo();
		}catch(int e){
		    cout << "int" << e << endl; 
		}catch(double e){
		    cout << "double" << e << endl;
		}catch(const char* e){
		    cout << "const char*" << e << endl;
		}catch(...){
		    cout << "app have exception" << endl; 
		}
		cout << "app continue" << endl;
}

