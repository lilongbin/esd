access()/chmod()/truncate()/umask();




回顾
Unix的文件管理方式
    在Unix/Linux系统中,用文件描述符代表一个打开的文件,文件描述符本质就是一个整数,只有对应文件表的整数才是文件描述符;系统给每个进程都有一张描述符总表,存的是描述符和文件表的对应关系;文件的各种信息和描述符的各种信息都存储在文件表中;
    open()函数就是在总表中创建新的对应关系;
    close()函数就是在总表中删除对应关系,整数还在但是失去了对应关系(贬为宿民);
    open()函数创建文件表,close()函数不一定删除文件表,close()函数只会删除文件描述符和文件表的对应关系,只有当文件表与描述符对应的计数到0时才删除文件表(只有最后一个人离开教室了才会关灯);
硬链接是给一个区域起一个别名;

文件操作函数
读写函数
    open()/read()/write()/close();
    读写函数都是unix系统函数,不限于文件;
    需要包含sys/types.h sys/stat.h fcntl.h头文件;
其他函数
    dup()/dup2()/fcntl()/stat()/access()/chmod()/truncate()/umask();
    需要包含sys/types.h sys/stat.h fcntl.h unistd.h头文件;

取文件状态时,权限的判断
flags & 3取后两位,也就是权限位;
    if(flags&3 == O_RDONLY) printf("可读");
    if(flags&3 == O_WRONLY) printf("可写");
    if(flags&3 == O_RDWR) printf("可读写");

应用中经常要求取后8位二进制
    flags & 0xFF

void*是万能指针,可以转换成其他任意类型的指针;

int stat(const char *path, struct stat *buf);//不需要打开文件
int fstat(int fd, struct stat *buf);//需要open后获取fd
int lstat(const char *path, struct stat *buf);//操作软链接文件

struct stat {
    dev_t     st_dev;     /* ID of device containing file */
    ino_t     st_ino;     /* inode number */
    mode_t    st_mode;    /* protection */
    nlink_t   st_nlink;   /* number of hard links */
    uid_t     st_uid;     /* user ID of owner */
    gid_t     st_gid;     /* group ID of owner */
    dev_t     st_rdev;    /* device ID (if special file) */
    off_t     st_size;    /* total size, in bytes */
    blksize_t st_blksize; /* blocksize for file system I/O */
    blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
    time_t    st_atime;   /* time of last access 访问*/
    time_t    st_mtime;   /* time of last modification 修改*/
    time_t    st_ctime;   /* time of last status change 改变*/
};

The following POSIX macros are defined to check the file type using the st_mode field:

S_ISREG(m)  is it a regular file?
S_ISDIR(m)  directory?
S_ISCHR(m)  character device?
S_ISBLK(m)  block device?
S_ISFIFO(m) FIFO (named pipe)?
S_ISLNK(m)  symbolic link? (Not in POSIX.1-1996.)
S_ISSOCK(m) socket? (Not in POSIX.1-1996.)

C语言中时间日期有两种类型
    整数 time_t,记录秒差(1970.01.01 00:00:00)
    结构 struct tm,成员包括年月日时分秒
