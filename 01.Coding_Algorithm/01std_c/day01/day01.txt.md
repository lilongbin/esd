# 1 Linux系统操作基础




Linux操作系统是一个多用户的操作系统;为每一个使用者起一个名字,这个名字叫做这个使用者的账号;

终端窗口是使用Linux操作系统的主要方式;终端窗口中使用键盘完成各种操作;
终端窗口中使用命令完成各种功能

whoami 可以查看当前用户使用的账号
clear 可以清除屏幕上的所有文字内容

iconv -f gb2312 -t utf-8 day01.txt > day01-utf-8.txt
该命令将gb2312编码的txt文件转换为utf-8编码的文件后存储到day01-utf-8.txt

dos2unix file.txt
会将file.txt由windows格式转换为unix格式
unix2dos file.txt
则完成相反的操作

在终端窗口中按Ctrl+Shift+t可以打开一个终端标签页,用Alt+数字编号切换.

文件系统是操作系统中专门用来管理文件的部分;文件系统采用多层分组的方式管理文件;
文件系统中采用文件夹(目录)来表示一个分组;每个文件一定属于一个分组(代表分组的文件夹包含组中的所有文件);
Linux文件系统有一个大分组包含其中所有文件, 和这个大分组对应的目录叫根目录, 用/表示. 

文件系统中使用路径表示任何一个文件夹或文件的位置;以根目录为开始位置编写的路径叫绝对路径,绝对路径一定以/做开头;
以任何目录为开始位置编写的路径叫相对路径,相对路径中使用..表示向左走一步;使用.表示原地踏步;
文件系统中左右相邻的目录之间有父子关系,左边的叫父目录,右边的叫子目录;

终端窗口里的当前目录表示相对路径的起点
pwd命令可以查看终端窗口里的当前目录

Linux文件系统中为每个账号专门保留一个目录,叫做这个账号的主目录,使用~表示.每次启动终端窗口后当前目录就是当前账号的宿主目录:
echo $HOME 可以查看当前用户的宿主目录
一个用户如果没有对应的用户主目录就无法登录到图形界面,只能登录终端窗口.
使用usermod命令可以修改用户名和主目录
usermod -l newname -s /bin/bash -m -d /home/newname oldname
userdel -r loginname 可以删除用户及其主目录

cd命令可以更改当前目录的位置change directory
cd 新的路径名
	可以切换到新的目录
	cd命令不加任何参数会直接切换到用户主目录.
cd - 可以切换到上一次所在的目录.
pwd 可以显示当前的工作目录
ls 命令可以查看任何目录中的内容
	-a选项可以查看目录中所有内容
	-l选项可以查看每个内容的详细信息
	-a选项和-l选项可以合并成-al
mkdir 命令可以创建新的目录;要求新目录原来还不存在但是它的父目录必须存在;-p选项可以把路径中所有还不存在的目录都创建出来;
rmdir 命令可以删除一个已经存在的空目录,目录必须是空的;
rm -rf 命令可以删除一个不为空的目录及其目录下的所有内容;-r表示递归,-f表示强制;

Tab键可以在命令行中自动补全命令或路径
上下方向键/<ctrl-p>可以在以前使用的命令中查找某个命令
<ctrl-r> 可以反向搜索历史命令,可以多次按下该键在多个搜索结果中切换;
history 命令可以列出使用命令的历史,在数字编号前加!可以执行对应编号的命令;

tar 命令可以对多个文件或文件夹进行打包操作;tar命令可以在打包完成之后再对打包结果进行压缩处理;
在Linux系统中对文件进行压缩处理可以使用如下命令
$ tar -zcvf 压缩文件名.tar.gz 路径1 路径2 ...
解压缩可以采用如下命令
$ tar -zxvf 压缩文件名.tar.gz
	-z选项对应gz文件,-j选项对应bz2文件,-J对应xz文件.
	-c表示创建create
	-x表示extract解压缩
	-v表示verbose冗长显示
	-f表示对文件操作
	-C dir可以在解压缩时解压到dir目录

dd 命令可以把指定的输入文件拷贝到指定的输出文件中,并且在拷贝的过程中可以进行格式化;
$ dd if=/dev/zero of=swap bs=1M count=1K
该命令将以/dev/zero文件填充出1M*1K=1G大小的文件swap;

$ dd if=ubuntu.iso of=/dev/sdg bs=1M
可以制作启动U盘

$ dd if=/dev/hdx of=MBR.bk bs=512 count=1
可以备份MBR

$ dd if=/dev/sdb of=/dev/sdb
可以修复硬盘

