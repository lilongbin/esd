/*
 * 类的声明mytime.h
 */
#ifndef __MYTIME_H__ //防止一个cpp文件重复包含;被多个文件包含没关系
#define __MYTIME_H__
//int g_var;//在C语言中会当全局变量处理,且没有分配空间;
//int g_var=10;//C语言中不赋值叫声明,赋值就是定义;C中全局变量可以重复声明;
//C++中分配存储空间的就叫定义,没有分配空间的叫声明;
extern int g_var;//加extern就是声明,可以重复包含头文件,因为可以重复声明;
//不加extern不同的编译器处理方式会有差异
class Mytime {
	int hour;
	int min;
	int sec;
	public:
	//构造函数
	//如果指定默认值,一定要在头文件中指定
	Mytime(int h = 0, int m = 0, int s = 0);
	void show();
	void dida();
	void run();
};
#endif //__MYTIME.H__
