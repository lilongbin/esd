文件位置指针
宏操作
多文件编程


文件位置指针
文件位置指针用来记录下一次文件操作的开始位置;
这个指针用来记录一个整数,这个整数表示这个位置到文件头的距离;
文件位置指针会随着文件的读写操作而移动;可以使用标准函数修改位置指针的数值;
ftell()标准函数可以得到位置指针的数值;
rewind()标准函数可以把文件位置指针调整到文件开头;
fseek()标准函数可以把文件位置指针移动到文件中任何一个位置;
fseek()的第三个参数是一个宏
	SEEK_SET	0	文件头作为基准位置
	SEEK_CUR	1	当前位置作为基准位置
	SEEK_END	2	文件尾作为基准位置
fseek()有三个参数(文件指针, 移动距离, 基准位置)
fseek(p_file, 2, SEEK_SET);
/*
 * 位置指针演示
 */
#include <stdio.h>
int main() {
	int id = 0;
	FILE *p_file = fopen("test.txt", "rb");
	if (p_file == NULL) {
		printf("fopen(): %m\n");
		return -1;
	} else {
		printf("位置指针在%ld\n", ftell(p_file));	//0
		fread(&id, sizeof(int), 1, p_file);
		printf("位置指针在%ld\n", ftell(p_file));	//4
		rewind(p_file);
		printf("位置指针在%ld\n", ftell(p_file));	//0
		fclose(p_file);
		p_file = NULL;
	}
	return 0;
}
/*
 * fseek() display
 */
#include <stdio.h>
int main() {
	char ch = 0;
	FILE *p_file = fopen("test.txt", "rb");	//abcdefghijklmn
	if (p_file == NULL) {
		printf("fopen(): %m\n");
		return -1;
	} else {
		fseek(p_file, 2, SEEK_SET);	//文件头做基准,移动2字节
		fread(&ch, sizeof(char), 1, p_file);
		printf("ch is %c\n", ch);	//c
		fseek(p_file, -2, SEEK_CUR);
		fread(&ch, sizeof(char), 1, p_file);
		printf("ch is %c\n", ch);	//b
		fseek(p_file, -4, SEEK_END);	//文件结束标志占一位
		fread(&ch, sizeof(char), 1, p_file);
		printf("ch is %c\n", ch);	//l
		fclose(p_file);
		p_file = NULL;
	}
	return 0;
}
/*
 * fseek() practice
 */
#include <stdio.h>
int main() {
	char c = 0;
	FILE *p_file = fopen("test.txt", "rb"); //abcdefghijklmn
	if (p_file) {
		while (fread(&c, sizeof(char), 1, p_file)) {
			printf("c is %c\n", c);
			fseek(p_file, 4, SEEK_CUR);
		}
		fclose(p_file);
		p_file = NULL;
	}
	return 0;
}


#define是一个预处理指令
这个预处理指令用来定义宏;
宏可以用来给数字或计算公式或函数体起名字;
编写宏时要把名字写在前边,被代表的内容写在后边;
宏名字中间不能有空格;
不要在宏定义语句中使用赋值操作符;
编译时编译器会直接用宏所代表的东西替换掉宏名称;
宏和变量有着本质的区别;
变量有自己的存储位置,宏没有自己的存储位置,宏在程序执行过程中是不可变化的;

可以使用宏代表一个编写程序时不确定的数字,在编译时指定这个数字;
在gcc命令中可以使用-D选项定义宏,例如给宏指定对应的数字;
不在源程序中定义宏SIZE在编译时使用gcc -DSIZE=10 6macro.c也可以成功编译
/*
 * macro display
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#define       SIZE     10
//gcc -DSIZE=10
int main() {
	int arr[SIZE] = { }, num = 0;
	srand(time(0));
	for (num = 0; num <= SIZE - 1; num++) {
		arr[num] = rand() % 36 + 1;
	}
	for (num = 0; num <= SIZE - 1; num++) {
		printf("%d ", arr[num]);
	}
	printf("\n");
	return 0;
}

使用gcc -E可以查看预处理之后的结果;

宏也可以给一个计算公式起名字;
宏可以使用参数表示计算公式中未知的内容,参数的个数没有限制;
宏的参数可以代表任何东西,所以宏的参数是没有类型的;
带参数的宏是采用二次替换的方式处理的;
用来给计算公式起名的宏中不能定义自己的变量;
/*
 * 宏macro演示
 */
