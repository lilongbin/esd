子进程的信号处理
发信号的方法
信号集
信号屏蔽

回顾
    进程管理//wait()/waitpid()可以让父进程等待子进程的结束,并负责获取子进程的退出信息;
    waitpid()可以有更多选择//可以选择是否阻塞/等待哪个进程;
    守护进程在后台运行;
    shell脚本编程对系统运维或嵌入式方向更有意义;
    进程创建的第二种方法vfork()+execl();//合作型;
        子进程执行的是全新的代码(与父进程无关);
    信号//信号就是用来做中断的,属于软件中断;
    服务器集群:负载均衡/内存(复制)共享
信号分类:可靠信号和不可靠信号
信号处理方式
    1.默认;2.忽略;3.自定义处理函数;
设置信号处理方式
    1.如果不设置将进行默认处理;
    2.用signal()/sigaction()可以设置;
答疑
    1.execl()是以新换旧;提供新运行的程序,但不会换进程号;
    2.signal()的返回值可以用来判断是否出错了;
    3.程序在运行期间任何时候都可以接收信号,也可以屏蔽信号;接收的信号不一定会处理;


子进程的信号处理
    如果创建了子进程,
    fork()创建的子进程完全沿袭父进程的信号处理方式,
    vfork()+execl()创建的子进程,父进程默认子进程也默认,父进程忽略子进程也忽略,父进程自定义处理函数子进程默认;
    原因是vfork()+execl()创建的子进程代码区没有父进程的处理函数;
    忽略和默认的宏所有的进程都可以共享,所以能够继承;
/*
 * fork()与信号处理
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void fa(int signo) {
    printf("捕获了信号%d\n", signo);
}
int main() {
    if (signal(SIGINT, fa) == SIG_ERR) {
        //先设置再判断//信号2自定义
        perror("signal 2"), exit(-1);
    }
    signal(SIGQUIT, SIG_IGN); //信号3忽略;
    pid_t pid = fork();
    if (pid == 0) {
        /* 子进程执行分支 */
        printf("chpid = %d\n", getpid());
        while (1) ;
        /* 分别用kill给子进程发信号验证子进程信号的处理方式 */
        exit(0);
    }
    printf("father pid = %d\n", getpid());
    printf("father over\n");
    return 0;
}

/*
 * vfork()+execl()信号处理方式
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void fa(int signo) {
    printf("捕获了信号%d\n", signo);
}
/* 练习写代码验证vfork()+execl()子进程对信号的处理方式 */
int main() {
    if (signal(SIGINT, fa) == SIG_ERR) {
        /* 先设置再判断//信号2自定义 */
        perror("signal 2"), exit(-1);
    }
    signal(SIGQUIT, SIG_IGN);    //信号3忽略;
    pid_t pid = vfork();
    if (pid == 0) {
        /* 子进程执行分支 */
        printf("chpid = %d\n", getpid());
        /* 分别使用kill命令给子进程发信号验证处理方式 */
        execl("./proc", "proc", NULL);
        /*
         * //proc.c
         * #include <stdio.h>
         * int main() {
         *     printf("%d\n", getpid());
         *     while (1) ;
         *     return 0;
         * }
         */
        //while(1);
        exit(0);
    }
    printf("father over\n");
    return 0;
}
    
killall a.out    可以结束所有的a.out进程;

发信号的方法
    1.键盘发送信号(部分信号);
        Ctrl+C    发送信号2,SIGINT;
        Ctrl+\    发送信号3,SIG_QUIT;
    2.出错(部分信号);
        整数除以0   信号8,SIGFPE;
        段错误      信号11,SIGSEGV;
        总线错误    信号7,SIGBUS;
    3.kill命令发送(全部信号);格式:
        kill -信号 进程PID
    4.信号发送函数
        raise()       给本进程发任意信号;
        kill()        给任意进程(或进程组)发任意信号;
        alarm()       给本进程发特定信号(闹钟);
        sigqueue()    给任意进程发任意信号,可以附带额外的数据(少用);

    主讲kill()函数,了解alarm();
int kill(pid_t pid, int signo);
参数
    pid指定发给哪个/哪些进程;
    signo就是发送哪个信号;
pid有4种值
    >0       给进程ID=pid的特定进程发信号;
    -1       给所有有权限的进程发信号;
    0        给本进程组的进程发信号;
    <-1      给进程组ID=-pid的进程发信号;
