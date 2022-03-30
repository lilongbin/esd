信号量集
网络编程常识
一些Socket编程的概念
模拟银行ATM系统分客户端和服务器端


程序员对工作的能力其实就是编码
编写代码并不困难,难的是商业建模;

模拟银行ATM系统分客户端和服务器端

客户端的工作
    1.提供界面,给客户选择;
    2.允许客户输出数据并提交(scanf());
    3.把数据封装在消息中,放入客户端发服务器的消息队列中(提交);
    4.等待服务器返回的处理结果;处理结果去服务器发回客户端的消息队列中找;把处理结果打印出来;
服务器端的工作:
    1.先启动服务器,在启动服务器的同时做一些初始化的工作,同时创建两个消息队列;
    2.等待客户端的请求;随时监控客户端发给服务器的消息队列;
    3.如果有消息,取出并处理(按消息类型),并把处理结果放入从服务器发给客户端的消息队列中;
    4.资源的回收;用信号关闭服务器,在关闭服务器的同时回收各种资源,尤其是两个消息队列的删除;
    
今天:
    IPC信号量集
    网络和线程

信号量集(semaphore arrays)
    信号量集和信号(signal)没有关系,是一个信号量的数组;
    信号量集就是信号量数组,信号量就是一个计数器;
    //如同马与马虎马上看起来很相似,其实没关系
    信号量是一个计数器,用于控制访问共享资源的最大并行(同时运行)进程/线程总数;
    假如信号量是3,有5个进程:1先进,结束;2 3 4同时上,2结束,5再上
    计数器有两种工作方式:
        1.自增型;开始时计数0,来一个自增1,走一个自减1,到计数最大值后不允许再来;
        2.自减型;开始计数就是最大值,来一个自减1,走一个自增1,计数到0就阻塞,直到有其他进程结束,计数不再是0;//便于编程维护
    如果进程需要访问多个共享资源,需要多个计数器,而多个计数器就使用信号量集(信号量数组);
    信号量集其实是进程间的调度,并不能真正的互发数据;

信号量集的编程步骤
    1.使用ftok()或者头文件生成key;
    2.使用semget(key,...)创建/获取信号量集;
        int semget(key_t key, int nsems/*数组大小*/, int semflg);
    3.使用semctl(semid,...)给每个信号量集中的每个信号量赋值;//给数组中的每个元素赋值;
    4.使用信号量集semop();
    5.如果不再使用,可以用semctl(semid,0,IPC_RMID)删除;//与之前略有不同;

函数注解
    semctl()初始化信号量集中的每个信号量,格式:
    semctl(semid, int index, int cmd, ...)
        如果cmd是SETVAL,可以给信号量集中的一个成员赋值,index是信号量集的下标,第四个参数就是初始值;比如:
        setctl(semid, 0, SETVAL, 5)//给第1个信号量最大计数设置为5;
        失败返回-1;可以使用errno;
        
    semop()用于计数的+1和-1;
    int semop(int semid, struct sembuf semoparray[], size_t nops);
    参数nops为信号量数组的大小;
    参数semoparray是一个指针,它指向一个信号量数组,信号量操作由sembuf结构表示:
    struct sembuf{
        unsigned short sem_num;/* 操作信号量的下标 */
        short         sem_op; /* 对信号量的操作方式:负数/0/正数 */
        short         sem_flg;/* 计数是否阻塞:0阻塞,IPC_NOWAIT不阻塞 */
    };
    如果sem_op为正,则对应于进程释放占用的资源数,sem_op值加到信号量上;如果指定了undo标志(sem_flg成员设置了SEM_UNDO位),则也从该进程的此信号量中减去sem_op;
    若sem_op为负,则表示要获取该信号量的控制资源;
