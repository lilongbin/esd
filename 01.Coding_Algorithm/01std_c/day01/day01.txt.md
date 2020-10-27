# 1 Linux系统操作基础




Linux操作系统是一个多用户的操作系统;每一个用户需要使用对应的账号登录后才可以操作;
终端窗口是使用Linux操作系统的主要方式;终端窗口中使用键盘完成各种输入,使用命令完成各种功能;

如果登录到Linux桌面系统可以找到终端并打开,部分操作系统可以使用< Ctrl+Alt+t >快捷键直接打开终端;
在终端窗口中按< Ctrl+Shift+t >可以新建一个终端标签页,用Alt+数字编号在每个终端标签页中切换.

# 快捷键
* Tab 键可以在命令行中自动补全命令或路径
* 上下方向键/< Ctrl-p > 可以在以前使用的命令中查找某个命令
* < ctrl-r > 可以反向搜索历史命令,可以多次按下该键在多个搜索结果中切换;

# 命令
* whoami 查看当前用户使用的账号
* clear  清除屏幕上的所有文字内容

* iconv -f gb2312 -t utf-8 day01.txt > day01-utf-8.txt
该命令将gb2312编码的txt文件转换为utf-8编码的文件后存储到day01-utf-8.txt

* dos2unix file.txt 将file.txt由windows格式转换为unix格式
* unix2dos file.txt 则完成相反的操作

文件系统是操作系统中专门用来管理文件的部分,采用多层分组的方式管理文件;
文件系统中采用文件夹(目录)来表示一个分组;每个文件一定属于某个分组(代表分组的文件夹包含组中的所有文件);
Linux文件系统有一个大分组包含其中所有文件, 和这个大分组对应的目录叫根目录, 用/表示. 

文件系统中使用路径表示任何一个文件夹或文件的位置;
* 以根目录为开始位置编写的路径叫绝对路径,绝对路径一定以/做开头;
* 以任何目录为开始位置编写的路径叫相对路径,相对路径中使用..表示向左走一步;使用.表示原地踏步;

文件系统中左右相邻的目录之间有父子关系,左边的叫父目录,右边的叫子目录;

终端窗口里的当前工作目录表示相对路径的起点;

Linux文件系统为每个账号保留一个主目录,使用~表示,每次启动终端窗口后默认工作目录就是当前账号的宿主目录:
* echo $HOME 可以查看当前用户的宿主目录
    ```
    一个用户如果没有对应的用户主目录就无法登录到图形界面,只能登录终端窗口.
    使用usermod命令可以修改用户名和主目录
    usermod -l newname -s /bin/bash -m -d /home/newname oldname
    userdel -r loginname 可以删除用户及其主目录
    ```

* pwd 命令可以查看当前工作目录
* cd命令可以更改当前目录的位置change directory
    ```
    cd 新的路径名 可以切换到新的目录
    cd 不加任何参数会直接切换到用户主目录.
    cd - 可以切换到上一次所在的目录.
    ```

* ls 可以查看任何目录中的内容
    * -a 选项可以查看目录中所有内容
    * -l 选项可以查看每个内容的详细信息
    * -a 选项和-l选项可以合并成-al

* mkdir 可以创建新的目录;
    * 要求新目录原来还不存在但是它的父目录必须存在;
    * -p选项可以把路径中所有还不存在的目录都创建出来;

* rmdir 可以删除一个已经存在的空目录,目录必须是空的;

* rm 可以用来删除文件或目录
    * -r recursive递归操作
    * -i interactive每一个删除要求用户确认
    * -f force强制删除,不需要用户确认
    * -v verbose冗长显示,explain what is being done.
    * rm -rf 目录名或文件名 可以删除一个不为空的目录及其目录下的所有内容;

* cp 把一个已经存在的文件或目录拷贝一份放在另外的地方
    * -d 保持源文件的属性,对链接文件会复制链接而不是复制一个新的实体
    * -f 强制执行,如果目标已经存在则会覆盖
    * -i 覆盖之前要求用户确认
    * -n no clobber,如果目标已存在则不覆盖
    * -r 递归操作,对拷贝的目录及其子目录递归操作
    * -v verbose冗长显示

