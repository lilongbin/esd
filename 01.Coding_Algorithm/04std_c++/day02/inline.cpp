/*****************************************
* Copyright (C) 2018 * Ltd. All rights reserved.
* 
* File name   : inline.cpp
* Author      : longbin
* Created date: 2018-08-08 22:31:02
* Description : 
*
*******************************************/

#include <iostream>

#include <string>
#include <map>
#include <vector>
using namespace std;
int getint()
{
	int i, j, k;
	i = 6;
	j = i + 1;
	k = j + 1;
	return k;
}
inline double getpi()
{
	return 3.14159;
}

/*
 * 编译后执行nm命令查看符号表
 * 0000000000400968 W _Z5getpiv
 * 000000000040085d T _Z6getintv
 */
int main() {
	int i = 0;
	cout << "int is: " << getint() << endl;
	for (i=0; i<100; i++)
	{
		cout << "double is: " << getpi() << endl;
	}
	return 0;
}