/*
 * 信号量集操作演示
 * sema.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>
int semid;
void sem_free(int signo) {
    printf("捕获到信号%d\n", signo);
    printf("正在回收资源\n");
    if (signo == 2) {
        semctl(semid, 0, IPC_RMID);
        printf("信号量集已回收\n");
        exit(0);
    }
}
int main() {
    printf("PID = %d\n", getpid());
    signal(SIGINT, sem_free);
    printf("按Ctrl+C退出\n");
    key_t key = ftok(".", 100);
    semid = semget(key, 1, 0666 | IPC_CREAT); //第二个参数是数组长度
    if (semid == -1) {
        perror("semget"), exit(-1);
    }
    int res = semctl(semid, 0, SETVAL, 5);    //初始化最大计数5
    if (res == -1) {
        perror("semctl"), exit(-1);
    }
    printf("成功创建并初始化信号量集\n");
    //练习:用信号Ctrl+C实现信号量集的回收;
    while (1) ;
    return 0;
}
/*
 * 信号量集操作演示
 * semb.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
int main() {
    printf("pid = %d\n", getpid());
    key_t key = ftok(".", 100);
    int semid = semget(key, 0, 0);    //获取时给0
    if (semid == -1) {
        perror("semget"), exit(-1);
    }
    int i;
    for (i = 0; i <= 9; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            printf("进程%d开始启动;申请访问资源\n", i + 1);
            struct sembuf op;
            op.sem_num = 0;    //操作下标为0的信号量
            op.sem_op = -1;    //申请访问,计数-1
            op.sem_flg = 0;    //0阻塞
            /* op.sem_flg = IPC_NOWAIT; //不阻塞 */
            semop(semid, &op, 1); //执行-1操作;
                //数组的地址==首元素的地址;
            printf("进程%d访问资源\n", i + 1);
            sleep(10);
            op.sem_op = 1; //释放资源,计数+1
            semop(semid, &op, 1);    //执行计数+1
            printf("进程%d释放资源\n", i + 1);
            exit(0);
        }
    }
    printf("父进程已经结束pid = %d\n", getpid());
    return 0;
}


网络编程
网络常识//程序员需要知道关于网络的一些基本常识,最重要的是IP地址和端口;
网络编程: TCP 和 UDP;

    ISO/OSI七层协议模型
=================================
    7    应用层Application        *** |
    6    表现层Presentation       *** |//Telnet/FTP/WWW等
    5    会话层Session            *** |
--    --    --    --    --    --    --    --    --  --  --
    4    传输层Transport          ### //TCP/UDP
---    ---    ---    ---    ---    ---    ---    ---    --
    3    网络层Network            ### //IP和路由
----------------------------------
    2    数据链路层Data Link      ### |
    1    物理层Physical           ### |//网卡驱动
=================================
TCP/IP的模型
    上三层,下四层;
    5会话层/6表现层和7应用层统称为大应用层;
    4传输层和3网络层不变;
    1物理层和2数据链路层可以合也可以分开;

协议(Protocol)和协议簇(Protocol Family)
    协议就是数据传送的方式和准则;
    一系列相关的协议就组成协议簇;协议簇一般以最核心的协议命名;协议簇在某些资料上写成协议族;

常见协议
    TCP        Transmission Control Protocol传输控制协议,基于连接的服务;//传输层
    IP         Internet Protocol;Internet协议,信息传递机制;//网络层
    UDP        User Datagram Protocol用户数据报协议,无连接的服务;//传输层
    HTTP       超文本传输协议;
    FTP        文件传输协议(上传和下载);
    收发邮件协议
    ...

消息包的逐层递增
    Upper Layer Protocol    #Msg#
    TCP                     #Msg#@@
    IP                      #Msg#@@&&
    Enthernet             **#Msg#@@&&**

一些Socket编程的概念
    流stream
    连接connection
    阻塞block/非阻塞non-block
    同步synchronous/异步asynchronous
IP地址
    IP地址是计算机在网络中的唯一标识,可以定位网络中的计算机;
    IP地址的本质是一个整数,分IPV4和IPV6,IPV4是主流,占32位(4个字节),IPV6占128位;每个Internet包必须带有IP地址;
    IP地址有两种表示方式:
    1.底层就是一个32位的整数,用8位十六进制数表示;
    2.点分十进制;每个字节转成一个十进制数(255),中间用点分隔;
    计算机更喜欢8位十六进制,而人更喜欢十进制,但在底层都是存储32位二进制;这两种表示方式可以进行转换;比如:
    192.168.100.17和0xC0A86411是等价的;