vi是Linux系统下的文本编辑器;vi只能在终端窗口里使用;而其他工具一般是在桌面上使用的,因此在进行终端操作的时候只能选用vi编辑器;
vi可以完成各种编辑操作,但是只能用键盘操作;

vi中把所有命令分成三组,任何时候只能使用其中一组里的所有命令. 
vi中使用工作模式决定当前可以使用哪一组命令
一共三种工作模式,一种工作模式对应一组命令
	正常模式下可以执行简单命令(由少数字母构成的命令);
	插入模式下可以修改文档内容,除Esc键之外都可以作为字符输入键;
	底行模式下可以输入复杂命令;

各种工作模式之间是可以相互切换的
在正常模式下输入i可以切换到插入模式
在正常模式下输入:可以切换到底行模式
在任何时候可以使用键盘左上角的Esc键切换到正常模式
插入模式和底行模式是不可以直接切换的

在命令行中使用如下命令可以启动vi
vi filename
	如果filename不存在则创建,如果已存在则直接打开
vi filename +20
	打开文件filename并将光标定定位到第20行;
每次进入vi后的初始模式都是正常模式

退出vi可以采用如下两种办法
	在底行模式下输入q!可以不保存文档中的修改直接退出
	在底行模式下输入wq或x可以先保存所有修改然后退出

底行模式下输入w可以保存文档的修改而不退出vi
vi中自带剪贴板,可以作为文字信息的中转站

在正常模式下使用nyy命令可以把当前光标及下面的几行拷贝到剪贴板上,其中n是一个数字,表示一共拷贝的行数;
在正常模式下使用np命令可以把剪贴板上的内容在当前光标所在行的下面粘贴n次;
在正常模式下使用ndd命令可以把当前光标所在行及下面的几行剪切到剪贴板上,n是数字代表一共剪切的行数.
正常模式下x可以删除一个字符,u可以撤销最近的编辑操作,Ctrl+r可以恢复最近的操作

vi 复制第5行到第10行并粘贴到第12行之后
:5,10 co 12
vi 剪切第5行到第10行并粘贴到第12行之后    
:5,10 m 12

改变文档显示字体大小
<Ctrl><Shift>+ 可以增大文件字体;
<Ctrl><Shift>- 可以减小文件字体;

文档内快速跳转
gg	//文档开头
G	//文档尾
100G	//第100行
:100	//第100行
Ctrl+f	//向前翻页
Ctrl+b	//向后翻页
w	//下一个单词的开头
e	//下一个单词的结尾
b	//上一个单词的开头

f搜索移动
fa	//到下一个a处
3fa	//到当前行的第3个a处;
F	//方向相反

文档内容替换
:%s/old/new/gc	//替换全文(%s),全行(g)的old为new并要求用户确认(c)
:10,100s/old/new/gc	//替换第10到第100行的全行的old为new并要求用户确认

大小写转换
gU	//转大写
gu	//转小写
~	//大小写切换

重复命令
.可以重复上一次命令;
N<cmd>可以重复某个命令N次;

区域选择
<action>a<obj>或<action>i<obj>
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
	vi"	会选择foo
	va"	会选择"foo"
	vi)	会选择"foo"
	va)	会选择("foo")	
	v2i)	会选择map (+) ("foo")
	v2a)	会选择(map (+) ("foo"))

块操作<c-v>
典型操作
	0 <c-v> <move> I <string> <Esc>
以上步骤分别代表
	0			移到行首,也可以移动到其他位置;
	<c-v>		进入列选模式,
	<move>		移动选择,
	I			插入模式, //A,追加模式
	<string>	编辑字符串,
	<Esc>		使每一行生效;	
在所有被选择的行后面追加某个字符串
	<c-v>
	选中相关的行;
	按$到行尾;
	按A,输入字符串;
	按<Esc>使每一行生效;

宏录制
	qa, 操作序列, q, @a, @@
qa录制操作记录在寄存器a,直到按q退出录制;
@a会replay存放在寄存器a中的录制宏;
@@是用来操作最新录制宏的快捷键;
示例
	在一个只有一行且这一行只有1的文本中,键入以下命令;
qaYp<c-a>q
	qa开始录制;
	Yp复制一行;
	<c-a>增加1;
	q停止录制;
@a
	在1下面写2;
100@@
	创建新的100行;会把数据增加到102;

多文件编辑
打开一个文件后,在正常模式下执行
打开
	:new 文件名
	:vi filename
	:sp filename
	:vs filename
	其中sp代表split创建分屏;将窗口分割为上下排列的窗口;
	vs代表vsplit,创建垂直分屏,将窗口分割为左右排列的窗口;
	<c-w>加方向键可以将光标在各个窗口中切换;
	<c-w>+或<c-w>-可以增大或减小窗口;
