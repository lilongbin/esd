多线程技术




回顾:
    网络编程//socket编程
    函数比较多
    普通网络编程模型
        1.socket();
        2.struct sockaddr_in;
        3.bind()/connect();
        4.read()/write();
        5.close();
    TCP网络编程步骤:
        1.socket();
        2.struct sockaddr_in;
        3.bind()/connect();
        4.listen()//server
        5.accept()//server
        6.read()/write();
        7.close();
    UDP网络编程步骤:
        1.socket();
        2.struct sockaddr_in;
        3.bind()//server
        4.read()/recvfrom()/sendto();
        5.close();

答疑:
    1.不是一个进程,端口号就不一样;

今天:
    进入名企最大的障碍就是编程经验不足,代码量不够,应用程度不够;所以要多花时间练习;

线程
    线程是轻量级的代码并行技术;线程不需要复制进程的资源,而是直接共享进程的资源;
    线程只需要一个额外的栈就可以了;因此很多应用都是使用多线程技术;
    主流的操作系统支持多进程,每个进程的内部支持多线程,线程可以嵌套;
    JAVA语言中没有进程概念,因为Java本身是运行在虚拟机中的,而虚拟机本身就是一个进程;
    大多数应用程序都是使用多线程;

如何实现代码并行?
    程序代码执行至少需要CPU(中央处理器)和内存,代码的并行就需要多个CPU和多段内存;
    内存可分段,CPU可分时间片;
    大多系统采用CPU时间片实现代码的并行(伪并行);首先把CPU的运行时间分成极小的CPU时间片,然后每个线程拿一片,有时间片的线程就有运行的权利,但先后次序是完全无序的;一轮之后再重新分配CPU时间片;
    人的感官是需要时间的,假定人的视觉需要0.1s, 0.1s = 100 ms,此时分1 ms做一个CPU时间片,有4个线程A B C D,每个线程先拿1 ms的CPU时间片,当我们看到四个线程时,每个线程都运行了25 ms;
    多线程之间是乱序运行,但每个线程内部都是顺序执行;
    线程和线程之间是互相独立,但又互有影响(资源有共享);
    多线程可以提升程序的效率;如多线程下载工具;
    
    每个进程的内部至少有一个线程,就是main(),叫主线程;
    主线程一旦结束,进程就随之结束,其他线程就随着进程的结束而结束;

Unix有哪些关于线程的API(Application Program Interface应用编程接口);
    多线程的开发定义在POSIX规范中,使用pthread.h头文件;
    所有的函数放在libpthread.so共享库文件中;编译和链接要使用-pthread选项或-lpthread;双L连接法,L和l在此可以省略;
    函数基本上都是以pthread_开头的;
    pthread即process中的thread;线程是隶属于进程的;

创建线程的函数
    pthread_create()
int pthread_create(//参数4个针(全是指针);
        pthread_t *id, //线程ID;
        const pthread_attr_t *attr, //线程属性,一般给0(默认);
        void *(*task) (void *), //函数指针
        void *argue //传给函数指针所调用函数需要使用的参数,无参数用0
    );
    参数id用于存储线程ID,每个线程用ID做标识;
    attr是线程属性,默认给0即可;
    task是函数指针,参数和返回值都可以是任意类型,没有限制;
    argue是task的参数,函数指针只能传函数地址,而参数用argue传入;
    成功返回0,失败返回错误码;
    注意线程的函数基本都返回错误码,而不使用errno(errno是全局变量,会相互覆盖,不能确定是谁改变的),因此处理线程的错误要使用strerror(),不能使用perror();
    On success, pthread_create() returns 0;
    on error, it returns an error number, and the contents of *thread are undefined;
    C语言用外部的全局变量errno(error number)记录错误信息;错误信息分为错误编号(int)和具体信息(字符串);每个错误编号都对应一个具体信息;errno存储的是错误编号;
    函数strerror()/perror()/printf()用于错误信息的显示和转换;
    strerror() //传入一个编号,返回具体信息(转换函数);
    perror() //不用传入错误编号,直接打印errno对应的信息(会自动换行);
    printf("%m") //直接打印errno对应的信息;
    不是所有的函数都使用errno处理处理错误,比如线程的函数;

pthread_self()函数可以取得当前线程的线程ID;
/*
 * 线程创建练习
 */
#include <stdio.h>
#include <pthread.h>
#include <string.h>
void *task(void *p) {
    int i = 0;
    for (i = 0; i <= 50; i++) {
        printf("task:%02d\t", i);
    }
    printf("\n");
}
int main() {
    pthread_t id, mid;
    /* 启动一个线程,执行task()函数; */
    int res = pthread_create(&id, 0, task, 0); //不会阻塞
    /* 不会等待线程的运行或结束 */
    if (res) {
        printf("%s\n", strerror(res));
    }
    mid = pthread_self();    //取当前线程的ID;
    printf("新启动线程id:%u,当前线程id:%u\n", id, mid);
    /* 线程的id比较大,需要用%u匹配; */
    int i = 0;
    for (i = 0; i <= 50; i++) {
        printf("M***:%02d\t", i);
    }
    printf("\n");
    usleep(100000);        //主线程结束,进程结束;
    /* 总闸关闭,所有的小开关都失效了 */
    return 0;
}
/*
 * 线程传参与资源共享;
 */
