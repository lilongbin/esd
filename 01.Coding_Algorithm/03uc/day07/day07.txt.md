fcntl()
读写锁
stat()/fstat()/lstat()


fcntl()
    操作文件描述符

#include <unistd.h>
#include <fcntl.h>
int fcntl(
        int fd, //文件描述符
        int cmd, //控制指令
        ... //可变参数,因控制指令而异
); //成功的返回值因cmd而异,失败返回-1;
对fd所表示的文件执行cmd所表示的控制,某些控制需要提供参数,某些控制会返回特定的值;

1.复制文件描述符
    int fd = fcntl(oldfd, F_DUPDF); //返回新的文件描述符
    int fd = fcntl(oldfd, F_DUPFD, newfd); //返回新的文件描述符
    复制oldfd为不小于newfd的文件描述符;
    若newfd文件描述符已用,该函数就会选择比newfd大的最小未用值,而非dup2()函数那样关闭之;
/*
 * fcntl()的F_DUPFD命令
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main() {
    int fd1 = open("test1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd1 == -1) {
        perror("open");
        return -1;
    }
    printf("fd1 = %d\n", fd1);
    int fd2 = open("test2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd2 == -1) {
        perror("open");
        return -1;
    }
    printf("fd2 = %d\n", fd2);

    /*
     * int fd3 = dup2(fd1, fd2);
     * //先关闭fd2,然后将fd1复制到fd2;
     * //以后fd2和fd2都代表fd1所代表的文件;
     * if (fd3 == -1) {
     *     perror("dup2");
     *     return -1;
     * }
     */
    /* int fd3 = fcntl(fd1, F_DUPFD, fd2); */
    //不关闭fd2,而是将fd1复制到fd2的下一个空闲位置;
    if (fd3 == -1) {
        perror("fcntl");
        return -1;
    }
    printf("fd3 = %d\n", fd3);
    const char *text = "123";
    if (write(fd1, text, strlen(text)*sizeof(text[0])) == -1) {
        perror("write");
        return -1;
    }
    text = "456";
    if (write(fd2, text, strlen(text)*sizeof(text[0])) == -1) {
        perror("write");
        return -1;
    }
    text = "789";
    if (write(fd3, text, strlen(text)*sizeof(text[0])) == -1) {
        perror("write");
        return -1;
    }
    close(fd3);
    close(fd2);
    close(fd1);
    return 0;
}

2.获取/设置文件状态标志
    一个状态标志占一个位;
    int flags = fcntl(fd, F_GETFL); //get flag
    if (flags & O_RDONLY) {
        /* 位操作,flags中O_RDONLY位为1 */
    } else {
        /* flags中O_RDONLY位为0 */
    }
    不能获取O_CREAT|O_EXCL|O_TRUNC与创建有关的属性;
    能访问就说明文件已经存在了,跟创建相关的已经没有必要获取;

    int res = fcntl(fd, F_SETFL, flags); //追加flags标志;
    在现有标志的基础上追加flags标志;
    但只能追加O_APPEND|O_NONBLOCK属性;
/*
 * fcntl()文件属性操作
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
struct {
    int flag;
    const char *desc;
} flist[] = {
    {O_RDONLY,    "O_RDONLY"}, //只读
    {O_WRONLY,    "O_WRONLY"}, //只写
    {O_RDWR,      "O_RDWR"},   //读写模式
    {O_CREAT,     "O_CREAT"},  //创建
    {O_EXCL,      "O_EXCL"},   //排他模式
    {O_NOCTTY,    "O_NOCTTY"}, //not control tty
    {O_TRUNC,     "O_TRUNC"},  //覆盖模式
    {O_APPEND,    "O_APPEND"}, //追加模式
    {O_NONBLOCK,  "O_NONBLOCK"}, //阻塞方式
    {O_DSYNC,     "O_DSYNC"}, //数据同步
    {O_ASYNC,     "O_ASYNC"}, //异步操作
    {O_RSYNC,     "O_RSYNC"}, //读同步
    {O_SYNC,      "O_SYNC"},  //同步
};
void print_all_flags() {
    int i = 0;
    for (i = 0; i < sizeof(flist) / sizeof(flist[0]); ++i) {
        printf("[0x%8x]%s\n", flist[i].flag, flist[i].desc);
    }
}
void print_flags(int flags) {
    printf("文件状态标志(0X%08X):", flags);
    size_t i;
    for (i = 0; i < sizeof(flist) / sizeof(flist[0]); ++i) {
        if (flags & flist[i].flag) {
            printf("%s ", flist[i].desc);
        }
    }
    printf("\n");
}

int main() {
    print_all_flags();
    int fd = open("test.txt",
               O_WRONLY | O_CREAT | O_TRUNC | O_ASYNC, 0666);
    /* O_ASYNC异步IO操作 */
    if (fd == -1) {
        perror("open");
        return -1;
    }
    int flags = fcntl(fd, F_GETFL); //获取文件flags;
    if (flags == -1) {
        perror("flags");
        return -1;
    }
    print_flags(flags);    //不能获取O_CREAT|O_EXCL|O_TRUNC

    if (fcntl(fd, F_SETFL,
                O_RDWR | O_APPEND | O_NONBLOCK) == -1) {
        //只能追加O_APPEND | O_NONBLOCK
        perror("fcntl");
        return -1;
    }
    if ((flags = fcntl(fd, F_GETFL)) == -1) {
        perror("fcntl");
        return -1;
    }
    print_flags(flags);    //只能追加O_APPEND|O_NONBLOCK
    close(fd);
    return 0;
}

