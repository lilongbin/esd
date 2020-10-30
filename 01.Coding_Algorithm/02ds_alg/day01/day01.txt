数据结构
逻辑结构
物理结构
栈

数据结构是对数据类型(存储方式)和数据之间相互关系的描述;
算法是对操作步骤的描述;

数据结构研究如何使用内存中的多个存储位置记录多个相关数据以及如何使用这些数据;
算法研究一些通用问题的解决方法和步骤(算法通常需要依赖某种数据结构); 

数据结构重点关注数据之间的关系; 
数据的逻辑结构描述了人对数据之间关系的看法和认识,这个结构和计算机硬件无关; 
数据的物理结构描述了计算机中存储位置之间的物理关系; 

逻辑结构分为
    集合结构    结构中的数据元素同属一个集合,无其他任何关系;
    线性结构    结构中的数据元素之间存在这一对一的线性关系;
    树状结构    结构中的数据元素之间存在这一对多的层次关系;
    网状结构    结构中的数据元素之间存在这多对多的任意关系;

物理结构分类

1-> 顺序结构
所有存储位置在计算机中连续排列(如数组和动态分配的存储位置);
    顺序结构中任何一个存储位置可以用一个编号表示,所以这种物理结构支持随机访问(任何一个存储位置都是可以直接拿到的); 
    插入/删除数据非常浪费时间;
    顺序结构一旦存在很难调整大小,所以很容易造成存储位置的浪费;
/*
 * 链式物理结构演示
 */
#include <stdio.h>
typedef struct node {
    int num;
    struct node *p_next;    //结构体指针才能指向结构体
} node;
int main() {
    node head = { }, fst = { }, sec = { }, thd = { };
    node end = { };
    node *p_node = NULL;
    head.p_next = &fst;    //虚构head头节点,只用一个指针变量
    fst.num = 1;
    fst.p_next = &sec;
    sec.num = 3;
    sec.p_next = &thd;
    thd.num = 5;
    thd.p_next = NULL;
    end.num = 7;        //追加新数据
    end.p_next = NULL;

    /* 查找最后一个有效数据所在节点 */
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (!(p_node->p_next)) {
            /* 挂接在最后一个有效节点下面成为新的有效节点; */
            p_node->p_next = &end;
            break;    //否则会无法结束,不断的添加新的节点
        }
    }

    /* 循环打印出所有有效节点内容 */
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (p_node->p_next) {
            printf("%d ", p_node->p_next->num);
        }
    }
    printf("\n");

    /* 摘掉最后一个节点 */
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (p_node->p_next && !(p_node->p_next->p_next)) {
            p_node->p_next = NULL;
        }
    }

    /* 摘除一节点 */
    if (head.p_next) {
        head.p_next = head.p_next->p_next;
    }

    /* 插入新的一节点 */
    end.p_next = head.p_next;    //先把头节点中的数据交接给新节点
    head.p_next = &end;    //头节点指向新的节点

    /* 列印 */
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (p_node->p_next) {
            printf("%d ", p_node->p_next->num);
        }
    }
    printf("\n");
    return 0;
}

2-> 链式结构
多个存储位置之间互相独立,任意两个存储位置之间可以使用指针连接;
    链式结构中每个存储位置叫一个节点;
单向线性链式存储结构中任何一个节点只可以导向另外一个点,可以从一个起点走导向任何一个节点;
    单向线性链式结构中每个节点需要包含一个指针,这个指针负责记录下一个节点的地址;
单向线性链式结构中最后一个节点里的指针必须记录 NULL;
可以在开头虚构一个头节点,头节点只作为起点使用而不记录有效数据; 

可以采用一个 for 循环完成对所有节点的处理;
for 循环格式如下
for (p_node = &head;//始于头节点
     p_node != NULL;
     p_node = p_node->p_next){//指向下一节点
    ......//对下一节点做处理;
}

链式存储结构中所有节点都应该是动态分配的;
/*
 * 动态分配节点的链式结构演示
 */
