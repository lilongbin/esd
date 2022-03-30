/*运算符重载*/
#include <iostream>
#include <string>
using namespace std;
int main(){
	string var_a = "abc123 ";
	string var_b = "bbc123";
	if(var_a == var_b){//底层是重载运算符实现的
		cout << "var_a == var_b" << endl;
	}
	if(var_a > var_b){
		cout << "var_a > var_b" << endl;
	}
	string var_c = var_a + var_b;
	cout << "var_c:  " << var_c << endl; 
	var_c = "abc123";
	cout << var_c.length() << endl;
	cout << var_c.at(0) << endl;
	cout << var_c[0] << endl;
	//越界访问的不同表现
	//cout << var_c.at(6) << endl;//越界访问
	cout << var_c[6] << endl;
	//如何把c风格的字符串变成string
	string var_d("hello world");
	cout << var_d << endl;//有运算符重载
	//如何把string变成c风格的字符串
	var_d += "hello";
	const char * mystr = var_d.c_str();
	cout << mystr << endl;
	

}
