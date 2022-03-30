/*标准IO的读写*/
#include <iostream>
using namespace std;
int main(){
	char c;
	c = cin.get();//从键盘读取一个字符
	cout.put(c);//把得到的字符打印到标准输出
	cout << "----" << endl;
	cin.get(c);
	cout << "----" << endl;
	cout << cin << endl;//判断输入流是否正常
	cout << "----" << endl;
	cout << c << endl;//
}