* mv 把一个已经存在的文件或目录移动到另一个地方,或更改名字
    * -f 强制执行,如果目标已经存在则会覆盖
    * -i 覆盖之前要求用户确认
    * -n no clobber,如果目标已存在则不覆盖
    * -v 冗长显示,显示进行了哪些操作
    ```
    对cp和mv命令而言,如果操作的源文件是文件名,
    当目标是一个目录时则结果文件名保持不变只是复制文件或移动文件的位置,
    当目标是一个路径后加上一个文件名,文件名可以与原来的相同此时文件名可以省略,如果文件名不同则表示复制为一个新的文件名或移动到一个新的位置并更改文件名.
    ```


* history 列出使用命令的历史,在数字编号前加!可以执行对应编号的命令;

* grep 过滤文本中符合条件的字符串
    * -i 或 --ignore-case 选项忽略字符大小写的差别;
    * -r 或 --recursive 递归处理,当指定要查找的是目录而非文件时,必须使用这项参数;
    * -n 或 --line-number 在显示符合样式的那一行之前,标示出该行的列数编号;

* tar 对多个文件或文件夹进行打包,并可以再对打包结果进行压缩处理;
    * -z 选项对应gz文件,-j选项对应bz2文件,-J对应xz文件.
    * -c 表示创建create
    * -x 表示extract解压缩
    * -v 表示verbose冗长显示
    * -f 表示对文件操作
    * -C dir可以在解压缩时解压到dir目录
    ```
    在Linux系统中对文件进行压缩处理可以使用如下命令
    tar -zcvf 压缩文件名.tar.gz 路径1 路径2 ...
    解压缩可以采用如下命令
    tar -zxvf 压缩文件名.tar.gz
    ```

* dd 可以把指定的输入文件拷贝到指定的输出文件中,并且在拷贝的过程中可以进行格式化;
    ```
    dd if=/dev/zero of=swap bs=1M count=1K
    该命令将以/dev/zero文件填充出1M*1K=1G大小的文件swap;

    dd if=ubuntu.iso of=/dev/sdg bs=1M
    可以制作启动U盘

    dd if=/dev/hdx of=MBR.bk bs=512 count=1
    可以备份MBR

    dd if=/dev/sdb of=/dev/sdb
    可以修复硬盘
    ```
* touch file
    * 如果file不存在则创建该文件
    * 如果file已经存在,则将文件的最后修改时间改成执行touch命令时的时间


* set 命令可以查看当前系统所有设置的环境变量;
    ```
    LC_TIME=zh_CN.UTF-8
    此时运行date命令
    2015年 07月 06日 星期一 13:49:19 CST
    然后执行export命令设置环境变量
    export LANG="en"
    再次运行date命令
    Mon Jul  6 13:50:32 CST 2015
    如果系统安装时选择中文系统,在运行man命令查看帮助信息时看到的可能会是翻译拗口的中文,可以用export命令临时设置语言环境再用man命令;
    export LANG="en"
    man date
    ```

* mount命令可以将系统所有已经加载的分区数据列出来;
    ```
    mount -a 会根据/etc/fstab的内容将所有相关磁盘挂载;
    ```

# vi 文本编辑器
vi 文本编辑器,只能在终端窗口中使用,而其他工具一般是在桌面上使用的,因此在进行终端操作时只能选用vi编辑器;
vi可以完成各种编辑操作,但是只能用键盘操作;

## 工作模式
vi中把所有命令分成三组,任何时候只能使用其中一组里的所有命令. 
vi中使用工作模式决定当前可以使用哪一组命令
vi一共三种工作模式,一种工作模式对应一组命令
* 正常模式 可以执行简单命令(由少数字母构成的命令);
* 插入模式 可以修改文档内容,除Esc键之外都可以作为字符输入键;
* 底行模式 可以输入复杂命令;

各种工作模式之间是可以相互切换的
* 在正常模式下输入i可以切换到插入模式
* 在正常模式下输入:可以切换到底行模式
* 在任何时候可以使用键盘左上角的Esc键切换到正常模式
* 插入模式和底行模式是不可以直接切换的

## 启动退出
在命令行中使用如下命令可以启动vi
* vi filename     如果filename不存在则创建,如果已存在则直接打开
* vi filename +20 打开文件filename并将光标定定位到第20行;
每次进入vi后的初始模式都是正常模式

