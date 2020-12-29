库 错误处理


# 回顾
* PATH用于配置可执行文件; 每个环境变量有他自己的适用场合;
* 对齐和补齐的作用是便于寻址
* 对于计算机底层来说一切皆01; 对于C语言来说一切皆整数;
```
unsigned int i = -1;//本赋值没有问题,类型是标识给我们看到
printf("%u, %d\n", i, i);//打印出来的会不同,因为解析不同,但面对的是同一个东西;
```

# 静态库和共享库;
windows下的dll即是动态链接库dinamic linked library;Linux中叫共享库shared object;
企业开发经常会把程序打包成一个库文件,进行整合和管理;

库分为静态库和共享库(又称动态库);是.o文件的打包;
1. "静态库"是代码的归档,在编译连接时会"复制"这段代码到目标文件中;
    //优点是独立,连接完成后就不再需要静态库,而且速度会稍快;
    //缺点是可执行文件占用空间较大,更新和维护不方便;
2. "共享库"在编译连接时会把代码的"地址"放入目标文件中;
    //优点是可执行文件占用空间较小,更新和维护方便;
    //缺点是在程序运行时必须保证能找到共享库,速度稍慢;
> 企业开发中主流使用共享库(维护方便,占用空间小);

默认情况下,GCC在链接时优先使用动态链接库,只有当动态链接库不存在时才考虑使用静态链接库;
gcc的-static选项可以强制使用静态库连接到可执行文件;
> gcc -static 01hello.c -o b.out
使用静态库生成b.out;生成的文件会比较大;

```
如果gcc -static 01hello.c报错
    /usr/bin/ld: cannot find -lc
    collect2: ld returned 1 exit status
请首先安装glibc-static;

由于在配置的过程中误删了libc.so导致编译无法进行
    /usr/lib/gcc/i686-redhat-linux/4.4.7/../../../crt1.o: In function `_start':
    (.text+0xc): undefined reference to `__libc_csu_fini'
    /usr/lib/gcc/i686-redhat-linux/4.4.7/../../../crt1.o: In function `_start':
    (.text+0x11): undefined reference to `__libc_csu_init'
    collect2: ld returned 1 exit status
然后拷贝了libc.so到/lib目录;/lib/libc.so的内容如下

/* GNU ld script
   Use the shared library, but some functions are only in
   the static library, so try that secondarily.  */
OUTPUT_FORMAT(elf32-littlearm)
GROUP ( /lib/libc.so.6 /usr/lib/libc_nonshared.a  AS_NEEDED ( /lib/ld-linux.so.3 ) )

结果还是无法编译;于是又执行yum install glibc*和yum reinstall glibc*
问题得以解决;
在设置系统环境的时候一定要小心谨慎,先做好备份,不要轻易删除文件;
```

# 静态库的创建步骤
1. 编写源文件02add.c;
2. 编译源文件,生成目标文件(.o);
    gcc -c 02add.c
3. 打包.o文件生成静态库文件.a;
    ar -r libmylib.a  02add.o //本命令可以创建库文件;
> 静态库文件名的命名规范:以lib开头,以.a结尾,中间为库名;
    ar -r lib库名.a 所有的.o文件

# 静态库的使用步骤
1. 编写应用程序02test.c;
2. 编译02test.c,生成目标文件(不连接);
    gcc -c 02test.c
3. 连接静态库文件和02test.o,有三种方法
    1. 直接连接 不是很专业
        gcc 02test.o libmyku.a
    2. 小l连接法 需要配置环境变量LIBRARY_PATH,导出库所在目录
        export LIBRARY_PATH=. #当前目录;
        gcc 02test.o -lmylib
    3. 双L连接法 重点推荐 gcc 02test.o -l库名 -L库目录
        gcc 02test.o -lmylib -L.
    > 注意:链接库参数要放在命令的后面,而且越基础的越靠后,如果libB又依赖libA则按-lB -lA顺序;
> 注意:编写企业代码,需要提供一个库文件和一个头文件出去;

# 共享库的创建步骤
1. 编写源文件03add.c;
2. 编译生成目标文件.o; -fPIC不写也是可以的,但不规范;
    Position-Independent Code,与位置无关的代码,没有绝对地址,全部使用相对地址,使用-fPIC可以使得动态库可以被多个程序共享;
    -fpic为了节约内存,在GOT里面预留了“短”长度,为了兼容各个系统,在生成位置无关的代码的时候,应该使用-fPIC参数;
    gcc -c -fPIC 03add.c
3. 生成共享库文件.so
    gcc -shared 03add.o -o libmyku.so
    //共享库的库文件名和静态库一样,有规范,区别就是以.so做后缀
    //有些系统的共享库后缀是.so.整数;