3.给文件加锁
    假设有一个文件同时被两个进程访问该文件的A区和B区,但是A区和B区有重叠;

第1种情况  在写锁区上加写锁;
-----------------------------------------------------------
进程1                       进程2
打开文件,准备写A区;         打开文件,准备写B区;

调用fcntl给A区加写锁
fcntl返回成功,A区被
加上写锁;

调用write写A区;              调用fcntl给B区加写锁,fcntl阻塞
                             或返回失败;

调用fcntl,解锁A区;           fcntl返回成功,B区被加上写锁;
                             调用write,写B区;
                             调用fcntl解锁B区;

关闭文件;                    关闭文件;
===========================================================

第2种情况  在写锁区上加读锁
------------------------------------------------------------
进程1                       进程2
打开文件,准备写A区          打开文件,准备读B区

调用fcntl给A区加写锁
fcntl返回成功,A区被
加上写锁;

调用write写A区,             调用fcntl给B区加读锁,fcntl阻塞
                            或返回失败;

调用fcntl,解锁A区;          fcntl返回成功,B区被加上读锁;
                            调用read,读B区;
                            调用fcntl解锁B区;

关闭文件;                   关闭文件;
===========================================================

第3种情况  在读锁区上加写锁
----------------------------------------------------------
进程1                       进程2
打开文件,准备读A区          打开文件,准备写B区

调用fcntl给A区加读锁
fcntl返回成功,A区被
加上读锁;

调用read读A区;              调用fcntl给B区加读锁,fcntl阻塞
                            或返回失败;

调用fcntl,解锁A区;          fcntl返回成功,B区被加上写锁;
                            调用write,写B区;
                            调用fcntl解锁B区;

关闭文件;                   关闭文件;
===========================================================

第4种情况  在读锁区上加读锁
------------------------------------------------
进程1                       进程2
打开文件,准备读A区;         打开文件,准备读B区;

调用fcntl给A区加读锁
fcntl返回成功,A区被
加上读锁;

调用read读A区;               调用fcntl给B区加读锁,
                             fcntl返回成功;
                             B区被加上读锁;

调用fcntl,解锁A区;           掉用read,读B区;
                             调用fcntl解锁B区;

关闭文件;                    关闭文件;
===========================================================

                 试图在区域上加
                 读锁     写锁
区域上没有任何锁  OK       OK
区域上已经有读锁  OK       NO
区域上已经有写锁  NO       NO
读锁也称为共享锁,写锁也称为独占锁(或排他锁);
    无论是读锁还是写锁都是协议锁(或君子锁,劝谏锁);
    如果有人不检查直接就write()也是没用的;

int fcntl(int fd,
        F_SETLKW/*会等待*//F_SETLK/*不等待*/,
        struct flock *lock
);

struct flock{
    short int l_type;//锁类型;
                     //F_RDLCK-读锁
                     //F_WRLCK-写锁
                     //F_UNLCK-解锁
    short int l_whence;//锁区偏移起点;
                        //SEEK_SET-文件头
                        //SEEK_CUR-当前位
                        //SEEK_END-文件尾
    off_t    l_start;//锁区偏移;
                     //从l_whence开始计算;
    off_t    l_len;//锁区长度;
                   //0表示锁到文件尾;
    pid_t    l_pid;//进程加锁,若加锁给-1;
};
例如
    1->给文件从距离文件头10个字节处锁到第40个字节处,加写锁;
struct flock lck;
lck.l_type = F_WRLCK; //F_UNLCK时是解锁;fcntl中不需要更改参数;
lck.l_whence = SEEK_SET;
lck.l_start = 10;
lck.l_len = 30;
lck.l_pid = -1;
fcntl(fd, F_SETLKW, &lck);
    如果成功返回0,如果失败返回-1;
    2->给文件解锁;