时间转换函数ctime()/localtime();
/*
 * 文件属性练习
 */
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
int main() {
    struct stat st;
    int res = stat("test.txt", &st);
    if (res == -1) {
        perror("stat"), exit(-1);    //exit是一个函数可以拼语句
    }
    printf("size: %d\n", st.st_size);    //文件大小
    printf("inode: %d\n", st.st_ino);    //文件inode
    printf("links: %d\n", st.st_nlink); //硬链接数
    printf("mode: %o\n", st.st_mode);    //文件类型+权限
    printf("mtime: %s\n", ctime(&st.st_mtime)); //时间
    if (S_ISDIR(st.st_mode)) {
        printf("是目录\n");
    }
    if (S_ISREG(st.st_mode)) {
        printf("是文件\n");
    }
    printf("权限: %o\n", st.st_mode & 07777);
    return 0;
}
/*
 * 文件属性练习
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    struct stat sb;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (stat(argv[1], &sb) == -1) {
        perror("stat");
        exit(EXIT_SUCCESS);
    }
    printf("File type:                ");
    switch (sb.st_mode & S_IFMT) {
        case S_IFBLK:
            printf("block device\n");
            break;
        case S_IFCHR:
            printf("character device\n");
            break;
        case S_IFDIR:
            printf("directory\n");
            break;
        case S_IFIFO:
            printf("FIFO/pipe\n");
            break;
        case S_IFLNK:
            printf("symlink\n");
            break;
        case S_IFREG:
            printf("regular file\n");
            break;
        case S_IFSOCK:
            printf("socket\n");
            break;
        default:
            printf("unknown?\n");
            break;
    }
    printf("I-node number:            %ld\n", (long)sb.st_ino);
    printf("Mode:                     %lo (octal)\n",
           (unsigned long)sb.st_mode);
    printf("Link count:               %ld\n", (long)sb.st_nlink);
    printf("Ownership:                UID=%ld   GID=%ld\n",
           (long)sb.st_uid, (long)sb.st_gid);
    printf("Preferred I/O block size: %ld bytes\n", (long)sb.st_blksize);
    printf("File size:                %lld bytes\n", (long long)sb.st_size);
    printf("Blocks allocated:         %lld\n", (long long)sb.st_blocks);
    printf("Last status change:       %s", ctime(&sb.st_ctime));
    printf("Last file access:         %s", ctime(&sb.st_atime));
    printf("Last file modification:   %s", ctime(&sb.st_mtime));

    exit(EXIT_SUCCESS);
}

access()函数用于按实际用户ID和实际组ID进行访问权限测试;
    测试成功返回0,失败返回-1;
测试中的mode常量
    R_OK    测试读权限
    W_OK    测试写权限
    X_OK    测试执行权限
    F_OK    测试是否存在
int access(const char *pathname, int mode);//
/*
 * access()函数练习
 */
#include <stdio.h>
#include <unistd.h>
int main() {
    char name[32] = "test.txt";
    if (!access(name, R_OK)) { printf("可读\n"); }
    if (!access(name, W_OK)) { printf("可写\n"); }
    if (!access(name, X_OK)) { printf("可执行\n"); }
    if (!access(name, F_OK)) { //判断文件是否存在
        printf("文件存在\n");
    } else {
        printf("文件不存在\n");
    }
    return 0;
}

chmod()/fchmod();
chmod()不会被屏蔽掉权限;
/*
 * chmod()函数练习
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
int main() {
    char name[32] = "test.txt";
    if (!access(name, R_OK)) { printf("可读\n"); }
    if (!access(name, W_OK)) { printf("可写\n"); }
    if (!access(name, X_OK)) { printf("可执行\n"); }
    if (!access(name, F_OK)) { //判断文件是否存在
        printf("文件存在\n");
    } else {
        printf("文件不存在\n");
    }
    /* chmod()中的权限给什么,实际就会是什么; */
    chmod(name, 0666); //改为读写权限
    return 0;
}

truncate(),ftruncate()函数用于指定文件大小,可以变大也可变小;
int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);
/*
 * truncate()函数练习
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
int main() {
    char name[32] = "test.txt";
    if (!access(name, R_OK)) { printf("可读\n"); }
    if (!access(name, W_OK)) { printf("可写\n"); }
    if (!access(name, X_OK)) { printf("可执行\n"); }
    if (!access(name, F_OK)) {    //判断文件是否存在
        printf("文件存在\n");
    } else {
        printf("文件不存在\n");
    }
    /* chmod()中的权限给什么,实际就会是什么; */
    chmod(name, 0666); //改为读写权限
    truncate(name, 1024);
    return 0;
}

link(),unlink()创建/删除一个文件的硬链接
link()可以创建一个指向现在文件的链接;
unlink()可以删除一个文件的链接;
    只有当链接数达到0时,文件删除;另外,当一个进程已经打开了该文件,其内容也不能删除,当进程关闭时,文件才会删除;

remove()对于文件unlink()功能相同,对对于目录和rmdir()相同;
rename()用于为文件或目录改名;

操作系统为了安全,会在创建一个新文件时屏蔽一些不安全的权限;操作系统默认屏蔽其他用户的写权限;
新建文件时的权限屏蔽可以设置,使用umask()可以设置新建文件时的权限屏蔽字;修改新建权限屏蔽字以后还需要原成默认屏蔽字;
umask()函数传入新的权限屏蔽字,返回之前的权限屏蔽字,返回的权限屏蔽字用于在使用后还原权限屏蔽字;
int oldvalue = umask(newvalue);

