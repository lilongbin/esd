/*getline从文件config.txt获取一行字符*/
#include <iostream>
#include <fstream>
using namespace std;
int main(){
	char data[20] = {0};//初始化数组
	ifstream ifs("config.txt");
	if(!ifs){
		cout << "打开配置文件失败" << endl;
		return -1;
	}

	ifs.getline(data,20,'=');//非格式化读取到data[]
	/*char serverIP[20] = {0};//非格式化读取
	ifs.getline(serverIP,20,'\n');*/
	string serverIP;//格式化读取到string类型的serverIP
	ifs >> serverIP;
	cout << serverIP << endl;
	
	ifs.getline(data,20,'=');
	short port;//格式化读取到short类型的port
	ifs >> port;
	cout << port << endl;

	ifs.getline(data,20,'=');
	char username[20] = {0};
	ifs >> username;
	cout << username << endl;
	ifs.close();
}
