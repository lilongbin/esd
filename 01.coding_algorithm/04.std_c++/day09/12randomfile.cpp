#include <iostream>
#include <fstream>
using namespace std;
int main(){
	fstream iofs("random.txt");
	if(!iofs){
		cout << "stream failed" << endl;
		return -1;
	}
	cout << iofs.tellp() << endl;
	cout << iofs.tellg() << endl;
	iofs << "hello";
	cout << iofs.tellp() << endl;
	cout << iofs.tellg() << endl;
	iofs << "world";
	cout << iofs.tellp() << endl;
	cout << iofs.tellg() << endl;
	/*向前调整5个字节*/
	iofs.seekp(-5,ios::cur); // 调整写指针
	cout << iofs.tellp() << endl; // 写指针
	cout << iofs.tellg() << endl; // 读指针
	iofs << 123;
	cout << iofs.tellp() << endl; // 写指针
	cout << iofs.tellg() << endl; // 读指针

	iofs.close();
}
