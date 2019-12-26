结构体
数据补齐对齐
枚举
联合

结构体可以用来统一存储不同类型的数据;
	结构体仅仅是一种数据类型,它本身不占有存储空间;
	结构体仅仅描述了多种数据之间的关系,是一种结构信息;
	结构体可以用来声明结构体变量,结构体变量实际占有内存空间;
声明结构体需要使用 struct 关键字;
结构体声明中包含多个变量声明语句,这些语句不会分配存储位置,因此不能在此初始化(会分配存储空间);
结构体声明本身可以放在头文件中;
可以在声明结构体的时候立刻声明结构体变量,但这种做法不好;
可以使用 struct 关键字和结构体名称一起作为数据类型名称来声明或定义变量;
/*
 * struct演示
 */
#include <stdio.h>
struct person{//声明结构体(名称)
	int id;
	char name[20]; //描述结构信息
	float salary; //不能在此初始化
}; //结构体声明语句,不占用存储位置
typedef struct person personinfo; //给结构体取别名
int main() {
	personinfo p1;	//声明结构体变量
	return 0;
}

typedef 关键字可以用来给数据类型起别名,例如: 
typedef struct person personinfo;
其中 struct person 是已经存在的结构体,后面的personinfo是 struct person 的别名;
只能使用 typedef 关键字给数据类型起别名,而不可以使用宏;因为宏是在编译时直接替换;
int* p_num = NULL, p_num1 = NUll;其实只声明了第一个变量为指针变量;
可以在声明结构体的同时立刻起别名,这个时候可以省略结构体本身的名称";
在C语言中结构体内部不可以包含函数;
/*
 * struct演示
 */
#include <stdio.h>
/*
 * struct person{//声明结构体(名称)
 *     int id;
 *     char name[20]; //描述结构信息
 *     float salary; //不能在此初始化
 * }; //结构体声明语句,不占用存储位置
 * typedef struct person personinfo; //给结构体取别名
 */
typedef struct person { // 声明结构体(名称)
	int id;
	char name[20]; // 描述结构体信息
	float salary; // 不能在此初始化
} personinfo;
/* 本方法同时完成两个工作,声明和起别名,此处可以省略person结构体名称 */
int main() {
	personinfo p1;	//声明结构体变量
	return 0;
}

使用如下格式可以表示结构体变量中的某个子变量
	结构体变量名称.子变量名称
注意.运算符的优先级非常高;
结构体变量也可以初始化,初始化的语法和数组初始化的语法一样;

练习
	声明一个结构体表示手机,包含以下信息:品牌,型号,价格;
	然后声明一个结构体变量表示iphone5;
/*
 * 声明一个结构体表示手机;包含以下信息:
 * 品牌,型号,价格;然后声明一个结构体变量表示iphone5
 */
#include <stdio.h>
#include <string.h>
typedef struct phone {
	char brand[10];
	char type[10];
	float price;
} phone;

int main() {
	//struct phone iphone5;
	phone iphone5 = {
		"Apple",
		"Iphone5",
		4000.0f
	}; //初始化的方式赋值
	/*
	 * strcpy(iphone5.brand, "Apple");
	 * strcpy(iphone5.type, "Iphone5");
	 * iphone5.price = 4000.0f;
	 */
	printf("品牌是%s\n", iphone5.brand);
	printf("型号是%s\n", iphone5.type);
	printf("价格是%g\n", iphone5.price);
	return 0;
}

	同类型的结构体变量之间可以直接赋值,不需要逐个子变量赋值;
	因此结构体变量可以作为函数的形参和返回值,但最好不这样做,因为结构体里面的内容可能非常多,执行效率不高;

练习
	声明一个结构体表示屏幕上的一个点,从键盘得到两个点的位置信息,并记录在两个结构体变量中,计算出两个点的中点位置信息并记录在一个新的结构体变量中,把新结构体变量的内容打印在屏幕上;