文件操作常用函数(UC版)
    open()        新建/打开一个文件,返回文件描述符;
    read()        读文件(读写内存块,不考虑类型);
    write()       写文件(读写内存块,不考虑类型);
    close()       关闭一个打开的文件;
    lseek()       指定文件的偏移量(读写的位置);
    fcntl()       复制描述符/获取描述符状态/文件锁;
    stat()        获取文件的信息,最常见的是取文件的大小;
    access()      判断文件是否存在;
    remove()      删除文件/目录;
    rename()      文件/目录改名;
    truncate()    指定文件的大小;
    chmod()       修改文件权限;
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
int creat(const char *pathname, mode_t mode);
    成功返回新的文件描述符,失败返回-1,带errno;
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, void *buf, size_t count);
    成功返回读写的字节数,失败返回-1;
int close(fd); 成功返回0,失败返回-1;
off_t lseek(int fd, off_t offset, int whence);
    成功返回当前位置,失败返回-1;
int fcntl(int fd, int cmd, ... /* arg */);
    返回值依具体操作而定;
int stat(const char *path, struct stat *buf);
int fstat(const char *path, struct stat *buf);
int lstat(const char *path, struct stat *buf);
    成功返回0,失败返回-1;
int access(const char *pathname, int mode);
    成功返回0,失败返回-1;
int remove(const char *pathname);
    成功返回0,失败返回-1;
int rename(const char *oldpath, const char *newpath);
    成功返回0,失败返回-1;
int truncate(const char *path, off_t length);
int ftruncate(int fd, off_t length);
    成功返回0,失败返回-1;
int chmod(const char *path, mode_t mode);
int fchmod(int fd, mode_t mode);
    成功返回0,失败返回-1;

    read()/write()用于读写文件;
    mmap()函数是用于映射内存的;
/*
 * mmap()映射硬盘上的文件,把文件当本进程的内存用
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
struct emp {
    int id;
    char name[20];
    double sal;
};
int main() {
    int fd = open("test.dat", O_CREAT | O_RDWR | O_TRUNC, 0666);
    /* 本处指定的权限应会限制后面mmap()函数终端权限 */
    if (fd == -1) {
        perror("open"), exit(-1);
    }
    /* 指定文件大小 */
    ftruncate(fd, sizeof(struct emp) * 3);
    /* 文件需要在硬盘上有空间,否则无法完成内存映射 */
    void *p = mmap(0,    //首地址由内核选择
               sizeof(struct emp) * 3, //放3个员工信息;仍映射一页
               PROT_READ | PROT_WRITE,    //权限;权限受fd限制
               MAP_SHARED,    //会把数据写入文件
               //MAP_PRIVATE,//其他进程看不到数据
               fd, 0    //描述符和偏移量
        );
    if (p == (void *)-1) {
        perror("mmap"), exit(-1);
    }
    struct emp *pe = p;    //把指针当数组使用
    pe[0].id = 100;
    strcpy(pe[0].name, "liubei");
    pe[0].sal = 30000.0;
    pe[1].id = 200;
    strcpy(pe[1].name, "guanyu");
    pe[1].sal = 24000.0;
    pe[2].id = 300;
    strcpy(pe[2].name, "zhangfei");
    pe[2].sal = 12000.0;

    int i = 0;
    for (i = 0; i <= 2; i++) {
        printf("%d %s %7.2f\n", pe[i].id, pe[i].name, pe[i].sal);
    }
    munmap(p, sizeof(struct emp) * 3);
    p = NULL;
    return 0;
}

目录操作常见函数
    mkdir()        新建一个目录;
    rmdir()        删除空目录;
    chdir()        改变当前目录;
    getcwd()    获取当前目录(不打印);
    opendir()    打开一个目录;
    readdir()    读目录的内容(子项);
int mkdir(const char *pathname, mode_t mode);
    成功返回0,失败返回-1;
int rmdir(const char *pathname);
    成功返回0,失败返回-1;
int chdir(const char *path);
int fchdir(int fd);
    返回值依文件系统而定;
