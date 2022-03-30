#include <iostream>
#include <cstdlib>
#include <stdexcept>
using namespace std;
int main(){
	int *pi = reinterpret_cast<int*>(malloc(0xffffffff));
	cout << pi << endl;
	try{
		int *parr = new int[0xffffffff];
	}catch(bad_alloc& e){
		cout << e.what() << endl;
	}
	string var_str = "abc";
	cout << var_str[3] << endl;
	try{
		cout << var_str.at(3) << endl;
	}catch(out_of_range& e){
		cout << e.what() << endl;
	}
}
