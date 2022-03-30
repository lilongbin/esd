#include <iostream>
#include <fstream>
using namespace std;
int main(){
	char data[20];
	ifstream ifs("testf.txt");
	if(!ifs){
		perror("open file testf.txt failed");
		return -1;
	}
	ifs.read(data,sizeof data);
	cout << data << endl;
	cout << ifs.gcount() << endl;//得到本次读取到的数据个数，类似c中的strlen
	ifs.close();
}