#include <stdio.h>
#define	PI		3.14f	//定义一个PI的宏,即给3.14起一个名字PI
#define	CIRCLE(r)		2 * PI * (r)
#define	AREAR(r)		PI * (r) * (r)
int main() {
	int radius = 0;
	printf("请输入半径: ");
	scanf("%d", &radius);
	printf("周长是:%g\n", 2 * PI * radius);
	printf("周长是:%g\n", CIRCLE(radius));
	printf("面积是:%g\n", AREAR(radius));
	return 0;
}

宏没有返回值变量,所以不能保证先完成宏内部的计算;
所有用来代表计算公式的宏都应该在计算公式外边加一对小括号,这样可以保证先完成宏内部的计算;
宏也没有形式参数,所以不能保证先计算参数的数值;
所有代表数字的宏参数都应该用小括号包括起来;
/*
 * macro display
 */
#include <stdio.h>
#define	SUB1(x, y)	(x)- (y)
#define	SUB2(x, y)	((x)- (y))
int main() {
	printf("SUB1(8, 3) is %d\n", SUB1(8, 3));
	printf("21 - SUB1(5, 3) is %d\n", 21 - SUB1(5, 2));
	printf("21 - SUB2(5, 3) is %d\n", 21 - SUB2(5, 2));
	printf("SUB2(10, 5-2) is %d\n", SUB2(10, 5 - 2));
	return 0;
}
/*
 * macro
 */
#include <stdio.h>
#define	MUL(x,y)	((x) * (y))
int main() {
	printf("MUL(8-2, 9+1)结果是:%d\n", MUL(8 - 2, 9 + 1));
	printf("60 / MUL(8-2, 9+1)结果是:%d\n", 60 / MUL(8 - 2, 9 + 1));
	return 0;
}

宏只是在编译的预处理阶段进行简单的替换;

如果一个宏里面需要经过复杂的处理才能得到一个结果数字,则这个宏必须写成一个表达式;
不要使用自增或自减的计算结果作为宏的参数;
/*
 * macro display
 */
#include <stdio.h>
#define	SQUARE(n)	((n) * (n))
int main() {
	int num = 4;
	printf("SQUARE(num+1) = %d\n", SQUARE(num + 1)); //25
	num = 4;
	printf("SQUARE(++num) = %d\n", SQUARE(++num));	//36?
	num = 4;
	printf("SQUARE(num++) = %d\n", SQUARE(num++));	//16?
	return 0;
}

宏操作符包括#和##
# 宏操作符可以把宏的一个参数转换成字符串字面值;
##操作符可以把一个代表标识符的参数和其他内容合并,生成一个新的标识符;
/*
 * macro 操作符演示
 */
#include <stdio.h>
#define	STR(n)		#n
#define LOCAL(n)	prefix_##n
int main() {
	printf("STR(123) is %s\n", STR(123)); //123
	int prefix_num = 10;
	int LOCAL(num1) = 20;	//与上一句等效,可以方便书写
	printf("%d\n", prefix_num);
	printf("%d\n", LOCAL(num1)); //prefix_num1 = 20
	return 0;
}

条件编译可以在编译时只编译某些语句而忽略另外一些语句;
条件编译形式1
#ifdef(#ifndef) <宏名称> 
	... 
#else 
	... 
#endif
以上语句可以根据某个宏是否被定义过而从两组语句中选择一组编译;
/*
 * 条件编译
 */
#include <stdio.h>
int main() {
//#ifdef ONE
#ifndef TWO
	printf("1\n");
#else
	printf("2\n");
#endif
	return 0;
}

练习 
	产品A
	产品B
/*
 * 点菜练习
 */
#include <stdio.h>
int main() {
	int order = 0;
	printf("请点菜: ");
	scanf("%d", &order);
#ifdef ZHAOBENSHAN
	if (order == 1) {
		printf("小鸡炖蘑菇真没有\n");
	} else {
		printf("龙虾没有\n");
	}
#else
	if (order == 1) {
		printf("小鸡炖蘑菇没有\n");
	} else {
		printf("龙虾有\n");
	}
#endif
	return 0;
}

条件编译形式2
#if	逻辑表达式
	...
#elif	逻辑表达式(多个)
	...
#else
	...
#endif
以上结构可以根据任何逻辑表达式从多组语句中选择一组编译;
条件编译于if分支的区别是前者是有条件的编译,后者是有条件的执行;
/*
 * 条件编译演示
 * 折扣比率练习
 */
#include <stdio.h>
int main() {
#if		defined(FACTORY)	//工厂
	printf("80%\n");
#elif	!defined(FACTORY) && !defined(ELITE)	//普通商店
	printf("100%\n");
#else
	printf("120%\n"); //精品店
#endif
	return 0;
}


多文件编程

多文件程序编写时,某个函数必须完整的属于某个文件;一个文件中可以包含多个函数;

