wait()/waitpid();
vfork()+execl()创建全新的子进程;
信号管理;


回顾

进程管理
进程的概念和Unix系统进程的启动顺序
Unix查看进程的状态
进程的基本函数:
    fork()/getpid()/getppid()
    fork()//通过复制自身去创建子进程;
    fork()//创建的子进程会复制代码区以外的所有进程内存区域,但在复制文件描述符时,只会复制描述符,不复制文件表;
    fork()//在运行时会创建子进程,因此父子进程都会有返回值,子进程返回0,父进程返回子进程的PID;
exit()和Exit()
    exit()不会立即退出,还能调用一些注册过的函数;
    _Exit()会立即退出,只做一些善后工作;

答疑
    1-> 文件描述符/文件表/v-node分别存储在内存中,i-node会在硬盘中保存一张总表,i-node保存于硬盘,i-node总表会从硬盘复制一份到内存;
    2-> 缓冲区的内容在fork()创建子进程时也会复制过来;

今天
exit(0);//如何取退出码?
The exit() function causes normal process termination and the value of status & 0377 is returned to the parent (see wait(2)).
退出码返回给父进程;必须保证子进程先结束,父进程才能拿退出码;
函数wait()/waitpid()用于让父进程等待子进程的结束,并取得子进程的退出信息;
wait()/waitpid()就是让父进程等待子进程
    1-> 如果所有子进程都在运行,父进程阻塞;
    2-> 如果有一个子进程结束,父进程取得子进程的退出信息并返回,父进程继续运行;
    3-> 如果没有子进程,父进程直接返回,继续运行;
    注:僵尸子进程用wait()/waitpid()回收;僵尸进程是已经终止但资源没有被回收的进程;所以wait()/waitpid()函数又叫殓(lian)尸工;
    如果一个子进程已经终止并且是僵尸进程,wait()会立即返回并取得该子进程的状态,否则阻塞;
二者的区别是
    在一个子进程终止前,wait()使其调用者阻塞,而waitpid()提供更多选择;

pid_t wait(int *status);//参数是status的地址
    wait()会让父进程等待任意子进程的结束,返回结束的子进程的PID,并把子进程的退出信息(是否正常退出和退出码)放入参数status参数中; 
    是否正常退出可以用WIFEXITED(status)判断,
    退出码用WEXITSTATUS(status)获取0-255;
/*
 * wait()函数演示
 */
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
    printf("current pid = %d\n", getpid());
    pid_t pid = fork();    //pid只是fork的返回值
    if (pid == 0) {
        /* 子进程执行的分支 */
        printf("child pid = %d\n", getpid());
        sleep(1);
        printf("child end\n");
        exit(10);
    }
    int stat;
    pid_t wpid = wait(&stat);
    /* 等待任意一个子进程的结束,
     * 参数为子进程退出码的地址
     * 返回等到的子进程的PID */
    printf("father go on\n");
    printf("endchild pid = %d\n", wpid);
    /* 判断子进程是否正常将结束 */
    if (WIFEXITED(stat)) {
        /* stat不能是指针,只能是数 */
        printf("进程是正常结束\n");
        /* 返回子进程的退出码 */
        printf("exit code: %d\n", WEXITSTATUS(stat));
    }
    return 0;
}

pid_t waitpid(pid_t pid, int *status, int options);
    可以等待指定的子进程;
    在等待的过程中父进程可以阻塞也可以不阻塞;
参数
    pid可以指定等待哪个/哪些子进程;
    options可以指定等待时是否阻塞;
pid的值
    -1,等待任意一个子进程的结束;
    >0,等待特定的子进程结束(子进程PID=pid);
    0,等待本进程组的子进程结束;
    <-1,等待进程组ID等于pid绝对值的子进程;
options的值
    0代表阻塞;
    WNOHANG代表非阻塞;如果options用了WNOHANG,返回有三种
        >0    等待到结束的子进程PID;
        0     没有子进程结束,直接返回;
        -1    出错了;
exit()不论参数是多少,都是正常结束进程,但一般用负数表示没有完成相关的功能;
/*
 * waitpid()函数练习
 * 一个父进程创建两个子进程
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
    pid_t pid1 = fork();
    pid_t pid2;
    if (pid1 > 0) {
        /* 父进程创建第2个子进程; */
        pid2 = fork();
    }
    if (pid1 == 0) {
        /* 子进程1执行的分支 */
        printf("pid1 = %d\n", getpid());
        sleep(1);
        printf("pid1 end\n");
        exit(-1);
    }
    if (pid2 == 0) {
        /* 子进程2执行的分支 */
        printf("pid2 = %d\n", getpid());
        sleep(3);
        printf("pid2 end\n");
        exit(20);
    }
    int stat;
    /* 在父进程中pid2是第2个子进程的pid,不是0; */
    pid_t wpid = waitpid(pid1 /*-1*/ , &stat, 0);
    /* -1等待任意一个子进程,>0等待特定的子进程; */
    /* 0代表阻塞, WNOHANG代表非阻塞; */
    printf("father end\n");
    printf("wpid = %d\n", wpid);
    if (WIFEXITED(stat)) {
        printf("进程正常结束\n");
        printf("exit code: %d\n", WEXITSTATUS(stat));
    }
    printf("end\n");
    return 0;
}

