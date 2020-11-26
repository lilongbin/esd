队列
链表



# 队列
+ 采用先进先出的方式管理数据;
+ 基本操作:push,pop
+ 放置数字和取数字是在两个不同的端点实现的;
+ 采用顺序存储结构实现队列时需要记录两个端点的位置;

顺序存储方式实现队列的演示
```
/*
 * 02queue.h
 */
#ifndef __02QUEUE_H__
#define __02QUEUE_H__
void init();
void deinit();
int empty();
int full();
void push(int);
int pop();
int front();
int size();
#endif //__02QUEUE_H__
```

```
/*
 * 顺序存储方式实现队列的演示
 * 02queue.c
 */
#include "02queue.h"
static int queue[10];        //static只在本文件可以使用
static int head, tail;
/* head记录第一个有效数据位置或空,tail记录第一个可以使用的空位置下标 */

/* 初始化函数 */
void init() {
    head = 0;
    tail = 0;
}

/* 清理函数 */
void deinit() {
    head = 0;
    tail = 0;
}

/* 判断是否已满 */
int full() {
    return tail == 10;
}

/* 判断是否为空 */
int empty() {
    return head == tail;
}

/* 放数据的函数 */
void push(int num) {
    queue[tail] = num;
    tail++;
}

/* 取数据的函数 */
int pop() {
    head++;
    return queue[head - 1];
}

/* 读取下一个有效数据 */
int front() {
    return queue[head];
}

/* 获得有效数据个数的函数 */
int size() {
    return tail - head;
}
```

```
/*
 * 队列测试演示
 * 02main.c
 */
#include <stdio.h>
#include "02queue.h"
int main() {
    init();
    printf(empty()? "空的\n" : "非空\n");
    push(1);
    push(2);
    push(3);
    printf("下一个数字是%d\n", front());
    printf("数据个数是%d\n", size());
    printf("%d\n", pop());
    printf("%d\n", pop());
    printf("%d\n", pop());
    printf(empty()? "空的\n" : "非空\n");
    push(4);
    push(5);
    push(6);
    push(7);
    push(8);
    push(9);
    push(10);
    printf(full()? "满的\n" : "不满\n");
    deinit();
    return 0;
}
```

顺序存储方式实现队列的演示
```
/*
 * 03queue.h
 */
#ifndef __3QUEUE_H__
#define __3QUEUE_H__
void init();
void deinit();
int empty();
int full();
void push(int);
int pop();
int front();
int size();
#endif //__3QUEUE_H__
```

```
/*
 * 顺序存储方式实现队列的演示
 * 03queue.c
 */
#include <stdlib.h>
#include "03queue.h"
typedef struct node {
    int num;
    struct node *p_next;
} node;
static node head;
/* 初始化函数 */
void init() {
    head.p_next = NULL;
}

/* 清理函数 */
void deinit() {
    while (head.p_next) {
        node *p_tmp = head.p_next;
        head.p_next = head.p_next->p_next;
        free(p_tmp);
        p_tmp = NULL;
    }
}

/* 判断是否已满 */
int full() {
    return 0;
}

/* 判断是否为空 */
int empty() {
    return !(head.p_next);
}

/* 放数据的函数 */
void push(int num) {
    node *p_tmp = (node *) malloc(sizeof(node)), *p_node = NULL;
    if (p_tmp) {
        p_tmp->num = num;
        p_tmp->p_next = NULL;
        for (p_node = &head; p_node; p_node = p_node->p_next) {
            if (!(p_node->p_next)) {
                p_node->p_next = p_tmp;
                break;
            }
        }
    }
}

/* 取数据的函数 */
int pop() {
    int ret = 1 << 31;
    if (head.p_next) {
        node *p_tmp = head.p_next;
        ret = head.p_next->num;
        head.p_next = p_tmp->p_next;
        free(p_tmp);
        p_tmp = NULL;
    }
    return ret;
}

/* 读取下一个有效数据 */
int front() {
    int ret = 1 << 31;
    if (head.p_next) {
        ret = head.p_next->num;
    }
    return ret;
}

/* 获得有效数据个数的函数 */
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
```

