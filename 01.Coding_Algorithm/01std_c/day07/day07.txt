break;
continue;
for循环
while循环


在循环中可以使用 break 语句随时终止循环的执行;
执行 break 语句后所在循环终止,循环变量也不会再改变,所以采用这种方式结束循环时逻辑表达式的计算结果仍然是真;
可以通过判断循环变量的真假来判断循环是否正常结束的;
#include <stdio.h>
int main() {
	int num = 0;
	for (num = 0; num <= 5; num++) {
		if (num == 3) {
			break; //跳出循环
		}
		printf("num = %d\n", num);
	}
	if (num <= 5) {
		printf("循环不是正常结束的\n");
	}
	if (!(num <= 5)) {
		printf("循环正常结束\n");
	}
}

continue 语句可以跳过当次循环中后面的语句,开始下一轮循环;
无论 break;还是 continue;都只对直接包含它的循环语句产生影响,不会影响到所在循环的外层循环;
break 只对循环和 switch 语句起作用;

#include <stdio.h>
int main() {
	int num = 0;
	for (num = 1; num <= 5; num++) {
		printf("%d\n", num);
		continue;
		/* continue下面的处于大括号里面的语句不执行,从头执行下一次循环 */
		printf("%d\n", 10 + num);
	}
	return 0;
}


循环嵌套结构可以用来解决复杂的循环问题
首先把复杂问题分组,为每组找到一个代表数字;要求所有组的代表数字是规律变化的;
循环嵌套至少由两个循环构成,其中一个包含另一个;
外循环负责描述组的代表数字变化过程,内循环负责完成某组内的所有处理任务;
/*
 * 54321
 * 4321
 * 321
 * 21
 * 1
 */
#include <stdio.h>
int main() {
	int num = 0, num1 = 0;
	for (num = 5; num >= 1; num--) {
		for (num1 = num; num1 >= 1; num1--) {
			printf("%d", num1);
		}
		printf("\n");
	}
	return 0;
}

循环嵌套的难点
循环嵌套结构中内循环的开始数字和结束数字很可能需要根据外循环的循环变量计算得到;
大部分情况下,内层循环的循环变量要要依赖于外层循环的循环变量,内层循环的循环变量和外层循环的循环变量存在着某种逻辑或数学关系;

练习
假设货币有三种面值: 1元2元和5元
计算出用这三种面值表示10元钱得到所有可能
/*
 * 假设货币有三种面值1,2,5
 * 计算表示10元的所有可能
 */
#include <stdio.h>
int main() {
	int rmb1 = 0, rmb2 = 0, rmb5 = 0;
	for (rmb5 = 0; rmb5 <= 2; rmb5++) {
		for (rmb2 = 0; rmb2 <= (10 - 5 * rmb5) / 2; rmb2++) {
			/*
			 * 循环嵌套中內循环的开始数字和结束数字很可能
			 * 需要根据外循环的循环变量计算得到;
			 */
			printf("5元钱有%d张,2元有%d张,1元有%d张\n",
			     rmb5, rmb2, 10 - 5 * rmb5 - 2 * rmb2);
		}
	}
	return 0;
}

/*
 * 打印9*9乘法表
 */
#include <stdio.h>
int main() {
	int i = 0, j = 0;
	for (i = 1; i <= 9; i++) {
		// 外循环打印每一行
		for (j = 1; j <= i; j++) {
			// 内循环处理每一个小部分
			printf("%dx%d=%-2d\t", j, i, i * j);
		}
		printf("\n");
	}
	return 0;
}

for语句的多种编写方法: 
	1.省略大括号(如果大括号内的语句只有一条时)
	2.使用逗号(,)操作符
	3.临时定义循环变量(C99规范)
	4.省略小括号中第一和第三部分,只保留逻辑表达式
	5.直接在小括号后面写,把循环结束(空语句)
	6.省略小括号中间的逻辑表达式(死循环)

/*
 * for的多种写法练习
 */
#include <stdio.h>
int main() {
	int num = 0, num1 = 0;
	for (num = 1; num <= 3; num++)
		printf("循环省略大括号%d\n", num);
	printf("\n");

	for (num = 1,num1 = 9; num <= num1; num ++, num1--, printf("使用,\n")){
		printf("%d * %d = %2d\n", num, num1, num * num1);
	}

	/*
	 * //只有在C99支持下才能在循环语句中大括号内部定义一个新的变量
	 * //gcc -std=c99 test.c
	 * for (int num2 = 1; num2 <= 3; num2++) {
	 *     printf("1");
	 * }
	 * printf("\n");
	 */
	num = 1;
	for ( /* 省略 */ ; num <= 3; /* 在循环语句中操作 */ ) {
		printf("省略头尾\n");
		num++;
	}
	printf("\n");

	for (num = 0; num <= 2; printf("我在小括号中\n"), num++) ;
	//使用,操作符
	//省略大括号;省略大括号内的语句
	printf("\n");

	printf("死循环\n");
	for (num = 1; /*省略逻辑表达式,死循环 */ ; num++) {
	}
	return 0;
}

while 循环语句
while 关键字也可以用来编写循环;
for 关键字编写的循环和 while 关键字编写的循环是完全可以相互替代的;
当我们不容易计算出编写循环的次数时,就可以考虑采用 while 关键字来编写循环

while关键字编写循环的格式
while (逻辑表达式) {
	反复执行的语句组
}
表示当逻辑表达式结果为真时,执行大括号里面的语句
/*
 * while循环演示
 */
