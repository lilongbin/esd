/*
 * 使用结构体设计时间类
 */
#include <iostream>
#include <unistd.h>
#include <cstdio>
using namespace std;
struct Timer {
	//特征
	int hour;
	int min;
	int sec;
	//行为
	void settime(int h = 0, int m = 0, int s = 0) {
		hour = h;
		min = m;
		sec = s;
	}
   	void showtime() {
		//cout << hour << ":"<< min << ":" << sec << endl;
		printf("%02d:%02d:%02d\r", hour, min, sec);	//回头显示
		fflush(stdout);	//刷缓冲
	}
	//时间走一秒
	void dida() {
		sec++;
		if (!(sec % 60)) {
			sec = 0;
			min++;
			if (!(min % 60)) {
				min = 0;
				hour++;
				hour %= 24;
			}
		}
	}
	void run() {
		//跑起来
		while (1) {
			//sleep(1);
			time_t t = time(NULL);
			while (t == time(NULL)) ;	//等效于sleep(1);
			dida();
			showtime();
		}
	}
};
int main() {
	Timer mytime;
	mytime.settime(23, 59, 50);
	mytime.run();
}