```
/*
 * 队列测试演示
 */
#include <stdio.h>
#include "03queue.h"
int main() {
    init();
    printf(empty()? "空的\n" : "非空\n");
    push(1);
    push(2);
    push(3);
    printf("下一个数字是%d\n", front());
    printf("数据个数是%d\n", size());
    printf("%d\n", pop());
    printf("%d\n", pop());
    printf("%d\n", pop());
    printf(empty()? "空的\n" : "非空\n");
    push(4);
    push(5);
    push(6);
    push(7);
    push(8);
    push(9);
    push(10);
    printf(full()? "满的\n" : "不满\n");
    deinit();
    return 0;
}
```

# 链表
包含一个线性链式存储结构和一组相关的操作函数;
链表的基本功能包括:插入/删除和遍历;

```
/*
 * 04linklist.h
 */
#ifndef __04LINKLIST_H__
#define __04LIKKLIST_H__
typedef struct node{
    int num;
    struct node *p_next;
} node;
void init();
void deinit();
int empty();
void insert_head(int);
void remove_head();
void insert_tail(int);
void remove_tail();
int get_head();
int get_tail();
int size();
void for_each(int(*)(void*,void*),void*);
#endif //__04LINKLIST_H__
```

```
/*
 * 链表演示
 * 04linklist.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "04linklist.h"
static node head;

/* 初始化函数 */
void init() {
    head.p_next = NULL;
}

/* 清理函数 */
void deinit() {            //不断的删除一节点
    while (head.p_next) {
        node *p_tmp = head.p_next;
        head.p_next = p_tmp->p_next;
        free(p_tmp);
        p_tmp = NULL;
    }
}

/* 判断空的函数 */
int empty() {
    return !(head.p_next);
}

/* 插入一节点 */
void insert(int num) {
    node *p_tmp = (node *) malloc(sizeof(node));
    if (p_tmp) {
        p_tmp->num = num;
        p_tmp->p_next = head.p_next;
        head.p_next = p_tmp;
    }
}

/* 删除一节点 */
void remove_head() {
    if (head.p_next) {
        node *p_tmp = head.p_next;
        head.p_next = p_tmp->p_next;
        free(p_tmp);
        p_tmp = NULL;
    }
}

/* 插入尾节点 */
void insert_tail(int num) {
    node *p_tmp = (node *) malloc(sizeof(node)), *p_node = NULL;
    if (p_tmp) {
        p_tmp->num = num;
        p_tmp->p_next = NULL;
        for (p_node = &head; p_node; p_node = p_node->p_next) {
            if (!(p_node->p_next)) {    //将新节点插入到尾部
                p_node->p_next = p_tmp;
                break;
            }
        }
    }
}

/* 删除尾节点 */
void remove_tail() {
    node *p_node = NULL;
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (p_node->p_next && !(p_node->p_next->p_next)) {
            free(p_node->p_next);
            p_node->p_next = NULL;
        }
    }
}

/* 获得一节点的内容 */
int get_head() {
    int ret = 1 << 31;
    if (head.p_next) {
        ret = head.p_next->num;
    }
    return ret;
}

/* 获得尾节点的内容 */
int get_tail() {
    int ret = 1 << 31;
    node *p_node = NULL;
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (p_node->p_next && !(p_node->p_next->p_next)) {
            ret = p_node->p_next->num;
            break;
        }
    }
    return ret;
}

/* 获得有效数据的个数 */
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

/*void print(){
    node *p_node = NULL;
    for(p_node = &head;p_node;p_node = p_node->p_next){
        if(p_node->p_next){
            printf("%d ",p_node->p_next->num);
        }
    }
    printf("\n");
}*/

/* 遍历函数(用函数指针)回调函数 */
void for_each(int (*p_func) (void *, void *), void *p_data) {
    node *p_node = NULL;
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (p_func(p_node, p_data)) {
            break;
        }
    }
}
```