#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int num;
    struct node *p_next;
} node;
int main() {
    node head = { }, *p_node = NULL;
    int num = 0;
    printf("请输入一个整数:");
    scanf("%d", &num);
    /* 插入新的尾节点 */
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (!(p_node->p_next)) {
            p_node->p_next = (node *) malloc(sizeof(node));
            p_node->p_next->num = num;
            p_node->p_next->p_next = NULL;
            break;
        }
    }
    /* 打印所有节点内容 */
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (p_node->p_next) {
            printf("%d ", p_node->p_next->num);
        }
    }
    printf("\n");
    /* 删除一节点 */
    if (head.p_next) {
        node *p_tmp = head.p_next;
        head.p_next = head.p_next->p_next;
        free(p_tmp);    //释放一节点内存
        p_tmp = NULL;
    }
    return 0;
}

逻辑结构和物理结构的关系
    1-> 任何一个逻辑结构可以采用多种物理结构实现;
    2-> 一个物理结构也可以用来实现多种逻辑结构;

数据结构中除了存储位置以外通常要提供一组函数,这组函数实现对这些存储位置的常见操作;
    1-> 创建/销毁;
    2-> 插入/删除;
    3-> 获取/修改;
    4-> 排序/查找; 

数据结构举例
1.栈
    采用后进先出的方式管理内部数据;
    一端位置固定(固定端叫栈底,活动端叫栈顶),另外一端随着数据的进出随时改变位置;
基本操作函数: push ,pop
/*
 * 03stack.h
 */
#ifndef __03STACK_H__
#define __03STACK_H__
void init();
void deinit();
int full();
int empty();
void push(int);
int pop();
int last();
int size();
#endif //__03STACK_H__
/*
 * 顺序物理结构实现栈
 * 03stack.c
 */
#include "03stack.h"
static int stack[10];        //静态变量只能本文件可以使用
static int top;            //栈顶位置
/* 初始化 */
void init() {
    top = 0;
}

/* 清理函数 */
void deinit() {
    top = 0;
}

/* 判断栈是否已满 */
int full() {
    return top == 10;
}

/* 判断栈是否为空 */
int empty() {
    return !top;
}

/* 向栈中放置新数据的函数 */
void push(int num) {
    stack[top] = num;
    top++;
}

/* 从栈中取数据的函数 */
int pop() {
    top--;
    return stack[top];
}

/* 读栈中最新(最新)数据 */
int last() {
    return stack[top - 1];
}

/* 得到栈中有效数据个数的函数 */
int size() {
    return top;
}
/*
 * 栈的测试代码
 * 03main.c
 */
#include <stdio.h>
#include "3stack.h"
int main() {
    init();
    printf(empty()? "空的\n" : "非空\n");
    push(4);
    push(5);
    push(6);
    printf("有效数据个数为%d\n", size());
    printf("最后一个有效数据是%d\n", last());
    printf("%d\n", pop());
    printf("%d\n", pop());
    printf("%d\n", pop());
    deinit();
    return 0;
}

/*
 * 04stack.h
 */
#ifndef __04STACK_H__
#define __04STACK_H__
void init();
void deinit();
int full();
int empty();
void push(int);
int pop();
int last();
int size();
#endif //__04STACK_H__
/*
 * 链式物理结构实现栈
 * 04stack.c
 */
#include <stdlib.h>
#include "04stack.h"
typedef struct node {
    int num;
    struct node *p_next;
} node;
static node head;
/* 初始化 */
void init() {
    head.p_next = NULL;
}

/* 清理函数 */
void deinit() {
    node *p_tmp = NULL;
    while (head.p_next) {
        /* 删除一节点 */
        p_tmp = head.p_next;
        head.p_next = head.p_next->p_next;
        free(p_tmp);    //释放一节点内存并清楚野指针
        p_tmp = NULL;
    }
}

/* 判断栈是否已满 */
int full() {
    return 0;
}

/* 判断栈是否为空 */
int empty() {
    return !head.p_next;    //一节点是否存在
}

/* 向栈中放置新数据的函数 */
void push(int num) {
    node *p_tmp = (node *) malloc(sizeof(node));
    if (p_tmp) {        //判断是否分配成功
        p_tmp->num = num;
        p_tmp->p_next = head.p_next;    //把新节点与头节点连接
        head.p_next = p_tmp;
    }
}