wait()和waitpid()的区别
    wait()是等待任意一个子进程的结束,等待过程必然阻塞;
    waitpid()可以等待指定的子进程结束(也可以任意),等待过程中父进程可以阻塞也可以不阻塞;


创建子进程的两种方式
    1-> fork()    复制父进程,创建子进程;
    2-> vfork()+execl()    创建全新的子进程;
pid_t vfork(void);
    create a child process and block parent;
    vfork()从语法上看,和fork()一样;但机制和fork()完全不同;
    vfork()不会复制父进程的任何资源;子进程会占用父进程的资源运行,父进程阻塞;直到子进程调用exec系列函数(比如:execl())或者子进程结束,资源就会还给父进程,解除父进程阻塞;
    用execl()函数可以让父子进程并行;

    vfork()函数只能创建新进程,但不提供程序;
    execl()只提供程序,不创建新的进程;
    vfork()+execl()既有进程,又有执行的程序;

fork()和vfork()函数的区别
    fork()要拷贝父进程的数据段;而vfork()不需要完全拷贝父进程的数据段,在子进程没有调用exec和exit()之前,子进程与父进程共享数据段;
    fork()不对父子进程的执行次序进行任何限制;而在vfork()调用中,子进程先运行,父进程挂起,直到子进程调用了exec或exit()之后,父子进程的执行次序才不再有限制;

    vfork()创建的子进程一定先于父进程运行,直到子进程运行了execl()函数才能同时运行;
    vfork()创建的子进程,如果不调用exec系列函数,必须用exit()强行退出,否则死循环;
    若使用vfork()在调用exec系列函数后,还要使用exit()函数,防止exec系列函数启动失败导致的死循环;
/*
 * vfork函数演示
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
    /* pid_t pid = fork(); */
    pid_t pid = vfork();
    /* vfork()创建的子进程会阻塞父进程并占用父进程资源 */
    if (pid == 0) {
        /* 子进程执行的分支; */
        sleep(1);
        printf("child\n");
        /* vfork()创建的子进程,如果不调用exec系列函数,
         * 必须用exit()强行退出,否则死循环; */
        exit(0);
    }
    printf("father\n");
    return 0;
}

execl()函数负责启动一个全新的程序;
格式
int execl(const char *path, const char *arg, ...);
    第1个参数是程序的全路径(路径/程序名),一定不能错;
    第2个参数是执行程序的命令(可以错),
    后面还可以跟可选参数,一般是选项或参数等,最后以NULL结束;
    失败返回-1,失败就意味着没有启动新程序;
    如果启动成功直接启动命令并退出,后面的语句不执行;
    注:execl()函数不会改变进程的PID,只会改变进程执行的代码(全新的程序);
/*
 * execl()函数演示
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    printf("begin\n");
    int res = 0;
    /* 路径如果错误,启动失败;命令错误没有关系; */
    res = execl("/bin/ls", "ls", NULL);
    /* res = execl("/bin/ls", "ls", "../", NULL); */
    /* res = execl("/bin/ls", "ls", "-al", "../", NULL); */
    /* 第1个参数表示程序路径,第2个参数就是命令; */
    /* 后面是可选参数; */
    /* 最后一个参数要为NULL; */
    printf("res = %d\n", res);
    printf("end\n");
    return 0;
}

vfork()+execl()练习
/*
 * vfork保证子进程先运行,
 * 子进程执行到execl时父子进程同时运行;
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
    pid_t pid = vfork();
    if (pid == 0) {
        /* 子进程执行的分支; */
        sleep(1);
        execl("/bin/pwd", "pwd", NULL);    //立刻将资源还给父进程;
        printf("child execl() failed\n");
        exit(0);    //防止execl启动失败导致的死循环;
    }
    printf("father\n");
    return 0;
}