struct flock lck;
lck.l_type = F_UNLCK; //解锁
lck.l_whence = SEEK_SET;
lck.l_start = 10;
lck.l_len = 30;
lck.l_pid = -1;
fcntl(fd, F_SETLKW, &lck);
以F_SETLK方式加锁,fcntl不会阻塞;
如果加锁失败返回-1,此时的errno == EACCES/EAGAIN;
如果加了锁但是没解锁,如果进程结束了或文件描述符被关闭了,进程里边跟该文件相关的协议锁自然就消失了;
文件锁标志是保存在v-node中的,并不是保存在文件表中,因为不同的进程open()同一个文件的时候,操作的是不同的文件表,但却都对应一个v-node;当加锁或解锁的时候都会检查v-node,并在加锁时添加到某个链表里;如果进程结束,文件表也就消失了,内核也会删掉对应进程的文件锁;
在v-node中一个文件可能会被不同的进程打开并加锁,加锁将按进程信息保存在某个链表中,进程操作时就会去检查锁的标志;如果某个进程没有锁协定,就不受锁的限制;
/*
 * 文件写锁
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
/* 加写锁的函数 */
int wlock(int fd, off_t start, off_t len, int wait) {
    /* wait传递要不要使用阻塞方式; */
    struct flock lock;
    lock.l_type = F_WRLCK; //写锁
    lock.l_whence = SEEK_SET;
    lock.l_start = start;
    lock.l_len = len;
    lock.l_pid = -1;
    return fcntl(fd, wait ? F_SETLKW : F_SETLK, &lock);
    /* 只有当fcntl()返回,函数才会拿到返回值return; */
    /* 如果fcntl()阻塞,函数也将阻塞在这里; */
}

/* 解锁 */
int ulock(int fd, off_t start, off_t len) {
    struct flock lock;
    lock.l_type = F_UNLCK; //解锁
    lock.l_whence = SEEK_SET;
    lock.l_start = start;
    lock.l_len = len;
    lock.l_pid = -1;
    return fcntl(fd, F_SETLK, &lock);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("用法: %s <字符串>\n", argv[0]);
        return -1;
    }
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
    /* 如果文件没有则创建,有的话就追加; */
    if (fd == -1) {
        perror("open");
        return -1;
    }
    /* 给整个文件加写锁 */
    if (wlock(fd, 0, 0, 1) == -1) {
        perror("wlock");
        return -1;
    }
    size_t i;
    /* 写操作 */
    for (i = 0; argv[1][i]; ++i) {
        if (write(fd, &argv[1][i], sizeof(argv[1][i])) == -1) {
            perror("write");
            return -1;
        }
        printf("%#x\n", (unsigned char)argv[1][i]);
        sleep(1);
    }
    /* 解锁 */
    if (ulock(fd, 0, 0) == -1) {
        perror("ulock");
        return -1;
    }
    close(fd);
    return 0;
}
文件写锁测试,编译后在不同的终端同时写,后一个进程将等待第一个进程解锁后才能继续写操作;

/*
 * 文件读锁
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
/* 加读锁 */
int rlock(int fd, off_t start, off_t len, int wait) {
    struct flock lock;
    lock.l_type = F_RDLCK; //加读锁
    lock.l_whence = SEEK_SET;
    lock.l_start = start;
    lock.l_len = len;
    lock.l_pid = -1;
    return fcntl(fd, wait ? F_SETLKW : F_SETLK, &lock);
}
/* 解锁 */
int ulock(int fd, off_t start, off_t len) {
    struct flock lock;
    lock.l_type = F_UNLCK; //解锁
    lock.l_whence = SEEK_SET;
    lock.l_start = start;
    lock.l_len = len;
    lock.l_pid = -1;
    return fcntl(fd, F_SETLK, &lock);
}

int main() {
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    /*
     * if (rlock(fd, 0, 0, 1) == -1) {
     *     //阻塞方式等待加读锁成功
     *     //傻傻的等待
     *     perror("rlock");
     *     return -1;
     * }
     */
    /* 进程阻塞的时候将被排到进程调度队列之外,
     * 处于等待唤醒状态,不占用处理器资源; */
    /* 如果文件已经被加写锁,再次加读锁时将失败 */
    while (rlock(fd, 0, 0, 0) == -1) {
        /* 采用非阻塞方式,出错时返回-1 */
        if (errno != EACCES && errno != EAGAIN) {
            //其他未知错误
            printf("rlock");
            return -1;
        }
        //加读锁失败
        printf("该文件正被锁定,空闲处理...\n");
        sleep(1);
    }
    char buf[1024];
    ssize_t readed;
    while ((readed = read(fd, buf, sizeof(buf))) > 0) {
        write(STDOUT_FILENO, buf, readed);
    }
    printf("\n");
    if (readed == -1) {
        perror("read");
        return -1;
    }
    /* 解锁,文件已经读取结束锁不再使用了 */
    if (ulock(fd, 0, 0) == -1) {
        perror("ulock");
        return -1;
    }
    return 0;
}
文件读锁测试,编译后在不同的终端一个写,一个读,读操作将等待写操作解锁后才能继续读操作;