/* 从栈中取数据的函数 */
int pop() {
    int num = 1 << 31;
    if (head.p_next) {    //一节点存在时取
        node *p_tmp = head.p_next;    //记录原来一节点地址,然后去释放
        num = head.p_next->num;
        head.p_next = head.p_next->p_next;
        free(p_tmp);
        p_tmp = NULL;
    }
    return num;
}

/* 读栈中最新(最新)数据 */
int last() {
    int num = 1 << 31;
    if (head.p_next) {
        num = head.p_next->num;
    }
    return num;
}

/* 得到栈中有效数据个数的函数 */
int size() {
    int cnt = 0;
    node *p_node = NULL;
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (p_node->p_next) {
            cnt++;
        }
    }
    return cnt;
}
/*
 * 栈的测试代码
 */
#include <stdio.h>
#include "04stack.h"
int main() {
    init();
    printf(empty()? "空的\n" : "非空\n");
    push(4);
    push(5);
    push(6);
    printf("有效数据个数为%d\n", size());
    printf("最后一个有效数据是%d\n", last());
    printf("%d\n", pop());
    printf("%d\n", pop());
    printf("%d\n", pop());
    deinit();
    printf(empty()? "空的\n" : "非空\n");
    deinit();
    return 0;
}

作业
    修改第二个版本的栈,要求每次从尾部进行插入和删除操作;
/*
 * 05stack.h
 */
#ifndef __05STACK_H__
#define __05STACK_H__
void init();
void deinit();
int full();
int empty();
void push(int);
int pop();
int last();
int size();
#endif //__05STACK_H__
/*
 * 链式物理结构实现栈2
 * 05stack.c
 */
#include <stdlib.h>
#include "1stack.h"
typedef struct node {
    int num;
    struct node *p_next;
} node;
static node head;

/* 初始化 */
void init() {
    head.p_next = NULL;
}

/* 清理函数 */
void deinit() {
    node *p_tmp = NULL;
    while (head.p_next) {
        /* 删除一节点 */
        p_tmp = head.p_next;
        head.p_next = head.p_next->p_next;
        free(p_tmp);    //释放一节点内存并清楚野指针
        p_tmp = NULL;
    }
}

/* 判断栈是否已满 */
int full() {
    return 0;
}

/* 判断栈是否为空 */
int empty() {
    return !head.p_next;    //一节点是否存在
}

/* 向栈中放置新数据的函数 */
void push(int num) {
    node *p_tmp = (node *) malloc(sizeof(node)), *p_node = NULL;
    if (p_tmp) {
        p_tmp->num = num;
        p_tmp->p_next = NULL;
        for (p_node = &head; p_node; p_node = p_node->p_next) {
            if (!(p_node->p_next)) {    //找到尾节点
                p_node->p_next = p_tmp;
                break;
            }
        }
    }
}

/* 从栈中取数据的函数 */
int pop() {
    int ret = 1 << 31;    /* 最小整数 */
    node *p_node = NULL;
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (p_node->p_next && !(p_node->p_next->p_next)) {
            ret = p_node->p_next->num;
            free(p_node->p_next);
            p_node->p_next = NULL;
        }
    }
    return ret;
}

/* 读栈中最新(最新)数据 */
int last() {
    int num = 1 << 31;    //定义num为最小整数
    node *p_node = NULL;
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (p_node->p_next && !(p_node->p_next->p_next)) {
            num = p_node->p_next->num;
        }
    }
    return num;
}

/* 得到栈中有效数据个数的函数 */
int size() {
    int cnt = 0;
    node *p_node = NULL;
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (p_node->p_next) {
            cnt++;
        }
    }
    return cnt;
}

/*
 * 栈的测试代码
 * 05main.c
 */
#include <stdio.h>
#include "1stack.h"
int main() {
    init();
    printf(empty()? "空的\n" : "非空\n");
    push(4);
    push(5);
    push(6);
    printf("有效数据个数为%d\n", size());
    printf("最后一个有效数据是%d\n", last());
    printf("%d\n", pop());
    printf("%d\n", pop());
    printf("%d\n", pop());
    deinit();
    printf(empty()? "空的\n" : "非空\n");
    deinit();
    return 0;
}