0x:     C0  A8  64 11
    C语言也提供了转换函数;
    ipconfig可以查看windows的IP地址,ipconfig/all可以查看物理地址;
    ifconfig可以查看Unix/Linux的IP地址,ifconfig -a;
四级IP地址
    class A: 0 NetWork(7bit) Local_Address(24bit) //是下面的总和
    class B: 10 NetWork(14bit) Local_Address(16bit) //是下面的总和
    class C: 110 NetWork(21bit) Local_Address(8bit) //是下面的总和
    class D: 1110 Multicast_Address(28bit)

IP地址的工作原理
    IP地址需要和网卡的物理地址绑定才能定位计算机,每块网卡的地址是出厂时就设定好的,无重复,叫物理地址(MAC地址/*machine*/);
子网掩码(Subnet Mask)
    子网掩码用于区分两个IP是不是在同一个子网中:
    166.111.160.1与166.111.161.45
    子网掩码:255.255.254.0
    IP和子网掩码做位与运算,结果一样的是一个子网;
    166.111.160.1
    255.255.254.0 (位与)
    166.111.160.0

    166.111.161.45
    255.255.254.0 (位与)
    166.111.160.0
    因此166.111.160.1与166.111.161.45在同一个局域网中;
    
    IP地址只能找到计算机(家),但对应不了计算机中的进程(门),端口号负责对应计算机中的某个进程;

端口
    在网络技术中,端口(Port)大致有两种意思:
    一是物理意义上的端口;比如,ADSL Modem/集线器/交换机/路由器用于连接其他网络设备的接口,如RJ-45端口/SC端口等等;
    二是逻辑意义上的端口;一般是指TCP/IP协议中的端口,端口号的范围从0到65535,比如用于浏览网页服务的80端口,用于FTP服务的21端口等等;
    端口就是计算机中某个进程的网络标识;只有"IP+端口"才能进行数据交互;
    端口也是一个整数,short 类型,范围0-65535;
    端口分类:
    0-1023//最好不要使用,系统使用其中的部分;
    1024-48xxx//正常使用的端口,有很少一部分会被某些安装的软件使用,比如,1521 Oracle数据库;
    48000以后的,动态端口,不稳定;
    
大小端字节顺序(大端格式big endian/小端格式little endian)
    不同的机器存储整数时,存放方式不同;比如,某个整数的4个字节分别是A B C D,有的机器是按A B C D方式存储,而有的机器是D C B A;
    整数的存储有本机格式和网络格式之分;本机格式的字节顺序不确定,而网络格式的字节顺序是确定的;为保证端口号正确传输,需要把本机格式转成网络格式;
    int x = 0x12345678;
    再用 char 逐字节打印,就可以知道本机格式;

union的使用受系统大小端的影响
    +----------------------+
    |   大端格式           |
    |   int i = 1;         |
    | 0x1  0x0  0x0  0x0   |
    |----------------------|
    | 高地址      低地址   |
    +----------------------+
    +----------------------+
    |   小端格式:          |
    | 低位数据放在低地址   |
    |   int i = 1;         |
    | 0x0  0x0  0x0  0x1   |
    |----------------------|
    | 高地址      低地址   |
    +----------------------+
union C {
    int i;
    char c;
};
union C c;
c.i = 1;
printf("%d\n", c.c); //??
// 如果是小端格式,1会存储在低地址,结果返回1
// 如果是大端格式,1会存储在高地址,结果返回0
/*
 * 大端格式小端格式验证
 */
#include <stdio.h>
int main(){
    int x = 0x12345678;
    char *p = (char *)&x;
    printf("%x, %x, %x, %x\n", p[0], p[1], p[2], p[3]);
    union C {
        int i;
        char c;
    } c;
    c.i = 1;
    printf("1 == 0x%08x\n", c.c);
    if (c.c == 1) {
        printf("little endian\n");
    } else {
        printf("big endian\n");
    }
    return 0;
}

ping命令可以查看网络是否畅通,ping后面跟IP地址或域名;

网络中的域名(网址)和IP的关系:
    上网应该是使用IP地址,因IP地址很难记忆,所以用域名(俗称网址)做助记,有专用的服务器负责把域名转成IP地址;

网络编程在C语言中叫socket编程;