/*
 * kill()函数练习
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void fa(int signo) {
    printf("进程%d捕获到了信号%d\n", getpid(), signo);
}
int main() {
    pid_t pid = fork();
    if (pid == 0) {
        signal(SIGINT, fa);    //子进程注册信号处理方式
        while (1) ;
    }
    printf("父进程%d给子进程发信号\n", getpid());
    sleep(1);
    kill(pid, SIGINT);
    return 0;
}

unsigned int alarm(unsigned int seconds);
    seconds秒之后产生一个闹钟信号,SIGALRM;不会产生第2个;
    如果seonds为0,将不会有新的闹钟被注册,意味着取消所有闹钟;
    如果之前已经注册过alarm()但还未到时,将被取消;
如果当前没有正在运行的闹钟,将返回0;
如果还有没结束的闹钟,将返回前面的闹钟剩余的秒数;
    可以用来做一些计划任务;
/*
 * alarm()函数使用
 */
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
void fa(int signo) {
    printf("捕获了信号%d\n", signo);
}
int main() {
    signal(SIGALRM, fa);
    alarm(1);
    sleep(2);
    unsigned int res = alarm(5);    //如果前面没有正在运行的闹钟,返回0;
    printf("res = %u\n", res);
    sleep(3);
    res = alarm(5);        //返回之前闹钟的剩余秒数;
    printf("res = %u\n", res);
    sleep(1);
    res = alarm(5);        //返回之前闹钟的剩余秒数;
    printf("res = %u\n", res);
    while (1) ;
    return 0;
}

unsigned int sleep(unsigned int seconds);
    会使调用的线程休眠,直到seconds到时;或者被没有忽略的信号中断;
    可能休眠seconds秒;也可能被非忽略的信号打断,并返回剩余秒数;
    睡足seconds秒后返回0,被信号中断返回剩余秒数;

int usleep(useconds_t usec);
    usleep()是微秒(microsecond)级的休眠函数;
    成功返回0,失败返回-1;
microsecond微秒us
milisecond毫秒ms
/*
 * sleep()函数演示
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void fa(int signo) {
    printf("捕获了信号%d\n", signo);
}
void print();
int main() {
    signal(SIGINT, fa);//为了不让信号退出进程,方便看到sleep效果
    printf("begin\n");
    unsigned int res = sleep(10); //睡足返回0,被信号打断返回剩余秒数;
    /* sleep()会被未忽略的信号中断; */
    printf("sleep() return value = %u\n", res); //返回剩余秒数
    print();
    printf("over\n");
    return 0;
}
/* usleep()是微秒级的休眠;10的-6次方 */
void print() {
    int i = 0;
    while (i++ <= 10) {
        printf("%d ", i);
        usleep(100000); //0.1s
        fflush(NULL);
    }
    printf("\n");
}

如果用一个int类型表示一个信号有无似乎有些浪费资源,可以考虑只用一个二进制位来表示信号的有无;
    long long int 是标c的64位整数;
    32位的有符号整数大致范围在正负21亿;即0x80000000到0x7FFFFFFF之间;
    32位的无符号整数大致范围在0到42亿;即0x00000000到0xFFFFFFFF之间;
做软件要考虑到扩展性,兼容性,健壮型,可移植性;
思考,如何存储一个50位的超大整数;
    方法1,以字符串形式存放;3 + '0' = '3';
    方法2,定义一个结构体,结构体里面分段存储;

信号集
    信号集就是信号的集合,可以理解成一个超大的整数(为了操作系统的扩展性);
    用一个二进制位对应一个信号(1代表有,0代表无);
    最后一位代表信号1,如果最后一位是1代表信号集中有信号1,如果是0,就没有信号1;
    信号集的类型    sigset_t;
    使用sizeof关键字可以获得sigset_t类型的大小,实际是128字节的超大整数;

对比数据结构
数据结构中逻辑结构包括
    1-> 集          元素之间没有任何关系,除了在一个集里面;
    2-> 线性结构    元素之间是前后一对一的关系;
    3-> 树形结构    元素之间是一对多的父子关系;
    4-> 网状结构    元素之间是多对多的网格关系;
物理结构
    线性和链表
运算结构
    1-> 创建和删除;
    2-> 增加元素和删除元素;
    3-> 修改和查找;
    4-> 排序和其他算法;

关于数据结构sigset_t,需要提供基本的函数如下
    1-> 增加元素
        sigaddset()      增加一个信号(将对应二进制位置1);
        sigfillset()     放入所有信号(全部增加);
    2-> 删除信号
        sigdelset()      删除一个信号(将对应二进制位置0);
        sigemptyset()    清空信号集(全部删除);
    3-> 查找信号
        sigismember()    判断信号是否存在信号集中;
int sigemptyset(sigset_t *set);
int sigfillset(sigset_t *set);
int sigaddset(sigset_t *set, int signum);
int sigdelset(sigset_t *set, int signum);
    成功返回0,失败返回-1;
