#include <iostream>
using namespace std;
int main(){
	char c,c1;
	cout << "--get--putback--" << endl;
	cin.get(c);
	cout << c << endl;
	//可以用来判断输入的第一个字符是什么来确定是否是需要的数据，然后扔回去；
	//可以偷偷的瞄一眼下一个字符是什么
	cin.putback(c);//回退，把上次取得的数据还回去
	char data[10] = {0};
	cin >> data;
	cout << data << endl;
	cout << "-----peek-------" << endl;
	c1 = cin.peek();//偷看一眼下一个字符，只是看，没动;相当于get和putback的结合；文件指针没有移动；
	cin >> data;
	cout << data << endl;

}
