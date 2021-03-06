IPC进程间通信
管道
共享内存
消息队列

回顾
    信号//信号的处理方式/父子进程之间信号处理方式的继承/信号集(一个超大整数)/信号屏蔽;
    sigprocmask()//设置信号屏蔽字;
    
答疑
    shell脚本属于解释型语言;运行一句解释一句,不做整体检测;脚本语言相当于一系列命令的集合;系统运维工程师需要掌握的工具;

IPC
    进程间通信(两个/多个进程数据交互);
    了解:信号应用中的计时器;

用指定的初始间隔和重复间隔时间为进程设定号一个计时器后,该计时器就会定时的向进程发送时钟信号;
Linux为每个进程维护3个计时器,分别是
    真实计时器SIGALRM
        计算程序运行的实际时间;
    虚拟计时器SIGVTALRM
        计算程序在用户态时所消耗的时间;
    实用计时器SIGPROF
        计算程序处于用户态和内核态所消耗的时间;

获取计时器的设置
int getitimer(int which, struct itimerval *value);
设置计时器:
int setitimer(int which, const struct itimerval *new_value,
                        struct itimerval *old_value);

struct itimerval {
    struct timeval it_interval; //next value
    struct timeval it_value;    //current value
};
struct timeval {
    long tv_sec;       //seconds
    long tv_usec;      //microseconds
};
/*
 * setitimer()定时器
 */
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
void fa(int signo) {
    printf("I am a superman!\n");
}
int main() {
    signal(SIGALRM, fa);
    /* 设置计时器 */
    struct itimerval timer;
    /* 开始时间 */
    timer.it_value.tv_sec = 3;    //开始秒数
    timer.it_value.tv_usec = 0;    //开始微秒数;
    /* 间隔时间 */
    timer.it_interval.tv_sec = 1;    //间隔的秒数;
    timer.it_interval.tv_usec = 0;    //间隔的微秒数
    setitimer(ITIMER_REAL, &timer, NULL);
    while (1);
    return 0;
}
/*
 * setitimer()定时器
 */
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
void fa(int signo) {
    printf("I am a superman %d !\n", signo);
}
int main() {
    signal(SIGPROF, fa);
    /* 设置计时器 */
    struct itimerval timer, otv;
    timer.it_value.tv_sec = 3;    //开始秒数
    timer.it_value.tv_usec = 0;    //开始微秒数;
    timer.it_interval.tv_sec = 1;    //间隔的秒数;
    timer.it_interval.tv_usec = 0;    //间隔的微秒数
    setitimer(ITIMER_PROF, &timer, &otv); //似乎没有捕获到
    //不确定这样的使用方式是否正确,待解
    while (1) {
        printf("hello\n");
        sleep(1);
        /* kill(getpid(), SIGPROF); */
    }
    return 0;
}


IPC进程间通信Inter Process Communication
进程间的通信方式
    1-> 文件;
    2-> 信号;
    3-> 管道;
    4-> 共享内存;
    5-> 消息队列;
    6-> 信号量集(semaphore);
    7-> 网络(套接字socket);
    ...
    其中,共享内存,消息队列和信号量集遵守相同的规范,叫XSI IPC;最重要的是消息队列;
    IPC的应用基本上遵循一个固定的套路,在编程时只需要按照固定的步骤调用相应的函数即可;
    消息队列,信号量和共享内存统称为XSI IPC;

管道
    管道是Unix最古老的IPC方式之一,目前较少使用;
    历史上它是半双工的(数据只能在一个方向流动),现在很多系统都提供全双工管道;
    管道分为有名管道和无名管道;
    有名管道可以用于各种进程的IPC; mkfifio()函数用于创建有名管道文件;

进程A          进程B        动作
建立管道文件                mkfifo
打开管道       打开管道     open
读写数据       读写数据     read/write
关闭管道       关闭管道     close
删除管道                    unlink

    无名管道只能用于fork()创建的父子进程之间的IPC;
    管道(pipe)的交互媒介是一种特殊的文件即管道文件;管道文件的创建必须用mkfifo命令或mkfifo()函数,touch不能创建管道文件;管道文件的后缀是.pipe;
    管道文件只做交互的媒介,不存储数据;因此只有在输入输出都存在时,才畅通,否则就卡住;
练习新建一个管道文件,用echo命令和cat命令测试以下;
        mkfifo test.pipe
        echo "hello" > test.pipe
        会卡在这里等待下一步操作
        再开启一个终端,然后
        cat test.pipe

编写两个程序,一个发送整数0-99,另外一个接收,采用管道的方式;
思路
    新建一个管道文件,然后发送的进程写文件,接收的进程读文件即可;