```
/*
 * 链表测试
 * 04main.c
 */
#include <stdio.h>
#include "04linklist.h"
int print_cb(void *p_node, void *p_data) {    //print call back函数
    if (((node *) p_node)->p_next) {
        printf("%d ", ((node *) p_node)->p_next->num);
        if (!(((node *) p_node)->p_next->p_next)) {
            printf("\n");
            return 1;
        }
    }
    return 0;
}
int main() {
    init();
    insert_tail(1);
    insert_tail(2);
    insert_tail(3);
    printf("有效数据个数是%d\n", size());
    for_each(print_cb, NULL);
    printf("%d ", get_tail());
    remove_tail();
    printf("%d ", get_tail());
    remove_tail();
    printf("%d\n", get_tail());
    remove_tail();
    printf(empty()? "空的\n" : "非空\n");
    deinit();
    return 0;
}
```

# 练习1
编写函数从链表中删除指定数字,用返回值表示操作结果(1表示成功,0表示失败);

```
/*
 * 05linklist.h
 */
#ifndef __05LINKLIST_H__
#define __05LIKKLIST_H__
typedef struct node{
    int num;
    struct node *p_next;
} node;
void init();
void deinit();
int empty();
void insert_head(int);
void remove_head();
void insert_tail(int);
void remove_tail();
int get_head();
int get_tail();
int size();
void for_each(int(*)(void*,void*),void*);
int remove_node(int);
#endif //__05LINKLIST_H__
```

```
/*
 * 链表演示
 * 05linklist.c
 */
//#include <stdio.h>
#include <stdlib.h>
#include "05linklist.h"
static node head;

/* 初始化函数 */
void init() {
    head.p_next = NULL;
}

/* 清理函数 */
void deinit() {            //不断的删除一节点
    while (head.p_next) {
        node *p_tmp = head.p_next;
        head.p_next = p_tmp->p_next;
        free(p_tmp);
        p_tmp = NULL;
    }
}

/* 判断空的函数 */
int empty() {
    return !(head.p_next);
}

/* 插入一节点 */
void insert(int num) {
    node *p_tmp = (node *) malloc(sizeof(node));
    if (p_tmp) {
        p_tmp->num = num;
        p_tmp->p_next = head.p_next;
        head.p_next = p_tmp;
    }
}

/* 删除一节点 */
void remove_head() {
    if (head.p_next) {
        node *p_tmp = head.p_next;
        head.p_next = p_tmp->p_next;
        free(p_tmp);
        p_tmp = NULL;
    }
}

/* 插入尾节点 */
void insert_tail(int num) {
    node *p_tmp = (node *) malloc(sizeof(node)), *p_node = NULL;
    if (p_tmp) {
        p_tmp->num = num;
        p_tmp->p_next = NULL;
        for (p_node = &head; p_node; p_node = p_node->p_next) {
            if (!(p_node->p_next)) {    //将新节点插入到尾部
                p_node->p_next = p_tmp;
                break;
            }
        }
    }
}

/* 删除尾节点 */
void remove_tail() {
    node *p_node = NULL;
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (p_node->p_next && !(p_node->p_next->p_next)) {
            free(p_node->p_next);
            p_node->p_next = NULL;
        }
    }
}

/* 获得一节点的内容 */
int get_head() {
    int ret = 1 << 31;
    if (head.p_next) {
        ret = head.p_next->num;
    }
    return ret;
}

/* 获得尾节点的内容 */
int get_tail() {
    int ret = 1 << 31;
    node *p_node = NULL;
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (p_node->p_next && !(p_node->p_next->p_next)) {
            ret = p_node->p_next->num;
            break;
        }
    }
    return ret;
}

/* 获得有效数据的个数 */
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

/*void print(){
    node *p_node = NULL;
    for(p_node = &head;p_node;p_node = p_node->p_next){
        if(p_node->p_next){
            printf("%d ",p_node->p_next->num);
        }
    }
    printf("\n");
}*/

/* 遍历函数(用函数指针)回调函数 */
void for_each(int (*p_func) (void *, void *), void *p_data) {
    node *p_node = NULL;
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (p_func(p_node, p_data)) {
            break;
        }
    }
}

/*//删除一个指定的数字
 int remove_node(int num){
    node *p_node = NULL;
    for(p_node = &head;p_node;p_node = p_node->p_next){
        if(p_node->p_next && p_node->p_next->num == num){
            node *p_tmp = p_node->p_next;
            p_node->p_next = p_node->p_next->p_next;
            free(p_tmp);
            p_tmp = NULL;
            return 1;
        }
    }
    return 0;
}*/

/* 删除指定数字callback */
typedef struct rdata {
    int num, ret;
} rdata;

int remove_cb(void *p_node, void *p_data) {
    if (((node *) p_node)->p_next
        && (((node *) p_node)->p_next)->num == ((rdata *) p_data)->num) {
        node *p_tmp = ((node *) p_node)->p_next;
        ((node *) p_node)->p_next = ((node *) p_node)->p_next->p_next;
        free(p_tmp);
        p_tmp = NULL;
        ((rdata *) p_data)->ret = 1;
        return 1;
    }
    return 0;
}

int remove_node(int num) {
    rdata rd = { };
    rd.num = num;
    for_each(remove_cb, &rd);
    return rd.ret;
}
```