/*
 * 结构体变量练习
 */
#include <stdio.h>
typedef struct position {
	int x, y;
} pt;
pt midpt(pt start, pt end) {
	pt mid = {};
	mid.x = (start.x + end.x) / 2;
	mid.y = (start.y + end.y) / 2;
	return mid;
	/* 可以返回结构体类型,但是效率不高 */
}
int main() {
	pt start = {}, end = {}, mid = {};	//初始化为0
	printf("请输入第一个点的位置: ");
	scanf("%d%d", &start.x, &start.y);
	printf("请输入第二个点的位置: ");
	scanf("%d%d", &end.x, &end.y);
	/* 同类型结构体变量可以直接赋值 */
	mid = midpt(start, end);
	printf("新坐标: %d,%d\n", mid.x, mid.y);
	return 0;
}

	使用结构体变量作为形参或返回值会浪费时间和空间,所以应该使用结构体指针作为形参和返回值;
/*
 * 结构体变量指针做返回值
 */
#include <stdio.h>
typedef struct position {
	int x, y;
} pt;
pt *midpt(const pt *p_start, const pt *p_end, pt *p_mid) {
	p_mid->x = (p_start->x + p_end->x) / 2;
	p_mid->y = (p_start->y + p_end->y) / 2;
	return p_mid;
	/* 返回一个结构体指针; */
	/* 数据通过一个指针带回 */
}

int main() {
	pt start = {}, end = {}, mid = {};	//初始化为0;
	printf("请输入第一个点的位置: ");
	scanf("%d%d", &start.x, &start.y);
	printf("请输入第二个点的位置: ");
	scanf("%d%d", &end.x, &end.y);
	midpt(&start, &end, &mid); //&mid称为输出参数;
	printf("新坐标: %d,%d\n", mid.x, mid.y);
	return 0;
}

通过结构体指针表示结构体变量内部子变量时需要使用->操作符,例如
	p_start->num
p_start是一个结构体指针,p_start->num表示p_start所指向的结构体变量start中的num成员;
	(*p_start).num等价于p_start->num;
以下三种形式等价
	1> 结构体变量.成员名;
	2> (*p_start).成员名;
	3> p_start->成员名;
其中->称为指向运算符;
	p->n	得到p指向的结构体变量中的成员n的值;
	p->n++	得到p指向的结构体变量中的成员n的值,用完该值后使它+1;
	++p->n	得到p指向的结构体变量中的成员n的值+1,然后再使用它;
其中.和->取成员运算符的优先级都很高,高于自增++和自减--运算符;

练习
	使用结构体变量,将一个代表点的位置打印在屏幕上
/*
 * 结构体变量与结构体指针
 */
#include <stdio.h>
typedef struct position {
	int x, y;
} pt;
pt *midpt(const pt *p_start, const pt *p_end, pt *p_mid) {
	p_mid->x = (p_start->x + p_end->x) / 2;
	p_mid->y = (p_start->y + p_end->y) / 2;
	return p_mid;
}
void print(const pt *p_pt) {
	printf("(%d,%d)\n", p_pt->x, p_pt->y);
}
int main() {
	pt start = {}, end = {}, mid = {};	//初始化为0;
	printf("请输入第一个点的位置: ");
	scanf("%d%d", &start.x, &start.y);
	printf("请输入第二个点的位置: ");
	scanf("%d%d", &end.x, &end.y);
	midpt(&start, &end, &mid);
	printf("新坐标: %d,%d\n", mid.x, mid.y);
	print(midpt(&start, &end, &mid));
	return 0;
}

	输入矩形对角线上的两个点的坐标,计算矩形的面积
/*
 * 输入矩形对角线上的两个点的坐标
 * 计算矩形的面积
 */
