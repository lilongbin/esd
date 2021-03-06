进程管理
fork()创建子进程
exit()和Exit()


回顾
文件的相关函数stat()/access()/truncate()/rename()/remove()
目录的相关函数mkdir()/rmdir()/chdir()/getcwd()/opendir()/readdir()
程序员基本上都是调用各种函数去写程序;
 
进程管理
    什么是进程?运行起来的程序就是进程,进程在内存中运行;
    主流的操作系统中,都采用多进程实现多任务并行;
    每个进程的内部采用多线程实现并行;
在Unix中查看进程用ps命令
ps    只能查看当前终端启动的进程
ps -ef    Unix/linux通用的查看所有进程
ps -aux    Linux支持,Unix不支持,但可以用whereis ps定位,然后用/usr/ucb/ps -aux可以运行;
进程常见的状态STAT
    D    Uninterruptible sleep(usually IO);
    R    正在运行(running)的进程;
    S    休眠(sleep)状态,大多数进程在多数时间都休眠;
    T    停止或被追踪;
    Z    僵尸(zombies)进程,就是已经结束但资源没有回收的进程;
    <    优先级高的进程;
    N    优先级较低的进程;
    L    有些页被锁进内存;
    s    进程的领导者,代表这个进程有子进程;
如果进程a启动了进程b,a就叫b的父进程,b叫做a的子进程;有些进程既是父进程,又是子进程;
    windows下有一个0号进程叫System Idle Process是空闲进程;

Unix进程的启动顺序
    系统启动进程0,进程0只负责启动进程1(init进程)或启动进程1和进程2;
    其他进程都是由进程1或进程2启动的;
Unix用进程的PID标识进程,PID的本质就是一个整数;
每个进程都有一个唯一的进程ID(PID),在同一时刻进程的PID不会重复;进程的PID可以延时重用;

几个常用函数
    getpid()    取当前进程的PID
    getppid()    取父进程的PID
    getuid()/geteuid()    取当前用户ID(有效用户ID)
    
启动子进程的函数
    fork()        通过复制父进程来启动子进程;
    vfork()+execl()    启动一个全新的子进程,有自己的一套;

fork()创建子进程(简单的复杂函数);
    pid_t    fork(void);
    fork无参,返回PID;
    fork()函数通过复制父进程,创建子进程;会复制除代码区之外的所有内存区域,代码区父子进程共享;
/*
 * fork()函数初探
 */
#include <unistd.h>
#include <stdio.h>
int main() {
    printf("begin\n");
    pid_t pid = fork();
    printf("end, pid = %d\n", pid);
    return 0;
}
    子进程是父进程的拷贝,即子进程从父进程得到了除代码区之外的数据段和堆栈段,这些需要分配新的内存;而对于只读的代码段,通常使用共享内存的方式访问;fork()返回后,父子进程都从调用fork()函数的下一条语句开始执行;
    fork()之前的代码只有父进程执行一次,fork()之后的代码父子进程都各执行一次(执行2次);
    fork()函数有两次返回,父进程返回子进程的PID,子进程返回0;
/*
 * fork()函数返回值可以区分出父子进程
 */
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
int main() {
    printf("begin\n");
    pid_t pid = fork();    //pid可以区分出父子进程;

    //父进程返回子进程的PID,子进程返回0;
    if (pid == -1) {
        perror("fork"), exit(-1);
    }
    //练习父子进程打印不同的内容
    //父进程打印1,子进程打印2
    //在父子进程中打印对方进程的ID;
    if (pid == 0) {
        //父子进程都会做判断,子进程满足条件
        printf("2\n");
        printf("我是子进程%d,父进程是%d\n", getpid(), getppid());
    } else {
        //父进程执行的分支;
        printf("1\n");
        printf("我是父进程%d,子进程是%d\n", getpid(), pid);
    }
    //if/else语句父子进程都执行,但是由于条件不同各自执行的部分不同
    printf("end, pid = %d\n", pid);
    return 0;
}

/*
 * fork()创建的父子进程内存空间相互独立
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int i1 = 10;
int main() {
    int i2 = 10;        //i2子进程复制
    char *str = malloc(10);
    strcpy(str, "abcd");
    pid_t pid = fork();
    printf("pid = %d\n", pid);
    /* 在父进程中返回子进程的PID,在子进程中返回0; */
    if (pid == 0) {
        printf("我是子进程fork()返回%d\n", pid);
    } else {
        printf("我是父进程fork()返回%d\n", pid);
    }
    /* i3父子进程分别创建; */
    int i3 = 10;
    if (pid == 0) {
        /* 子进程执行分支 */
        /* i1,i2子进程会复制 */
        /* i3是父子进程分别创建的,不是复制的 */
        i1 = 20, i2 = 20, i3 = 20;
        str[0] = '1';
        printf("child:i1=%d,i2=%d,i3=%d,str=%s\n", i1, i2, i3, str);
        printf("chaddr:&i1=%p,&i2=%p,&i3=%p,&str=%p\n", &i1, &i2, &i3, str);
        exit(0);
        /* 执行后保证后面的不会执行 */
    }
    sleep(1);
    printf("father:i1=%d,i2=%d,i3=%d,str=%s\n", i1, i2, i3, str);
    printf("faaddr:&i1=%p,&i2=%p,&i3=%p,&str=%p\n", &i1, &i2, &i3, str);
    /* 每个进程都有自己独立的虚拟内存空间; */
    /* 子进程复制了父进程的内存空间,虚拟地址相同,
     * 但属于不同进程 */
    return 0;
}

    fork()函数创建子进程后,父子进程谁先运行不确定,不同的系统有不同的算法;谁先结束也不确定;
    fork()创建子进程时,如果父进程有文件描述符,子进程会复制文件描述符,但不复制文件表;