#include <stdio.h>
#include <pthread.h>
void *task(void *p) {
    int *pi = (int *)p;
    printf("*pi = %d\n", *pi);
    *pi = 200;
}
int main() {
    pthread_t id;
    int x = 100;
    pthread_create(&id, 0, task, &x);
    sleep(1);
    pthread_join(id, NULL); //可以等待线程(id)的结束;
    printf("x = %d\n", x); //200
    /* 线程不复制进程的资源,直接共享进程的资源; */
    return 0;
}

    在创建线程时,传参是传递地址,但直接传递整数(指针的本质也是整数)也是可行的;
    在传地址时,注意保证地址是有效的;空指针/野指针/已经被free()的堆区指针都是无效的;
/*
 * 线程传参练习
 */
#include <stdio.h>
#include <string.h>
#include <pthread.h>
/* 练习写一个线程,传入半径,计算圆的面积; */
void *task1(void *p) {
    double r = *(double *)p;
    printf("圆面积:%lg\n", 3.14 * r * r);
}
void *task2(void *p) {
    /* 特殊用法,把整数当指针传入,然后再把指针当整数用 */
    /* 拿指针当整数来用 */
    int i = (int)p;
    printf("i = %d\n", i);
}
int main() {
    pthread_t id1, id2;
    double r;
    printf("please input r:\n");
    scanf("%lf", &r);
    pthread_create(&id1, 0, task1, &r);
    /* pthread_join()可以让一个线程等待另外一个线程结束 */
    pthread_join(id1, NULL);
    int x = 100;
    /*
     * int *px;//野指针不可以做参数传入
     * //结果不确定或段错误
     * pthread_create(&id2, 0, task2, px);
     */
    pthread_create(&id2, 0, task2, (void *)x);
    pthread_join(id2, NULL);
    printf("x = %d\n", x);
    return 0;
}

pthread_join()函数可以让一个线程等待另外一个线程;
比如在线程a中调用了pthread_join(b, NULL),线程a会等待线程b结束;
线程没有父子线程之说;

线程可以有返回值,返回值由pthread_join()函数的第二个参数带回;
线程返回值类型是 void *,因此参数的类型就是 void **类型;
int pthread_join(pthread_t id, void **retval);
/*
 * pthread_join()取线程的返回值
 */
#include <stdio.h>
#include <pthread.h>
#include <string.h>
/*
 * char *get() {
 *     //return "abc";//可以,返回一个有效的地址;
 *     char *s1 = "abc";    ///返回指向字面值的指针可以;
 *     return s1;
 *     //char s2[] = "abc";//指向栈区的指针,不可以;
 *     //return s2;
 *     //返回值类型可以是指针;不能是数组,不能确定大小;
 * }
 * int *test() {
 *     //int x = 100; return &x; //不可以返回局部变量的地址;
 *     static int x = 100;
 *     return &x;
 * }
 */
void *task1(void *p) {
    static int sum = 0;
    int i = 0;
    for (i = 1; i <= 10; i++) {
        sum += i;
    }
    return &sum; //pp = &sum;//将返回值&num给pp带回
}
void *task2(void *p) {
    int sum = 0;
    int i = 0;
    for (i = 1; i <= 100; i++) {
        sum += i;
    }
    return (void*)sum;
}
int main() {
    pthread_t id1, id2;
    pthread_create(&id1, 0, task1, NULL);
    int *p;
    pthread_join(id1, (void **)&p);    //p不再是野指针
    //p是一级指针,&p是二级指针;join函数中要转换成void**;
    //只要保持p和函数return后面类型一致即可;
    printf("sum is %d\n", *p);
    int num;
    pthread_create(&id2, 0, task2, NULL);
    pthread_join(id2, (void **)&num);
    printf("sum is %d\n", num);
    /*
     * printf("可以取到%s\n", get());
     * int *pi = test();
     * printf("可以取到%d\n", *pi);
     */
    return 0;
}

关于返回值的一些常识
    1-> 返回值类型不能是数组,但可以是指针;
    2-> 可以返回局部变量,但不能返回指向局部变量的地址;
    3-> static 修饰的局部变量地址可以返回;//在全局区;

线程的退出
    1.正常退出
        在线程的函数中执行了return;语句;
        执行了void pthread_exit(void* retval)函数;
    2.非正常退出
        被其他线程用int pthread_cancel(pthread_t thread)取消;
        自身运行出了问题;
    注:exit()退出的是进程,不能用于退出线程;否则所有线程全结束;
    信号退出的是进程,也不能用于退出线程;
/*
 * pthread_exit()
 */
#include <stdio.h>
#include <pthread.h>
#include <string.h>
void *task1(void *p) {
    int i = 0;
    while (++i) {
        printf("1");
        if (i >= 1000) {
            pthread_exit((void*)i);
            /* 退出进程并返回指针的值; */
        }
    }
}
void *task2(void *p) {
    while (1) printf("2");
}
int main() {
    pthread_t id1, id2;
    pthread_create(&id1, 0, task1, NULL);
    pthread_create(&id2, 0, task2, NULL);
    int *p;
    pthread_join(id1, (void **)&p);
    printf("thread 1 return: %d\n", p);
    if (!pthread_cancel(id2)) {
        /* 取消一个线程的执行,成功结束返回0 */
        printf("thread 2 has been canceled\n");
    }
    return 0;
}

int pthread_join(pthread_t thread, void ** rval_ptr);
功能
    调用这将挂起并等待新进程终止;
    当新线程调用pthread_exit()退出或者return时,进程中的其他线程可通过pthread_join()获得进程的提出状态;
使用约束
    一个新线程仅仅允许一个线程使用该函数等待它终止;
    被等待线程应处于可join状态,即非DETACHED状态;
返回值
    成功返回0,失败返回错误码;
说明
    类似于waitpid()函数;
        
