程序的存储
字符串操作函数
指针数组
main()函数的形参


程序的存储
	程序在内存中是分段存储的;
6->栈区 	存放局部变量,块变量,形式参数和返回值的存储位置;这个段落的大小随着程序的运行不断改变;每当一个函数调用出现时就从这个段落中分配一段空间来记录它自己的变量;当函数调用结束时它所分配的空间被计算机回收;不同函数调用的空间遵循后进先出的原则;

5->堆区 	存放动态分配的存储位置;动态分配存储位置的分配和回收工作由程序员编写语句管理,如果管理错误会产生严重后果;

4->BSS段	存放初值为0或没有初始化的全局变量;在main()函数执行之前会自动清0;
3->全局区	存放static变量和初值不为0的全局变量,这个段落的大小不会随着程序的运行而改变;主函数执行之前分配,进程结束时回收;

2->只读常量区	存放字符串字面值和const修饰的全局变量;
1->代码区	存放代码(函数)的区域,只读的区域;


字符串处理函数

字符串是专门用来记录大量文字信息的, 字符串包含多个连续的字符类型存储位置, 使用这些存储位置记录文字信息;
ASCII码为0的字符表示字符串的结束位置, 这个字符用'\0'表示; 有时需要在编程时保证'\0'字符出现在文字信息末尾;
在程序中使用第一个存储位置的地址表示整个字符串的文字信息;
所有字符串都可以使用 char* 类型指针表示, 只要把第一个字符存储位置的地址记录在指针中;

字符串字面值是一种字符串;例如"abc", "+-*"等用双引号括起来的字符表示;
字符串字面值在编译好以后会用首字符地址代替, 并在末尾加上'\0';
字符串字面值在程序运行时不可以被修改(存储在只读常量区);

同样的字符串字面值在内存中占同一段存储位置;
并列的两个字符串字面值会被编译器自动合并成一个, 如"abc""def"编译时合并然后自动在最后加'\0';
字符数组也可以当字符串使用;
如果想使用字符数组表示字符串就必须保证其中包含'\0'字符;
字符数组是可以用字符串字面值进行初始化的;
这个时候字符串字面值中的'\0'字符会被初始化到数组中;

/*
 * 字符串演示
 */
#include <stdio.h>
int main() {
	char str[] = "abc";
	printf("\"abc\"的地址是%p\n", "abc");
	/* "abc"字符串字面值被存储在只读区; */
	printf("str[]的地址是%p\n", str);
	printf("%c\n", *"abc"); //"abc"代表的是这个字符串的首地址;
	printf("str is %s\n", str);
	//*"abc" = 'z'; 错误,程序运行时不可修改;
	printf("sizeof(str) is %d\n", sizeof(str));
	return 0;
}

使用字符串字面值对字符数组初始化完成后他们各占一组存储位置, 相互之间没有关系;
使用字符串给字符数组赋值, 实际上在数组中存储的是一份字符串的拷贝;
字符数组中的所有存储位置都是可以被修改的;

字符串不可以使用普通操作符进行操作;可以使用标准函数实现对字符串的操作,这些标准函数需要包含string.h文件;

	sizeof关键字可以得到存储位置的大小(包括字符串结尾标志'\0');
	strlen()用来计算字符串中有效字符的个数;
	strcat()用来把一个字符串'追加'到另一个字符串的末尾,会修改一个原来的字符串,用返回值表示新字符串;这个函数可能造成下标越界,所以是不安全的;
	strncat()可以指定最多可以合并多少个字符到字符串,所以可以避免下标越界;
	strcpy()可以复制一个字符串,调用函数需要提供存储位置用来记录复制得到的新字符串;用返回值表示复制得到的新字符串;也可能造成下标越界,也是不安全的;
	strncpy()功能和strcpy()类似,但只复制前n个字符;
	strcmp()用来比较两个"字符串"的大小,比较的依据是字符的ASCII码数值;返回1表示前一个字符串大,返回0表示一样大,返回-1表示前一个字符串小;
	strncmp()只比较两个字符串中的前n个字符,第三个参数为n指定比较的个数;

一些C语言字符串处理相关的函数原型可以参考kernel/lib/string.c

编写strcpy函数(10分)
	已知strcpy函数的原型是 char *strcpy(char *strDest, const char *strSrc);
	其中strDest是目的字符串,strSrc是源字符串;
	1->不调用C++/C的字符串库函数,请编写函数strcpy()