char *getcwd(char *buf, size_t size);
char *getwd(char *buf);
char *get_current_dir_name(void);
    成功返回指向当前工作路径字符串的指针(与buf相同),失败返回NULL:
DIR *opendir(const char *name);
DIR *fdopendir(int fd);
    成功返回一个指向目录流的指针;失败返回-1;
struct dirent *readdir(DIR *dirp);
    成功返回DIR*指针,失败返回NULL;
int readdir_r(DIR *dirp, struct dirent *entry,
                struct dirent **result);
    dirent结构
    struct dirent {
        ino_t d_ino; //i-node号
        off_t d_off; //i节点的偏移量
        unsigned short d_reclen; //length of this record
        unsigned char d_type; //type of file;
        char d_name[256]; //文件名;
    }
    成功返回1,目录结束返回0;失败返回-1;
void rewinddir(DIR *dirp);
long telldir(DIR *dirp);
void seekdir(DIR *dirp, long offset);

    mkdir()函数用于创建一个空目录,mode指定权限;
    rmdir()函数用于删除一个空目录(其实还有.和..);
    char *getcwd(char *buf, size_t size);//双返回,可以构成链式表达式;
    可以用getcwd(0, 0)只取返回值,不存储在buf里;
/*
 * readdir()函数演示
 */
#include <stdio.h>
#include <dirent.h>
int main() {
    DIR *dir = opendir("./");
    /* 读第一个子项(directory entry) */
    struct dirent *ent = readdir(dir);
    while (ent != NULL) {
        /* d_type是子项类型,4代表目录;
         * d_name是子项名称 */
        printf("%d, %s\n", ent->d_type, ent->d_name);
        ent = readdir(dir);    //继续到下一个子项
        /* readdir()会一个一个子项的读取 */
    }
    /* 不用close(); */
    return 0;
}
/*
 * readdir()练习
 */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
/* print()函数是递归函数,实现打印出所有目录内容 */
/* 包括各层子目录(ent->d_type == 4) */
void print(char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        return;        //void类型的函数,return后面不要有数据;
    }
    struct dirent *ent;
    while (ent = readdir(dir)) {
        /* 首先调用readdir(),然后赋值,最后再判断 */
        if (strcmp(".", ent->d_name) == 0
            || strcmp("..", ent->d_name) == 0) {
            /* printf("%d, %s\n", ent->d_type, ent->d_name); */
            continue;
        }
        /* 注意目录的拼接和切换 */
        if (ent->d_type == 4) {    //子项是目录
            printf("%d, %s/%s/\n", ent->d_type, path, ent->d_name);
            char buf[256] = { };
            /* 拼接字符串 */
            sprintf(buf, "%s/%s", path, ent->d_name);
            /* 如果子项是一个目录,继续递归 */
            print(buf);    //子项递归
        } else { //子项是文件
            printf("%d, %s/%s\n", ent->d_type, path, ent->d_name);
        }
    }
}
int main() {
    print("..");
    return 0;
}

/*
 * readdir()练习
 */
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
int dir_depth = 0;
/* print()函数是递归函数,实现打印出所有目录内容 */
/* 包括各层子目录(ent->d_type == 4) */
void print(char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        return;    //void类型的函数,return后面不要有数据;
    }
    struct dirent *ent;
    while (ent = readdir(dir)) {
        /* 首先调用readdir(),然后赋值,最后再判断 */
        if (strcmp(".", ent->d_name) == 0
            || strcmp("..", ent->d_name) == 0) {
            /* printf("%d, %s\n", ent->d_type, ent->d_name); */
            continue;
        }
        /* 注意目录的拼接和切换 */
        if (ent->d_type == 4) {    //子项是目录
            int i = dir_depth;
            while (i-- > 0) printf("\t");
            printf("%d, %s/\n", ent->d_type, ent->d_name);
            char buf[256] = { };
            /* 拼接字符串,得到新的路径名 */
            sprintf(buf, "%s/%s", path, ent->d_name);
            dir_depth++; //目录深度自增
            /* 如果子项是一个目录,递归 */
            print(buf);    //子项递归
        } else { //子项是文件
            int i = dir_depth;
            while (i-- > 0) printf("\t");
            printf("%d, %s\n", ent->d_type, ent->d_name);
        }
    }
    dir_depth--; //回溯
}
int main() {
    print("..");
    return 0;
}