# 共享库的使用步骤
    和静态库的使用步骤一样;
    共享库不可以直接运行但可以参与运行;
    在运行时必须配置环境变量LD_LIBRARY_PATH;export LD_LIBRARY_PATH=. //配置运行时的环境变量;

共享库在使用时必须要保证能查找得到;
如果找不到,需要配置LD_LIBRARY_PATH然后就可以查找的到;

ldd命令可以查看依赖哪些库;
ldd a.out命令可以查看相关的共享库文件

# 动态链接加载器接口
系统提供了一套API(应用程序编程接口,就是各种函数)可以直接打开共享库文件;
需要包含头文件 dlfcn.h
连接时需要加上-ldl选项;
```
    dlopen()    打开库文件 void * dlopen(const char* pathName, int mode);
    dlsym()     从打开的库文件中得到函数 void *dlsym(void *handle, const char *symbol);
    dlclose()   关闭 int dlclose(void *handle);
    dlerror()   判断是否出错 char *dlerror(void);
```

举例
```
#include <stdio.h>
#include <dlfcn.h>

typedef int(*FUNC_ADD)(int, int);

int dl_loader_api_test() {
    void* handle = dlopen("./libmyku.so", RTLD_LAZY);
    if (NULL == handle) {
        printf("ERROR: %s\n", dlerror());
        return -1;
    }
    do {
        FUNC_ADD pfunc_add = (FUNC_ADD)dlsym(handle, "add");
        printf("1+2= %d\n", pfunc_add(1, 2));
    } while (0);
    dlclose(handle);

    return 0;
}

int main() {
    return dl_loader_api_test();
}

```
gcc -ldl test.c #编译错误,找不到符号表
gcc test.c -ldl #编译成功,连接库参数要放在后面

# 程序员的错误处理
编程要把正确的搞定,也要把错误的搞定,还要防止别人有意无意的破坏;

主流的编程语言(除了C语言外)基本都使用异常机制处理错误,C语言中没有异常机制;

C程序员用返回值代表是否出错,如果出错了,可以借助errno和perror()/strerror()进行错误的识别和处理. 
返回值有4种情况:
1. 如果返回int,并且返回的正常数据非负数;可以返回-1代表出错,正常数据直接返回;
2. 如果返回int,并且返回的正常数据可能是负数;可以返回-1代表出错,0代表没错,正常数据用指针传递;
3. 如果返回指针,用 NULL 代表出错, 其他代表正常;
4. 如果不需要考虑错误问题,可以用 void 型函数,无返回值;
> 注意
    以上4种情况只是经验之谈,大多如此;但不是绝对的;
    如有时返回指针不用NULL而用-1表示出错((void*)-1))也是可以的;

一个函数影响外部数据的方式有2种:
1. 用 return 语句返回值赋值;
2. 参数中传递指针形式做出参;

练习
```
有4个函数
a返回两个数的最大值,如果这两个数相等,返回错误; // 数据用指针传递,情况2
b返回0-10的随机数,如果随机数为0则函数返回错误; // 可以用-1表示出错,情况1
c传入一个字符串,如果传入的是"error",返回错误;否则返回原来函数的字符串; // 返回指针,情况3;
d打印一个传入的字符串; // 不需要返回值,也无须考虑错误,情况4;
```

```
/*
 * 错误处理演示
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/* 情况1,正常值非负,用-1表示出错 */
int ran10() {
    srand(time(0)); //设置种子防止伪随机
    int ra = rand() % 11;
    if (ra == 0) {
        return -1;
    }
    return ra; //返回-1代表出错,数据正常返回;
}

/* 情况2,正常值也有负数,返回0表示正常,数据用指针传出 */
int max(int num1, int num2, int *pi) {
    if (num1 == num2) {
        return -1;    //相等则返回
    }
    *pi = (num1 > num2) ? num1 : num2;
    return 0; //0代表没有出错,数据存在*pi中
}

/* 情况3,返回值是指针类型,返回NULL代表出错,其他值直接返回 */
char *iserror(char *str) {
    if (!strcmp(str, "error")) {
        return NULL; //返回NULL代表错误
    }
    return str; //返回指针
}

/* 情况4,不需要考虑出错问题,用void型函数; */
void print(char *str) {
    printf("%s\n", str);
}

int main() {
    int num = 0;
    int r = 0;

    //case 1; -1 error, other ok
    r = ran10();
    if (r == -1) {
        printf("ran error \n");
    } else {
        printf("r = %d\n", ran10());
    }

    //case 2; -1 error, other ok, outvalue with pointer
    r = max(-1, -2, &num);
    if (r == -1) {
        printf("error !\n");
    } else {
        printf("r = %d, max = %d\n", r, num);
    }

    //case 3; NULL error, other ok
    char *s = iserror("ok");
    if (s == NULL) {
        printf("iserror error !\n");
    } else {
        printf("%s\n", s);
    }

    //case 4; ignore error
    print(s);

    return 0;
}
```