#include <stdio.h>
typedef struct pt {
	int x, y;
} pt;
typedef struct rect {
	pt pt1, pt2;
} rect;
int area(const rect * p_rect) {
	int ret = 0;
	ret = (p_rect->pt1.x - p_rect->pt2.x) * (p_rect->pt1.y - p_rect->pt2.y);
	return ret > 0 ? ret : 0 - ret; //保证返回非负
}
int main() {
	rect r1 = { };
	printf("请输入第一个点的位置: ");
	scanf("%d%d", &r1.pt1.x, &r1.pt1.y);
	printf("请输入第二个点的位置: ");
	scanf("%d%d", &r1.pt2.x, &r1.pt2.y);
	printf("area is %d\n", area(&r1));
	return 0;
}

数据补齐对齐

数据对齐
	不同类型的数据在内存中按照一定的规则排列,而不是一个挨一个的顺序排放;
	任何变量的地址必须是P的整数倍,这个规则叫做数据对齐;
	P取:#pragma pack(n)指定的字节数(2/4/8/...)和这个变量中最大子变量二者中的最小值;
	数据对齐会造成结构体内部不同子变量之间有空隙;

数据补齐
	一个结构体变量的大小必须是P的整数倍,这个规则叫数据补齐;
	P取:#pragma pack(n)指定的字节数(2/4/8/...)和结构体中最大的子变量所占用的字节数二者中的最小值;
	这种补齐可能造成结构体在最后多占用一些浪费的字节;

#pragma pack(整数) 可以指定结构的对齐和补齐的字节数;
#pragma pack() 默认是4字节

"结构体中子变量的顺序会影响结构体的大小;
占用空间小的子变量写前边可以节约内存空间;

struct占用内存大小
    每一个成员起始于0偏移处; 
    每一个成员按其类型大小和指定对齐参数n中较小的一个进行对齐; 
        偏移地址要对齐;
		成员占用大小需对齐; 
        结构体成员的对齐参数为其所有成员使用的对齐参数最大值和pack()参数二者的最小值;
	结构体总长度必须为所有对齐参数的整数倍; 
/*
 * 数据对齐,补齐演示
 */
#include <stdio.h>
typedef struct { //假设存储位置都起始于地址0
	char str[2]; //2 //起始于地址0,占2字节;
	int num; //4 //起始于地址4,占4字节;
} stru; //8
typedef struct {
	char ch; //1 //起始于地址0,占1字节;
	short snum; //2 //起始于地址2,占2字节;
	char ch1; //1 //起始于地址4,占1字节; //补齐数据至2的整数倍
} stru1; //6
typedef struct {
	char ch; //1 //起始于地址0,占1字节;
	short snum; //2 //起始于地址4,占2字节;
	char ch1; //1 //起始于地址8,占1字节;
	int *p_num; //4 //起始于地址12,占4字节;
} stru2; //16
int main() {
	printf("sizeof(stru) is %ld\n", (long)sizeof(stru)); //8
	/* str与num中间空了2个字节;这是由于数据对齐造成的; */
	printf("sizeof(stru1) is %ld\n", (long)sizeof(stru1)); //6
	/* 地址数据补齐为最大子变量与系统pack(n)指定的字节数二者中
	 * 的最小值的整数倍,即2的整数倍; */
	printf("sizeof(stru2) is %ld\n", (long)sizeof(stru2)); //16
	return 0;
}

练习
	一个班有5个学生,每个学生参加三门期末考试(语文,数学,英语);
	用一个结构体记录一个学生的所有成绩;编写函数计算出这个班每门科目的平均成绩并记录在一个结构体中,最后把所有平均成绩打印在屏幕上;
/*
 * 班级成绩管理
 */
