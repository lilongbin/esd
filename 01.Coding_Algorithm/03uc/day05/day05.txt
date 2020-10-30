文件系统
open()/creat()/close()
read()
write()


回顾
malloc()/calloc()/realloc()/free();
一次性分配33个内存页,是由malloc()自身设定的;
malloc()分配内存时会自动添加一些附加信息(控制数据),
内存通常指虚拟内存;
free()只会释放所分配的虚拟内存地址,实际上是把控制数据中的标记修改为空闲;
所有的映射和解除映射都是以内存页为单位的;
brk()/sbrk()维护了一个位置,指针,指向堆尾;
一般用sbrk()分配内存,用brk()释放内存
mmap()/munmap()可以映射/解除映射物理内存/文件;
APP -> malloc()/free()    ->brk()/sbrk() ->mmap()/munmap() ->kernel

文件系统
文件系统的基本概念
    1.在Unix操作系统中,每个文件以一个或多个数据块离散的存放在磁盘的块表区中(柱面表区);
    2.一个文件的每个数据块的存储位置保存在I节点(i-node)中;
    3.对应系统中多个文件的I节点保存在磁盘的I节点表中,每个I节点通过一个下标唯一地标识,这个下标称为I节点号;
    4.文件的名称和其所对应的I节点号保存在目录文件中;
    5.访问文件的过程:根据文件名到目录文件中找到相应的I节点号,再根据I节点号到I节点表中找到对应的I节点,根据I节点找到每个数据块在磁盘上的存储位置,进而访问其中的数据;
    6.根目录/的I节点信息保存在一个特殊的位置即超级块super block中,每次挂载(mount)文件系统时首先找到根目录的位置;
    7.以上所述文件数据的存储结构和访问方式,被称为文件系统fs;
    格式化硬盘的过程实际就是重新建立文件系统的过程;

一切皆文件
    fscanf(stdin, ...);
    fprintf(stdout, ...);
    Linux环境下文件具有特殊的意义,它为系统中的服务和设备提供了一种抽象接口;
    程序完全可以向访问普通文件一样,访问串口/网络/鼠标/键盘/打印机等各种设备;
    大多数情况下只需要使用五个最基本的系统调用
        open()/close()/read()/write()/ioctl();
广义文件
    1-> 目录文件
    2-> 设备文件
        控制台        /dev/console
        声卡          /dev/audio
        标准输入输出  /dev/tty
        空设备        /dev/null

文件相关的系统调用
    open()        //用来打开/创建文件,类似于fopen();
    close()       //用来关闭文件,类似于fclose();
    read()        //用来读取文件,类似于fread();
    write()       //用来写入文件,类似于fwrite();
    lseek()       //设置读写位置,类似于fseek()/ftell();
    creat()       //创建文件;
    fcntl()       //修改文件属性;
    unlink()      //删除硬链接文件;
    rmdir()       //删除空目录
    remove()      //删除硬链接(unlink)/删除空目录(rmdir);
注意
    1.如果被unlink/remove删除的是文件的最后一个硬链接,并且没有进程正在打开该文件,那么该文件在磁盘上的存储区域将被立即标记为free;
    反之,如果有进程正在打开该文件,那么该文件在目录中条目虽然被立即删除,但它在磁盘上的存储区域将在所有打开它的进程关闭该文件以后才会被标记为free;
    2.如果被unlink/remove删除的是一个软链接文件,那么仅软链接本身被删除,源文件不受影响;
    创建硬链接相当于创建了一个别名,还是统一块数据区域,可以用ls -i命令查看,inode节点号是一样的;

