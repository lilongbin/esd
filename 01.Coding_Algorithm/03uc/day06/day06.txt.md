lseek()
dup()/dup2()
sync()/fsync()/fdatasync()
fflush()


系统IO和标准IO
    当应用程序调用系统函数时,需要切换用户状态和内核态,因此频繁调用会导致性能的损失;
    标准库做了必要的优化,内部会维护一个缓冲区,只有满足特定条件时,才将缓冲与系统内核同步;借此可以降低系统调用的频率,减少进程在用户态和内核态之间切换的次数,提高运行效率;
/*
 * sys/std io test
 * sysio.c
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main() {
    int fd = open("sysio.dat", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    unsigned int i;
    for (i = 0; i < 100000; ++i) {
        write(fd, &i, sizeof(i));
    }
    close(fd);
    return 0;
}
/*
 * sys/std io test
 * stdio.c
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main() {
    FILE *fp = fopen("sysio.dat", "wb");
    if (!fp) {
        perror("fopen");
        return -1;
    }
    unsigned int i;
    for (i = 0; i < 100000; ++i) {
        fwrite(&i, sizeof(i), 1, fp);
    }
    fclose(fp);
    return 0;
}
使用以下命令编译和测试
gcc stdio.c -o stdio
gcc sysio.c -o sysio
time sysio
time stdio
发现stdio明显的比较快;

lseek()
    每个打开的文件都有一个与之相关的"文件位置";
    文件位置通常是一个非负的整数,用于度量从文件头开始计算的字节数;
    所有的读写操作都从当前文件位置开始,并根据所读写的字节数增加文件位置;
    打开一个文件时,除非指定了O_APPEND,否则文件位置一律被设为0;
    lseek()函数仅修改文件表中记录的文件位置,并不引发任何IO动作;
    lseek()函数可以将文件位置设置到文件尾之后,这样在后续写操作以后会在文件中形成空洞;文件空洞不占用磁盘空间,但会被计算在文件大小内;//下载软件在下载文件时候会首先建立相应大小的空文件;

#include <sys/types.h>
#include <unistd.h>
off_t lseek(
    int fd, //文件描述符;
    off_t offset; //偏移量;
    int whence //起始位置;
); //成功返回调整以后的文件位置,失败返回-1;

whence取值
    SEEK_SET //文件头(文件的第一个位置);
    SEEK_CUR //从当前位置(下一次读写操作的位置);
    SEEK_END //从文件尾(文件最后一个字节的下一个位置);
/*
 * lseek()函数练习
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main() {
    int fd = open("seek.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    const char *text = "hello world !";
    if (write(fd, text, strlen(text) * sizeof(text[0])) == -1) {
        perror("write");
        return -1;
    }
    /* 读写都会改变文件当前位置 */
    off_t pos = lseek(fd, 0, SEEK_CUR);
    if (pos == -1) {
        perror("lseek");
        return -1;
    }
    printf("当前文件位置: %ld\n", pos); //13
    if (lseek(fd, -7, SEEK_CUR) == -1) {
        perror("lseek");
        return -1;
    }
    pos = lseek(fd, 0, SEEK_CUR);
    printf("当前文件位置: %ld\n", pos); //6
    text = "Linux";
    if (write(fd, text, strlen(text) * sizeof(text[0])) == -1) {
        perror("write");
        return -1;
    }

    /* 从文件尾向后偏移,再写入将产生文件空洞 */
    if (lseek(fd, 8, SEEK_END) == -1) {
        perror("lseek");
        return -1;
    }
    text = " <-文件这里有空洞!";
    if (write(fd, text, strlen(text)) == -1) {
        perror("write");
        return -1;
    }
    /* 文件尾的位置也代表文件的大小 */
    off_t size = lseek(fd, 0, SEEK_END);
    if (size == -1) {
        perror("lseek");
        return -1;
    }
    printf("文件的大小是: %ld字节\n", size);
    close(fd);
    return 0;
}

dup()/dup2()函数
    duplicate a file descripter;获得文件描述符的副本;

    #include <unistd.h>
    int dup(int oldfd);
    int dup2(int oldfd, int newfd);
成功时返回文件描述符oldfd的副本(新的描述符),失败返回-1;
    复制一个已打开文件的描述符;
    dup()函数返回的一定是当前未使用的最小的文件描述符;
    dup2()函数可以由第二个参数newfd指定期望复制到的文件描述符,若所指定的文件描述符已打开,则先关闭之,再复制;
    所返回的文件描述符副本与源文件描述符oldfd对应同一个文件表;
    文件描述符与文件并不是一一对应;

注意区分通过dup()/dup2()获得文件描述符副本,和两次open()同一个文件的区别