切换
	:e#	上一个文件
	:bn	下一个文件
	:bp	上一个文件
	ctrl+^在当前文件和上一个文件间转换
关闭
	:bw关闭当前文件

在底行模式下可以加一个!执行shell命令
	:!ls	//执行ls命令
	:r!ls	//将执行ls命令的结果嵌入到正在编辑的文档内

按v可以进入可视模式,移动光标可以选择内容,然后按y可以拷贝选中内容,按p可以粘贴缓冲区内容到当前光标之后.
按Ctrl+v可以上下移动光标进行列选,然后按I进入行首插入模式,编辑完成按两次Esc.
按Shift+v可以上下移动光标进行块选,然后按=可以对文档内容进行格式化缩排.

设置命令可以扩展vi的功能
设置命令是在底行模式下使用set命令实现的;
在底行模式下输入set nu可以让vi显示行号;set nonu取消显示行号

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

touch file
	如果file不存在则创建该文件
	如果file已经存在,则将文件的最后修改时间改成执行touch命令时的时间

rm 命令可以用来删除文件或目录
	-r	recursive递归操作
	-i	interactive每一个删除要求用户确认
	-f	force强制删除,不需要用户确认
	-v	verbose冗长显示,explain what is being done.

cp 命令可以把一个已经存在的文件或目录拷贝一份放在另外的地方
	-d	保持源文件的属性,对链接文件会复制链接而不是复制一个新的实体
	-f	强制执行,如果目标已经存在则会覆盖
	-i	覆盖之前要求用户确认
	-n	no clobber,如果目标已存在则不覆盖
	-r	递归操作,对拷贝的目录及其子目录递归操作
	-v	verbose冗长显示

mv 命令可以把一个已经存在的文件或目录移动到另一个地方,或更改名字
	-f	强制执行,如果目标已经存在则会覆盖
	-i	覆盖之前要求用户确认
	-n	no clobber,如果目标已存在则不覆盖
	-v	冗长显示,显示进行了哪些操作
对cp和mv命令而言,如果操作的源文件是文件名,
当目标是一个目录时则结果文件名保持不变只是复制文件或移动文件的位置,
当目标是一个路径后加上一个文件名,文件名可以与原来的相同此时文件名可以省略,如果文件名不同则表示复制为一个新的文件名或移动到一个新的位置并更改文件名.

set 命令可以查看当前系统所有设置的环境变量;
LC_TIME=zh_CN.UTF-8
此时运行date命令
2015年 07月 06日 星期一 13:49:19 CST
然后执行export命令设置环境变量
export LANG="en"
再次运行date命令
Mon Jul  6 13:50:32 CST 2015

如果系统安装时选择中文系统,在运行man命令查看帮助信息时看到的可能就会是中文,但是翻译可能会很费解;可以用export命令临时设置语言环境再用man命令;
export LANG="en"
man date

mount命令可以将系统所有已经加载的分区数据列出来;
mount -a 会根据/etc/fstab的内容将所有相关磁盘挂载;

如何删除/*和*/注释的语句;
用%s/pattern/new/gc; 其中/是分隔符,也可以换用其他任何字符,如#;
关键是如何书写正确的pattern正则表达式,考虑到*是正则表达式中的元字符,因此在设计时,先用x代替,然后再替换回*;
参考<<精通正则表达式>>对/x string x/类型的匹配采用如下模式
	[opening normal* (special normal*)* closing]
现根据/x string x/来设计正则表达式
opening		/x
normal*		[^x]*x+
special		[^/x]
closing		x/
因此得出/x string */正则表达式为
	/x[^x]*x+([^/x][^x]*x+)*/
将所有的x替换为*,并考虑到*为元字符,需要适用\转义,得
	/\*[^*]*\*+([^/*][^*]*\*+)*/
还要注意在正则表示使中/也需要转义,因此得到最终的/* string */的正则表达式
	\/\*[^*]*\*+([^/*][^*]*\*+)*\/
然后使用awk的gsub函数处理即可
cat akari.c | awk 'BEGIN{RS=""}{gsub(/\/\*[^*]*\*+([^/*][^*]*\*+)*\//, " ", $0); print $0}'


作业 
    抄写snake.c达到20分钟以内且无任何错误;
```cpp
/*
 * snake.c
 */
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#define APPLE			'@'
#define SNAKEHEAD		'+'
#define SNAKETAIL		'-'
#define SIZE			10

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