文件描述符
    int fd = open(...);
    1.文件描述符的本质就是内核为每个进程维护的文件描述符表中存储的文件表指针的下标;//深刻理解
        文件描述符表(在内核层)中存储的文件表指针指向"文件表";
        文件表中存储着文件的状态和位置信息以及v-node指针;
        v-node指针指向v-node表(内核层);
        v-node表中存放着磁盘中i-node表的拷贝;
    访问文件时会根据I节点号到I节点表中找到对应的I节点,根据I节点找到每个数据块在磁盘上的存储位置,进而访问其中的数据;
  +----+  +------------+  +------+  +--------+  +------------+
  | fd |->|文件描述符表|  |文件表|  |v-node表|  |磁盘i-node表|
  |    |  |以文件描述符|  | 状态 |  |        |  |            |
  |    |  |为下标的文件|  | 位置 |  | inode  |  |            |
  |    |  |表指针      |->|v-node|  | 的拷贝 |->|            |
  |    |  |            |  |指针  |->|        |  |            |
  +----+  +------------+  +------+  +--------+  +------------+
    grep __IO_FILE /usr/include/*.h
/usr/include/stdio.h:typeded struct __IO_FILE FILE;
    grep _fileno /usr/include/*.h -n
/usr/include/libio.h:294:  int _fileno;
    vi /usr/include/libio.h +294
在标准C语言中FILE *fp = fopen();
_fileno是FILE的其中一个成员,而_fileno就是文件描述符;

    2.文件描述符是一个非负的整数;
    3.每个文件描述符对应一个打开的文件;
    4.文件描述符从open函数返回,同时作为参数传递给后续的文件函数(read/write/close...)使用;
    5.内核缺省为每个进程打开三个文件表述符:
        标准输入0  STDIN_FILENO
        标准输出1  STDOUT_FILENO
        标准错误输出2 STDERR_FILENO
        #include <unistd.h>
/*
 * 文件描述符演示
 */
#include <stdio.h>
#include <unistd.h>
int main() {
    printf("stdin->_fileno: %d\n", stdin->_fileno);     //0
    printf("stdout->_fileno: %d\n", stdout->_fileno);    //1
    printf("stderr->_fileno: %d\n", stderr->_fileno);    //2

    FILE *fp = fopen("a.out", "r");
    printf("fp->_fileno: %d\n", fp->_fileno);    //3
    fclose(fp);

    FILE *fp1 = fopen("a.out", "r");
    printf("fp1->_fileno: %d\n", fp1->_fileno);    //3
    fclose(fp1);
    printf("一个进程同时最多打开的文件描述符个数是%ld\n",
           sysconf(_SC_OPEN_MAX));
    printf("fclose(stdout);\n");
    fclose(stdout);
    printf("hello world !");
       //等价与fprintf(stdout, "hello world !\n");
    return 0;
}

    6.可以在输入输出重定向时指定定向文件描述符;
/*
 * 重定向练习
 * ./a.out 0<i.txt 1>o.txt 2>e.txt
 */
#include <stdio.h>
int main() {
    int i;
    printf("please input a number: \n");
    fscanf(stdin, "%d", &i);
    fprintf(stdout, "标准输出: %d\n", i);
    fprintf(stderr, "标准出错: %d\n", i);
    return 0;
}

    7.一个进程可以使用的文件描述符的范围是0到OPEN_MAX;OPEN_MAX宏在早期的Unix/Linux中被定义为63,所以一个进程同时最多只能打开64个文件;现在的Unix/Linux系统可以同时打开更多文件;
    通过sysconf(_SC_OPEN_MAX)调用可以获取当前系统所允许的进程最多同时打开的文件描述符个数;

Unix系统文件相关的系统调用
open()/creat()/close()
    对应的头文件是#include <fcntl.h>

int open(
    const char *pathname, //文件路径;
    int flags, //状态标志;
    mode_t mode //权限模式,只在创建时有效;
); //打开/创建文件都可以使用此函数;

flags为以下值的位或
    O_RDONLY    //只读|
    O_WRONLY    //只写|->三个只能选一个;
    O_RDWR        //读写|
    O_APPEND    //追加,注意追加不可以和只读放在一起,否则冲突;
    O_CREAT        //创建,不存在即创建;已存在,直接打开,保留原有内容;
                //除非位或了下面的标志...;
    O_EXCL        //排斥exclude,已存在则失败,防止意外覆盖原有文件;
                //可以用errno来判断失败的原因;
    O_TRUNC        //清空,已存在则清空;
            //O_EXCL/O_TRUNC只能选一个与0_CREAT位或;