多文件程序编写步骤: 
	1->把所有函数分散在多个不同的.c源文件中(通常主函数单独写在一个源文件中),即编写每个单独的.c源文件;
	2->为每个.c源文件编写对应的.h头文件;
		头文件中只包含对应.c文件中用到的变量和函数的声明;
		如果.c源文件中只包含main()函数则不需要编写对应头文件,头文件中应该包含对应源文件中所有函数的声明;有存储位置的东西不能写在头文件中(如变量的定义(赋值));
	3->为每个.c源文件添加所有需要的头文件;
		如果一个.c源文件使用了某个.h头文件中声明的变量或函数,那么这个.h头文件就需要被包含进来;
	4->采用gcc命令完成编译,要把所有以.c命名的源文件名称都写在命令中;
		编译的时候其实是先单独编译每个文件,然后再链接到一起的;

头文件中要采用条件编译以避免重复包含的问题;

如果要在某个源文件中需要使用其他源文件中声明的全局变量,需要在使用前加extern关键字声明,否则使用的将是一个全新的变量;

用extern关键字声明的变量通常在.c源文件中声明,然后在对应的.h头文件中用extern再次声明;这样其他文件只要包含它的头文件就可以了,不需要在每个需要用它的.c源文件中都用extern声明一次;
(即在.c声明一个全局变量,然后在它的头文件中再用extern声明一次,其他使用它的文件只需要包含这个头文件就可以直接使用该变量了,不用再用extern声明);
static静态全局变量只能在本文件中使用,不可以被其他源文件使用;
static静态函数只能在本文件中使用,不可以被其他源文件使用;
/*
 * 14add.h
 */
#ifndef __14ADD_H__
#define	__14ADD_H__
//头文件使用条件编译,避免被重复包含
void add(int, int);
#endif // __14ADD_H__

/*
 * 14add.c
 */
#include <stdio.h>
#include "14add.h" //双引号表示在同一目录下
int res;
//如果res声明为static变量将被限定在本源文件内使用
void add(int x, int y) {
	res = x + y; 
}

/*
 * 多文件编程演示14main.c
 */
#include <stdio.h>
#include "14add.h"
extern int res;//使用其他文件声明的变量
//如果使用int res; 编译器将重新申请一个全新的变量;
int main() {
	add(3, 6);
	printf("res = %d\n", res);
	return 0;
}

练习
	从键盘得到一个整数,在主函数中打印出来,用多文件编程;
/*
 * 15read.h
 */
#ifndef __15READ_H__
#define __15READ_H__
/*
 * 声明read.c中的num为外部变量,包含该头文件的源文件都可以使用num;
 * 只要包含该.h头文件就可以了,不必在每个.c源文件中都用extern声明一次;
 */
extern int num;
void read_num();
#endif // __15READ_H__
/*
 * 15read.c
 */
#include <stdio.h>
#include "15read.h"
int num; //声明全局变量num;
void read_num() {
	printf("Please input a number: ");
	scanf("%d", &num);
}
/*
 * 从键盘得到一个整数,在主函数中打印出来15main.c
 */
#include <stdio.h>
#include "15read.h"
//extern int num; //不必再声明,在15read.h中已声明
int main() {
	read_num();
	printf("num =%d\n", num);
	return 0;
}


作业
	编写一个宏,这个宏可以根据一个十六进制数位计算出对应的十进制数字;
/*
 * 宏练习,十六进制转十进制
 */
#include <stdio.h>
#define	HEX_2_INT(n)	('0'<(n) && (n) <= '9' ? (n)-'0': 'a' <= (n) && (n)<='f'? (n)-'a'+10:(n)-'A'+10)
int main() {
	char ch = 0;
	printf("请输入一个十六进制数位: ");
	scanf("%c", &ch);
	printf("对应十进制数字是 %d\n", HEX_2_INT(ch));
	return 0;
}

	采用多文件编程方式编写程序生成一张彩票,彩票数据记录在全局数组中;
/*
 * 02lottery.h
 */
#ifndef	__02LOTTERY_H__
#define	__02LOTTERY_H__
extern int lottery[];//全局数组,声明为外部变量
void create();//函数声明
#endif	// __02LOTTERY_H__

/*
 * 02lottery.c
 */
#include <stdlib.h>
#include "02lottery.h"
int lottery[7];
void create() {
	int num = 0;
	for (num = 0; num <= 6; num++) {
		lottery[num] = rand() % 36 + 1;
	}
}

/*
 * 多文件彩票练习
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "02lottery.h"
int main() {
	int num = 0;
	srand(time(0));
	create();
	for (num = 0; num <= 6; num++) {
		printf("%d ", lottery[num]);
	}
	printf("\n");
	return 0;
}