```
/*
 * 链表测试
 * 05main.c
 */
#include <stdio.h>
#include "05linklist.h"
int print_cb(void *p_node, void *p_data) {    //print call back函数
    if (((node *) p_node)->p_next) {
        printf("%d ", ((node *) p_node)->p_next->num);
        if (!(((node *) p_node)->p_next->p_next)) {
            printf("\n");
            return 1;
        }
    }
    return 0;
}

int main() {
    init();
    insert_tail(1);
    insert_tail(2);
    insert_tail(3);
    printf("有效数据个数是%d\n", size());
    for_each(print_cb, NULL);
    printf("%d ", get_tail());
    printf("\n删除操作返回%d\n", remove_node(1));
    for_each(print_cb, NULL);
    printf("%d ", get_tail());
    remove_tail();
    printf("%d\n", get_tail());
    remove_tail();
    printf(empty()? "空的\n" : "非空\n");
    deinit();
    return 0;
}
```

# 练习2
```
/*
 * data.h
 */
#ifndef __DATA_H__
#define __DATA_H__
typedef struct node {
    int id;
    struct node *p_next;
} node, *ll_head;
ll_head ll_create(void); /* create a linked list */
node *ll_input(node *);
void ll_insert(ll_head, node *); /* insert a node to the linked list */
void ll_delete(ll_head, node *); /* delete a node from the linked list */
node *ll_locate(ll_head, int); /* return if the node exists */
void ll_free(ll_head); /* free memory */
void ll_traversal(ll_head); /* traversal the linked list */
#endif /* __DATA_H__*/
```