/*
 * fork()创建子进程时,如果父进程有描述符,
 * 子进程会复制文件描述符,但不复制文件表
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
int main() {
    //pid_t pid = fork(); //父子进程将分别创建文件描述符
    int fd = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0666); if (fd == -1) {
        perror("open"), exit(-1);
    }
    pid_t pid = fork();    //子进程复制文件描述符
    /* 复制文件描述符,不复制文件表 */
    if (pid == 0) {
        /* 子进程执行分支 */
        printf("child:fd=%d\n", fd);
        write(fd, "abc", 3);
        close(fd);    //关闭子进程的fd
        exit(0);    //执行后保证后面的不会执行
    }
    sleep(1);
    printf("father:fd=%d\n", fd);
    write(fd, "123", 4);
    /* 如果两个文件描述符对应同一个文件表,
     * 文件位置偏移量是同一个,内容不会相互覆盖;
     * 说明没有复制文件表 */
    close(fd);        //关闭父进程的fd
    /* close()只删除对应关系,只有当文件描述符和文件表的对应关系为为0时才删除文件表 */
    return 0;
}

父子进程之间的关系
    fork()之后,父子进程同时运行,如果子进程先结束,子进程给父进程发一个信号,父进程负责回收子进程的资源;
    fork()之后,父子进程同时运行,如果父进程先结束,子进程变成孤儿进程,会认进程1(init进程)做新的父进程;init进程叫孤儿院;
    fork()之后,父子进程同时运行,如果子进程发信号时出现了问题,或者父进程没有及时处理信号,子进程就会变成僵尸进程Z;

fork()出现错误的原因
    1系统进程总数有限额;
    2用户进程总数有限额;
一般情况下,不可能超限额,因此fork()可以不判断-1,fork()出错的后果就是子进程创建失败,父进程继续执行;

练习
    验证如果父进程先结束,子进程会以init进程做新的父进程;
思路
    父进程先sleep(),运行子进程,子进程打印此时的父进程PID,然后子进程再sleep(),父进程结束后,子进程再次打印父进程的PID;
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
    printf("父进程pid=%d\n", getpid());
    pid_t pid = fork();
    if (pid == 0) {
        printf("父进程PID=%d\n", getppid());
        sleep(2);
        printf("父进程PID=%d\n", getppid());
    } else {
        printf("pid = %d\n", pid);
        sleep(1);
        printf("父进程%d结束\n", getpid());
        /* ./a.out的父进程是bash的子进程,
         * 结束后bash就会打印一次终端提示符 */
    }
    return 0;
}

进程的结束/终止
进程可能是正常结束也可能是非正常结束;
进程终止的5种正常情况
    1> 主函数main()中执行 return 语句;
    2> 函数 exit()可以终止进程;
    3> _exit()/_Exit()可以终止进程;
    4> 进程的最后一个线程执行了return返回语句(结束);
    5> 进程的最后一个线程调用pthread_exit()函数(结束);
非正常结束进程的方法
    1> 被信号终止;
    2> 主线程被其他线程取消;

return 和 exit()区别:
    return 是用来退出函数的;
    exit() 是用来退出进程的;

exit()/_exit()/_Exit()的区别
    The function _exit() terminates the calling process "immediately".
    exit()函数定义在stdlib.h中,而_exit()定义在unistd.h中;
    exit()被调用时不会立即结束进程,会先调用exit_handler并调用atexit()/on_exit()注册过的函数之后再结束进程;
    _exit()/_Exit()在底层是一样的,没有区别; _Exit()立即结束进程;
    _exit()函数只为进程实施内核清理工作;子进程中最好用_exit(),而exit()会影响父进程的状态;
    
    atexit(函数指针)允许进程在结束之前调用其他函数,但如果用_Exit()结束进程时不调用;
int atexit(void (*func)(void))
    可以注册多个函数,一个函数也可注册多次,按FILO顺序执行;
    函数注册后,无法取消注册;
    在清理函数中调用exit()在Linux中会继续执行剩下的清理函数但在某些系统可能出现死循环;
    子进程会继承父进程的清理函数;

/*
 * atexit()/exit()演示
 */
#include <stdio.h>
#include <stdlib.h>
void func1() {
    printf("func1 is called\n");
}
void func2() {
    printf("回收资源,善后处理\n");
}
int main() {
    atexit(func1);        //只注册func1(),只有在exit()时才调用;
    atexit(func2);        //atexit()的参数是函数指针,可以多次调用;
    printf("begin\n");
    /* exit()不会立即结束,可以调用atexit()注册过的函数再结束进程; */
    exit(0);        //参数是退出码,可以用来记录退出情况;
    _Exit(0);        //立即结束,不掉用fa;
    printf("end\n");
    return 0;
}

