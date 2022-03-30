/*****************************************
* Copyright (C) 2018 * Ltd. All rights reserved.
* 
* File name   : debug.cpp
* Author      : longbin
* Created date: 2018-08-09 22:06:05
* Description : 
*
*******************************************/

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <string>
#include <map>
#include <vector>
#include "debug.hpp"
using namespace std;

void test() { DBG_ASSERT(0); }
void func6() { test(); }
void func5() { func6(); }
void func4() { func5(); }
void func3() { func4(); }
void func2() { func3(); }
void func1() { func2(); }

void get_memory_map()
{
	std::string cmd_str;
	std::string pid = std::to_string(getpid());
	cout << "PID: " <<  getpid() << endl;
	cmd_str = "cat /proc/" + pid;
   	cmd_str.append("/maps > mem-map.txt");

	system(cmd_str.c_str());
	sleep(1);
}

int main() {
	func1();
	get_memory_map();
	return 0;
}

