函数
返回值
形参实参


函数

在大规模的程序中需要对语句进行分组管理,把相互之间联系比较紧密的语句合并成一组;
分组可以在多个不同层次上进行,最低一级分组的结果叫代码块,代码块由{}大括号包括;
在大括号前面添加
    类型名 函数名()的就是函数;
函数的形式如
void func() {
    do something;
}
任何函数一定包含若干条语句;
任何C语言程序都是由一个或多个函数构成的;
绝大多数语句必须属于某个函数;
在C语言中函数名字是唯一的;
在程序进行过程中不同函数之间一定要存在联系和协作;
任何一次函数之间的协作一定发生在两个函数之间,不排除函数与自身的反馈(自己调用自己);
函数之间的协作只在某个时间范围内有效
两个函数之间的一次协作叫做一次函数调用
函数调用过程中发起调用的函数叫做调用函数(类似于校学生会主席)
被动的接受调用的函数叫做被调用函数(类似于院系学生会主席)

绝大多数函数调用过程中存在数据传递现象;(下达任务,完成后汇报情况);
任何函数调用过程中存在两个方向相反的数据传递过程(下达任务,或反馈是否完成);
这个数据传递的过程是我们研究的重点;

任何一个函数作为被调用函数参与一次函数调用过程时,为了实现两个方向的数据传递,需要各准备一组相关的变量(都有自己的一套组织)用来存放;

调用函数向被调用函数传递的数据称为实参,即实际参数;
被调用函数使用与实参相对应的数据类型(派相关人员对接)接收传递过来的参数,这个参数叫形参,即形式参数;
形式参数可以与实参名字相同,但不代表同一个存储空间(传递复制的数据)(比如都叫外联部);
实参和形参的个数可以不止一个;

被调用函数执行结束或因某种条件而结束时,可以向调用者返回自己执行的情况或结果,这个值用return关键字来实现(结果由院主席向校主席统一汇报),而且一个函数在一次被调用结束时只能返回一个值;

当一个主调函数调用另一个被调函数时,程序将进入被调函数执行,直到被调函数执行结束才会回来继续执行主调函数的下一条语句;

返回值

返回值变量用来实现从被掉用函数向调用函数传递数据;
任何函数最多只能有一个返回值变量;
常用来反馈函数执行的结果(负数或零,或非负数或指针等),或者其他一些标志;
函数返回值的类型由函数声明时在函数名前指定;

返回值变量只能在函数结束的那一刻才能使用
对返回值变量的赋值需要使用 return 关键字实现;
只有调用函数才能从返回值变量中获得数据
在被掉用函数结束的时候才能拿到数据;
把函数调用语句当数字使用表示从返回值变量中获得数据;

/*
 * 返回值演示
 */
#include <stdio.h>

int add() {
    return 2 + 4;
}

int main() {
    int num = 0;
    num = add();
    printf("return %d\n", num);
    return 0;
}

练习
    编写一个多函数程序,用一个函数从键盘得到数字;
    主函数得到这个数字并打印在屏幕上;
/*
 * 用一个函数从键盘得到数字,主函数得到数字并打印在屏幕上
 */
#include <stdio.h>
/* 返回一个int型的值 */
int read() {
    int num;
    printf("请输入一个数字: ");
    scanf("%d", &num);
    return num;
}

/* 不返回任何值 */
void show() {
    printf("I am show()\n");
}

int show1() {
    printf("I am show1()\n");
    // printf("1\n");
    // return 0;
    // 应该返回int型的值,但函数没有明确指定,结果不确定
}

int main() {
    int num = read(); //调用一次
    int num1;
    printf("步骤1>\n");
    printf("输入的数字是:%d\n", num); //直接适用num的值
    printf("步骤2>>\n");
    printf("输入的数字是:%d\n", read()); //调用一次read()
    printf("步骤3>>>\n");
    printf("输入的数字是:%d\n", num);    //不再调用read()
    printf("步骤4>>>\n");
    show();
    num1 = show1();        //结果不确定
    printf("show1 is %d\n", num1);
    return 0;
}


使用void声明函数表示返回值变量类型为空,意味着不使用返回值变量类型;
如果没有明确指出返回值变量类型则计算机缺省认为返回值变量类型是整型;

如果没有使用 return 关键字对返回值变量赋值,则返回的变量内容不确定;
如果对返回值变量进行赋值时两边的类型不一致,则可能出现意想不到的结果;

