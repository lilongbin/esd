gcc基础与C语言的环境变量


# 回顾标准C语言的内容
    变量/类型/运算符/表达式/流程控制语句(if-else/switch-case/for/while)

## 数组
    用于存储多个相同类型数据的容器
    数组/数组元素/数组下标/数组长度
```
    int arr[5] = {1, 2, 3, 4, 5};
    arr就是数组,是数据的容器而不是数据本身;
    arr[i]是数组元素,代表数组中的数据;
    i 是数组的下标,从0开始;
    5 就是数组的长度;
    数组的操作其实就是对下标的操作;
    数组可以看成常指针,就是arr不可以改变指向,但arr[i]可以改变值;
```

## 结构
    用于存储多个相关数据的数据结构,这些相关数据的类型可以不同,但逻辑上要统一;
    这些数据是有相关关系的,不能是没有任何关系的数据;
    结构默认情况下有对齐和补齐;
    struct 结构体名{};
    其中,结构的类型是:struct 结构体名(两个单词算类型);
    typedef跟结构体没有任何关系,只是用来给类型取别名;

## 指针
    变量其实是一块内存,每个内存都有内存地址; 指针就是存储地址的变量; 
```
    int i = 10;
    int *pi = &i;(存i的地址)
        *pi 就能拿到i的值; 
```

## 字符串
    C语言字符串的类型有两种:
```
    char *str;    //字符指针代表字符串
    char str[100];    //字符数组代表字符串
```
    C语言没有string类型,不可以直接对字符数组赋值;

## 各种标准C函数
    printf()/scanf()
    sprintf()/sscanf()
    malloc()/free()/memset()
    strcpy()/strcmp()/strlen()/strcat()
    fopen()/fseek()/fread()/fwrite()/fclose()
    srand()/rand()/time()/...

## 数据结构
    堆栈 队列 链表 有序二叉树

## 算法
    排序算法: 冒泡排序, 选择排序, 插入排序, 快速排序, 归并排序;
    查找算法: 线性查找(无条件), 二分查找(必须有序);

## 练习1
    0-1999的随机数1000个,已知无重复,求最快排序算法; 
```
    利用数组下标;
    1-> 定义一个长度是2000的数组arr,清0; 
    2-> 遍历1000个随机数,arr[随机数] = 1;
    3-> 打印值是1的数组下标就ok; 
```

## 练习2
    一个文件中包含n个正整数,其中n=10的7次方;已知数据不重复;
    请编写程序,将文件中的数字按升序排序;
    根据练习1的思路,但是为节省空间,每个数只用1个bit;
    #define NUM 10000000
    申请的数组为a[1 + NUM/32];
    参考代码如下
```
/*
 * generate.c
 */
/* Include Files */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

/* MACROS */
#define    NUM        10000000
#define    SHIFT    5
#define MASK    0x1F

/* CONSTANTS AND VARIABLES */
int a[1 + NUM/32] = { 0 }; /* define an arry and initialize every member */

/* INTERNAL FUNCTIONS */
void setbit(int n) {
    /* set flag */
    a[n >> SHIFT] |= 1 << (n & MASK); /* a[n/32] |= 1<<(n%32) */
}
void cl_bit(int n) {
    /* clear flag */
    a[n >> SHIFT] &= ~(1 << (n & MASK)); /* a[n/32] |= 1<<(n%32) */
}
int testbit(int n) {
    /* if the n bit exist, resturn 1 */
    return a[n >> SHIFT] & (1 << ( n & MASK));
}
int test_all_bit() {
    int i, res;
    for(i = 0; i <= NUM/32; i++) {
        if (a[i]){
            return a[i];
        }
    }
    return a[i];
}
int list_bit(int n) {
    int i = 0, j = 0;
    for (i = 0; i <= NUM - 1; i++) {
        if (testbit(i)){
            if (j == n) {
                return i;
            }
            j++;
        }
    }
    return i;
}

/* IMPLEMENTATION */
int main() {
    /* create file data.db to save number */
    int fd1 = open("data.db", O_RDWR | O_CREAT | O_TRUNC, 0664);
    if (-1 == fd1) {
        perror("open");
        return -1;
    }

    /* read number of the file, and set flags */
    int i, res;
    for (i = 0; i <= NUM - 1; i++) {
        setbit(i); /* set flags */
    }

    srand(time(0));
    int n = NUM;
    int node;
    printf("starting to generate datas...\n");
    while (test_all_bit()) {
        if (n < 1000 ){
            node = rand() % n;
            i = list_bit(node);
        } else {
            i = rand() % NUM;
        }
        if (testbit(i)) {
            write(fd1, &i, sizeof(int));
            printf("%d\r", i);
            cl_bit(i);
            n--;
        }
    }
    printf("generated ok!\n");

    close(fd1);
    return 0;
}
```