退出vi可以采用如下两种办法
* 在底行模式下输入q!可以不保存文档中的修改直接退出
* 在底行模式下输入wq或x可以先保存所有修改然后退出
底行模式下输入w可以保存文档的修改而不退出vi

## 移动跳转
文档内快速跳转
* gg    //文档开头
* G     //文档尾
* 100G    //第100行
* :100    //第100行
* Ctrl+f    //向前翻页
* Ctrl+b    //向后翻页
* w    //下一个单词的开头
* e    //下一个单词的结尾
* b    //上一个单词的开头

f搜索移动
* fa    //到下一个a处
* 3fa   //到当前行的第3个a处;
* F     //方向相反

## 替换转换
* 文档内容替换
    * :%s/old/new/gc    //替换全文(%s),全行(g)的old为new并要求用户确认(c)
    * :10,100s/old/new/gc    //替换第10到第100行的全行的old为new并要求用户确认

* 大小写转换
    * gU    //转大写
    * gu    //转小写
    * ~     //大小写切换

## 复制粘贴
vi中自带剪贴板,可以作为文字信息的中转站
* 在正常模式下使用nyy命令可以把当前光标及下面的几行拷贝到剪贴板上,其中n是一个数字,表示一共拷贝的行数;
* 在正常模式下使用np命令可以把剪贴板上的内容在当前光标所在行的下面粘贴n次;
* 在正常模式下使用ndd命令可以把当前光标所在行及下面的几行剪切到剪贴板上,n是数字代表一共剪切的行数.

正常模式下按x可以删除一个字符,u可以撤销最近的编辑操作,Ctrl+r可以恢复最近的操作

底行模式使用co或m实现复制和剪切
vi 复制第5行到第10行并粘贴到第12行之后
:5,10 co 12
vi 剪切第5行到第10行并粘贴到第12行之后
:5,10 m 12


## 选择
区域选择
< action > a < obj > 或 < action > i < obj >
action可以是任何的命令,如d删除,y复制,v可视模式
a代表all,包括obj;i是inner,在obj内部的;
obj可以是;
    w一个单词,W一个以空格为分割的单词;
    s一个句子;
    p一个段落;
    特别的字符如"/'/)/}/]等成对符号的右一半;
假如有一个字符串
    (map (+) ("foo"))
此时,光标在第1个o上;
    vi"    会选择foo
    va"    会选择"foo"
    vi)    会选择"foo"
    va)    会选择("foo")
    v2i)    会选择map (+) ("foo")
    v2a)    会选择(map (+) ("foo"))

## 块操作
块操作< c-v >
典型操作
0 < c-v > < move > I < string > < Esc >
以上步骤分别代表
* 0            移到行首,也可以移动到其他位置;
* < c-v >      进入列选模式,
* < move >     移动选择,
* I            插入模式, //A,追加模式
* < string >   编辑字符串,
* < Esc >      使每一行生效;

在所有被选择的行后面追加某个字符串
* < c-v >
* 选中相关的行;
* 按$到行尾;
* 按A,输入字符串;
* 按< Esc >使每一行生效;

按v可以进入可视模式,移动光标可以选择内容,然后按y可以拷贝选中内容,按p可以粘贴缓冲区内容到当前光标之后.

按Ctrl+v可以上下移动光标进行列选,然后按I进入行首插入模式,编辑完成按两次Esc.

按Shift+v可以上下移动光标进行块选,然后按=可以对文档内容进行格式化缩排.

## 其他命令
改变文档显示字体大小
< Ctrl Shift + > 可以增大文件字体;
< Ctrl Shift - > 可以减小文件字体;

重复命令
.可以重复上一次命令;
N< cmd >可以重复某个命令N次;

## 宏录制
qa, 操作序列, q, @a, @@
* qa录制操作记录在寄存器a,
* 按q退出录制;
* @a会replay存放在寄存器a中的录制宏;
* @@是用来操作最新录制宏的快捷键;

示例
    在一个只有一行且这一行只有1的文本中,键入以下命令;
1. qaYp< c-a >q
    * qa开始录制;
    * Yp复制一行;
    * < c-a >增加1;
    * q停止录制;