C语言用外部的全局变量errno(error number)记录错误信息;
    错误信息包括错误编号(int)和具体信息(字符串);
    errno存储的是错误编号; 错误编号与具体信息有映射关系;

函数strerror()/perror()/printf("%m\n")用于错误信息的显示和转换;
```
char *strerror(int errnum)    传入一个编号,返回具体信息(转换函数);
void perror(const char *s)    不用传入错误编号,直接打印errno对应的信息(会自动换行);
printf("%m\n")                直接打印errno对应的信息;
```
    不是所有的函数都使用errno处理错误,比如线程的函数;

man strerror 命令查看strerror的帮助信息

errno只有在出错时才会改变值,不出错也不会恢复值;
> errno只能说明出过什么错,而不能据此判断当前步骤是否出错;
>> 若判断当前步骤是否出错要使用函数的返回值; 确定出错以后再使用errno判断出了什么错;

```
/*
 * perror()使用示例
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
int main() {
    FILE *file = fopen("/etc/passwd1", "r");
    if (file == NULL) {    //判断是否出错
        printf("[%d] %s\n", errno, strerror(errno));
        perror("fopen 出错了");
        //perror()会打印"参数: 错误信息"自动换行
        //其中参数就是传给perror()的参数;
        //函数出错基本都是使用perror(),线程一般不用perror()
        printf("%m\n");
    } else {
        fclose(file);
    }
    file = NULL;    //如果确保file不再使用可以省略;
    return 0;
}
```

# 在Linux中获取指令的帮助信息
man命令可以查看命令/函数和头文件等的帮助信息;
如果man命令显示的不是英文,可以首先执行,export LANG="en";
可以安装翻译软件goldendict

使用举例
```
man string.h
    使用空格或Page Down翻页,也可使用上下键滚屏
    在结果中可以使用搜索,n下一个,N上一个
    q退出
```

```
man 3 printf    //查看C库函数
    3表示的是man查找帮助的来源,可分为以下8种;
    首先要查看概述,尤其注意其中的头文件和函数原型,参数类型,返回值类型;
    然后查看描述信息,可以简要了解函数的功能;
    最后还要看函数的返回值的意义;
```

```
man find
    查找系统命令的帮助信息;
    首先看name,了解命令的基本功能;
    然后看概述,了解命令的使用形式;
    然后再看描述,了解其具体功能;
    然后还要看选项信息,了解各选项的意义;
    如果可能还可以看一些使用范例;
```

不需要记住帮助信息,只需要明白使用的有价值的信息即可,用的多的自然就会记住常用的;
```
man man
The standard sections of the manual include
   1   User Commands //用户命令
   2   System Calls  //系统命令
   3   C Library Functions //C库函数
   4   Devices and Special Files    //设备和特设文件
   5   File Formats and Conventions //文件格式与转换
   6   Games et. Al.  //游戏等
   7   Miscellanea    //杂集
   8   System Administration tools and Deamons //系统管理工具
```

# 指针的回顾
```
指针就是一个存储另一个变量地址的变量;
    int i = 10;
    int *pi = &i;
pi就是指针,i就是普通整型变量;
    *pi == i
    &i == pi

指针的运算
    支持加法和减法,但加法只能加上整数;
pi + 1 就是移动指针, 移动的字节数由指向变量的类型决定;
    如果pi是 int *, 移动4个字节;
    如果是 char *, 移动1个字节;
    如果pi是 char **, 移动 char*的大小,即4个字节;
    sizeof(指向的类型);

    *p++      先做p++再取*;但后++会在语句结束时才做;
    (*p)++    先取*再++;
    如果 char** p, (*p)++导致*p移动一个字节,p不动;
```

char *str[5];   //指针数组,存放指针的数组(char *)str[5];
char (*str)[5]; //数组指针,指向数组的指针;

一定要多练


# 总结
1. 如何创建共享库
    * 编写代码;
    * 编译代码,获得目标文件(-fpic);
    *  gcc -shared -o 对目标文件进行连接,得到库文件;

2. 如何调用共享库
    * 编写代码;
    * 编译测试代码,得到目标文件;
    * 连接代码和共享库; 双L连接法: gcc src.c -l库名 -L库目录

3. C语言错误处理
C程序员用返回值代表是否出错,如果出错了,可以借助errno和perror()/strerror()进行错误的识别和处理. 
    返回值有4种情况:
    1. 如果返回int,并且返回的正常数据非负数;可以返回-1代表出错,正常数据直接返回;
    2. 如果返回int,并且返回的正常数据可能是负数;可以返回-1代表出错,0代表没错,正常数据用指针传递;
    3. 如果返回指针,用 NULL 代表出错, 其他代表正常;
    4. 如果不需要考虑错误问题,可以用 void 型函数,无返回值;