```
/*
 * sort.c
 */
/* Include Files */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

/* MACROS */
#define    NUM        10000000
#define    SHIFT    5
#define MASK    0x1F

/* CONSTANTS AND VARIABLES */
int a[1 + NUM/32] = { 0 }; /* define an arry and initialize every element */

/* INTERNAL FUNCTIONS */
void setbit(int n) {
    /* find the array member of bit n, and set flag */
    if (n > NUM){
        printf("too large\n");
        return ;
    }
    a[n >> SHIFT] |= 1 << (n & MASK); /* a[n/32] |= 1<<(n%32) */
}
int testbit(int n) {
    /* if the n bit exist, resturn 1 */
    return a[n >> SHIFT] & (1 << ( n & MASK));
}

void show_time() {
    time_t t = time(NULL);
    struct tm *mytm = localtime(&t);
    printf("%04d年%02d月%02d日 %02d:%02d:%02d t=%d\t", 
                mytm->tm_year+1900,    mytm->tm_mon+1, mytm->tm_mday, 
                    mytm->tm_hour, mytm->tm_min, mytm->tm_sec, (int)t);
}
/* IMPLEMENTATION */
int main() {
    /* open data.db and create file res.db to save the result of sorting */
    int fd1 = open("data.db", O_RDONLY);
    if (-1 == fd1) {
        perror("open");
        return -1;
    }

    /* read number of the file, and set flags */
    int i, n, res;
    show_time();
    printf("start to sorting %d nums...\n", NUM);
    for (i = 0; i <= NUM - 1; i++) {
        res = read(fd1, &n, sizeof(int));
        if (res == -1) {
            perror("read");
            return -1;
        } else if (res == 0) {
            break;
        }
        setbit(n); /* set flags */
    }

    /* traversal the array and write every element to res.db */
    int fd2 = open("res.db", O_RDWR | O_CREAT | O_TRUNC, 0664);
    if (-1 == fd2) {
        perror("open");
        return -1;
    }

    printf("writing to file...\n");
    for (i = 0; i <= NUM -1; i++) {
        if (testbit(i)) {
            write(fd2, &i, sizeof(int));
            //printf("%d\t", i);
        }
    }
    show_time();
    printf("sorting over!\n");

    close(fd1);
    close(fd2);
    return 0;
}
```

```
gcc generate.c -o generate
gcc sort.c -o sort
```
然后分别运行generate可以生成10000000个数字,sort可以完成排序

算法是没有固定的,就好比是说飞机快还是汽车快,要看应用场景;
算法要靠平时慢慢的积累;


Unix/Linux操作系统下C的开发主要讲述Unix系统的原理和机制/提供的系统函数
# 概要
+ Unix/Linux的静态库和共享库
+ 标C的错误处理(UC也适用)
+ Unix/Linux的内存管理
+ Unix/Linux的文件/目录操作
+ Unix/Linux的进程管理
+ Unix/Linux的信号机制
+ Unix/Linux的进程间通信(IPC)
+ Unix/Linux的网络编程
+ Unix/Linux的多线程编程 

Unix操作系统是美国AT&T公司于1971年在PDP-11上运行的操作系统;具有多用户多任务的特点,支持多种处理器架构,最早于1969年在AT&T的贝尔实验室开发;
贝尔实验室还研发了C语言;

> 1. 标准 行业的准则,所有的公司必须遵守; 
> 2. 产品 产品是以质量为主的软件,按照大多数用户的需求设计,而不是迎合某些特定客户的; 
> 3. 项目 针对特定的客户,受特定客户的控制;