int sigismember(const sigset_t *set, int signum);
    存在返回1,不存在返回0,失败返回-1;
/*
 * 信号集练习
 */
#include <stdio.h>
#include <signal.h>
void print(const sigset_t *set, int size) {
    int i = size;
    char *p = (char *)set;
    printf("0x");
    while (i-- > 0) {
        printf("%02x", p[i]);
    }
    printf("\n");
}
int main() {
    printf("set size = %d\n", sizeof(sigset_t)); //128
    /* sigset_t的大小是128字节,可以容纳128*8个信号; */
    sigset_t set;
    printf("清空前set: "); print(&set, sizeof(sigset_t));

    /* 清空信号集 */
    sigemptyset(&set);    //清空set
    printf("清空后set: "); print(&set, sizeof(sigset_t));

    /* 增加信号 */
    sigaddset(&set, 1); //第1个bit置1
    printf("放入1, set: "); print(&set, sizeof(sigset_t));
    sigaddset(&set, 2);
    printf("放入2, set: "); print(&set, sizeof(sigset_t));
    sigaddset(&set, 3); //第3个bit置1
    printf("放入3, set: "); print(&set, sizeof(sigset_t));
    sigaddset(&set, 7);
    /* printf("放入7, set = %d\n", set); */
    printf("放入7, set: "); print(&set, sizeof(sigset_t));
    /* 删除信号 */
    sigdelset(&set, 3); //第3个bit清0
    /* printf("删除3, set = %d\n", set); */
    printf("删除3, set: "); print(&set, sizeof(sigset_t));

    /* 查找信号 */
    if (sigismember(&set, 2)) {
        printf("信号2在信号集中\n");
    } else {
        printf("信号2不在信号集中\n");
    }
    return 0;
}

信号屏蔽
    在执行一些关键代码时,进程需要屏蔽一些信号,防止信号中断关键任务;
    信号屏蔽无法保证信号不来,但信号可以暂时不做处理,不会中断关键代码;等到关键代码执行完毕,解除信号屏蔽时再中断代码,返回执行信号处理的函数;
    函数sigprocmask()负责信号屏蔽和解除信号屏蔽;
int sigprocmask(int how, const sigset_t *newset, sigset_t *oldset);
参数
    newset    代表需要屏蔽的信号(集);//传入的参数
    oldset    代表传出旧的信号屏蔽字(不用传出给NULL);//传出的参数;
    how是运算的方式
        SIG_BLOCK      旧的+新的,比如
            abc + cde -> abcde
        SIG_UNBLOCK    旧的-新的,比如
            abc - cde -> ab
        SIG_SETMASK    直接使用新的,不考虑旧的,比如
            abc  cde -> cde
        注:how直接选择SIG_SETMASK即可;

    sigset_t pend;
    sigpending(&pend);可以取屏蔽期间哪些信号来过;
int sigpending(sigset_t *set);
    可以将屏蔽期间捕获的信号存入set中;
    成功返回0,失败返回-1;
/*
 * sigprocmask()信号屏蔽练习
 */
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
void fa(int signo) {
    printf("捕获了信号%d\n", signo);
}
int main() {
    signal(SIGINT, fa);    //不可靠信号不支持排队,屏蔽时丢失;
    signal(SIGQUIT, fa); //只能知道该信号来过;
    signal(50, fa);        //可靠信号支持排队,屏蔽时不丢失;
    printf("pid = %d\n", getpid());
    printf("执行普通程序,不屏蔽信号\n");
    sleep(20);
    printf("++++++++++++++++++++++++\n");
    printf("执行关键程序,屏蔽信号\n");
    sigset_t new, old;
    sigemptyset(&new);
    sigaddset(&new, SIGINT);
    sigaddset(&new, SIGQUIT);
    sigaddset(&new, 50); //已准备号待屏蔽的信号
    sigprocmask(SIG_SETMASK, &new, &old); //屏蔽
    sleep(15);
    printf("关键代码执行完毕,将解除屏蔽\n");
    sigset_t pend;
    sigpending(&pend); //解除屏蔽前取信号屏蔽期间哪些信号来过;
    printf("------------------------\n");
    sigprocmask(SIG_SETMASK, &old, NULL); //解除屏蔽
    printf("已解除屏蔽\n");
    int i = 0;
    for (i = 1; i <= 63; i++) {
        /* if (sigismember(&pend, SIGINT)) { */
        if (sigismember(&pend, i)) {
            printf("信号屏蔽期间,信号%d来过\n", i);
        }
    }
    sleep(10);
    return 0;
}