```
/*
 * data.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "data.h"

/* create a linked list */
ll_head ll_create(void) {
    node *new = malloc(sizeof(struct node));
    if (new == NULL) {
        perror("malloc");
        return NULL;
    }
    new->p_next = NULL;
    //printf("create linked list successfully !\n");
    return new;
}

/* insert a node to the linked list */
void ll_insert(ll_head head, node * tmp) {
    if (ll_locate(head, tmp->id)) {
        printf("the id(%d) has exited\n", tmp->id);
        return;
    }
    node *new = malloc(sizeof(struct node));
    if (new == NULL) {
        perror("malloc");
        return;
    }
    new->id = tmp->id;
    new->p_next = NULL;

    node *this = head;
    for (this = head; this; this = this->p_next) {
        /* insert id to link list in order */
        if (this->p_next == NULL) {
            this->p_next = new;
            break;
        } else if (this->p_next->id > tmp->id) {
            new->p_next = this->p_next;
            this->p_next = new;
            break;
        }
    }
}

/* delete a node from the linked list */
void ll_delete(ll_head head, node * tmp) {
    node *this = head;
    node *fro = this;
    int flag = 0;
    for (; this;) {
        fro = this;
        this = this->p_next;
        if (this->id == tmp->id) {
            fro->p_next = this->p_next;
            free(this);
            this = fro;
            flag = 1;
            printf("delete id(%d)\n", tmp->id);
        }
    }
    if (this == NULL && flag == 0) {
        printf("the node not exists\n");
    }
}

/* free the memory of the linkedlist */
void ll_free(ll_head head) {
    node *fro = head;
    node *this = head;
    for (; this->p_next;) {
        fro = this;
        this = this->p_next;

        fro->p_next = this->p_next;
        //printf("free(%02d,%02d) ", this->x, this->y);
        free(this);
        this = fro;
    }
    //printf("\n");
}

/* return if the node exists */
node *ll_locate(ll_head head, int id) {
    node *this = head;
    while (this = this->p_next) {
        if (this->id == id) {
            return this;
        }
    }
    return NULL;
}

/* traversal the linked list */
void ll_traversal(ll_head head) {
    node *this = head;
    while (this = this->p_next) {
        printf("%d\n", this->id);
    }
}
```

```
/*
 * 按顺序插入用户输入的数据不超过10000个
 * 直到用户输入0时结束;
 * user.c
 * */
#include <stdio.h>
#include <stdlib.h>
#include "data.h"

int main() {
    node *ll_head = ll_create();
    node tmp;
    int num = 0;
    while (num++ <= 10000) {
        printf("please input a num: ");
        scanf("%d", &tmp.id);
        if (tmp.id == 0) {
            break;
        }
        printf("id = %d\n", tmp.id);
        ll_insert(ll_head, &tmp);    //插入
    }

    ll_traversal(ll_head);    //遍历链表,顺序打印
    ll_free(ll_head);    //释放空间
    return 0;
}
```

# 练习
给链表增加按顺序插入的函数;
使用遍历函数加返回值;
```
/*
 * 07linklist.h
 */
#ifndef __07LINKLIST_H__
#define __07LIKKLIST_H__
typedef struct node {
    int num;
    struct node *p_next;
} node;
void init();
void deinit();
int empty();
void insert_head(int);
void remove_head();
void insert_tail(int);
void remove_tail();
int get_head();
int get_tail();
int size();
void for_each(int (*)(void *, void *), void *);
int insert_in_order(int);
#endif //__07LINKLIST_H__
```

