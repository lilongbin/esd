三目操作符
类型转换
分支
循环


三目操作符可以根据一个布尔值从两个不同的表达式中挑选一个来使用
三目表达式的格式如下:
	布尔值 ? 表达式1 : 表达式2
当布尔值为真时运算表达式1,否则运算表达式2; 
	strcmp(str1, "yes") ? printf("yes\n") : printf("no\n");

/*
 * 绝对值练习
 */
#include <stdio.h>
int main() {
	int num = 0;

	printf("请输入一个数字");
	scanf("%d", &num);

	num = num < 0 ? 0 - num : num;
	printf("绝对值是:%d\n", num);

	return 0;
}

三目运算符可以嵌套使用;

/*
 * 转大写字母练习
 */
#include <stdio.h>
int main() {
	char ch = 0;
	printf("请输入一个字母");
	scanf("%c", &ch);
	/* ch = (ch >= 'a' && ch <= 'z') ? ch - 'a' + 'A' : ch; */
	ch &= ~(1 << 5);
	printf("大写字母为:%c\n", ch);
	return 0;
}

/*
 * 四则表达式练习
 */
#include <stdio.h>
int main() {
	char ch = 0;
	int num = 0, num1 = 0;
	printf("请输入一个表达式");
	scanf("%d%c%d", &num, &ch, &num1);
	num = (ch == '+' ? num + num1 : (ch == '-' ? num - num1 : num * num1));	//仅支持+-*操作;
	printf("计算结果是:%d\n", num);
	return 0;
}

类型转换
如果一个表达式中包含多个不同类型的数据,则必须首先把他们转换成同一种类型然后才能计算
这个转换过程是由计算机自动完成的,叫做隐式类型转换; 
隐式类型转换中把占地小的数据转换成占地大的类型
当多个数据所占大小一样的时候把整数转换成浮点数,把有符号数转换成无符号数; 
c语言中任何数据可以当作任何类型使用; 
在程序中给数据指定类型的做法叫做强制类型转换; 

强制类型转换语法如下:
	(char)num
这表示把num变量当char类型数据使用
强制类型转换有可能造成问题

/*
 * 类型转换
 */
#include <stdio.h>
int main() {
	printf("大小是%d\n", sizeof(1 ? 1 : 0.9));	//8
	printf("大小是%d\n", sizeof(1 ? 1 : 9));	//4
	printf("-7 + 3 > 0 is %d\n", -7 + 3 > 0);	//0
	printf("-7 + 3u > 0 is %d\n", -7 + 3u > 0);	//1
	printf("(char)300 is %d\n", (char)300);	//44
	return 0;
}

强制类型转换的实现方式是临时生成一个新数据,使用旧数据对新数据进行赋值;
类型转换并不会改变原数据; 

int a = 1;
(unsigned char)a == 1;
(short)a == 1;
(int)a == 1;
并不会因为强制类型转换而多读取a所在的存储空间;
只是用原来的数据临时生成了一个新类型的数据供以后解读;

对指针的强制类型转换会影响程序对数据的读取和解析方式

#include <stdio.h>
int main() {
	char arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	void *p = NULL;
	p = arr;
	/* 对指针的强制类型转换会影响程序对数据的读取和解析方式 */
	int inta = *(int *)p;
	short shorta = *(short *)p;
	char chara = *(char *)p;
	printf("%x, %x, %x\n", inta, shorta, chara);
	/* 4030201, 201, 1 */
	printf("%p, %p, %p\n", (int *)p, (short *)p, (char *)p);
	/* 0x7fff52f3b040, 0x7fff52f3b040, 0x7fff52f3b040 */
	return 0;
}