mode的取值与chmod命令的权限参数一致,均为八进制;
open()成功则返回文件描述符,失败则返回-1;

int creat(
    const char *pathname, //文件路径;
    mode_t mode //权限模式
                //仅创建有效
); //常用于创建文件
成功返回文件描述符,失败返回-1;相当于这样调用open函数:
open(pathname, O_WRONLY | O_CREAT | O_TRUNC, mode);

关闭文件的实质是释放内核中的文件描述符表;
int close(int fd); //成功返回0,失败返回-1;

实际创建文件的权限 = mode & ~umask;
因此所有umask(权限掩码)中包含的权限,在创建的文件中都不会存在;
如:0666 & ~0002 == 0664;
/*
 * open()函数练习
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main() {
    /* 创建文件,读写权限,如果不存在就创建,已存在就清空 */
    int fd1 = open("test.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (fd1 == -1) {
        perror("open");
        return -1;
    }
    printf("文件描述符fd1 = %d\n", fd1);    //3
    /* 以只读模式再次打开文件 */
    int fd2 = open("test.txt", O_RDONLY);    //open的参数表是可变的;
    if (fd2 == -1) {
        perror("open");
        return -1;
    }
    printf("文件描述符fd2 = %d\n", fd2);    //4
    close(fd2);
    close(fd1);
    return 0;
}


write()
#include <unistd.h>
ssize_t write(
    int fd, //文件描述符;
    const void *buf, //操作地址;从buf写入到fd对应文件;
    size_t count //期望写入字节数;
); //成功时返回实际写入字节数,失败则返回-1;
ssize_t //int
size_t  //尽量使用这个类型,会随系统而变;
    32位中为 unsigned int
    64位中为 unsigned long int
/*
 * write()函数练习
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
int main() {
    //创建文件
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    const char *text = "Hello World";    //指定缓冲区
    printf("写入内容: %s\n", text);
    /* 定义期望写入字节数 */
    size_t towrite_num = strlen(text) * sizeof(text[0]);
    ssize_t written_num = write(fd, text, towrite_num);    //write
    if (written_num == -1) {
        perror("write");
        return -1;
    }
    printf("期望写入%d字节,实际写入%d字节.\n", towrite_num,
           written_num);
    close(fd);        //关闭文件
    return 0;
}


read()
#include <unistd.h>
ssize_t read(
        int fd, //文件描述符
        void *buf, //操作缓冲区;//从fd对应文件读取到buf中;
        size_t count //期望读取的字节数;                
); //成功时返回实际读取字节数;
读到文件尾返回0,如果读取失败返回-1;
标C中有一个函数feof();可以判断是否读到文件尾,如果是则返回1;

/*
 * read()函数练习
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
int main() {
    int fd = open("test.txt", O_RDONLY);    //以只读方式打开;
    if (fd == -1) {
        perror("open");
        return -1;
    }
    char text[256];        //缓冲区;
    size_t toread = sizeof(text);    //期望读取字节数;
    ssize_t readed = read(fd, text, toread);    //read
    if (readed == -1) {
        perror("read");
        return -1;
    }
    /* 设置结尾,防止后面垃圾信息干扰 */
    text[readed / sizeof(text[0])] = '\0';
    printf("期望读取%d字节,实际读取%d字节\n", toread, readed);
    printf("读取的内容是:\n%s\n", text);
    close(fd);        //关闭文件
    return 0;
}


练习
    写一个文件拷贝程序,带有覆盖检查功能;
提示
    在一个循环中,读一块,写一块,读完结束;
    调用open函数打开目标文件时,给O_WRONLY|O_CREAT|O_EXCL,若目标文件存在,则open失败,判断errno == EEXIST,说明目标已经存在;