char *strcpy(char *strDest, const char *strSrc)
{
	assert((strDest!=NULL) && (strSrc !=NULL)); // 2分
	char *address = strDest; // 2分
	while( (*strDest++ = * strSrc++) != '/0'); // 2分
	return address ; // 2分
}
	2->strcpy()能把strSrc的内容复制到strDest,为什么还要char *类型的返回值
		为了实现链式表达式; // 2分
		如 size_t length = strlen(strcpy(strDest, "hello world"));

/**
 * strcpy - Copy a %NUL terminated string
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 */
char *strcpy(char *dest, const char *src)
{
	char *tmp = dest;
	while ((*dest++ = *src++) != '\0');
	return tmp;
}
函数类型为char*可以构成链式表达式,如 size_t length = strlen(strcpy(strDest, "hello world"));
返回的是tmp变量的值即dest的值,是目标表达式的首地址;

/**
 * strncpy - Copy a length-limited, %NUL-terminated string
 * @dest: Where to copy the string to
 * @src: Where to copy the string from
 * @count: The maximum number of bytes to copy
 *
 * The result is not %NUL-terminated if the source exceeds
 * @count bytes.
 *
 * In the case where the length of @src is less than  that  of
 * count, the remainder of @dest will be padded with %NUL.
 *
 */
char *strncpy(char *dest, const char *src, size_t count)
{
	char *tmp = dest;

	while (count) {
		if ((*tmp = *src) != 0)
			src++;
		tmp++;
		count--;
	}
	return dest;
}

/**
 * strcat - Append one %NUL-terminated string to another
 * @dest: The string to be appended to
 * @src: The string to append to it
 */
char *strcat(char *dest, const char *src)
{
	char *tmp = dest;

	while (*dest)
		dest++;
	while ((*dest++ = *src++) != '\0') ;
	return tmp;
}

/**
 * strncat - Append a length-limited, %NUL-terminated string to another
 * @dest: The string to be appended to
 * @src: The string to append to it
 * @count: The maximum numbers of bytes to copy
 *
 * Note that in contrast to strncpy(), strncat() ensures the result is
 * terminated.
 */
char *strncat(char *dest, const char *src, size_t count)
{
	char *tmp = dest;

	if (count) {
		while (*dest)
			dest++;
		while ((*dest++ = *src++) != 0) {
			if (--count == 0) {
				*dest = '\0';
				break;
			}
		}
	}
	return tmp;
}

/**
 * strcmp - Compare two strings
 * @cs: One string
 * @ct: Another string
 */
int strcmp(const char *cs, const char *ct)
{
	unsigned char c1, c2;

	while (1) {
		c1 = *cs++;
		c2 = *ct++;
		if (c1 != c2)
			return c1 < c2 ? -1 : 1;
		if (!c1)
			break;
	}
	return 0;
}

/**
 * strncmp - Compare two length-limited strings
 * @cs: One string
 * @ct: Another string
 * @count: The maximum number of bytes to compare
 */
int strncmp(const char *cs, const char *ct, size_t count)
{
	unsigned char c1, c2;

	while (count) {
		c1 = *cs++;
		c2 = *ct++;
		if (c1 != c2)
			return c1 < c2 ? -1 : 1;
		if (!c1)
			break;
		count--;
	}
	return 0;
}

/**
 * strlen - Find the length of a string
 * @s: The string to be sized
 */
size_t strlen(const char *s)
{
	const char *sc;

	for (sc = s; *sc != '\0'; ++sc);
	return sc - s;
}

/**
 * memset - Fill a region of memory with the given value
 * @s: Pointer to the start of the area.
 * @c: The byte to fill the area with
 * @count: The size of the area.
 *
 * Do not use memset() to access IO space, use memset_io() instead.
 */
void *memset(void *s, int c, size_t count)
{
	char *xs = s;

	while (count--)
		*xs++ = c;
	return s;
}

/**
 * memcpy - Copy one area of memory to another
 * @dest: Where to copy to
 * @src: Where to copy from
 * @count: The size of the area.
 *
 * You should not use this function to access IO space, use memcpy_toio()
 * or memcpy_fromio() instead.
 */
void *memcpy(void *dest, const void *src, size_t count)
{
	char *tmp = dest;
	const char *s = src;

	while (count--)
		*tmp++ = *s++;
	return dest;
}

