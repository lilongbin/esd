/*
 * union
 */
#include <iostream>
using namespace std;
void union_test1() {
    //可以定义匿名联合
	union {
        //二者共享相同的内存地址;
		int m;
		char d[4];
	};
	m = 0x31323334;// 当前系统是低字节序
	//49:'1',50:'2',51:'3',52:'4'
	for (int i = 0; i < 4; i++) {
		cout << d[i] << " ";
	}
    //4 3 2 1;
	cout << endl;
}

void union_test2() {
	union UE {
		int iE;
		char cE;
	};
	// iE and cE has the same memory start addr in union;
    union UE ue {};
	ue.iE = 0x01020304;
    cout << "ue.iE = " << std::to_string(ue.iE) << endl;
    cout << "ue.cE = " << std::to_string(ue.cE) << endl;
}

int main() {
    union_test1();
    union_test2();
    return 0;
}