作业
    写一个程序myls,实现ls -ial的功能;
    当myls后面跟一个文件时可以显示文件的详细信息,当后面跟的是一个目录时,可以显示目录中子项的详细信息;
    用带两个参数的主函数
int main(int argc, char *argv[]) {
    试验一下argv[i]都是什么,argc就是数组长度
}
思路
    先判断后面跟的是文件还是目录(stat)
    如果是文件调用stat()可以显示文件信息;
    如果是目录调用opendir()readdir()查找项名,再用stat()取子项的详细信息(子项是目录也不需要递归)
/*
 * myls练习1
 * 模拟ls -il
 */
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
int is_file(char *file, struct stat *st) {
    /* printf("file: %s\n", file); */
    if (st->st_mode & S_IFDIR || st->st_mode & S_IFREG
            || st->st_mode & S_IFLNK || st->st_mode & S_IFBLK
            || st->st_mode & S_IFCHR || st->st_mode & S_IFSOCK
            || st->st_mode & S_IFIFO) {
        return 1;
    } else {
        return 0;
    }
}
void print_finode(char *file, struct stat *st) {
    printf("%7ld ", st->st_ino);
}
void print_ftype(char *argv, struct stat *st) {
    /* 获取文件类型需要使用宏函数 */
    if (S_ISDIR(st->st_mode)) {
        printf("d");
    } else if (S_ISREG(st->st_mode)) {
        printf("-");
    } else if (S_ISLNK(st->st_mode)) {
        printf("l");
    } else if (S_ISBLK(st->st_mode)) {
        printf("b");
    } else if (S_ISCHR(st->st_mode)) {
        printf("c");
    } else if (S_ISSOCK(st->st_mode)) {
        printf("s");
    } else if (S_ISFIFO(st->st_mode)) {
        printf("p");
    }
}
void print_fmod(char *argv, struct stat *st) {
    /* 权限是与07777做位与;第一个7是用来表示设置位的; */
    /* USR */
    if (st->st_mode & S_IRUSR) 
        printf("r");
    else
        printf("-");

    if (st->st_mode & S_IWUSR) 
        printf("w");
    else 
        printf("-");

    if (st->st_mode & S_ISUID)
        printf("s");
    else if (st->st_mode & S_IXUSR) 
        printf("x");
    else
        printf("-");

    /* GRP */
    if (st->st_mode & S_IRGRP) 
        printf("r");
    else 
        printf("-");

    if (st->st_mode & S_IWGRP) 
        printf("w");
    else 
        printf("-");

    if (st->st_mode & S_ISGID)
        printf("s");
    else if (st->st_mode & S_IXGRP) 
        printf("x");
    else
        printf("-");

    /* OTH */
    if (st->st_mode & S_IROTH) 
        printf("r");
    else 
        printf("-");

    if (st->st_mode & S_IWOTH) 
        printf("w");
    else 
        printf("-");

    if (st->st_mode & S_ISVTX)
        printf("t");
    else if (st->st_mode & S_IXOTH) 
        printf("x");
    else
        printf("-");

    printf(" ");
}
void print_fnlink(char *file, struct stat *st) {
    printf("%ld ", st->st_nlink);
}
void print_fusr(char *file, struct stat *st) {
    printf("%ld %ld ", st->st_uid, st->st_gid);
}
void print_fsize(char *file, struct stat *st) {
    printf("%5ld ", st->st_size);
}
void print_ftime(char *file, struct stat *st) {
    /* struct tm *mytime = localtime(&(st->st_atime)); */
    struct tm *mytime = localtime(&(st->st_ctime));
    /* struct tm *mytime = localtime(&(st->st_mtime)); */
    char time[32] = {};
    char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    char *mon[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dev"};
    sprintf(time, "%s %d %02d:%02d ",
            mon[mytime->tm_mon], mytime->tm_mday,
            mytime->tm_hour, mytime->tm_min);
    printf("%s", time);
}
void print_fname(char *file) {
    printf("%s\n", file);
}
void myls(char *file) {
    struct stat st;
    if (stat(file, &st) == -1) {
        printf("stat: %m\n");
        return ;
    }
    /* printf("file: %s %d\n", file, is_file(file, &st)); */
    if (!is_file(file, &st)) {
        printf("%s: No such file or directory\n", file);
        return ;
    }
    print_finode(file, &st);
    print_ftype(file, &st);
    print_fmod(file, &st);
    print_fnlink(file, &st);
    print_fusr(file, &st);
    print_fsize(file, &st);
    print_ftime(file, &st);
    print_fname(file);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }
    while (*argv++ != NULL) {
        if (*argv) {
            myls(*argv);
        }
    }
    return 0;
}