/**
 * memmove - Copy one area of memory to another
 * @dest: Where to copy to
 * @src: Where to copy from
 * @count: The size of the area.
 *
 * Unlike memcpy(), memmove() copes with overlapping areas.
 */
void *memmove(void *dest, const void *src, size_t count)
{
	char *tmp;
	const char *s;

	if (dest <= src) {
		tmp = dest;
		s = src;
		while (count--)
			*tmp++ = *s++;
	} else {
		tmp = dest;
		tmp += count;
		s = src;
		s += count;
		while (count--)
			*--tmp = *--s;
	}
	return dest;
}

/**
 * memcmp - Compare two areas of memory
 * @cs: One area of memory
 * @ct: Another area of memory
 * @count: The size of the area.
 */
int memcmp(const void *cs, const void *ct, size_t count)
{
	const unsigned char *su1, *su2;
	int res = 0;

	for (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--)
		if ((res = *su1 - *su2) != 0)
			break;
	return res;
}

/**
 * strstr - Find the first substring in a %NUL terminated string
 * @s1: The string to be searched
 * @s2: The string to search for
 */
char *strstr(const char *s1, const char *s2)
{
	size_t l1, l2;

	l2 = strlen(s2);
	if (!l2)
		return (char *)s1;
	l1 = strlen(s1);
	while (l1 >= l2) {
		l1--;
		if (!memcmp(s1, s2, l2))
			return (char *)s1;
		s1++;
	}
	return NULL;
}

/*
 * 字符串函数演示
 */
#include <stdio.h>
#include <string.h>
int main() {
	char buf[20] = "abc";
	printf("\"abc\"有效字符个数是%d\n", strlen("abc"));
	printf("\"abc \"有效字符个数是%d\n", strlen("abc "));
	printf("strcat()后的结果是%s\n", strcat(buf, "def"));
	printf("buf is %s\n", buf);
	printf("strcpy()后的字符串是%s\n", strcpy(buf, "xyz"));
	/* strcopy()的返回值就是第一个参数buf */
	printf("buf is %s\n", buf);
	printf("strcmp()结果是%d\n", strcmp("abc", "abd"));
	return 0;
}
"abc"有效字符个数是3
"abc "有效字符个数是4
合并后的结果是abcdef
buf is abcdef
复制后的字符串是xyz
buf is xyz
比较结果是-1


可以使用%s做占位符读写字符串
这个时候计算机会处理连续多个存储位置, 而不仅仅一个, 遇到'\0'才会结束;
如果字符数组在存储时越界就会丢失'\0'结束符, 在用%s时就会有意想不到的事情发生;
使用scanf()从键盘读字符串是不安全的;

/*
 * 字符串读写演示
 */
#include <stdio.h>
#include <string.h>
int main() {
	char buf[20]={};
	printf("请输入一个字符串: ");
	scanf("%s", buf); //中间不可有空格或超出数组
	printf("字符串是: %s\n", buf);
	return 0;
}
运行结果为 
请输入一个字符串: 字符串是: hljlkk

fgets()函数可以从任何文件得到一个字符串,并放在一个数组中;
在linux系统中一切都可以用文件表示,键盘是标准输入设备,用标准输入文件表示(stdin),显示器是标准输出设备,用标准输出文件表示(stdout);
char *fgets(char *s, int size, FILE *stream);
需要三个参数 
	数组名称(得到的字符串存储在这个数组的存储位置中);
	数组中存储位置的个数;
	要读取的文件指针(stdin);
fgets()函数会在数组有效字符最后加'\0'; 
如果输入的字符个数不够多则会把最后的回车也读入进去;
读取完成后如果输入缓冲区中还留有垃圾数据则需要清理;

/*
 * 字符串读写演示
 */
#include <stdio.h>
#include <string.h>
int main() {
	char buf[20] = { };
	printf("请输入一个字符串: ");
	//scanf("%s", buf); //中间不可有空格或超出数组
	fgets(buf, 10, stdin);
	//第一个参数是数组,读取10个字符,从标准输入读取;
	printf("字符串是: %s\n", buf);
	if (strlen(buf) == 9 && buf[8] != '\n') {
		//当buf中有九个有效字符且最后一个不是回车,清除输入缓存
		//否则会影响后面的fgets();
		scanf("%*[^\n]");
		scanf("%*c");
	}
	printf("请输入一个字符串: ");
	fgets(buf, 10, stdin);
	//第一个参数是数组,读取10个字符,从标准输入读取;
	printf("字符串是:%s\n", buf);
	return 0;
}
运行结果: 
请输入一个字符串: 字符串是: hlkhhasl;
请输入一个字符串: 字符串是: hlkfjakjg

