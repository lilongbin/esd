/*
 * 构造函数
 */
#include <iostream>
#include <unistd.h>
#include <cstdio>
using namespace std;
class Timer {
	public:
		//自定义的构造函数默认是私有的
		Timer() {
			//初始化成员变量
			hour = 23;
			min = 59;
			sec = 50;
			cout << "我是构造函数,我怕谁" << endl;
		}
	private:
		//特征
		int hour;
		int min;
		int sec;
		//行为
	public:
		void settime(int h = 0, int m = 0, int s = 0) {
			hour = h;
			min = m;
			sec = s;
		}
	private:
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
	//private:
	public:
		void run() {
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
	//在栈区构建对象,自动调用1次构造函数
	Timer mytime;
	//用类构建一个对象,构造函数被自动调用一次；
	//Timer是类mmytime是一个对象;
	//mytime.settime(23,59,50);
	mytime.run();
}