/*
 * myls练习2
 * 模拟ls -ial
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
enum {
    F_FIFO = 1,
    F_CHR, F_DIR, F_REG, F_BLK, F_LNK, F_SOCK
};
int is_file(char *file, struct stat *st) {
    /* 判断文件类型 */
    if (S_ISDIR(st->st_mode)) {
        return F_DIR;
    } else if (S_ISREG(st->st_mode)) {
        return F_REG;
    } else if (S_ISLNK(st->st_mode)) {
        return F_LNK;
    } else if (S_ISBLK(st->st_mode)) {
        return F_BLK;
    } else if (S_ISCHR(st->st_mode)) {
        return F_CHR;
    } else if (S_ISSOCK(st->st_mode)) {
        return F_SOCK;
    } else if (S_ISFIFO(st->st_mode)) {
        return F_FIFO;
    } else {
        return 0;
    }
}
void print_finode(char *file, struct stat *st) {
    /* 获取文件的inode节点 */
    printf("%7ld ", st->st_ino);
}
void print_ftype(char *argv, struct stat *st) {
    /* 获取文件类型需要使用宏函数 */
    if (S_ISDIR(st->st_mode)) {
        printf("d");
    } else if (S_ISREG(st->st_mode)) {
        printf("-");
    } else if (S_ISLNK(st->st_mode)) {
        printf("l");
    } else if (S_ISBLK(st->st_mode)) {
        printf("b");
    } else if (S_ISCHR(st->st_mode)) {
        printf("c");
    } else if (S_ISSOCK(st->st_mode)) {
        printf("s");
    } else if (S_ISFIFO(st->st_mode)) {
        printf("p");
    }
}
void print_fmod(char *argv, struct stat *st) {
    /* 权限是与07777做位与;第一个7是用来表示设置位的; */
    char permission[10] = "rwxrwxrwx";
    unsigned int mode = (unsigned int)st->st_mode;
    int bit = 0;
    for (bit = 0; bit < 9; bit++) {
        if (!(mode & (0x1 << bit))) {
            permission[8-bit] = '-';    
        }
    }
    if (st->st_mode & S_ISUID)
        permission[2] = 's';    
    if (st->st_mode & S_ISGID)
        permission[5] = 's';    
    if (st->st_mode & S_ISVTX)
        permission[8] = 't';
    printf("%s ", permission);
}
void print_fnlink(char *file, struct stat *st) {
    /* 获取文件的硬链接数 */
    printf("%2ld ", (long)st->st_nlink);
}
void print_fusr(char *file, struct stat *st) {
    /* 获取文件的属主和属组的ID */
    printf("%4d %4d  ", st->st_uid, st->st_gid);
}
void print_fsize(char *file, struct stat *st) {
    switch (is_file(file, st)) {
        case F_DIR:
        case F_REG:
        case F_LNK:
            /* 文件大小 */
            printf("%8lld ", (long long)st->st_size);
            break;
        case F_BLK:
        case F_CHR:
            /* 特殊设备的主次设备号 */
            printf("%3d, %3d ",
                    major(st->st_rdev), minor(st->st_rdev));
            break;
        case F_SOCK: 
        case F_FIFO:
            /* 文件大小 */
            printf("%8lld ", (long long)st->st_size);
            break;
    }
}
void print_ftime(char *file, struct stat *st) {
    /* struct tm *mytime = localtime(&(st->st_atime)); */
    struct tm *mytime = localtime(&(st->st_ctime));
    /* struct tm *mytime = localtime(&(st->st_mtime)); */
    char time[32] = {};
    char *mon[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dev"};
    sprintf(time, "%s %d %02d:%02d ",
            mon[mytime->tm_mon], mytime->tm_mday,
            mytime->tm_hour, mytime->tm_min);
    printf("%s", time); //打印文件相关的时间
}
void print_fname(char *file) {
    printf("%s\n", file); //处理文件名
}
void myls_il(char *file) {
    struct stat st;
    if (stat(file, &st) == -1) {
        printf("stat: %m\n");
        return ;
    }
    if (!is_file(file, &st)) {
        printf("%s: No such file or directory\n", file);
        return ;
    }
    /* print_finode(file, &st); */
    print_ftype(file, &st);
    print_fmod(file, &st);
    print_fnlink(file, &st);
    print_fusr(file, &st);
    print_fsize(file, &st);
    print_ftime(file, &st);
    print_fname(file);
}
void myls_rec(char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        printf("opendir(%s): %m\n", path);
        return;
    }
    struct dirent *ent;
    while (ent = readdir(dir)) {
        if (strcmp(".", ent->d_name) == 0 ||
                strcmp("..", ent->d_name) == 0) {
            continue;
        }
        char buf[256] = {};
        snprintf(buf, sizeof(buf), "%s/%s", path, ent->d_name);
        if (ent->d_type == 4) {
            /* 递归调用 */
            myls_rec(buf);
        } else {
            myls_il(buf);
        }
    }
    closedir(dir);
}
void myls_ial(char *file) {
    struct stat st;
    if (stat(file, &st) == -1) {
        printf("stat: %s %m\n", file);
        return ;
    }
    if (!is_file(file, &st)) {
        printf("%s: No such file or directory\n", file);
        return ;
    }
    if (!(S_ISDIR(st.st_mode))) {
        myls_il(file);
    } else {
        /* 去除路径结尾的/ */
        while (strlen(file) > 1) {
            if (file[strlen(file) - 1] == '/') {
                file[strlen(file) - 1] = '\0';
            } else {
                break;
            }
        }
        /* 调用递归函数处理目录 */
        myls_rec(file);
    }
}