/*
 * 编写一个模拟登录系统;
 * 假设用户名为Admin,密码是123456;给用户三次尝试机会,
 * 如果三次都失败则提示登录失败,否则提示登录成功;
 */
#include <stdio.h>
#include <string.h>
int main() {
	char user[10] = "Admin\n", passwd[10] = "123456\n";
	//用户最后一次输入的是回车,所以加'\n'.
	char arr[10] = { }, arr1[10] = { };
	int i = 0;
	for (i = 0; i <= 2; i++) {
		printf("请输入用户名: ");
		fgets(arr, 10, stdin);
		//printf("%s",arr);
		if (strlen(arr) == 9 && arr[8] != '\n') {
			//输入的内容多了
			scanf("%*[^\n]");	//清除
			scanf("%*c");
		}
		if (strncmp(arr, user, strlen(user))) {
			continue;	//用户名错误,直接重新循环
		}
		printf("请输入密码: ");
		fgets(arr1, 10, stdin);
		if (strlen(arr1) == 9 && arr[8] != '\n') {
			scanf("%*[^\n]");
			scanf("%*c");
		}
		if (strcmp(arr1, passwd)) {
			continue;
		}
		break;
	}
	if ((i <= 2)) {
		printf("登录成功\n");
	} else {
		printf("登录失败\n");
	}

	return 0;
}
运行结果为: 
请输入用户名:
请输入密码:
登录成功

字符串与整数转换的函数
int atoi(const char *nptr);
	将字符串转换成整型数,atoi()会扫描参数nptr字符串,跳过前面的空格,直到遇到数字或正负号才开始做转换,而再次遇到非数字或字符串结束符'\0'时结束转换,并将结果返回;
	返回转换后的整数;
long atol(const char *nptr);
long long atol(const char *nptr);
	使用以上几个函数,需要添加头文件stdlib.h;
/*
 * atoi()函数演示
 */
#include <stdio.h>
#include <stdlib.h>
int main() {
	char a[] = "-100";
	char b[] = "456";
	char c[] = "1234567890";
	int d = 0;
	long e = 0;
	d = atoi(a) + atoi(b);
	printf("d = %d\n", d);
	e = atol(c);
	printf("e = %ld\n", ++e);
	return 0;
}

strtol()与strtoll();
long int strtol(const char *nptr, char **endptr, int base);
long long int strtol(const char *nptr, char **endptr, int base);
	使用这两个函数需要添加头文件stdlib.h;
strtol()会将nptr指向的字符串,根据参数base,按权转化为long int,然后返回这个值;
参数base的范围是2~36或0;他决定了字符串每一位的权值;
可以被转换的合法字符依base而定;
	当base为2,合法字符为'0','1';
	当base为8,合法字符为'0','1',...'7';
	当base为10,合法字符为'0','1',...'9';
	当base为16,合法字符为'0','1',...'9','a',...'f';
	当base为24,合法字符为'0','1',...'9','a',...'n';
	当base为36,合法字符为'0','1',...'9','a',...'z';
其中字母不去分大小写,比如'A'和'a'都会被转化为10;
当字符合法时,'0'...'9'依次被转换为十进制的0-9,'a',...'z'依次被转换为十进制的10~35;
strtol()函数检测到第一个非法字符时,立即停止检测和转换;其后的所有字符都被当作非法字符处理;合法字符串会被转换为long int,并作为函数的返回值返回;
非法字符串,即第一个非法字符的地址被赋值给参数endptr,endptr是二级指针;strtol()通过它带回非法的字符串;
多数情况下,endptr设置为NULL,即不传递非法字符串;

	如果base为0,按8进制或十进制或16进制;八进制或十六进制时取决于原字符串是否以0或0x开头;
	如果base为0或16,当字符串以0x(0X)开头,那么x(X)会被忽略,字符串按16进制转换;
	如果base不等于0或16,当字符串以0x(0X)开头,那么x被视为非法字符;
/*
 * strtol()函数演示
 */