# Unix的三大派生版本
1. System V: AIX / Solaris / HP-UX / IRIX
2. Berkley:  FreeBSD / NetBSD / OpenBSD / Mac OS X
3. Hybrid:   Minix(Mini Unix迷你版类Unix) / Linux

# Linux版本
+ Linux,全称GNU/Linux,是一种免费使用和自由传播的类UNIX操作系统;内核由 Linus Benedict Torvalds 于1991年10月5日首次发布;
+ Linux操作系统的诞生/发展和成长过程始终依赖着五个重要支柱:Unix操作系统,MINIX操作系统,GNU计划,POSIX标准和Internet网络;
+ Linux是一种自由和开放源代码的类Unix系统; Tux(一只企鹅,全称为tuxedo)是Linux的标志;
+ Linux和GNU结合做成了完整的操作系统,通过POSIX规范(标准)实现了和Unix系统的完美兼容,通过GNU通用许可协议GPL解决了版权的问题; 
+ GNU发起开始于1984年,由自由软件基金支持;GNU的基本原则是共享;
+ GNU的主旨在于发展一个类Unix,并且为自由软件的完整操作系统,GNU系统;
+ GNU提供shell和界面;
+ POSIX是由IEEE和ISO/IEC开发的一簇标准;该标准是基于现有的Unix实践和经验,描述了操作系统的调用服务接口,用于保证编制的应用程序可以在源代码一级上在多个操作系统上移植运行;
+ 非版权copyleft,带有标准的copyleft声明,确认作者的所有权和标志;它声明,任何人不但可以自由分发该成果,还可以自由地修改它,但你不能声明你做了原始的工作,或声明是由他人做的;最终,所有派生的成果必须遵循这一条款;

## Linux特点
+ 遵循GNU/GPL协议;
+ 开放性;
+ 多用户;
+ 多任务;
+ 设备独立性;
+ 提供了丰富的网络功能;
+ 可靠的系统安全;
+ 良好的可移植性;

## Linux常用发行版
+ 大众的Ubuntu
+ 锐意的Fedora
+ 老牌的RedHat/CentOS(Rocky)
+ 优雅的LinuxMint
+ 华丽的OpenSUSE
+ 稳健的OpenEuler
+ 自由的Debian
+ 简洁的Slackware
+ 本土化的RedFlag-Linux

