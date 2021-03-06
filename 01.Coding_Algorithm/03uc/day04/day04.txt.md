Unix内存管理




# 堆内存的管理
> 程序员全权负责

## malloc()和free()
C程序员分配和回收内存的工具;

malloc()在Unix系统中一次映射33个内存页,如果申请的内存比较大(达到32个内存页),系统会映射出比用户申请的内存稍大的内存页数;牺牲空间换时间;
```
int *pi = malloc(4);//malloc(16);
free(pi);//free()如何知道释放多少空间呢
```
malloc()函数除了分配内存之外还需要额外保存一些附加数据(比如分配的大小),附加数据由底层的双向链表维护;中间还会有一些空;但附加数据的存在不会影响内存的正常使用,只是会占用一些内存空间罢了;
free()一定会释放虚拟内存地址,但不一定解除对物理内存的映射;用了malloc()最后33个内存页free()不会解除映射,等到进程结束才解除映射;

```
/*
 * malloc()函数演示
 */
#include <stdlib.h>
#include <stdio.h>
//我的老师有一个很富有的亲戚;
int main() {
    int a, b, c;        //系统自动分配和回收(栈区)
    printf("[Stack] a: %p, b: %p, c: %p\n", &a, &b, &c);
    int *p1 = malloc(4);    //有附加数据存在
    int *p2 = malloc(4);    //因此不挨着
    int *p3 = malloc(4);    //只分配地址,不再做映射
    printf("[malloc] p1 = %p, p2 = %p, p3 = %p\n", p1, p2, p3);
    printf("*(p1-1): 0x%x\n", *(p1-1));
    // *(p1+100) = 10; //已映射33个内存页,可以存放数据,但不安全
    // printf("%d\n", *(p1+100)); //不受保护
    // *(p1-1)= 0; //清理附加数据,所以malloc()不能越界,否则附加数据可能被破坏;
    free(p1);        //只释放了虚拟内存地址,不一定解除内存映射;
    free(p2);
    free(p3);
    printf("PID = %d\n", getpid());
    *p1 = 100; //内存页没有被释放掉
    printf("%d\n", *p1);    //100
    while (1);        //死循环
    return 0;
}
```

> 学习跟打怪升级是一个道理,行动最重要;动手是关键;
没有做过一个完整的项目,就不是一个程序员,最多是一个准程序员;

结论
+ malloc()负责分配堆内存,需要多少就申请多少,比较大的内存申请最好申请4k的整数倍;
+ malloc()分配的内存不要越界,否则会破坏附加数据;
+ malloc()和free()一定要配对使用;

## sbrk()和brk()
    Unix的系统函数(依托于Unix系统);
    sbrk()和brk()依赖于底层维护的一个位置addr来实现内存的管理;
```
void *sbrk(intptr_t increment);
```
+ 参数increment是分配/回收内存的大小(字节);
    如果是正数,就是分配内存;
    如果是负数,就是回收内存;
    如果是0不分配也不回收内存,取当前的位置;
返回改变(移动)之前的位置;负数的返回值是没有实用意义的;
如sbrk(4)分配内存,返回分配之前的初始位置;
    sbrk()函数映射内存时以页为单位,按需映射内存页;
    回收时立即释放内存并解除映射;

```
/*
 * sbrk()函数演示
 */
#include <stdio.h>
#include <unistd.h>
int main() {
    void *p1 = sbrk(4);    //分配了4个字节的内存;映射了一个内存页
    void *p2 = sbrk(4);    //地址是挨着的,与malloc()不同
    void *p3 = sbrk(4);
    int *p4 = sbrk(4); //不用强制类型转换也没有警告;
    printf("p1: %p, p2; %p, p3; %p, p4; %p\n", p1, p2, p3, p4);
    *p4 = 100;
    sbrk(-4);        //释放4个字节
    sbrk(-8);        //释放8个字节,不清理(擦除)内存中的数据;
    void *p5 = sbrk(0);    //p5在04的位置;
    printf("p5 = %p\n", p5);
    printf("p4 = %d\n", *p4);    //数据没有被清理;
    printf("PID = %d\n", getpid());
    p5 = sbrk(4093);    //4+4093=4096+1;正好过一页,增加一页
    sleep(10);
    printf("退回一页\n");
    sbrk(-1);        //立即释放内存并解除映射(退页)
    sleep(10);
    printf("全部退回\n");
    sbrk(-4096);        //释放内存并解除映射
    while (1) ;
    return 0;
}
```