2. @a
    在1下面写2;
3. 100@@
    创建新的100行;会把数据增加到102;

## 多文件编辑
打开一个文件后,在正常模式下执行
打开
    :new 文件名
    :vi filename
    :sp filename
    :vs filename
    其中sp代表split创建分屏;将窗口分割为上下排列的窗口;
    vs代表vsplit,创建垂直分屏,将窗口分割为左右排列的窗口;
    < c-w >加方向键可以将光标在各个窗口中切换;
    < c-w >+或< c-w >-可以增大或减小窗口;
切换
    :e#    上一个文件
    :bn    下一个文件
    :bp    上一个文件
    ctrl+^ 在当前文件和上一个文件间转换
关闭
    :bw关闭当前文件

## 执行外部命令
在底行模式下可以加一个!执行shell命令
*    :!ls    //执行ls命令
*    :r!ls    //将执行ls命令的结果嵌入到正在编辑的文档内

## 设置
设置命令可以扩展vi的功能
设置命令是在底行模式下使用set命令实现的;
* set nu 显示行号;
* set nonu 取消显示行号;

note:在底行模式下输入

~/.vimrc 文件可以记录各种set命令,每次vi启动的时候都会从这个文件中读取所有set命令并按顺序执行.

```vim
"" ---------.vimrc----------------
set fileencodings=usc-bom,utf-8,GB18030,gbk,big5
set nu
set ts=4
set softtabstop=4
set shiftwidth=4
set expandtab

set ignorecase
set smartcase
set incsearch
set nohlsearch
set showmatch

set scrolloff=6
set nocompatible

set laststatus=2
set statusline=[%n]\ %F%m%r%h\ %=%{&encoding}\ %l,%c\ %p%%\ %L\ 
syntax reset
syntax on
```

gVim是Windows操作系统下的vi,打开后切换到底行模式打开新文件:vi filename

练习vi
    使用vi编写abc.txt,在文件中输入Hello world!,然后不保存退出
    使用vi编写abc.txt,在文件中输入Hello China!,然后保存不退出
    使用vi编写abc.txt,把文件修改为Hello world!,然后保存退出


# 如何删除/*和*/注释的语句
用%s/pattern/new/gc; 其中/是分隔符,也可以换用其他任何字符,如#;
关键是如何书写正确的pattern正则表达式,考虑到*是正则表达式中的元字符,因此在设计时,先用x代替,然后再替换回*;
参考《精通正则表达式》 对/x string x/类型的匹配采用如下模式
[opening normal* (special normal*)* closing]

```
现根据/x string x/来设计正则表达式
opening        /x
normal*        [^x]*x+
special        [^/x]
closing        x/
因此得出/x string */正则表达式为
    /x[^x]*x+([^/x][^x]*x+)*/
将所有的x替换为*,并考虑到*为元字符,需要适用\转义,得
    /\*[^*]*\*+([^/*][^*]*\*+)*/
还要注意在正则表示使中/也需要转义,因此得到最终的/* string */的正则表达式
    \/\*[^*]*\*+([^/*][^*]*\*+)*\/
然后使用awk的gsub函数处理即可
    cat akari.c | awk 'BEGIN{RS=""}{gsub(/\/\*[^*]*\*+([^/*][^*]*\*+)*\//, " ", $0); print $0}'
```

# 链接文件
链接文件可以用来代表另外一个文件
ln命令可以创建链接文件, 命令使用方法和cp命令一样;
* 直接用ln命令创建出来的链接文件叫硬链接文件,可以独立于原文件而存在;相当于对某一块存储空间又取了一个名字;
* 使用-s选项可以创建软链接文件,软链接不能独立于原文件而存在,源文件消失则软链接文件变成无效连接文件;

如果用cp命令复制一个链接文件时没有指定-d选项,则会复制一份文件的实体;
在计算机中文件名和文件内容不是一回事,只是文件系统帮我们做了一个映射;
连接文件只是多了一个文件名,文件内容并没有增加一份;
cp命令则是多了一个文件名和一份文件内容;