#include <stdio.h>
typedef struct {
	int chn, math, eng;
} rank;
rank *ave(const rank *p_rank, int size, rank *p_ave) {
	int num = 0;
	for (num = 0; num <= size - 1; num++) {
		p_ave->chn += (p_rank + num)->chn;
		p_ave->math += (p_rank + num)->math;
		p_ave->eng += (p_rank + num)->eng;
	}
	p_ave->chn /= size;
	p_ave->math /= size;
	p_ave->eng /= size;
	return p_ave;
}
int main() {
	rank ranks[5] = { };
	rank ave_rank = { };
	int num = 0;
	for (num = 0; num <= 4; num++) {
		printf("请输入3门考试成绩: ");
		scanf("%d%d%d", &ranks[num].chn, &ranks[num].math,
		      &ranks[num].eng);
	}
	ave(ranks, 5, &ave_rank);
	printf("语文平均: %d, 数学平均: %d, 英语平均: %d\n",
			ave_rank.chn, ave_rank.math, ave_rank.eng);
	return 0;
}


枚举

枚举类型可以把一组相关名称转换成数字;
使用关键字 enum 声明枚举类型,转换成的数字默认从0开始依次递增;
也可以指定默认的起始数据;

如果不关心转换成的数值就可以使用枚举类型;
如果对转换成的数值有要求就需要使用宏:
/*
 * 枚举演示
 */
#include <stdio.h>
/*
 * #define SPR	O
 * #define SUM	1
 * #define AUT	2
 * #define WIN	3
 */
int main() {
	int season = 0;
	//enum {SPR, SUM, AUT, WIN}; //声明枚举类型
	enum {SPR = 10, SUM, AUT, WIN }; //声明枚举类型并指定起始数据
	printf("SUM = %d\n", SUM);
	printf("请输入季节: ");
	scanf("%d", &season);
	if (season == SUM) {
		printf("是夏天\n");
	} else {
		printf("不是夏天\n");
	}
	printf("AUT is %d\n", AUT);
	return 0;
}


联合

联合也是一种数据类型,其中包括多个子变量;
联合使用 union 关键字声明;

可以使用typedef给联合类型取别名;
typedef union un {
	char ch[2];
	int num;
} un;

联合中所有子变量都占有同样的存储位置,他们之间是互相影响的;
联合的大小是其中占用存储空间最大的子变量的大小;
联合中不同的子变量可以看成是对同样内存空间的不同使用方式;
联合主要在当内存较小时能够充分利用内存;
/*
 * union
 */
#include <stdio.h>
typedef union un {
	char ch[2];
	int num;
} un;
int main() {
	un un1 = { };
	un1.num = 0;
	un1.ch[0] = 'a';
	un1.ch[1] = 'b';
	/* ch和num的起始地址一样; */
	printf("un1.num = 0x%x\n", un1.num);
	printf("sizeof(un1) = %d\n", sizeof(un1));
	return 0;
}

作业
	编写函数从已知的两条线段中找到比较长的那条并赋值给返回值;
/*
 * 线段练习
 * 编写函数从已知的两条线段中找到比较长的那条并赋值给返回值;
 */
#include <stdio.h>
//计算线段长度平方的宏
#define LEN2(p_l) (((p_l)->start.x - (p_l)->end.x) * ((p_l)->start.x - (p_l)->end.x) + ((p_l)->start.y - (p_l)->end.y) * ((p_l)->start.y - (p_l)->end.y))
typedef struct pt {
	int x, y;
} pt;
typedef struct line {
	pt start, end;
} line;
/* 找出较长的线段 */
const line *longer(const line *p_l1, const line *p_l2) {
	return LEN2(p_l1) > LEN2(p_l2) ? p_l1 : p_l2;	
}
int main() {
	line l1 = {}, l2 = {};
	printf("please input line1's position: ");
	scanf("%d%d%d%d", &l1.start.x, &l1.start.y, &l1.end.x, &l1.end.y);
	printf("please input line2's position: ");
	scanf("%d%d%d%d", &l2.start.x, &l2.start.y, &l2.end.x, &l2.end.y);
	line const *p_l = NULL;
	p_l = longer(&l1, &l2);
	printf("result: ((%d, %d), (%d, %d))\n", p_l->start.x, p_l->start.y, p_l->end.x, p_l->end.y);
	return 0;
}