sbrk()虽然同时具备分配和回收内存的能力,但是回收内存不方便;因此brk()负责回收内存;
编程时一般使用sbrk()分配内存,使用brk()回收内存;
    int brk(void *newaddr);    //直接把新的位置传进来(参数);
    成功返回0,失败返回-1;可以使用perror();
brk()的使用离不开sbrk(),至少需要使用sbrk()取得当前位置;

```
/*
 * brk()函数演示
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main() {
    void *p = sbrk(0);    //先取得位置;
    brk(p + 4);        //分配了4个字节的内存;
    brk(p + 8);        //再次分配4个字节;
    brk(p + 4);        //回收了4个字节;
    int *pi = p;        //放入一个int/double/char*
    *pi = 100;

    double *pd = sbrk(0);
    brk(pd + 1);        //指针加1;注意指针的运算
    *pd = 12000.0;

    char *pc = sbrk(0);
    brk(pc + 10);
    //pc = "zhangfei"; //改变了地址,丢失原来内存的地址,内存泄漏
    strcpy(pc, "zhangfei");
    printf("%d, %lg, %s\n", *pi, *pd, pc);

    brk(pc);        //释放字符串所在内存
    brk(pd);
    brk(pi);
    return 0;
}
```

练习
    参考brk.c的代码,重新编写一个brksbrk.c,存入一个 int/double/char*
    但使用sbrk()分配内存,使用brk()回收内存,思考如何更简练;

```
/*
 * sbrk()/brk()
 * 使用sbrk()分配内存,brk()回收内存
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main() {
    /* 分配内存用sbrk()更方便; */
    void *p = sbrk(4);    //void *p = sbrk(0); brk(p + 4);
    int *pi = p;
    *pi = 100;

    double *pd = sbrk(8);
    *pd = 12000.0;
    char *pc = sbrk(10);
    strcpy(pc, "zhangfei");
    printf("%d, %lg, %s\n", *pi, *pd, pc);
    printf("pi = %p, pd = %p, pc = %p\n", pi, pd, pc);
    printf("PID = %d\n", getpid());
    printf("10s后释放内存\n");
    sleep(10);

    /* 释放用brk()方便; */
    brk(p);
    return 0;
}
```

## mmap()和munmap()
用于内存映射/解除映射
    mmap()可以映射物理内存/文件,
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
int munmap(void *addr, size_t length);
    100//读权限
    010//写权限
    001//执行权限
二进制的位运算:位与,位或,位反,位异或;

位或|运算可以拼接权限;
    1|1 = 1
    1|0 = 1
    0|1 = 1
    0|0 = 0

位或运算可以用于拼接权限/选项;
前提条件是选项/权限做成只有一个二进制位是1,不会出现覆盖的情况;

```
/*
 * mmap()函数演示
 */
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>

int main() {
    void *p = mmap(0, //首地址由内核指定
               4, //映射内存的大小,不足一页会补足一页
               PROT_READ | PROT_WRITE, //权限,一般是读写
               MAP_ANONYMOUS | /* 映射物理内存必选项 */
               MAP_PRIVATE,    /* MAP_SHARED */ //SHARED用于文件
               //MAP_PRIVATE文件内存都可以用,区别是其他进程是否可以操作
               0, 0); //最后两个参数映射文件时才用;

    if (p == MAP_FAILED) { //出错了
        perror("mmap");
        return -1;
    }
    int *pi = p;
    *pi = 100;
    //*(pi+100) = 200;printf("%d\n", *(pi+100));//说明内存映射一页
    munmap(p, 4);        //解除映射
    return 0;
}
```

如果考虑通用性,分配内存使用malloc()和free(),想自定义内存管理方式可以使用Unix的系统函数;

系统调用(system call)
    因为用户层不能直接访问内核层,而很多功能必须由内核提供和管理,所以必须有一种方式能进入内核层;
    Unix系统定义了一系列的函数用于进入内核层完成功能,这一系列函数统称为系统调用;
    系统调用可以被标准C函数使用,也可以被程序员直接调用;
    比如malloc()是标C函数,sbrk()/mmap()就是系统调用函数;