dup()/dup2()只复制文件描述符表中的文件表指针,不会重建新的文件表;
fd1    |->文件表->V节点(I节点信息表);
fd2    |
没有创建新的文件表;操作fd1和fd2会同步操作同一个文件;

open()会创建一个新的文件表,并为其分配新的文件描述符:
fd2->文件表    |->v节点(I节点信息表);
fd1->文件表    |
多次open()同一文件,同时操作fd1和fd2会相互覆盖文件内容
/*
 * dup()/dup2()函数演示
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
int main() {
    int fd1 = open("dup.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd1 == -1) {
        perror("open");
        return -1;
    }
    printf("fd1 = %d\n", fd1);    //3
    int fd2 = dup(fd1);
    if (fd2 == -1) {
        perror("dup");
        return -1;
    }
    printf("fd2 = %d\n", fd2);    //4
    int fd3 = dup2(fd2, 100);
    if (fd3 == -1) {
        perror("dup2");
        return -1;
    }
    printf("fd3 = %d\n", fd3);    //100
    char buf[64] = "Hello, World !";
    /* 用fd1写文件 */
    if (write(fd1, buf, strlen(buf) * sizeof(buf[0])) == -1) {
        perror("write");
        return -1;
    }
    /* 用fd2移动文件当前位置 */
    if (lseek(fd2, -7, SEEK_CUR) == -1) {
        perror("lseek");
        return -1;
    }
    const char *text = "Linux";
    /* 用fd3再次写文件 */
    if (write(fd3, text, strlen(text) * sizeof(text[0])) == -1) {
        perror("write");
        return -1;
    }
    close(fd3);
    /* 关闭fd3后再用fd2移动位置 */
    if (lseek(fd2, 0, SEEK_SET) == -1) {
        perror("lseek");
        return -1;
    }
    /* 通过fd1读取文件内容 */
    if (read(fd1, buf, 64)) {
        printf("%s\n");
    }
    close(fd2);
    close(fd1);
    return 0;
}

/*
 * open()与dup()/dup2()的方式不同
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
int main() {
    int fd1 = open("same.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd1 == -1) {
        perror("open");
        return -1;
    }
    printf("fd1 = %d\n", fd1);    //3
    int fd2 = open("same.txt", O_RDWR);    //open会创建新的文件表;
    if (fd2 == -1) {
        perror("open");
        return -1;
    }
    printf("fd2 = %d\n", fd2);    //4
    const char *text = "Hello, world !";
    if (write(fd1, text, strlen(text) * sizeof(text[0])) == -1) {
        perror("write");
        return -1;
    }
    text = "Linux";    
    /* fd2与fd1对应同一个文件,但文件表不同 */
    /* 后写入的会覆盖先写入的内容 */
    if (write(fd2, text, strlen(text) * sizeof(text[0])) == -1) {
        perror("write");
        return -1;
    }

    return 0;
}

/*
 * dup()的使用示例
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main() {
    int fd = open("use_dup.log", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    printf("关闭标准输出,重定向到文件\n");
    /*
     * close(STDOUT_FILENO);
     * //把标准输出的文件描述符释放,以便让dup占用
     * dup(fd); //dup()占用了标准输出的文件描述符
     */
    dup2(fd, STDOUT_FILENO);  //相当于以上两句的效果
    /* 会把标准输出重定向到日志文件 */
    printf("内存分配失败\n");
    printf("打开文件失败\n");

    /* 如果不用dup()/dup2(),可能需要修改所有的 */
    /* printf()为fprintf();工作量很大,易出错; */
    return 0;
}
其实shell中的输出重定向操作就是通过这种方式来操作的;


sync()/fsync()/fdatasync()
fflush()

    大多数的磁盘IO都要通过缓冲进行,写入文件其实只是写入缓冲区,直到缓冲区满,才将其排入队列;
    延迟写降低了写操作的次数;提高写操作的效率,但是会导致磁盘文件与缓冲区数据不同步;
    sync()/fsync()/fdatasync()用于强制磁盘文件与缓冲区同步;
    sync()将把进程中所有被修改过的缓冲区排入写队列,立即返回,并不等待写磁盘操作完成; //不带参数
    fsync()只针对一个文件,且一直等到写磁盘操作完成才返回;
    fdatasync()只同步文件数据,不同步文件属性;

    #include <unistd.h>
    void sync(void);
    int fsync(int fd);      \
    int fdatasync(int fd);/成功返回0,失败返回-1;

===========================================
          应用程序内存
          |          |
      fwrite()       |
          |          |
          V          |
    标准库缓冲    write()
          |          |
      fflush()       |
          V          V
         内 核 缓 冲 区
               |
   sync()/fsync()/fdatasync()
               |
               V
         写队列/磁盘设备    
===========================================