#include <stdio.h>
int main() {
	char arr[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
	void *p = NULL;

	p = arr;
	/* 对指针的强制类型转换会影响程序对数据的读取和解析方式 */
	printf("%x, %x, %x\n", *(char *)p, *(short *)p, *(int *)p);
	/* 1, 201, 4030201 */

	/* 强制类型转换的实现方式是临时生成一个新数据, */
	/* 使用旧数据对新书据进行赋值;以后的操作采用的都是新数据; */
	printf("%x, %x, %x\n", (char)arr[0], (short)arr[0], (int)arr[0]);
	/* 1, 1, 1 */
	return 0;
}

C语言隐式类型转换
算术运算表达式中,低类型转换为高类型;
赋值表达式中,表达式的值转换为左边变量的类型;
函数调用时,实参转换为形参的类型;
函数返回值,return表达式转换为返回值类型;

char ->
short -> int -> unsigned int -> long -> unsigned long -> double <- float

#include <stdio.h>
int main() {
    int i = -2;
    unsigned int j = 1;
    if ( (i + j) >= 0 ) {
        printf("i+j >= 0\n");
    } else {
        printf("i+j < 0\n");
    }
    printf("i+j=%0X\n", i + j); // FFFFFFFF
    printf("i+j=%d\n", i + j); // -1
    printf("i+j=%u\n", i + j); // 4294967295
	// 有符号和无符号类型在内存中的表示都是一样的;
	// 关键看我们的计算机如何解析;
    return 0;
}

-2
+2: 00000000 00000000 00000000 00000010
-2: 11111111 11111111 11111111 11111101 + 1
-2: 11111111 11111111 11111111 11111110
-2: 0xFFFFFFFE
+1: 00000000 00000000 00000000 00000001

-2+1:
    11111111 11111111 11111111 11111111
    0xFFFFFFFF
-1
+1  00000000 00000000 00000000 00000001
-1: 11111111 11111111 11111111 11111110 + 1
-1: 11111111 11111111 11111111 11111111
-1: 0xFFFFFFFF
printf("%d", i + j);
%d: 以int类型打印i+j; 结果是0xFFFFFFFF,被解析为-1
%u: 把-2转为uint,0xFFFFFFFE很大的正数;

强制类型转换的实现方式是临时生成一个新数据,使用旧数据对新书据进行赋值; 以后的操作采用的都是新数据;

int a = 1;
(unsigned char)a == 1;
(short)a == 1;
(int)a == 1;
并不会因为强制类型转换而多读取a所在的存储空间; 
只是用原来的数据重新生成了一个新类型的数据供以后解读;

char arr[10] = {1,2,3,4,5,6,7,8,9,10};
void *p = NULL;
p = arr;
int inta = *(int *)p;
short shorta = *(short *)p;
char chara = *(char *)p;                           
printf("%p, %p, %p\n", (int *)p, (short *)p, (char *)p);
// 被强制类型转换的数据并没有发生变化
printf("%x, %x, %x\n", inta, shorta, chara);
// 4030201, 201, 1
// 指针的类型变化,对其解析的方式就会不同,读取对应地址的方式也不同


流程控制语句可以让程序中的语句不再从上到下逐条执行; 
言外之意就是程序一般是按照从上到下的顺序执行; 

1. 分支语句
是一种流程控制语句,分支可以把程序中的某些语句忽略掉不去执行; 

if关键字可以用来编写分支语句;
if (condition){
	sentence;
}
if分支语句中只有当逻辑表达式为真时才会执行对应的所有语句; 
如果多个分支的逻辑表达式之间存在互斥关系(任何时候最多只有一个表达式为真)则可以采用else关键字把他们合并成一个分支语句;
if (condition_1) {
	sentence;
}
else if (condition_2) {
	sentence;
}

一个分支语句中的多个逻辑表达式之间如果具有互补关系(任何时候有且只有一个逻辑表达式结果为真)则可以把最后一个逻辑表达式省略; 
if (condition_1) {
	sentence;
}
else {
	sentence;
}

/*
 * if分支演示
 */
#include <stdio.h>
int main() {
	int num = 0;
	printf("请输入一个整数");
	scanf("%d", &num);
	if (num > 0) {
		printf("正数\n");
	} else if (num == 0) {
		printf("零\n");
	} else {
		printf("负数\n");
	}
	return 0;
}

/*
 * 编写程序根据用户给定的年月计算天数
 */
#include <stdio.h>
int main() {
	int year, month;
	printf("请输入年和月");
	scanf("%d%d", &year, &month);
	int day = 0;
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8
	    || month == 10 || month == 12) {
		day = 31;
	} else if (month == 4 || month == 6 || month == 9 || month == 11) {
		day = 30;
	} else if (month == 2) {
		if (!(year % 400) || (!(year % 4) && year % 100)) {
			day = 29;
		} else {
			day = 28;
		}
	}

	printf("%d年%d月共%d天\n", year, month, day);

	return 0;
}