/*
 * 管道练习a发送
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main() {
    int res = mkfifo("test.pipe", 0666);
    if (res == -1) {
        perror("mkfifo"); exit(-1);
    }
    /* open()的O_CRET是建立不了管道文件的,只能使用mkfifo */
    /* open()函数只能创建普通文件 */
    int fd = open("test.pipe", O_WRONLY); //写
    /* 对管道文件不要使用O_RDWR,
     * 否则系统会认为既是读管道又是写管道,直接运行; */
    if (fd == -1) {
        perror("open"), exit(-1);
    }
    int i;
    for (i = 0; i <= 99; i++) {
        write(fd, &i, 4);
        usleep(100000);    //0.1s
        printf("发送%d ", i);
        if (!(i % 10))
            printf("\n");
    }
    printf("\n");
    close(fd);
    return 0;
}
/*
 * 管道练习b接收
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main() {
    int fd = open("test.pipe", O_RDONLY); //读
    if (fd == -1) {
        perror("open"), exit(-1);
    }
    int i;
    for (i = 0; i <= 99; i++) {
        int x;
        read(fd, &x, 4);
        printf("接收到%d\n", x);
    }
    close(fd);
    return 0;
}

共同的使用方法
    1.创建时都需要使用key,key是一个整数,外部程序使用key来获取内核中的IPC结构(共享内存/消息队列和信号量集,也就是交互媒介);
    2.key的生成方式有三种
        a.宏IPC_PRIVATE直接做key,这种基本不使用;只能创建IPC结构,别的进程不能调用;
        b.定义一个头文件,把所有的key写在头文件中;
        c.函数ftok()可以用一个真实存在的目录和一个人工分配的项目ID(0-255有效,即低8位有效)自动生成一个key;
    3.所有的IPC结构在内核中对应一个唯一的ID,标识每一个IPC结构;
    4.key是用来查找ID的,ID是用来定位IPC结构的;key -> ID -> IPC结构;
        //key是外部的,只有找到ID之后才可以定位IPC结构;
        函数xxxget(),比如shmget(key,...)取共享内存;msgget(key,...)取消息队列;可以用key取得ID,后续的代码使用ID即可;
    5.创建IPC结构时,都需要提供一个flags参数,这个参数一般是
        0666 | IPC_CREAT | IPC_EXCL
        权限   创建IPC    如果存在,直接返回-1代表出错;
    6.每种IPC结构都需要提供一个操作函数
        xxxctl(),它至少包括以下功能
        a-> IPC_STAT    取IPC结构的相关属性(查看);
        b-> IPC_SET     修改IPC结构的部分属性;
        c-> IPC_RMID    删除IPC结构;
    注意:IPC结构由内核管理,如果不删除,重启后依然存在;用完记得删除;

关于IPC相关命令
    ipcs    查看IPC结构;
        ipcs -a    查看所有;
        ipcs -m    共享内存;
        ipcs -q    消息队列;
        ipcs -s    信号量集;
    ipcrm    删除IPC结构;需要指定结构的ID;
        ipcrm -m ID 删除共享队列
        ipcrm -q ID 删除消息队列
        ipcrm -s ID 删除信号量集
    
共享内存
    共享内存是以一块内存作为IPC交互的媒介,这块内存由内核维护和管理,允许其他进程映射;
    IPC中共享内存效率高;
    共享内存最大的问题就是多进程同时修改时很难控制;

                 编程模型
     服务进程             客户进程           动作
使用约定文件创建key  使用约定文件创建key    ftok()
使用key创建共享内存  使用key创建共享内存    shmget()
挂接到共享内存       挂接到共享内存         shmat()
使用内存             使用内存
卸载共享内存         卸载共享内存           shmdt()
释放共享内存                                shmctl()

共享内存的使用步骤
    1.创建key;
        可以使用头文件定义或ftok()函数;
        key_t ftok(const char *pathname, int proj_id);
        参数是真实存在的文件路径和非零的项目id;
    2.用key创建/获取ID;
        得到key后使用shmget(key,...)函数创建/获取共享内存ID;
        #include <sys/shm.h>
        int shmget(key_t key, size_t size, int shmflg);
            size//共享内存的大小(字节);//获取时设为0即可;
            shmflag//一般是0666|IPC_CREAT|IPC_EXCL;//获取时设为0即可;
            成功返回虚拟内存首地址,失败返回-1;
    3.挂接;
        使用shmat(ID)函数挂接(映射)共享内存;
        void *shmat(int shmid, const void *shmaddr, int shmflg);
            shmaddr为0时,系统自动分配地址;
            后面两个参数设为0即可;
            成功时返回共享的虚拟内存的首地址;
    4.正常使用;
    5.脱接;
        使用shmdt(ID)函数脱接(解除映射)共享内存;
        int shmdt(const void *shmaddr);
            参数为挂接时返回的首地址;
    6.删除;
        int shmctl(int shmid, int cmd, struct shmid_ds *buf);
        如果确定不再使用,需要使用函数shmctl(id,IPC_RMID,NULL)删除共享内存;
/*
 * IPC共享内存a
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
/* 创建共享内存,并存入数据 */
int main() {
    //1创建key
    key_t key = ftok(".", 100);    //路径不存在会失败;
    if (key == -1) {
        perror("ftok"), exit(-1);
    }
    //2用key创建ID
    int shmid = shmget(key, 4, 0666 | IPC_CREAT | IPC_EXCL);    //
    /* 新建时需要3个参数,获取时后两个参数为0即可; */
    if (shmid == -1) {
        perror("shmget"), exit(-1);
    }
    printf("共享内存创建成功\n");
    //3挂接
    void *p = shmat(shmid, 0, 0);    //挂接
    if (p == (void *)-1) {
        perror("shmat"), exit(-1);
    }
    //4使用
    int *pi = p;
    *pi = 100;
    sleep(10); //使用ipcs -m 可以查看挂接数
    //练习:写shmb.c把100从共享内存中读出来;
    //5脱接
    shmdt(p);        //脱接
    //6删除
    /* shmctl(shmid, IPC_RMID, 0);//删除 */
    return 0;
}
/*
 * IPC共享内存b
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int main() {
    //1创建key
    key_t key = ftok(".", 100);
    if (key == -1) {
        perror("ftok"), exit(-1);
    }
    //2用key获取ID
    int shmid = shmget(key, 0, 0);
    /* 获取的时候后两个参数给0就可以 */
    if (shmid == -1) {
        perror("shmget"), exit(-1);
    }
    printf("获取共享内存\n");
    //3挂接
    void *p = shmat(shmid, 0, 0);
    if (p == (void *)-1) {
        perror("shmat"), exit(-1);
    }
    //4使用
    int *pi = p;
    printf("*pi = %d\n", *pi);
    //5脱接
    shmdt(p);
    sleep(1);
    //6删除
    shmctl(shmid, IPC_RMID, 0);
    printf("共享内存已删除\n");
    return 0;
}