# GCC的选项和用法
+ -E 预处理,把预处理指令(以#开头的指令)处理掉
+ -S 生成汇编文件(.s文件)
+ -c 只编译不进行连接(不生成a.out)
+ -o 改变目标文件的名称
+ -O 可以优化
+ -g 生成调试信息
+ -v 查看gcc的版本
+ -Wall (Warning all)可以生成更多的警告信息,代码更规范; 
+ -Werror 在所有产生警告的地方作为错误处理,停止编译;
+ -L 指定连接库目录
+ -l 指定连接库名
+ -I 指定头文件路径

计算机语言分为 机器语言,汇编语言和高级语言; 

## GCC编译过程可以细分为4个阶段
1. 预处理Pre-Processing;宏展开等,可以生成.i文件
> gcc -E hello.c -o hello.i
>> 带-o选项可以把输出到屏幕改为文件;
2. 编译Compiling(狭义的编译);进行语法分析,转换成汇编语言,生成.s文件
> gcc -S hello.i
>> 生成hello.s
3. 汇编Assembling;把汇编语言代码转换成目标代码,生成.o文件
> gcc -c hello.s
>> 生成hello.o
4. 连接Linking;连接器ld将as创建的目标文件转换为可执行文件,生成a.out文件
> gcc hello.o

参考代码
```
/* hello.c */
#include <stdio.h>
int main() {
    printf("Hello Unix C\n");
    /* return 0; */
}
```

gcc hello.c -Wall -Werror 可以生成更多的警告信息;

## 与C语言相关的文件名后缀
    .a    //静态对象库
    .c    //需要预处理的C语言源代码
    .h    //C语言源代码头文件
    .i    //不需要预处理的C语言源代码
    .o    //目标文件
    .s    //汇编语言代码
    .so   //共享对象库

## 指定编译文件类型
    -x指定编译代码类型:c/c++/assembler/none;
    gcc -x c -Wall -0 main hello.c
    如果是none,会根据扩展名自动确认;

## 关于头文件.h和源文件.c
    各种声明一般都写在.h头文件中,各种实现都写在.c源文件中; 
    头文件的作用是给其他文件调用源文件时使用的; 

C语言中,头文件一般放
* 变量的声明(赋值不行,赋值就属于定义要写在源文件中)
* 函数的声明(实现不行)
* 结构的声明
* 宏的定义

# 常见的预处理指令
    #include <文件名>
    #include "文件名"
        将指定的文件插入到#include的位置; 尖括号先找系统;双引号先找当前位置,再找系统;
    #define 宏 定义
        定义宏变量或宏函数;
    #undef 宏
        删除宏;
    #if/elif/else/endif/ifdef/ifndef/
        条件编译;
    #error 提示信息
        产生错误,挂起预处理程序; 注:#error一旦产生错误,编译失败; 
    #warning 提示信息
        创建一个警告;
    #pragma
        提供额外信息的标准方法,可以用来指定平台;增加额外功能;
    #pragma GCC dependency 文件名a
        比较当前文件和文件a的最后修改时间,如果当前文件是最近修改的就没问题,否则产生一个警告; 
    #pragma GCC poison 标识符
        poison后面的标识符将被定为毒药,禁止继续使用,否则引发错误; 
    #pragma pack(整数)
        pack(n)可以指定结构的对齐和补齐的字节数n; 
    #pragma pack(push,1)
    #pragma pack(pop)
        配合使用可以临时设置pack
    #
        转化为字符串,#define STR(x) #x
    ##
        连接操作符号,用于宏内连接两个字符串;#define _CONCAT_(a, b) a##b

参考代码
```
/*
 * 预处理指令演示
 */
#include <stdio.h>    //C编译器比较宽松

#define VERSION 4
#if (VERSION < 3)
    #error "版本过低" //停止编译
#elif (VERSION > 3)
    #warning "版本较高" //可以不用双引号,此时中间不可有空格;
#endif

#pragma GCC dependency "01hello.c"
#pragma GCC poison goto
#pragma pack(2)            //pack(1)是取消对齐和补齐

int main() {
    //goto ok; //goto被限制使用
ok:    printf("over\n");    //ok就是这个语句的标签
    struct s {
        char c1; //1
        int i;   //4
        char c2; //1
    };

    printf("sizeof(struct) = %d\n", sizeof(struct s));
    // pack(1)时结果为6
    // pack(2)时结果为8
    // pack(4)时结果为12
    return 0;
}
```

> #if宏与if语句的区别是: #if宏是有条件的编译,if语句是有条件的执行;

# 环境变量
    操作系统在启动时会把一些常用的参数预先加载到内存中,这就是环境变量;
    Linux命令可以直接使用而不需要加上路径,是因为开机启动时所在路径已经被加载到PATH环境变量了;
    比如
    运行可执行文件默认是要带路径的,但如果把它的路径配置在环境变量PATH中,就可以不带路径在任意目录下直接用文件名启动; //有利有弊
    我们执行程序是使用./a.out是因为./是路径,如果把当前目录配置在PATH环境变量中,就可以不带路径直接执行;
    linux环境变量的路径之间使用冒号分割;

windows中的环境变量在[我的电脑]右击,[属性]->[高级]->环境变量;找到Path,编辑变量名和变量值;
windows环境变量的路径之间用分号分割;

## shell分为sh,csh,bash等
    在终端输入sh回车就进入sh环境,方向键都不能正常使用了,这是原始版本;
    如果安装了csh并进入csh环境时,提示符将变成%
    bash的提示符默认是$,超级用户是#

## a.out直接运行的方法(bash版)
    export PATH=$PATH:. #使原来的PATH加上当前目录后再赋值给PATH变量;
    export是对外导出,可以在加载它的进程的所有子进程中使用;
    $PATH就是之前的所有的PATH的值
    :是Unix系统的路径分隔符,Windows用;号
    .代表当前目录
    注意=的两边都不要留空格,bash语法决定;
    只对当前窗口有效,如果想开机就有效,要把这个写入配置文件; 
> 需要去登录目录下找 .bashrc 文件,并把 export PATH=$PATH:. 写在 .bashrc 最下面即可; 
    cd 直接回车就到了登录目录; cd -就又回到之前的目录$OLDPWD;
    如果希望立即生效需要source .bashrc重新加载一下; 

    如果修改错误了, whereis vi #查看vi在哪个目录下
    /usr/bin/vi  .bashrc #将PATH改对了就可以了; 

## 改变终端提示符
    export PS1='[\W]$'
    export PS1='[\w]$'

程序员就应该会一些别人做不到的技能^_^;

# C语言的环境变量
    C_INCLUDE_PATH       查找C头文件的目录;
    CPLUS_INCLUDE_PATH   查找C++头文件的目录;
    CPATH                查找C语言头文件,相当于-I选项;
    LIBRARY_PATH         编译时连接文件(静态库和共享库)路径,相当于-L选项;
    LD_LIBRARY_PATH      运行时定位共享库路径,编译时没影响;

## 程序员自定义的头文件的几种查找方法
1. 在""中放入路径,比如: "./day01/xx.h";便于代码移植;
2. 把.h头文件所在目录配置到环境变量CPATH中;
3. 编译连接时用gcc -I 头文件所在目录 

## 静态库链接时搜索路径顺序
1. GCC命令参数-L指定的库目录
2. 环境变量LIBRARY_PATH指定的路径
3. 再找内定目录 /lib /usr/lib /usr/local/lib 这是当初compile gcc时写在程序内的

## 动态库连接时搜索路径顺序
1. 编译目标代码时-L指定的路径或-Wl,-rpath指定的路径
2. 环境变量LIBRARY_PATH指定的路径
3. /etc/ld.so.cache中缓存的动态库路径,可通过修改配置文件/etc/ld.so.conf增删路径,修改后需root运行ldconfig命令使修改生效;
4. 默认的动态库搜索路径/lib
5. 默认的动态库搜索路径/usr/lib

## 执行时动态库搜索路径顺序
1. 编译目标代码时-Wl,-rpath指定的路径
2. 环境变量LD_LIBRARY_PATH指定的路径
3. /etc/ld.so.cache中缓存的动态库路径,可通过修改配置文件/etc/ld.so.conf增删路径,修改后需root运行ldconfig命令使修改生效;
4. 默认的动态库搜索路径/lib
5. 默认的动态库搜索路径/usr/lib

+ ldd命令可以查看可执行文件依赖那些动态库;
+ ldconfig用来使/etc/ld.so.conf的修改生效;
+ nm用来查看.so库中的函数名字,标记是T的就是动态库里面生成的名字;

```
/*
 * add.h
 */
#ifndef _ADD_H__ //防止头文件的重复include
#define _ADD_H__
int add1(int a, int b);
double add2(double a, double b);
#endif //练习:写add.c实现两个函数,不要主函数
```

```
/*
 * add.c
 * 如果在这个文件中的函数不会调用其他函数,
 * 就不需要添加add.h头文件;
 */
int add1(int a, int b) {
  return a+b;
}
double add2(double a, double b) {
  return a+b;
}
```

```
/*
 * test.c
 */
#include <stdio.h>
#include "./head_dir/add.h"
/*
 * #include <add.h>
 * //需要在编译时用gcc -I head_dir
 * //或者export CPATH=head_dir
 */

int main(){
    int       r1 = add1(2, 3);
    double    r2 = add2(2.1, 3.1);
    printf("%d, %lf\n", r1, r2);
    return 0;
}
```

编译时用gcc test.c add.c

编译时找不到头文件叫:致命错误;
PATH是用来配置系统环境变量的,主要服务于系统的命令;
CPATH用于C语言编译时寻找C语言头文件;

当你还不是项目经理的时候,如果没有绝对把握,干好自己的任务再默默的去干自己的事就行了;不要急于去表现;
这个时候可以多想多问多观察,但不一定要多干;