验证execl()不启动新进程,只提供程序;
思路
    用vfork()创建子进程,在调用execl()函数之前打印vfork()创建的子进程PID,在execl()调用程序中打印一些子进程的PID,如果两个相等,意味着execl()没有创建新的子进程;
    打印PID的子进程的程序自己写一个;
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
    printf("current pid = %d\n", getpid());
    pid_t pid = vfork();
    if (pid == 0) {
        /* 子进程执行的分支; */
        //sleep(1);
        printf("main child pid = %d\n", getpid());    //获取进程PID
        printf("马上执行execl()\n");
        /* 首先编写打印自己pid的程序并编译为printpid.o */
        execl("./printpid.o", "printpid", NULL); //立刻将资源还给父进程;
        exit(0);    //防止execl启动失败导致的死循环;
    }
    printf("father is running ...\n");
    waitpid(pid, NULL, 0);    //让父进程等待子进程结束,防止僵尸进程
    printf("father go on\n");
    return 0;
}
/*
 * 打印自己pid的函数
 * gcc 07printpid.c -o printpid.o
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    printf("我是execl中调用的子函数pid = %d\n", getpid());
    return 0;
}


Unix信号管理
    信号(signal)
    Unix系统中,用信号实现软件中断;
    Ctrl+C        ->SIGINT
    段错误        ->SIGSEGV
    总线错误      ->SIGBUS
    浮点数例外    ->SIGFPE
    终端关闭      ->SIGHUP
    定时到期      ->SIGALARM
    Ctrl+\        ->SIGQUIT不同于信号2,会产生core dump文件;

中断的概念
    中断(interrupt)是程序中止(暂停)现在的代码,转而执行其他的代码;
    中断分为软件中断和硬件中断;软件中断就是用软件的方式中断程序,硬件中断就是硬件出故障导致程序中断;
    软件中断的主要方式就是信号;
    信号的本质是非负整数;每个信号都有一个宏名称,都以SIG开头,比如信号2是SIGINT宏;
    用命令kill可以查看/发送信号;
    kill -9 pid    给进程发信号9,用于结束进程;
    kill -l        字母l(list),可以查看所有的信号;
    
关于0做除数
    整数除以0会引发浮点数例外FPE,终止程序;
    浮点除以0会得到结果,结果是无穷大;

    Unix信号和Linux信号不同,linux:0-64,中间不连续;Unix:0-48,此外,有些信号对应的值也不相同;因此编程时尽量使用信号的宏名称,而不要用数值;
    信号是异步处理方式;无法判断信号什么时候会来,因此就无法知道什么时候处理信号;
    信号0有特殊用途,本身不代表任何的事件,也不会处理;用于测试是否有权限发信号;
    kill -0 1
    进程之间可以互相发信号,但受到用户权限的影响;用户只能给自己的进程发信号,不能给其他用户的进程发信号;root可以给所有进程发信号;

    硬件故障和函数调用都可能产生信号;
信号的分类
    不可靠信号//这种信号不支持排队,因此有可能丢失,是非实时信号;
            //1-31都是不可靠信号;
    可靠信号//支持排队,因此不会丢失,是实时信号;
            //34-64都是可靠信号;
    
程序收到信号以后的处理方式
    1-> 默认处理方式,80%的默认处理方式是退出进程;
    2-> 忽略信号,不做任何处理;
    3-> 程序员可以自定义信号的处理方式,只需要写一个信号处理函数;
    信号9不能被忽略,也不能自定义;

信号处理的实现步骤
    1-> 写一个信号处理函数;
    2-> 用signal()/sigaction()注册信号处理方式;
#include <signal.h>
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler函数指针);
    将信号与处理方式绑定在一起;
    第2个参数为函数指针 void (*fa)(int),函数为void类型,参数为int;
    函数返回函数指针格式,即返回函数;
    失败返回SIG_ERR;
当signal(信号, 函数指针)执行完毕后,只要有信号来,系统就会调用函数指针所对应的函数;
    第2个参数决定了信号的处理方式,可以是
        SIG_IGN        忽略;
        SIG_DFL        默认处理(一般都是恢复成默认);
        函数指针    自定义函数的处理方式;
/*
 * signal()函数演示
 * 再用命令kill发信号9和11试试
 */
#include <stdio.h>
#include <signal.h>
void func(int signo) {        //signo就是信号
    printf("捕获到信号%d\n", signo);
    signal(SIGINT, SIG_DFL);    //恢复信号2默认处理方式
    printf("信号2已恢复默认\n");
}
int main() {
    signal(SIGINT, func);    //把信号2该成自定义func处理;
    signal(SIGQUIT, SIG_IGN);    //把信号3改为忽略(Ctrl+\);
    signal(SIGKILL, func);    //信号9只能默认,但不报错;
    //signal(SIGINT, SIG_DFL);
    printf("pid = %d\n", getpid());
    while (1) ;
    return 0;
}

