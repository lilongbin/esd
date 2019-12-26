#ifndef MYTIME_H
#define MYTIME_H
	class Mytime{
		int hour;
		int min;
		int sec;
		public:
		Mytime();
		Mytime(int hour,int min = 0,int sec = 0);//注意避免重载冲突
		~Mytime();//析构
		Mytime(const Mytime&);//拷贝构造
		static int g_var;//要在类外初始化
		void show();
		void dida();
		void run();
	};

#endif
