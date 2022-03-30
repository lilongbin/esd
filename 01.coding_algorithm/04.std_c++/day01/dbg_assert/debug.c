/*****************************************
* Copyright (C) 2018 * Ltd. All rights reserved.
* 
* File name   : debug.c
* Author      : longbin
* Created date: 2018-08-09 22:42:25
* Description : 
*
*******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "debug.h"

void test() { DBG_ASSERT(0); }
void func6() { test(); }
void func5() { func6(); }
void func4() { func5(); }
void func3() { func4(); }
void func2() { func3(); }
void func1() { func2(); }

int main()
{
	char cmd_str[256] = {};
	func1();
	printf("PID: %d\n", getpid());
	snprintf(cmd_str, sizeof(cmd_str), "cat /proc/%d/maps > mem-map.txt", getpid());
	system(cmd_str);
	sleep(1);
	return 0;
}