## 软连接和硬连接区别
* 硬连接只是取了一个别名,还指向同一块数据和inode,其他什么都没做,因此删除原文件后硬链接仍有效;直到删除原文件和所有的硬链接文件存储区域才会是失效;
* 软连接是增加了一个文件,有自己的inode和数据块;记录某个实体文件的信息,因此删除原文件后软件失效;

使用帮助
```
ln [OPTION]... [-T] TARGET LINK_NAME   (1st form)
ln [OPTION]... TARGET                  (2nd form)
ln [OPTION]... TARGET... DIRECTORY     (3rd form)
ln [OPTION]... -t DIRECTORY TARGET...  (4th form)
In the 1st form, create a link to TARGET with the name LINK_NAME.
In the 2nd form, create a link to TARGET in the current directory.
In the 3rd and 4th forms, create links to each TARGET in DIRECTORY.
    -f    //移除已存在的目标文件
    -i    //如果目标文件存在,则要求用户确认
```
ln -s /home/abc/def/jhi/tools /home/abc/tools
    /home/abc/def/jhi/tools 可以是一个文件,也可以是一个目录
    如果tools是一个目录,连接文件仍然是一个文件,使用rm tools删除连接文件,不能使用rm tools/ 删除;

# 文件属性
由文件类型和代表文件权限的英文字母构成; 决定了文件可以怎么使用;
文件属性分成3组,每一组3个字母,针对一种特定的用户;三种用户分别是文件属主user/属组group和其他人others; 
每组属性包含3个字母,第一个字母表示是否可读,第二个字母表示是否可写,第三个字母表示是否可执行; 
字母r表示可以读,字母w表示可以写,字母x表示可以执行,字母-表示没有对应权限;
每一组的三个字母可以使用0~7之间到八进制数表示(r对应4,w对应2,x对应1); 

相关命令
* 使用ls -l 命令可以查看文件属性;
* chmod命令可以修改文件的属性,执行chmod需要一定的权限; 
    + chmod mod file
    + chmod mod dir -R
    - mod是可选的ugoa标识加上可选的符号+-=以及权限;权限可以使8进制表示的数值,也可以是rwx;
    - u代表user,g代表group,o代表others,a代表all;+表示增加某权限,-代表去除某权限,=直接用8进制赋值;
* chown命令可以修改文件的属组和属主;
    + chown user[:group] file
    + chown user[:group] dir -R

# 进程基本概念
在早期面向进程设计的计算机结构中,进程是程序的基本执行实体;
在当代面向线程设计的计算机结构中,进程是线程的容器.

* 包含多个命令的文件叫脚本文件,可以用来自动化的完成各种繁琐的工作;
* 脚本语言不同于编译程序的语言编程,脚本不需要编译即可执行,在执行时由特定的解释器逐行解释执行,一行出错并不会影响后面的语句执行;
* C/C++等属于编译型语言,需要编译后才可以执行,一行出错会影响整个程序的执行;
* 程序是计算机中的一个文件,程序的内容不会随着时间而改变;
* 进程是根据程序创建出来的一组数据,进程会随着时间变化,用户真正使用的是进程而不是程序; 

操作系统为每个进程分配了一个整数作为进程ID即PID,不同进程的ID不同; 
## 相关命令
* ps命令可以查看当前终端窗口中的进程;
    * -ef选项或-aux选项可以查看系统中的所有进程
    * -ef选项兼容Unix系统; 
* kill命令可以给进程发信号; 
    * kill -l 可以查看所有的信号列表
    * kill -signal PID 给进程号为PID的进程发送signal信号;
    * -1选项可以先挂起当前进程,结束子进程,再返回关闭当前进程并处理善后;
    * -9选项可以强制结束一个进程; 
    * Ctrl+c可以把占住终端窗口的进程结束掉,实际是发送了信号2; 

# 重定向
输入重定向可以让程序从文件中得到需要的信息,输入重定向使用 < 实现;
输出重定向可以让命令把本来输出到终端标准输出窗口中的内容写入到文件中;
在命令的最后使用>号可以实现输出重定向的效果;
* 使用>实现输出重定向会把文件中原有内容覆盖掉;
* 使用>>实现输出重定向会把新内容追加到原有文件的后面;

# 管道
linux系统中可以使用管道把多个命令连成一条直线,前一个命令的输出作为后一个命令的输入; 
管道使用一个|符号使用; 