int main(int argc, char **argv) {
    /* 默认操作当前目录 */
    if (argc < 2 && !argv[1]) {
        myls_ial(".");
        return 0;
    }
    /* 循环处理所有参数 */
    while (*argv++ != NULL) {
        if (*argv) {
            myls_ial(*argv);
        }
    }
    return 0;
}

/*
 * myls练习3
 * 模拟ls -ial
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <sys/types.h>
enum {
    F_FIFO = 1,
    F_CHR, F_DIR, F_REG, F_BLK, F_LNK, F_SOCK
};
int is_file(char *file, struct stat *st) {
    /* 判断文件类型 */
    switch (st->st_mode & S_IFMT) {
        case S_IFIFO:
            return F_FIFO;
        case S_IFCHR:
            return F_CHR;
        case S_IFDIR:
            return F_DIR;
        case S_IFBLK:
            return F_BLK;
        case S_IFREG:
            return F_REG;
        case S_IFLNK:
            return F_LNK;
        case S_IFSOCK:
            return F_SOCK;
        default:
            return 0;
    }
}
void print_finode(char *file, struct stat *st) {
    /* 获取文件的inode节点 */
    printf("%7ld ", st->st_ino);
}
void print_ftype(char *argv, struct stat *st) {
    switch (st->st_mode & S_IFMT) {
        case S_IFIFO:
            printf("p");
            break;
        case S_IFCHR:
            printf("c");
            break;
        case S_IFDIR:
            printf("d");
            break;
        case S_IFBLK:
            printf("b");
            break;
        case S_IFREG:
            printf("-");
            break;
        case S_IFLNK:
            printf("l");
            break;
        case S_IFSOCK:
            printf("s");
            break;
        default:
            break;
    }
}
void print_fmod(char *argv, struct stat *st) {
    /* 权限是与07777做位与;第一个7是用来表示设置位的; */
    char permission[10] = "rwxrwxrwx";
    unsigned int mode = (unsigned int)st->st_mode;
    int bit = 0;
    for (bit = 0; bit < 9; bit++) {
        if (!(mode & (0x1 << bit))) {
            permission[8-bit] = '-';    
        }
    }
    if (st->st_mode & S_ISUID)
        permission[2] = 's';    
    if (st->st_mode & S_ISGID)
        permission[5] = 's';    
    if (st->st_mode & S_ISVTX)
        permission[8] = 't';
    printf("%s ", permission);
}
void print_fnlink(char *file, struct stat *st) {
    /* 获取文件的硬链接数 */
    printf("%2ld ", (long)st->st_nlink);
}
void print_fusr(char *file, struct stat *st) {
    /* 获取文件的属主和属组的ID */
    /* printf("%4d %4d  ", st->st_uid, st->st_gid); */
    struct passwd *passwd = getpwuid(st->st_uid);
    printf("%-8s ", passwd->pw_name);
    struct group *grp = getgrgid(st->st_gid);
    printf("%-8s ", grp->gr_name);
}
void print_fsize(char *file, struct stat *st) {
    switch (is_file(file, st)) {
        case F_DIR:
        case F_REG:
        case F_LNK:
            /* 文件大小 */
            printf("%8lld ", (long long)st->st_size);
            break;
        case F_BLK:
        case F_CHR:
            /* 特殊设备的主次设备号 */
            printf("%3d, %3d ", major(st->st_rdev), minor(st->st_rdev));
            break;
        case F_SOCK: 
        case F_FIFO:
            /* 文件大小 */
            printf("%8lld ", (long long)st->st_size);
            break;
    }
}
void print_ftime(char *file, struct stat *st) {
    /* struct tm *mytime = localtime(&(st->st_atime)); */
    struct tm *mytime = localtime(&(st->st_ctime));
    /* struct tm *mytime = localtime(&(st->st_mtime)); */
    char time[32] = {};
    char *mon[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dev"};
    sprintf(time, "%s %d %02d:%02d ",
            mon[mytime->tm_mon], mytime->tm_mday,
            mytime->tm_hour, mytime->tm_min);
    printf("%s", time); //打印文件相关的时间
}
void print_fname(char *file, struct stat *st) {
    printf("%s\n", file); //处理文件名
}
void myls_il(char *file) {
    struct stat st;
    if (stat(file, &st) == -1) {
        printf("stat: %m\n");
        return ;
    }
    if (!is_file(file, &st)) {
        printf("%s: No such file or directory\n", file);
        return ;
    }
    /* print_finode(file, &st); */
    print_ftype(file, &st);
    print_fmod(file, &st);
    print_fnlink(file, &st);
    print_fusr(file, &st);
    print_fsize(file, &st);
    print_ftime(file, &st);
    print_fname(file, &st);
}
void myls_rec(char *path) {
    struct stat st;
    if (stat(path, &st) == -1) {
        printf("stat: %s %m\n", path);
        return ;
    }
    if (!S_ISDIR(st.st_mode)) return ;
    DIR *dir = opendir(path);
    if (dir == NULL) {
        printf("opendir(%s): %m\n", path);
        return;
    }
    struct dirent *ent;
    while (ent = readdir(dir)) {
        char buf[256] = {};
        snprintf(buf, sizeof(buf), "%s/%s", path, ent->d_name);
        if (strcmp(".", ent->d_name) == 0 ||
                strcmp("..", ent->d_name) == 0) {
            continue;
        }
        if (ent->d_type == 4) {
            /* 如果目标是目录,递归调用 */
            myls_rec(buf);
        } else {
            myls_il(buf);
        }
    }
    closedir(dir); //回溯
}
void myls_ial(char *file) {
    struct stat st;
    if (stat(file, &st) == -1) {
        printf("stat: %s %m\n", file);
        return ;
    }
    if (!is_file(file, &st)) {
        printf("%s: No such file or directory\n", file);
        return ;
    }
    if (!S_ISDIR(st.st_mode)) {
        myls_il(file);
    } else {
        /* 去除路径结尾的/ */
        while (strlen(file) > 1) {
            if (file[strlen(file) - 1] == '/') {
                file[strlen(file) - 1] = '\0';
            } else {
                break;
            }
        }
        /* 调用递归函数处理目录 */
        myls_rec(file);
    }
}

int main(int argc, char **argv) {
    /* 默认操作当前目录 */
    if (argc < 2 && !argv[1]) {
        myls_ial(".");
        return 0;
    }
    /* 循环处理所有参数 */
    while (*argv++ != NULL) {
        if (*argv) {
            myls_ial(*argv);
        }
    }
    return 0;
}

程序员基本上都是调用各种函数去写程序;

