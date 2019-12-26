/*****************************************
* Copyright (C) 2018 * Ltd. All rights reserved.
* 
* File name   : endian.cpp
* Author      : longbin
* Created date: 2018-08-09 20:52:07
* Description : 
*
*******************************************/

#include <iostream>
using namespace std;

bool isLittleEndian()
{
	/*
	 * iE and cE has the same memory start addr in union;
	 * put 0x1 to an integer variable and read the first byte
	 * will return 1 if litte endian, otherwise return 0;
	 */
	union UE {
		int iE;
		char cE;
	};
	union UE ue;
	ue.iE = 0x1;
	return (ue.cE == 1);
}

int main() {
	cout << "isLittleEndian: " << isLittleEndian() << endl;
	return 0;
}