/*
 * 写一个文件拷贝程序,带有覆盖检查功能
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("用法: %s <源文件> <目标文件>\n", argv[0]);
        return -1;
    }
    /* 以只读方式打开源文件 */
    int src = open(argv[1], O_RDONLY);
    if (src == -1) {
        perror("open");
        return -1;
    }
    struct stat srcfile_st;
    /* 取源文件的权限 */
    if (fstat(src, &srcfile_st) == -1) {
        perror("fstat");
        return -1;
    }
    /* 以源文件的权限,读写方式创建目标文件 */
    int dst = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, srcfile_st.st_mode);
    if (dst == -1) {
        /* 如果返回失败,判断错误类型 */
        if (errno != EEXIST) {
            perror("open");
            return -1;
        }
        //目标已经存在
        printf("文件%s已经存在,是否覆盖?(Y/N)", argv[2]);
        int ch = getchar();    //只取一个字符
        if (ch != 'y' && ch != 'Y') {
            return 0;
        }
        /* 重新创建文件,如果存在则清空 */
        if ((dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, srcfile_st.st_mode)) == -1) {
            perror("open");
            return -1;
        }
    }
    char buf[1024] = {};
    ssize_t bytes;
    /* 循环读写,注意运算符优先级,最好加小括号标识 */
    /* while (bytes = read(src, buf, sizeof(buf)) > 0) { //错误 */
    while ((bytes = read(src, buf, sizeof(buf))) > 0) {
        printf("读取内容到地址%p\n", buf);
        printf("读取字节%d\n", bytes);
        if (write(dst, buf, bytes) == -1) {
            perror("write");
            return -1;
        }
    }
    if (bytes == -1) {
        perror("read");
        return -1;
    }
    /* 关闭文件 */
    close(dst);
    close(src);
    return 0;
}

练习
    分别以二进制和纯文本方式读写文件;
    二进制文件与纯文本文件取决于文件的存储方式,一个是存储数据本身,一个是存储数据格式化成文本之后的数据;
    hexdump -C txt.txt 命令可以以16进制查看文件
/*
 * UNIX C
 * uc_bintxt.c
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
typedef struct Employee {
    char name[256];
    int age;
    double salary;
} EMP;

/* 以二进制的方式写test.bin */
void bin_write(void) {
    char name[256] = "张飞";
    int age = 30;
    double salary = 20000.5;
    EMP emp = { "赵云", 20, 10000.5 };
    int fd = open("test.bin", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open");
        exit(-1);
    }
    if (write(fd, name, sizeof(name)) == -1
        || write(fd, &age, sizeof(age)) == -1
        || write(fd, &salary, sizeof(salary)) == -1
        || write(fd, &emp, sizeof(emp)) == -1) {
        perror("write");
        close(fd);
        exit(-1); //exit()是有尊严的自杀,kill()是杀别人;
    }
    close(fd);
}

/* 以二进制的方式读test.bin */
void bin_read(void) {
    char name[256];
    int age;
    double salary;
    EMP emp;
    int fd = open("test.bin", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(-1);
    }
    if (read(fd, name, sizeof(name)) == -1
        || read(fd, &age, sizeof(age)) == -1
        || read(fd, &salary, sizeof(salary)) == -1
        || read(fd, &emp, sizeof(emp)) == -1) {
        perror("read");
        close(fd);
        exit(-1);
    }
    close(fd);
    printf("%s %d %lg\n", name, age, salary);
    printf("%s %d %lg\n", emp.name, emp.age, emp.salary);
}

/* 在标准C语言中可以直接使用fprintf()实现以文本方式写文件; */
/* 在UC中需要使用函数进行转换; */
/* 以纯文本方式写test.txt */
void txt_write(void) {
    char name[256] = "张飞";
    int age = 30;
    double salary = 20000.5;
    EMP emp = { "赵云", 20, 10000.5 };
    char text[1024];
    /* 以二进制形式写文本,就会显示出文本 */
    /* 实际会写入文本的ASCII码 */
    snprintf(text, sizeof(text), "%s %d %lg\n%s %d %lg",
           name, age, salary,
           emp.name, emp.age, emp.salary);    //防止数据溢出
    /* 在内存中格式化字符串 */
    /* sprintf(text, "%s %d %lg\n%s %d %lg",
     *        name, age, salary,
     *        emp.name, emp.age, emp.salary); */
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd == -1) {
        perror("open");
        exit(-1);
    }
    if (write(fd, text, strlen(text) * sizeof(text[0])) == -1) {
        perror("write");
        close(fd);
        exit(-1);
    }
    close(fd);
}