/*
 * 编程从键盘得到三个整数,找出其中最大的整数打印在屏幕上
 * 要求不使用另外的变量,
 * 三个变量的内容可以修改但必须保证永远记录用户输入的三个数字
 */
#include <stdio.h>
int main() {
	int a = 0, b = 0, c = 0;
	printf("请输入三个整数: ");
	scanf("%d%d%d", &a, &b, &c);
	if (a < b) {
		a ^= b;		//交换
		b ^= a;
		a ^= b;
	}

	if (a < c) {
		a ^= c;		//交换
		c ^= a;
		a ^= c;
	}
	printf("输入的三个数字为: %d, %d, %d\n", a, b, c);
	printf("最大数字为: %d\n", a);

	return 0;
}

如果有一组数字,数字的个数有限,每个数字对应一组专门的处理语句;
这种情况的分支可以采用下面的语法实现; 

switch ... case 语句也可以用来实现分支,这种分支专门用来解决上面提到的情况; 
格式:
	switch (num) {
		case 1:
			...;
		case 2:
			...;
		default:
			...;//可以省略
	}
break; 用于结束一个小分支(跳出当前所在层次的循环); 
default; 处理列举之外的情况;

/*
 * 季节练习
 */
#include <stdio.h>
int main() {
	int season = 0;
	printf("请输入一个代表季节的数字: ");
	scanf("%d", &season);

	switch (season) {
	case 1:
		printf("春天\n");
		break;
	case 2:
		printf("夏天\n");
		break;
	case 3:
		printf("秋天\n");
		break;
	case 4:
		printf("冬天\n");
		break;
	default:
		printf("太任性\n");
		break;
	}
	return 0;
}

2. 循环语句
也是流程控制语句,它可以让一组语句多次反复执行

for关键字可以用来编写循环语句
for循环的编写步骤:
	1.声明循环变量
	2.确定循环变量变化过程中的开始数字和结束数字
	3.编写小括号描述循环变量的变化过程; 
	(把循环变量赋值成开始数字; 用逻辑表达式描述循环变量和结束数字的之间的关系; 描述循环变量的变化方式)
		在小括号前面加关键字for
		在小括号后面加入一对大括号,其中包含反复执行的语句; 
	4.编写大括号里面的语句用来处理循环变量所对应数字的处理操作; 

for循环语句中每次循环变量发生变化则大括号里的语句执行一次,
每次大括号里的语句执行时,循环变量都对应范围内的某一个数字;
大括号里的语句负责处理循环变量当前所对应数字的操作; 
如:
for (i = 0; i <= 5; i++) {
	printf("%d", i);
}

/*
 * for循环演示
 */
#include <stdio.h>
int main() {
	int num = 0;
	for (num = 1; num <= 5; num++) {
		printf("%d ", num);
	}
	printf("\n");
	return 0;
}

/*
 * for练习
 * 编程计算10到50之间所有整数的和
 */
#include <stdio.h>
int main() {
	int num = 0, sum = 0;
	for (num = 10; num <= 50; num++) {
		sum += num;
	}
	printf("sum is %d\n", sum);
}

假设有如下循环
	for(1; 2; 3){
		4;
	}
以上循环按照如下分组方式执行:
	[1,2] [4,3,2] [4,3,2] [4,3,2] ... 除了第一组以外所有组都一样;
正常情况下循环会在一组已经结束而下一组还没有开始的时候结束; 
每组的最后一步都是编号为2的语句,这条逻辑表达式直接决定循环语句是否应该立刻结束; 如果逻辑表达式的结果是真则开始下一组,否则结束循环; 
如果循环是正常结束的,循环结束时编号为2的逻辑表达式结果一定是假
编号为4的语句有可能一次也不被执行;

    for(1-->2<--3){
            |\ /
            | 4;
    }       |
           quit

作业
	1.编程从用户给出的数字中,找出最大数,要求不使用新变量,三个变量的内容不可以改变