stat()/fstat()/lstat()

获取文件属性(元数据);
#include <sys/stat.h>
int stat(
    const char *path; //文件路径;
    struct stat *buf; //文件属性;
);
int fstat(
    int fd, //文件描述符;
    struct stat *buf; //文件属性;
);
int lstat(
        const char *path; //文件路径;
        struct stat *buf; //文件属性;
); //不跟踪软链接
第一个参数叫输入参数,第二个参数较输出参数;
返回值0表示成功,-1表示失败;执行结果由输出参数获取;
fstat()函数需要首先打开文件,传入文件描述符;其他两个函数不需要打开;

当用stat()操作一个软链接文件,获取的是软链接目标文件的属性;
而用lstat()操作一个软链接文件,获取的是软链接本身的属性;

struct stat {
    dev_t     st_dev; //设备ID;
    ino_t     st_ino; //inode;
    mode_t    st_mode; //权限和类型;
    nlink     st_nlink; //硬链接数;
    uid_t     st_uid; //属主ID;
    gid_t     st_gid; //属组ID;
    dev_t     st_rdev; //特殊设备ID;
    off_t     st_size; //总字节数;
    blksize_t st_blksize; //I/O块字节数;
    blkcnt_t  st_blocks; //占用块(512B)数;windows叫簇,linux叫块
    time_t    st_atime; //最后访问时间;
    time_t    st_mtime; //最后修改时间;
    time_t    st_ctime; //最后状态改变时间;
};
其中st_mode(0TTSUGO) //第一个为数字零表示八进制;后一个是大写字母o;
        TT //文件的类型; 6bit
            S_IFDIR //目录类型(d); directory
            S_IFREG //普通文件类型(-); regular
            S_IFLNK //软链接(l); link
            S_IFBLK //块设备(b); block
            S_IFCHR //字符设备(c); character
            S_IFSOCK //Unix域套接字(s); socket
            S_IFIFO //有名管道(p); first in fist out
        S //附加模式(可执行位); 3bit
            S_ISUID //设置用户ID位(属主可执行位x -> s/S);
            S_ISGID //设置组ID位(属组可执行位x -> s/S);
            S_ISVTX //粘滞位(其他用户可执行位x -> t/T);
            //-rwsr-sr-x
            //drwxrwxrwt (如/tmp)
        U //属主的权限; 3bit
            S_IRUSR //属主可读
            S_IWUSR //属主可写
            S_IXUSR //属主可执行
        G //属组的权限; 3bit
            S_IRGRP //属组可读
            S_IWGRP //属组可写
            S_IXGRP //属组可执行
        O //其他用户的权限; 3bit
            S_IROTH //其他用户可读
            S_IWOTH //其他用户可写
            S_TXOTH //其他用户可执行

    1.任何用户登录系统,都会启动一个shell进程,该进程的属主和属组取决于登录用户的UID和GID;
    2.由登录shell启动的任何进程,其属主和属组都继承自该shell进程,此UID和GID被称为实际UID和实际GID;
    3.决定一个进程对系统的访问能力的是有效UID和有效GID,一般情况下进程的有效UID和有效GID与其实际UID和实际GID一样;
    4.如果一个可执行程序带有设置用户ID或者设置组ID位,那么运行该程序的进程的有效UID和有效GID就取自"该程序的属主和属组";
    ls -l /usr/bin/passwd
    -rwsr-xr-x. 1 root root 25980 2月  22 2012 /usr/bin/passwd
    该文件只有root才可以修改,但是有s属性,普通用户也可以运行该命令修改自己的密码;
    5.所谓粘滞位,就是具有该位的目录下面的文件只能被该文件的属主或者是root删除或更名;
    粘滞位只能指针目录设置,对于文件无效;设置了粘滞位权限的目录,使用ls命令查看其属性时,其他用户权限处的x将变成t;使用chmod命令设置目录权限时,o+t,o-t权限模式可分别用于添加/移除粘滞位权限;
    当目录被设置了粘滞位权限以后,即便用户对该目录有写权限,也不能删除该目录下的其他用户的文件数据,而只能有该文件的所有者和root用户才能有权删除;
    对目录设置粘滞位以后,允许各用户在目录中任意写入删除数据,但是禁止删除其他用户的数据;
    id命令可以查看实际的和有效的用户与组ID;

判断文件的类型常使用以下宏函数;
    S_ISDIR(m) //判断是否是目录文件;
    S_ISREG(m) //判断是否是普通文件;
    S_ISLNK(m) //是否软链接;
    S_ISBLK(m) //是否块设备;
    S_ISCHR(m) //是否字符设备;
    S_ISSOCK(m) //是否Unix域套接字;
    S_ISFIFO(m) //是否有名管道;
其中m表示获取的st_mode;