/* 以纯文本方式读test.txt */
void txt_read(void) {
    char name[256];
    int age;
    double salary;
    EMP emp;
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(-1);
    }
    char text[1024] = { };
    if (read(fd, text, sizeof(text)) == -1) {
        perror("read");
        exit(-1);
    }
    close(fd);
    /* printf("%s\n", text); */
    /* text就是读取到的文本 */
    /* 用sscanf()提取字符串 */
    sscanf(text, "%s%d%lf%s%d%lf",
           name, &age, &salary,
           emp.name, &emp.age, &emp.salary);
    printf("%s %d %lg\n%s %d %lg\n",
           name, age, salary,
           emp.name, emp.age, emp.salary);
}

int main(void) {
    bin_write();
    bin_read();
    txt_write();
    txt_read();
    return 0;
}

在标准C语言中可以直接调用fprintf()函数以文本方式写入文件;
使用fgets()一次读取文件的一行;
使用feof()函数判断是否已经读到文件末尾;

/*
 * standard C
 * std_bintxt.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Employee {
    char name[256];
    int age;
    double salary;
} EMP;

/* 以二进制的方式写test.bin */
void bin_write(void) {
    char name[256] = "张飞";
    int age = 30;
    double salary = 20000.5;
    EMP emp = { "赵云", 20, 10000.5 };
    FILE *fp = fopen("test.bin", "wb");
    if (fp == NULL) {
        exit(-1);
    }
    fwrite(name, sizeof(name), 1, fp);
    fwrite(&age, sizeof(age), 1, fp);
    fwrite(&salary, sizeof(salary), 1, fp);
    fwrite(&emp, sizeof(emp), 1, fp);
    fclose(fp);
    fp = NULL;
}

/* 以二进制的方式读test.bin */
void bin_read(void) {
    char name[256];
    int age;
    double salary;
    EMP emp;
    FILE *fp = fopen("test.bin", "rb");
    if (fp == NULL) {
        exit(-1);
    }
    fread(name, sizeof(name), 1, fp);
    fread(&age, sizeof(age), 1, fp);
    fread(&salary, sizeof(salary), 1, fp);
    fread(&emp, sizeof(emp), 1, fp);
    fclose(fp);
    fp = NULL;
    printf("%s %d %lg\n", name, age, salary);
    printf("%s %d %lg\n", emp.name, emp.age, emp.salary);
}

/* 在标准C语言中可以直接使用fprintf()实现以文本方式写文件; */
/* 在UC中需要使用函数进行转换; */
/* 以纯文本方式写test.txt */
/* fprintf() */
void txt_write(void) {
    char name[256] = "张飞";
    int age = 30;
    double salary = 20000.5;
    EMP emp = { "赵云", 20, 10000.5 };
    char text[1024];
    FILE *fp = fopen("test.txt", "wb");
    if (fp == NULL) {
        exit(-1);
    }
    /* 以二进制形式写文本,就会显示出文本 */
    /* 实际会写入文本ASCII码的二进制数据 */
    fprintf(fp, "%s %d %lg\n%s %d %lg",
           name, age, salary,
           emp.name, emp.age, emp.salary);
    fclose(fp);
    fp = NULL;
}

/* 以纯文本方式读test.txt */
/* fgets() + feof() */
void txt_read(void) {
    char name[256];
    int age;
    double salary;
    EMP emp;
    FILE *fp = fopen("test.txt", "rb");
    if (fp == NULL) {
        exit(-1);
    }
    char text[1024] = { };
    char *tmp = text;
    while (!feof(fp)) {
        /* fgets一次读取一行 */
        fgets(tmp, sizeof(text), fp);
        /* text就是读取到的文本 */
        if (strstr(text, "赵云")) {
            /* 在text字符串中找到子字符串"赵云" */
            printf("%s", text);
            if (!strstr(text, "\n")) {
                /* 如果结果中没有换行符,打印换行 */
                printf("\n");
            }
        }
    }
    fclose(fp);
    fp = NULL;
}

int main(void) {
    bin_write();
    bin_read();
    txt_write();
    txt_read();
    return 0;
}

