/*getline键盘获取一行字符*/
#include <iostream>
using namespace std;
int main(){
	char data[10] = {0};//初始化数组
	cout << "cin=" << cin << endl;
	cin.getline(data,8);//最多只能输入num-1个字符，否则出错
	//一旦IO出错，便拒绝IO
	cout << data << endl;
	cout << "cin=" << cin << endl;
	//如果流出错则修正错误状态
	if(!cin){//标准输入出错
		cout << "修正IO流错误" << endl;
		cin.clear();//清除错误状态
	}
	cout << "cin=" << cin << endl;
	//清理缓冲，忽略掉缓冲中的字符
	//cin.ignore();//忽略掉一个字符
	cin.ignore(100,'\n');//最多忽略掉100个字符，直到'\n'
	cin.getline(data,8,'=');//指定结束符
	cout << data << endl;
}