# 分离输出命令tee
tee [OPTION] [FILE]
Copy standard input to each FILE, and also to standard output;
* tee命令后面可以跟多个文件名
    * -a    //追加到文件末尾
    * -i    //忽略中断信号
```
ls -a |tee -a list.txt
    系统会执行ls -a命令,把结果显示在屏幕上同时以追加方式输出到文件list.txt中
```

# 通配符
在命令中使用通配符编写路径可以用一个路径代表多个实际路径; 
* ?是一个通配符,可以用来代表 单个 任意字符
* *是一个通配符,可以用来代表 任意多个 任意字符

# 练习
    抄写snake.c达到20分钟以内且无任何错误;
```cpp
/*
 * snake.c
 */
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#define APPLE            '@'
#define SNAKEHEAD        '+'
#define SNAKETAIL        '-'
#define SIZE            10

/* define point struct */
typedef struct {
    int row;
    int col;
} Pos;

/* define a snake struct */
typedef struct {
    Pos head;
    Pos tail;
} Snake;

Snake snake;
Pos apple;

/* judge the point if is valid */
bool is_same(const Pos * pFirstPos, const Pos * pSecondPos) {
    if ((pFirstPos->row == pSecondPos->row)
        && (pFirstPos->col == pSecondPos->col)) {
        return true;
    } else {
        return false;
    }
}

/* initialize a snake function*/
void init_snake() {
    int row = rand() % (SIZE - 2);
    int col = rand() % (SIZE - 2);
    int direction = rand() % 4;
    snake.head.row = row;
    snake.head.col = col;
    switch (direction) {
    case 0:
        //tail is above the head
        snake.tail.row = row - 1;
        snake.tail.col = col;
        break;
    case 1:
        //tail is below the head
        snake.tail.row = row + 1;
        snake.tail.col = col;
        break;
    case 2:
        //tail in on the left of the head
        snake.tail.row = row;
        snake.tail.col = col - 1;
        break;
    default:
        //tail is on the right of the head
        snake.tail.row = row;
        snake.tail.col = col + 1;
        break;
    }
}

/* create an apple */
void plant_apple() {
    do {
        apple.row = rand() % (SIZE - 2);
        apple.col = rand() % (SIZE - 2);
    } while ((is_same(&apple, &(snake.head)))
         || (is_same(&apple, &(snake.tail))));
}

/* show current status function */
void show_map() {
    int row = 0;
    int col = 0;
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            if ((row == apple.row) && (col == apple.col)) {
                printf("%c", APPLE);
            } else if ((row == snake.head.row)
                   && (col == snake.head.col)) {
                printf("%c", SNAKEHEAD);
            } else if ((row == snake.tail.row)
                   && (col == snake.tail.col)) {
                printf("%c", SNAKETAIL);
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

/* snake move function */
void move_snake() {
    int direction = 0;
    int row = 0;
    int col = 0;
    printf("input direction:<0 up, 1 left, 2 down, 3 right>");
    scanf("%d", &direction);
    switch (direction) {
    case 0:
        if ((snake.head.row - 1) >= 0) {
            snake.tail.row = snake.head.row;
            snake.tail.col = snake.head.col;
            snake.head.row--;
        }
        break;
    case 1:
        if ((snake.head.col - 1) >= 0) {
            snake.tail.row = snake.head.row;
            snake.tail.col = snake.head.col;
            snake.head.col--;
        }
        break;
    case 2:
        if ((snake.head.row + 1) < SIZE) {
            snake.tail.row = snake.head.row;
            snake.tail.col = snake.head.col;
            snake.head.row++;
        }
        break;
    default:
        if ((snake.head.col + 1) < SIZE) {
            snake.tail.row = snake.head.row;
            snake.tail.col = snake.head.col;
            snake.head.col++;
        }
        break;
    }
    if (is_same(&apple, &(snake.head)) || (is_same(&apple, &(snake.tail)))) {
        plant_apple();
    }
}

/* main function */
int main() {
    srand(time(0));
    init_snake();
    plant_apple();
    show_map();
    while (1) {
        move_snake();
        show_map();
    }
    return 0;
}
```