```
/*
 * 链表演示
 * 07linklist.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "07linklist.h"
static node head;
/* 初始化函数 */
void init() {
    head.p_next = NULL;
}

/* 清理函数 */
void deinit() {
    /* 不断的删除一节点 */
    while (head.p_next) {
        node *p_tmp = head.p_next;
        head.p_next = p_tmp->p_next;
        free(p_tmp);
        p_tmp = NULL;
    }
}

/* 判断空的函数 */
int empty() {
    return !(head.p_next);
}

/* 插入一节点 */
void insert(int num) {
    node *p_tmp = (node *) malloc(sizeof(node));
    if (p_tmp) {
        p_tmp->num = num;
        p_tmp->p_next = head.p_next;
        head.p_next = p_tmp;
    }
}

/* 删除一节点 */
void remove_head() {
    if (head.p_next) {
        node *p_tmp = head.p_next;
        head.p_next = p_tmp->p_next;
        free(p_tmp);
        p_tmp = NULL;
    }
}

/* 插入尾节点 */
void insert_tail(int num) {
    node *p_tmp = (node *) malloc(sizeof(node)), *p_node = NULL;
    if (p_tmp) {
        p_tmp->num = num;
        p_tmp->p_next = NULL;
        for (p_node = &head; p_node; p_node = p_node->p_next) {
            if (!(p_node->p_next)) {    //将新节点插入到尾部
                p_node->p_next = p_tmp;
                break;
            }
        }
    }
}

/* 删除尾节点 */
void remove_tail() {
    node *p_node = NULL;
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (p_node->p_next && !(p_node->p_next->p_next)) {
            free(p_node->p_next);
            p_node->p_next = NULL;
        }
    }
}

/* 获得一节点的内容 */
int get_head() {
    int ret = 1 << 31;
    if (head.p_next) {
        ret = head.p_next->num;
    }
    return ret;
}

/* 获得尾节点的内容 */
int get_tail() {
    int ret = 1 << 31;
    node *p_node = NULL;
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (p_node->p_next && !(p_node->p_next->p_next)) {
            ret = p_node->p_next->num;
            break;
        }
    }
    return ret;
}

/* 获得有效数据的个数 */
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

/*void print(){
    node *p_node = NULL;
    for(p_node = &head;p_node;p_node = p_node->p_next){
        if(p_node->p_next){
            printf("%d ",p_node->p_next->num);
        }
    }
    printf("\n");
}*/

/* 遍历函数(用函数指针)回调函数 */
void for_each(int (*p_func) (void *, void *), void *p_data) {
    node *p_node = NULL;
    for (p_node = &head; p_node; p_node = p_node->p_next) {
        if (p_func(p_node, p_data)) {
            break;
        }
    }
}

/* 按顺序插入 */
/*int insert_in_order(int num){
    node *p_node = NULL;
    for (p_node = &head;p_node;p_node = p_node->p_next){
        node *p_tmp = p_node->p_next;
        if (!p_tmp || p_tmp->num>num){
            node *p_tmp1 = (node*)malloc(sizeof(node));
            if(p_tmp1){
                p_tmp1->num = num;
                p_tmp1->p_next = NULL;
                p_tmp1->p_next = p_tmp;
                p_node->p_next = p_tmp1;
                return 1;
            }
        }
    }
    return 0;
}*/

typedef struct rdata {
    int num, ret;
} rdata;

int insert_cb(void *p_node, void *p_data) {
    node *p_tmp = ((node *) p_node)->p_next;
    if (!p_tmp || p_tmp->num > ((rdata *) p_data)->num) {
        node *p_tmp1 = (node *) malloc(sizeof(node));
        if (p_tmp1) {
            p_tmp1->num = ((rdata *) p_data)->num;
            p_tmp1->p_next = NULL;
            p_tmp1->p_next = p_tmp;
            ((node *) p_node)->p_next = p_tmp1;
            ((rdata *) p_data)->ret = 1;
            return 1;
        }
    }
    return 0;
}

int insert_in_order(int num) {
    rdata idt = { num };
    for_each(insert_cb, &idt);
    return idt.ret;
}
```

```
/*
 * 链表测试
 * 07main.c
 */
#include <stdio.h>
#include "07linklist.h"
int print_cb(void *p_node, void *p_data) {
    /* print call back函数 */
    if (((node *) p_node)->p_next) {
        printf("%d ", ((node *) p_node)->p_next->num);
        if (!(((node *) p_node)->p_next->p_next)) {
            printf("\n");
            return 1;
        }
    }
    return 0;
}

int main() {
    init();
    insert_tail(1);
    insert_tail(5);
    insert_tail(9);
    insert_in_order(7);
    insert_in_order(13);
    printf("有效数据个数是%d\n", size());
    for_each(print_cb, NULL);
    deinit();
    return 0;
}
```
