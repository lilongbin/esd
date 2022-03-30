/*文件的输入输出*/
#include <fstream>
#include <iostream>
using namespace std;
int main(){
	ifstream ifs("03getput.cpp");//读取文件
	if(!ifs){
		perror("open file failed");
		return -1;
	}
	char c;
	while((c=ifs.get()) != EOF){//循环打印
		cout.put(c);
	}
	//练习将得到的字符写入到文件
	ofstream ofs("copy03putget.cpp.txt");
	if(!ofs){
		perror("copy file open failed");
		return -1;
	}
	/*while(ifs){//典型的错误
		ifs.get(c);//结束的时候会多读一次，最后一个字符会写两遍
		ofs.put(c);
	}*/
	while((c=ifs.get()) != EOF){//循环打印
		ofs.put(c);
		//cout.put(c);
	}
	ofs.close();
	ifs.close();//关闭文件
}

