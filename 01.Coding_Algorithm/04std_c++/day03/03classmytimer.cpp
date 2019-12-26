/*
 * 用class描述类的行为和特征
 */
#include <iostream>
#include <unistd.h>
#include <cstdio>
using namespace std;
class Timer {
	//权限关键字后面加冒号，修饰到下一个权限出现
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
	Timer mytime;
	mytime.settime(23, 59, 50);
	mytime.run();
}

