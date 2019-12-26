#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdlib>
using namespace std;
/*对数据进行^*/
void _xor(const char* src,const char* des,unsigned char key){
	cout << "程序框架已完成" << endl;
	ifstream ifs(src,ios::binary);
	if(!ifs){
		perror("open file failed");
		return;
	}
	ofstream ofs(des,ios::binary);
	if(!ofs){
		perror("open target file failed");
		return;
	}
	char data[50] = {0};
	while(ifs.read(data,sizeof data)){
		//数组是满的
		for(int i = 0;i <= 50-1;i++){
			data[i] = data[i] ^ key;
		};
		ofs.write(data,sizeof data);
	}
	//最后一次读取的数据加密后写入文件
	int gcount = ifs.gcount();
	for(int i = 0;i <= gcount -1;i++){
		data[i] = data[i] ^ key;
	}
	ofs.write(data,gcount);
	/*关闭资源*/
	ifs.close();
	ofs.close();
}
void enc(const char* src,const char* des){//加密函数
	/*随机生成密钥*/
	srand(time(NULL));
	unsigned char key = rand() % 256;
	cout << "key = " << (int)key << endl;
	_xor(src,des,key);
}
void dec(const char* src,const char* des,unsigned char key){//解密函数
	_xor(src,des,key);
}
int main(int argc, char ** argv){
	if(argc <3){
		cout << "命令使用错误，应如下："<< endl;
		cout << argv[0]<<" 源文件名 加密文件名" <<endl;
		cout << argv[0]<<" 加密文件 破解文件名  key" << endl;
		return -1;
	}else if(argc == 3){
		cout << "文件加密"<< endl;
		//调用一个函数，对文件数据进行加密
		enc(argv[1],argv[2]);//加密函数
	}else if(argc >= 4){
		cout << "文件解密" << endl;
		//调用一个函数，对文件进行解密
		dec(argv[1],argv[2],atoi(argv[3]));//解密函数
	}
}