#include <stdio.h>
int main() {
	int num = 0;
	while (num >= 0) {
		printf("Please input a num: ");
		scanf("%d", &num);
	}
	return 0;
}

编写死循环优先采用如下形式
while (1) {
	//循环体;
}

练习
	编写程序计算两个整数的最大公约数
/*
 * 求两个数的最大公约数
 */
#include <stdio.h>
int main() {
	int num1 = 0, num2 = 0, ret = 0;
	printf("请用户输入两个整数: ");
	scanf("%d%d", &num1, &num2);
	while (num1 % num2) {
		ret = num2;
		num2 = num1 % ret;
		num1 = ret;
		printf("num1=%d, num2=%d, ret=%d\n", num1, num2, ret);
	}
	printf("最大公约数是:%d\n", num2);
	return 0;
}

假设有如下whlie语句
while (1) {
	2;
}
它按照如下分组方式执行: 
[1][2,1][2,1][2,1]...
正常情况下 while 语句在两组之间结束,每一组的最后一个步骤都是编号为1的逻辑表达式,如果它的结果是真则启动下一组,否则结束循环;
//如果while语句正常结束则逻辑表达式的结果一定是假
while语句中大括号内部的语句有可能不执行
while关键字也可以编写空语句和死循环

while (1) {
	printf("\n");
} //死循环
以上语句是死循环
while (1);
以上语句是空语句
while 循环中可以使用 break;和 continue;

采用 do ... while 语句也可以实现循环,格式如下: 
do {
	反复执行的语句;
} while (逻辑表达式);

/*
 * do {} while ();
 */
#include <stdio.h>
int main() {
	int num = -1;
	/*
	 * while (num >= 0) {
	 *     printf("请输入一个数字");
	 *     scanf("%d", &num);
	 * }
	 */
	do {
		printf("请输入一个数字:");
		scanf("%d", &num);
		printf("%d\n", num);
	} while (num >= 0);
	return 0;
}

使用 do {...} while ();语句实现的循环可以保证大括号里面的语句至少执行一次;
假设有如下循环语句
do {
	2;
} while (1);
它按照以下分组方式执行: 
[2,1][2,1][2,1]...
相当于把whlie循环中的第一组砍掉

scanf()标准函数在结束时返回了一个整数数字,如果是0,表示没有读到有效数据;
返回的数字和用户输入的数字没有任何关系,标准函数的调用语句直接当数字使用可以得到它返回的数字;
scanf()的返回值是读取到的有效字节数;
如果返回0表示没有读到有效数据;

以下两条语句可以清空输入缓冲区的内容
scanf("%*[^\n]");
scanf("%*c");
/*
 * scanf()
 */
#include <stdio.h>
int main() {
	int num = 0;
	int flag = 0;
	do {
		printf("Please input a number: ");
		if (flag) {
			scanf("%*[^\n]");
			scanf("%*c");
		}
		flag = 1;
	} while (!scanf("%d", &num));
	scanf("%*[^\n]");
	scanf("%*c");
	printf("num is: %d\n", num);
	return 0;
}

goto语句也是一条流程控制语句,它可以任意指定下一条语句;
不要使用goto语句
一般在初始化程序中会大量使用goto语句来处理异常

作业
	1.在屏幕打印如下内容: 
			   *
			  ***
	  		 ***** 
		    *******
		   *********
	每次只能打印一个字符
#include <stdio.h>
int main() {
	int num = 0, num1 = 0, i = 3;
	for (num = 1; num <= 4; num++) {
		for (num1 = 1; num1 <= num + 3; num1++) {
			if (num1 < num + i) {
				printf(" ");
			} else {
				printf("*");
			}
		}
		i -= 2;
		printf("\n");
	}
	return 0;
}

	2.现在有一组自行车,三轮车,汽车(4个轮子,一个座位)
这些车一共由10个座位和28个轮子
编程计算所有可能性并打印在屏幕上
/*
 * 自行车,三轮车,汽车
 */
#include <stdio.h>
int main() {
	int num = 0, num1 = 0;	//num汽车,num1三轮车
	for (num = 0; num <= 7; num++) {
		for (num1 = 0; num1 <= (28 - 4 * num) / 3; num1++) {
			//内层循环变量由外层循环变量计算得出
			if (2 * (10 - num - num1) + 4 * num + 3 * num1 == 28) {
				printf("汽车%d辆,三轮车%d辆,自行车%d辆\n",
						num, num1, 10 - num - num1);
			}
		}
	}
	return 0;
}

	3.编写一个猜数游戏
	使用一个没有初始化的整数类型,变量得到一个从0到99之间的数字;
	程序中让用户不停的猜,直到猜对为止;
	每次猜完都要提示
#include <stdio.h>
int main() {
	int guess, userinput = 0;
	while (1) {
		printf("请用户输入一个想要猜的数字:");
		scanf("%d", &userinput);
		printf("%d\n", guess);
		printf("%p", &guess);
		if (userinput == guess % 100) {
			printf("恭喜您猜对了!\n");
			break;
		} else if (userinput < guess % 100) {
			printf("亲,你猜小了,再来一次吧!\n");
		} else {
			printf("亲,您猜大了,再来一次吧!\n");
		}
	}
	return 0;
}

	4.编程统计一个用户给定的数
/*
 * 编程统计一个用户给定的数位
 */
#include <stdio.h>
int main() {
	int num = 0, count = 0;
	printf("请输入一个数字:");
	scanf("%d", &num);
	while (num != 0) {
		num /= 10;
		count++;
	}
	printf("输入数字共有%d位\n", count);
	return 0;
}
		