消息队列
    应用最广,IPC中的重点
    把数据放入消息中,把消息放入队列中;队列由内核负责创建和维护;
消息队列的使用步骤
    1.用ftok()或头文件定义方式生成key;
    2.用key创建/获取消息队列的ID;
        msgget(key, ...);
        int msgget(key_t key, int msgflg);
        成功返回ID,失败返回-1;
    3.发送消息/接收消息;
    msgsnd()    //放入/发送消息;
    msgrcv()    //取出/接收消息;
    int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
    msgsnd(ID, 消息首地址, 消息长度, 0/IPC_NOWAIT);
    在使用有类型的消息时,第二个参数地址是整个结构的地址,第三个参数大小值是数据区的大小(不包括消息类型mtype);
    ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);
    msgrcv(ID, 接收变量首地址, 接收变量buf大小, 消息类型/*0代表接收所有类型*/, 0/IPC_NOWAIT);
    4.如果确定不再使用消息队列,需要删除;
    int msgctl(int msqid, int cmd, struct msqid_ds *buf);
        msgctl(msgid, IPC_RMID, struct msgid_ds *buf);
    注意所有的函数名是msg而不是msq,或许是由于历史原因,应该小心;
可以用msgctl(msgid, IPC_STAT, &msqid_ds)查询消息队列的信息;
    查询结果放在msqid_ds的结构体指针所对应的变量中;
/*
 * 消息队列a
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main() {
    //1生成key
    key_t key = ftok(".", 200);
    //2创建消息队列的ID
    int msgid = msgget(key, 0666 | IPC_CREAT);
    /* IPC_EXCL不要,因为第二次放入时队列已经存在会失败; */
    if (msgid == -1) {
        perror("msgget"), exit(-1);
    }
    printf("消息队列创建成功\n");
    //3发送消息
    int res = msgsnd(msgid, "hello", 5, 0); /*IPC_NOWAIT非阻塞 */ 
    if (res == -1) {
        perror("msgsnd"), exit(-1);
    }
    printf("send ok !\n");
    /* 练习:写msgb.c用msgrcv()把消息取出来并打印; */
    return 0;
}
/*
 * 消息队列b
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
int main() {
    //1生成key
    key_t key = ftok(".", 200);
    //2获取消息队列的ID
    int msgid = msgget(key, 0);    //接收时最后一个参数为0
    if (msgid == -1) {
        perror("msgget"), exit(-1);
    }
    printf("消息队列获取成功\n");
    //3接收消息
    printf("消息队列recieving...\n");
    char buf[50] = { };
    ssize_t res = msgrcv(msgid, buf, sizeof(buf), 0, 0);
    /* 前一个0表示接收任意类型的消息,后一个表示阻塞 */
    if (res == -1) {
        perror("msgrcv"), exit(-1);
    }
    printf("收到了%d字节,内容%s\n", res, buf);
    //4删除消息队列
    if (!msgctl(msgid, IPC_RMID, NULL)) {
        printf("消息队列已删除\n");
    }
    return 0;
}
思考,如果消息被放入到消息队列中,本来是发给进程B的,但由于进程A先起来了,于是就把消息取走了,如何才能避免这种情况呢;
给每个消息贴上一个标签用于标识类型;