/*
 * 编程从用户给出的数字中,找出最大数,
 * 要求不使用新变量,单个变量的内容不可以改变
 */
#include <stdio.h>
int main() {
	int a = 0, b = 0, c = 0;
	printf("请输入三个数字: ");
	scanf("%d%d%d", &a, &b, &c);
	printf("最大数字为:");
	if (a <= b) {
		if (b <= c) {
			printf("%d\n", c);
		} else {
			printf("%d\n", b);
		}
	} else {
		if (a <= c) {
			printf("%d\n", c);
		} else {
			printf("%d\n", a);
		}
	}
	return 0;
}

	2.编程根据用户给出的时分秒数据计算出下一秒的数据,如下格式打印在屏幕上
	hh:mm:ss
	hh表示小时数,mm表示分钟数,ss表示秒数
/*
 * 编程根据用户给出的时分秒数据计算出下一秒的数据,
 * 按如下格式打印在屏幕上:
 * hh:mm:ss
 * hh表示小时数,mm表示分钟数,ss表示秒数
 */
#include <stdio.h>
int main() {
	int hh, mm, ss;
	printf("请输入时,分,秒的数字: ");
	scanf("%d%d%d", &hh, &mm, &ss);

	/* 第一种方法 */
	if (ss == 59) {
		ss = 0;
		if (mm == 59) {
			mm = 0;
			if (hh == 23) {
				hh = 0;
			} else {
				hh++;
			}
		} else {
			mm++;
		}
	} else {
		ss++;
	}
	printf("下一秒的时间是: ");
	printf("%02d:%02d:%02d\n", hh, mm, ss);

	/* 第二种方法 */
	if (mm == 59 && ss == 59) {
		hh++;
		hh %= 24;
	}
	if (ss == 59) {
		mm++;
		mm %= 60;
	}
	ss++;
	ss %= 60;
	printf("下一秒的时间是: ");
	printf("%02d:%02d:%02d\n", hh, mm, ss);

	return 0;
}

	3.编写程序判断用户给出的非负数是不是素数
	素数即不可以被1和它本身以外任何数整除
/*
 * 编写程序判断用户给定的非负数是不是素数
 * 素数即除了1和它本身之外再没有别的约数
 */
#include <stdio.h>
int main() {
	unsigned int num = 0;
	printf("请输入一个非负数: ");
	scanf("%d", &num);
	int i = 0;
	for (i = 2; i <= num - 1; i++) {
		if (!(num % i)) {
			printf("数字%d不是素数(%d)\n", num, i);
			break;
		}
	}
	if (!(i <= num - 1)) {
		printf("数字%d是素数\n", num);
	}

	return 0;
}

	4.使用循环编程解决砝码逻辑
/*
 * 使用循环编程解决砝码逻辑
 */
#include <stdio.h>
int main() {
	unsigned int a = 0;
	printf("请输入重量: ");
	scanf("%d", &a);
	int i = 0;
	for (i = 1; i <= a; i *= 2) {
		printf("%d\t", i);
	}
	printf("\n");

	return 0;
}

	5.编程根据用户给定的花瓣片数在屏幕上交替打印爱我和不爱我
/*
 * 编程根据用户给定的花瓣数在屏幕上交替打印爱我和不爱我
 */
#include <stdio.h>
int main() {
	int num = 0;
	printf("请输入花瓣数: ");
	scanf("%d", &num);

	for (num; num > 0; num--) {
		if (num % 2) {
			printf("爱我\n");
		} else {
			printf("不爱我\n");
		}
	}

	return 0;
}

	6.使用循环解决鸡兔同笼的问题,共有40个头,100只脚,计算鸡和兔子分别有多少只
/*
 * 使用循环解决鸡兔同笼问题:
 * 共有40个头,100只脚,计算鸡和兔子分别有多少只
 */
#include <stdio.h>
int main() {
	int a = 40, b = 100;
	int ji = 0, tu = 0;
	for (ji = 0; ji <= 40; ji++) {
		tu = 40 - ji;
		if (ji * 2 + tu * 4 == 100)
			printf("鸡有%d只,兔子有%d只\n", ji, tu);
	}
	return 0;
}