#include <stdio.h>
#include <stdlib.h>
void strtol_test1(int base) {
	char buf[20] = "1079end3";
	char *stop;
	printf("buf = %s, base = %d\n", buf, base);
	printf("\tstrtol(buf, &stop, base) = %ld\n", strtol(buf, &stop, base));
	printf("\tenptr: %s\n", stop);
}
void strtol_test2(int base) {
	char buf[20] = "0x31a";
	char *stop;
	printf("buf = %s, base = %d\n", buf, base);
	printf("\tstrtol(buf, &stop, base) = %ld\n", strtol(buf, &stop, base));
	printf("\tenptr: %s\n", stop);
}
void strtol_test3(int base) {
	char buf[20] = "017ac";
	char *stop;
	printf("buf = %s, base = %d\n", buf, base);
	printf("\tstrtol(buf, &stop, base) = %ld\n", strtol(buf, &stop, base));
	printf("\tenptr: %s\n", stop);
}
int main() {
	strtol_test1(0);
	strtol_test1(2);
	strtol_test1(8);
	strtol_test1(10);
	strtol_test1(16);
	strtol_test1(36);
	strtol_test2(0);
	strtol_test2(8);
	strtol_test2(10);
	strtol_test2(16);
	strtol_test2(36);
	strtol_test3(0);
	strtol_test3(8);
	strtol_test3(10);
	strtol_test3(16);
	strtol_test3(36);
	return 0;
}


采用二维数组可以记录多个相关字符串,以后可以采用循环依次处理其中的每个字符串;这种方式会造成存储位置的浪费;
采用这种方式无法表示多个不同来源的字符串;

/*
 * 多个相关字符串记录演示
 */
#include <stdio.h>
int main() {
	char ranks[5][4]={"48", "52", "96", "37", "100"};
	//二维数组,当每一组长度不一时,浪费存储空间;
	int num = 0;
	for (num = 0; num <= 4; num++){
		printf("%s ", ranks[num]);
	}
	printf("\n");
	return 0;
}
运行结果: 48 52 96 37 100


指针数组

指针数组包含多个存储位置, 每个存储位置用一个字符类型指针表示;
指针数组也可以用来表示多个相关字符串;
采用这种方式表示多个相关字符串可以避免二维数组存储空间浪费的问题;

/*
 * 多个相关字符串记录演示
 */
#include <stdio.h>
int main() {
	//char ranks[5][4]={"48","52","96","37","100"};
	//二维字符型数组表示
	char *ranks[5] = { "48", "52", "96", "37", "100" };
	//一维字符型数组指针表示,可以适当的节约存储空间;
	//类型是char* [5];字符串数组,元素是字符串;
	//rank[i]中存放的是指向字符串的指针,即字符串的首地址;
	int num = 0;
	for (num = 0; num <= 4; num++) {
		printf("%s\n", ranks[num]);
	}
	return 0;
}

指针数组名称可以记录在二级指针变量中
二维数组名称和二级指针完全无关;
一维数组和一级指针是等价的; 

主函数main()也有参数
第二个参数是一个指针数组, 其中每个指针记录从命令中拆出来一个字符串的首地址;
第一个参数记录第二个参数中有效指针存储位置的个数;

/*
 * 主函数参数演示
 */
#include <stdio.h>
//int main(int argc,char *argv[]){ //指针数组
int main(int argc, char **argv) { //二级指针
	//argc记录argv中有效指针存储位置的个数;
	//argv是一个指针数组,其中每个指针记录从命令中拆分出来一个字符串的首地址;
	//agrv可以看成一个指针数组,也可以看成是一个二维指针;
	int num = 0;
	for (num = 0; num <= argc - 1; num++) {
		printf("argv中记录了%s\n", argv[num]);
	}
	printf("argv[]中记录的有效指针存储位置个数%d\n", argc);

	return 0;
}
运行结果: 
./a.out
hjh
klkl
sdgfsd
dg
argv[]中记录的有效指针存储位置个数5

作业
	编写函数mystrcat完成两个字符串内容的合并,使用指针;
/*
 * 编写函数mystrcat完成两个字符串内容的合并,使用指针;
 */
#include <stdio.h>
#include <string.h>
char *mystrcat(char *p_dest, const char *p_src) {
	char *p_tmp = p_dest;
	while (*p_dest) p_dest++; //移动指针到字符串结尾
	while ((*p_dest++ = *p_src++) != '\0'); //循环赋值到第二个字符串结尾
	return p_tmp;
}
int main() {
	char buf[20] = "abcdefg";
	printf("%s\n", mystrcat(buf, "123xyz"));
	printf("buf is %s\n", buf);
	return 0;
}