消息类型
    消息分为有类型消息和无类型消息;
    无类型消息 <==> 数据
        可以使用任意类型;
        比如可以是int,double,字符串,结构,联合;
        这种消息严格遵守先进先出;
    有类型的消息 == 消息类型 + 数据
        因此必须是结构体类型;格式如下
    struct 消息名/*可自定义*/ {
        long mtype;//第一个成员必须是消息类型;
        ...//后面可以随便写,是自定义的数据;
    };
    msgsnd()发送有类型消息时,没有特殊要求;
    msgrcv()接收有类型消息时,可以使用第4个参数选择接收消息的类型;
        其中mtype必须大于0; 负数和0有特殊用途;
    msgrcv()第4个参数(long msgtype)可能的值
        1-> 正数    接收指定类型的消息;
        2->  0      接收任意类型的消息(先进先出);
        3-> 负数    接收小于等于flags绝对值的消息,次序是先小后大;

number  a b c d e f g h
msgtype 2 5 3 1 2 3 1 4
假如msgrcv()函数中接收类型是
    3  : c f 阻塞或返回-1;
    0  : a b c d e f g h 阻塞或返回-1;
    -3 : d g a e c f 阻塞或返回-1;
/*
 * 消息队列,按类型接收消息a
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>
struct Msg {
    long mtype;        //消息类型
    char buf[20];    //存储有效数据;
};
/* int msgid; */
void fa(int signo) {
    //信号处理函数无法传参,因此可以定义全局变量,也可重新获取
    key_t key = ftok(".", 100);
    int msgid = msgget(key, IPC_CREAT | 0666);
    //练习:使用msgctl(msgid,IPC_STAT,结构指针)判断消息数是否为0再清空;
    //或者关闭时将消息队列写入文件,启动时再加载进来;
    printf("捕获信号%d\n", signo);
    if (signo == 2) {
        struct msqid_ds mds;
        if (!msgctl(msgid, IPC_STAT, &mds)) {
            if (mds.msg_qnum <= 0) {
                msgctl(msgid, IPC_RMID, 0);
                printf("消息队列%d已经删除\n", msgid);
            } else {
                printf("消息队列%d还有%d个msg\n", msgid, mds.msg_qnum);
            }
        }
        printf("消息队列设置恢复默认\n");
        printf("进程已退出\n");
        signal(SIGINT, SIG_DFL);
        exit(0);    //退出进程
    }
}
int main() {
    key_t key = ftok(".", 100);
    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget"), exit(-1);
    }
    struct Msg msg1, msg2;
    msg1.mtype = 1; strcpy(msg1.buf, "zhangfei");
    msg2.mtype = 2; strcpy(msg2.buf, "guanyu");
    /* 注意发送的时候,大小只是数据的大小,不包括数据类型 */
    msgsnd(msgid, &msg1, sizeof(msg1.buf), 0);
    msgsnd(msgid, &msg2, sizeof(msg2.buf), 0);
    printf("pid = %d\n", getpid());
    signal(SIGINT, fa);
    while (1);    //为了回收消息队列的资源(删除);
    return 0;
//在msgtypea中写用信号2删除消息队列的代码
}

/*
 * 消息队列,按类型接收消息b
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
struct Msg {
    long mtype;        //消息类型
    char buf[20];    //存储有效数据;
};
int main() {
    key_t key = ftok(".", 100);
    int msgid = msgget(key, 0);
    if (msgid == -1) {
        perror("msgget"), exit(-1);
    }
    struct Msg msg;
    int res, num;
    for (num = 2; num >= 0; num--) {
        /* 接收类型为num的消息 */
        res = msgrcv(msgid, &msg, sizeof(msg.buf), num, 0);
        printf("接收了%d字节数据,类型:%d,内容:%s\n",
                   res, msg.mtype, msg.buf);
    }
    return 0;
}

在使用有类型的消息时,第2个参数地址是整个结构的地址,但第3个参数大小只是数据区的大小(不包括消息类型msgtype):

资源的管理一般遵循谁创建谁回收的原则    