return关键字可以立刻结束函数的执行,只要函数在执行时碰到该语句就会立刻结束函数的执行;
exit()标准函数可以立刻结束整个进程的运行,需要包含文件stdlib.h;它比return更暴力,结束的更彻底;
/*
 * exit练习
 */
#include <stdio.h>
#include <stdlib.h>
void func() {
    printf("我在func中2\n");
    return;
    printf("3\n");
}

void func1() {
    printf("我在func1中5\n");
    exit(0);        //0与return的0是一样的含义
    printf("6\n");
}

int main() {
    printf("我在main中1\n");
    func();
    func1();
    printf("4\n");
    return 0;
}

练习
    从键盘得到两个数,计算二者和,主函数打印出求和结果;
/*
 * 返回值练习
 */
#include <stdio.h>
int add() {
    int i = 0, j = 0;
    printf("请输入两个数字: ");
    scanf("%d%d", &i, &j);
    return i + j;
}

int main() {
    printf("sum is %d\n", add());
    return 0;
}


形参与实参

    为了实现从调用函数向被调用函数传递数据,被调用函数需要准备一组变量,这组变量叫形式参数;
    他们只能在被调函数中使用;只靠这些数据是不能完成整个数据的传递的,还需要更原始的数据;
    为了实现数据的传递,需要调用函数提供这些数据,调用函数提供的这些数据叫实际参数;
    实际参数既可以是变量也可以是其他方式表示;
    传递的是数据而不是存储位置,值传递;不能通过函数改变实参本身;
    函数的形参类型和个数没有限制,但返回值最多只能有一个;
/*
 * 参数演示
 */
#include <stdio.h>
void show(int num) {
    printf("show(%d)\n", num);
}

void sum(int num, int num1) {
    printf("sum is %d\n", num + num1);
}

int main() {
    int num = 10;
    show(5);
    show(num);
    sum(13, 7);
    return 0;
}

/*
 * 参数与返回值演示
 */
#include <stdio.h>
void show(int num) {
    printf("show(%d)\n", num);
}

int sum(int num, int num1) {
    return num + num1;
}

int main() {
    int num = 10;
    show(5);
    show(num);

    int sum = show1(13, 7);
    printf("sum is %d\n", sum);
    return 0;
}

作业
    1.编写程序在屏幕上打印如下内容:
1 x 9 = 9
2 x 8 = 16
...
5 x 5 = 25
每一行使用一个函数调用语句实现打印
/*
 * 编写程序在屏幕上打印如下内容,
 * 每一条使用一个函数调用语句实现打印;
 * 1 x 9 = 9
 * 2 x 8 = 16
 * 3 x 7 = 21
 * 4 x 6 = 24
 * 5 x 5 = 25
 */
#include <stdio.h>
void show(int x, int y) {
    printf("%d x %d = %2d\n", x, y, x * y);
}

int main() {
    int i = 0;
    for (i = 1; i <= 5; i++) {
        show(i, 10 - i);
    }
    return 0;
}

    2.编程判断某个给定数字是否素数;
/*
 * 编程判断一个数是否素数
 */
#include <stdio.h>
int is_su(int num) {
    int num1 = 0;
    for (num1 = 2; num1 < num; num1++) {
        if (!(num % num1)) {
            return 0;    // 0表示不是素数
        }
    }
    return 1;
}

int main() {
    int i = 0;
    printf("请输入一个数字");
    scanf("%d", &i);
    scanf("%*[^\n]");
    scanf("%*c");

    if (is_su(i)) {
        printf("是素数\n");
    } else {
        printf("不是素数\n");
    }

    return 0;
}

    3.编写函数生成一张彩票并打印在屏幕上;
    可以出现重复数字,彩票中的数字个数由主函数指定;
/*
 * 编写函数生成一张彩票并打印在屏幕上;
 * 可以出现重复数字,彩票中的数字个数由主函数指定
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
void lottory(int num) {
    int arr[num], i = 0;
    for (i = 0; i < num; i++) {
        //生成随机数
        arr[i] = rand() % 36 + 1;
    }
    for (i = 0; i < num; i++) {
        //循环打印
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int num = 0;
    srand(time(0));
    printf("请输入彩票的位数: ");
    scanf("%d", &num);
    scanf("%*[^\n]");
    scanf("%*c");

    lottory(num);
    return 0;
}

