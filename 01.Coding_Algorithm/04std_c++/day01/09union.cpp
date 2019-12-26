/*
 * union
 */
#include <iostream>
using namespace std;
int main() {
	union {			//可以定义匿名联合
		int m;
		char d[4];
	};			//二者共享相同的内存地址;
	m = 0x31323334;		// 当前系统是低字节序
	//49->'1',50->'2',51->'3',52->'4'
	for (int i = 0; i < 4; i++) {
		cout << d[i] << " ";
	}			//4 3 2 1;
	cout << endl;
}
