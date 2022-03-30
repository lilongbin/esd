/*
 * 类的实现mytime.cpp
 */
#include "mytime.h"
#include <cstdio>
#include <unistd.h>
//把mytime.h头文件中的实现函数拷贝过来
//带初始化参数列表的构造函数
Mytime::Mytime(int h, int m, int s):hour(h), min(m), sec(s) {
}
void Mytime::show() {
	printf("%02d:%02d:%02d\r", hour, min, sec);
	fflush(stdout);
}
void Mytime::dida() {
	if (++sec == 60) {
		sec = 0;
		if (++min == 60) {
			min = 0;
			if (++hour == 24) {
				hour = 0;
			}
		}
	}
}
void Mytime::run() {
	while (1) {
		sleep(1);
		dida();
		show();
	}
}
