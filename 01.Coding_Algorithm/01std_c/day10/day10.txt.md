函数形参
数组做形参
文件操作函数


函数形参

形式参数是在函数调用发生时临时创建出来的,在函数调用结束时又被销毁;
形式参数只有在函数调用期间才可以使用;
使用普通变量作为形式参数只能传递数据不能传递存储位置;
被调函数如果修改了普通变量形参对其他函数没有任何影响;
如果声明被调用函数时小括号()内是空的,表示函数可以接受任意个数任意类型的形参;
如果想表示函数没有任何形参,则应该在小括号内写void如(void);

/*
 * void参数列表演示
 */
#include <stdio.h>
void print() {
	printf("不是void形参\n");
}

void print1(void) {
	printf("void形参\n");
}

int main() {
	print(1, 2, 3);
	print1();		//print1函数形参列表为void
	return 0;
}

数组做函数的形参传递的是数组的存储位置,因为数组名就代表数组的首地址;
数组的本质是指针,指针即地址;数组不是普通的变量;

函数对数组(高一级指针)形参所做的修改会影响调用函数的实参;
传递的指针或数组就相当于一个容器,虽然函数形参的变化不会改变实参(容器)本身;但会改变容器中的值,因为形参和实参虽是两个无关的变量,但变量中的值(地址)都指向同一块存储空间;
因此数组形参可以实现双向数据传递,这种参数叫做输入输出参数;
虽然在C语言中参数的传递都是值传递,但如果传递的是指针(或数组),因为传递的这个值代表的是一个地址,形参的改变也会影响到实参(容器)所指向的存储空间的值;

普通变量形参只能把数据从调用函数传递到被调用函数,这种参数叫输入参数;
函数的形参是在函数内部生成的局部变量,函数调用结束时被释放;
数组名称和存储位置的地址都可以作为实参和数组形参配对;
数组形参仅仅相当于一个指针,只表示一个数组的首地址,无法表示其中包含的存储位置个数,需要另一个形参表示这个信息;
/*
 * 数组做形参演示
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void arr_param(int arr[10]) {
	printf("sizeof(arr[10]) = %ld\n", (long)sizeof(arr[10]));
	// sizeof(arr[10]) = 4
	// 数组做形参就相当于一个指针;
}
void lottery(int arr[], int size) {
	/* 函数声明也可以写成
	void lottery(int *arr, int size) */
	int num = 0;
	for (num = 0; num <= size - 1; num++) {
		arr[num] = rand() % 36 + 1;
	}
}

int main() {
	srand(time(0));
	int arr[10] = { }, num = 0;
	arr_param(arr);

	lottery(arr, 6);	//6小于arr[10]声明中的10,可以使用

	for (num = 0; num <= 5; num++) {
		printf("%d ", arr[num]);
	}
	printf("\n");
	return 0;
}

练习
	把一个数组里面的所有随机数字变为其相反数
/*
 * 数组做形参练习
 * 练习把一个数组里面的所有数字变为其相反数
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void neg(int arr[], int size) {
	int num = 0;
	for (num = 0; num <= size - 1; num++) {
		printf("%d ", arr[num]);
		arr[num] = 0 - arr[num];
	}
	printf("\n");
}
void print(int arr[], int size) {
	int num = 0;
	for (num = 0; num <= size; num++) {
		printf("%d ", arr[num]);
	}
	printf("\n");
}

int main() {
	int arr[20] = { }, num = 0;
	srand(time(0));
	for (num = 0; num <= 10; num++) {
		arr[num] = rand() % 100 - 50;
	}
	print(arr, 10);
	neg(arr, 5);	//只对前5个数据进行取相反数操作,后面不变
	print(arr, 10);
	return 0;
}

///////////////////////////////////////////////////////
/*
 * 指针, 高级指针, 函数的形参与实参,传值
 * Longbin Li
 * 2014-09-25
 */
#include <stdio.h>

/*
 * 函数的返回值最多只能有一个,
 * 一般用来判断函数的执行情况如大部分Unix C库函数;
 * 还有一部分用来得到临时的执行结果,类似于sizeof关键字;
 * 还有一部分可以返回指针,如malloc()函数;
 *
 * strcpy()函数同样也返回一个char*类型的指针,
 * 可以实现链式表达式,也就是为了方便函数调用而设计的,如
 * int length = strlen(strcpy(strdest, "hello world"));
 * 这条语句就是链式表达式;
 */

/*
 * 函数的参数可以有多个,但函数的形参与实参类型要相同或赋值兼容;
 * 在函数参数的小括号里如果为空,则表示可以接收任意类型任意个数的参数;
 */

/* 在C语言中函数形参的改变不会改变实参的值; */
void swap_int(int num1, int num2) {
	int tmp0;
	tmp0 = num1;
	num1 = num2;
	num2 = tmp0;
	/*
	 * 函数形参num1/num2发生改变,不能改变实参a/b的值
	 * 函数被调用时num1和num2为函数的局部变量,num1=a,num2=b;
	 * 改变num1和num2的值,实际是在修改被调函数内部的局部变量的值;
	 * 当函数调用结束,局部变量被释放,而实参的值一直都没有被改变;
	 */
}

void swap_p_int(int *p1, int *p2) {
	int tmp;
	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
	/* 函数形参p1/p2发生改变,不能改变实参&a/&b的值 */
	/*
	 * 但&a/&b作为a/b的高一级指针形式,
	 * 通过改变*p1,*p2的值可以改变a/b的值 
	 * 因为p1,p2指向了a和b所在的存储位置;
	 */
}

void swap_pp_int(int **pp1, int **pp2) {
	int *tmp = NULL;
	tmp = *pp1;
	*pp1 = *pp2;
	*pp2 = tmp;
	/* 实参为ppa=&pa,ppb=&pb时;
	 * 改变形参也不会改变&pa和&pb的值,
	 * 但可以改变pa和pb的值(指向)
	 */
}

/*
 * 如果要通过调用函数改变某个变量的值,不能直接把这个变量传递给被调用函数;
 * 而是要传递变量存储空间的地址给调用函数,这样就可以在被调用函数内操作它的存储空间中存储的值来实现修改变量的值;
 * 因为C语言函数的传参只是传值,形参只是在数值上与实参的值相同,但形参和实参变量却是不同的变量,对应不同的存储空间,没有必然联系; 
 */

/*
 * 如果要通过函数调用来改变某个实参变量的值,需要传递它的高一级指针形式;
 * 如果希望改变一个普通变量的值,需要传递它的指针;
 * 如果希望改变一个指针变量的值,需要传递它的更高一级指针;
 */
int main() {
	int a = 1, b = 2;
	int *pa = &a, *pb = &b;
	int **ppa = &pa, **ppb = &pb;

	printf("============================================\n");
	printf("\ta = %d,\t b = %d\n", a, b);
	swap_int(a, b);
	printf("swap_int(a, b)\n");
	printf("\ta = %d,\t b = %d\n", a, b);

	printf("============================================\n");
	printf("\ta = %d,\t b = %d\n", a, b);
	/* * %p是用来打印地址的占位符,
	 * 会根据系统读取4字节或8字节并以16进制打印 */
	printf("\t&a = %p,\t &b = %p\n", &a, &b);
	swap_p_int(&a, &b);
	printf("swap_p_int(&a, &b)\n");
	printf("\t&a = %p,\t &b = %p\n", &a, &b);
	printf("\ta = %d,\t b = %d\n", a, b);
	printf("--------------------------------------------\n");
	printf("\t*pa = %x,\t *pb = %x\n", *pa, *pb);
	printf("\tpa = %p,\t pb = %p\n", pa, pb);
	swap_p_int(pa, pb);
	printf("swap_p_int(pa, pb)\n");
	printf("\tpa = %p,\t pb = %p\n", pa, pb);
	printf("\t*pa = %x,\t *pb = %x\n", *pa, *pb);

	printf("============================================\n");
	printf("\tpa = %p,\t pb = %p\n", pa, pb);
	printf("\t&pa = %p,\t &pb = %p\n", &pa, &pb);
	swap_pp_int(&pa, &pb);
	printf("swap_pp_int(&pa, &pb)\n");
	printf("\t&pa = %p,\t &pb = %p\n", &pa, &pb);
	printf("\tpa = %p,\t pb = %p\n", pa, pb);

	printf("============================================\n");
	printf("\t*ppa = %p,\t *ppb = %p\n", *ppa, *ppb);
	printf("\tppa = %p,\t ppb = %p\n", ppa, ppb);
	swap_pp_int(ppa, ppb);
	printf("swap_pp_int(ppa, ppb)\n");
	printf("\tppa = %p,\t ppb = %p\n", ppa, ppb);
	printf("\t*ppa = %p,\t *ppb = %p\n", *ppa, *ppb);
	printf("--------------------------------------------\n");

	return 0;
}
///////////////////////////////////////////////////////

二维数组与形参
	可以用二维数组名作为实参或者形参,在被调用函数中对形参数组定义时可以指定所有维数的大小,也可以省略第一维的大小说明,如
	void Func(int array[3][10]);
	void Func(int array[][10]);
	二者都是合法的而且等价,但是不能把第二维或者更高维的大小省略,如下面的定义是不合法的
	void Func(int array[][]);
	因为从实参传递来的是数组的起始地址,在内存中按数组排列规则存放(按行存放),而并不区分行和列,如果在形参中不说明列数,则系统无法决定应为多少行多少列,不能只指定第一维而不指定第二维,下面写法是错误的
	void Func(int array[3][]);
	实参数组可以大于形参数组,例如形参数组定义为
	void Func(int array[3][10]);
	而实参数组定义为
	int array[5][10];
	这时形参数组只取实参数组的一部分,其余部分不起作用;
	将二维数组当作参数的时候,必须指明所有维数大小或者省略第一维,但是不能省略第二维或者更高维的大小,这是由编译器原理限制的;
	根据编译原理可知,如果我们省略了第二维或者更高维的大小,编译器将不知道如何正确的寻址;但是我们在编写程序的时候却需要用到各个维数都不固定的二维数组作为参数,这就难办了,编译器不能识别啊,怎么办呢?
	编译器虽然不能识别,但是我们完全可以不把它当作一个二维数组,而是把它当作一个普通的指针,再另外加上两个参数指明各个维数,然后我们为二维数组手工寻址,这样就达到了将二维数组作为函数的参数传递的目的,根据这个思想,我们可以把维数固定的参数变为维数随机的参数,例如
	void Func(int array[3][10]); 
	void Func(int array[][10]);
	变为
	void Func(int **array, int RowSize, int LineSize);
	在转变后的函数中,array[i][j]这样的式子是不对的(不信,大家可以试一下),因为编译器不能正确的为它寻址,所以我们需要模仿编译器的行为把array[i][j]手工转变为
	*((int *)array + LineSize*i + j);即把二维数组当作一维数组来处理;

数组作为形参的问题总结
一维数组作为函数形参
	数组作为形参时,编译器通常只会检查数组形参关联的实参,检查的项目包括实参是不是指针/指针类型和数组元素的类型是否匹配,但不会检查数组的长度;
	void print( int *a[] )
	void print( int *a[10] )
	void print( int *a )
	上面两个是二级指针,下面一个是一级指针;
	
	在很多情况下,将数组形参直接定义为指针要比使用数组语法定义方便很多;因为定义为指针后,函数可以借助于指针方便的操作数组元素;
	数组以非引用类型传递时,数组会自动转换为同类型的指针,即初始化为相应类型实参的副本;调用函数时,函数实际操作的是指针的副本,而不会修改实参指针的值,但是可以通过指针改变数组元素的值;
	
多维数组的传递
	多维数组的元素本身就是数组;
	
	对二维数组的处理可以采用将二维数组看作一维或者二维数组来处理,下面两个例子分别采用了这两种方法;第3个例子有点不同,但实际上也是利用了一维数组作中间过渡处理;
	
	例1 将二维数组当作一维数组来处理
	print_array和主函数中的循环printf实现了同样效果
#include <stdio.h>
void print_array(int *p, int RowSize, int LineSize) {
	int i, j;
	for(i = 0 ; i < RowSize ; i++) {
		for(j = 0 ; j < LineSize ; j++) {
			printf("%d ", *(p + i*LineSize + j));
		}
		printf("\n");
	}
}

void main() { 
	int i, j, a[3][3] = { {1,0,0} , {0,1,0} , {0,0,1} };
	print_array((int *)a, 3, 3);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			printf("%d ", *(*(a+i) + j));
		}
		printf("\n");
	}
}
	
	例2 将二维数组依旧当作二维数组来处理
	下面是一个字符串数组的参数传递程序,实现将字符串数组中的字符串按照从小到大的顺序进行排序;
	//WordSort实现了对5个字符串的排序
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void WordSort(char p[][10], int RowSize) {
	int n = 0, m;
	char temp[10];
	for (n = 0; n < RowSize; n++) {
		for (m = n + 1; m < RowSize; m++) {
			if ( strcmp(p[m], p[n]) < 0 ) { 
				strcpy(temp, p[n]);
				strcpy(p[n], p[m]);
				strcpy(p[m], temp);
			}
		}
	}
	for (n = 0; n < 5; ++n) {
		printf("In subfunction: %s\n", p[n]);
	}	
}
void main() {
	int k=0;
	char word[5][10];
	printf("please input 5 words: ");
	for(; k < 5; ++k) {
		scanf("%s", word[k]);
	}
	WordSort(word, 5);
	printf("sorted word:\n");
	for(k = 0; k < 5; k++) {
		printf("In main function: %s\n", word[k]);
	}
	getchar();
}
	
	例3 用"行指针"传递参数
/************************************/
//二维数组作为形参的参数传递方式之一
/************************************/
#include <stdio.h>
/* 传递数组指针 */
/* a是一个指向3个整型元素的数组的指针 */
void print_array_1(int (*a)[3], int Row_Size) { 
	int j; 
	for(j = 0; j < 3*Row_Size; j++) {
		printf("%d ", (*a)[j]);
		if (j % 3 == 2) printf("\n");
	}
}
void print_array_2(int (*a)[3], int Row_Size) { 
	int i,j;
	for(i = 0; i < Row_Size; i++) {
		for(j = 0; j < 3; j++) {
			printf("%d ", *(*(a+i) + j));
		}
		printf("\n");
	}
}
void main() { 
	int i, j, value = 0; 
	int a[4][3] = {0}; 
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 3; j++) { 
			a[i][j] = ++value;
		}
	}
	print_array_1(a, 4);
	printf("\n");
	print_array_2(a, 4); 
} 
	
	这个程序中的两个函数实现了相同的功能:打印数组元素;这种方法可能容易使人迷惑:int (*a)[3] 是什么东西呢?还得看谭浩强先生编著的《C程序设计》(P229-P230),上面这样写道(在本例中) *a有3个元素,每个元素为整型;也就是a所指向的对象是有3个整型元素的数组,即a是行指针;
	
用这个方法处理字符串数组(字符型二维数组),还是比较方便的
	//打印数组内字符串(一行)
#include <stdio.h>
void print_string(char (*string)[20], int Row_Size) {
	int i;
	for (i = 0; i < Row_Size; i++) {
		printf("%s\n",string+i);
	}
}
void main() {
	char a[6][20] = {"God", "bless", "you", "who", "help", "themselves"};
	print_string(a,6);
}
	

隐式声明

gcc编译时如果先处理函数调用语句会采用函数隐式声明猜测一个函数的格式,隐式声明格式如下:
int add();
这表示函数的返回值是整数类型,函数可以接受任意数量任意类型的参数;
函数的隐式声明是不可靠的,不应该依赖函数的隐式声明,因为它有可能会出错;
函数大括号前面的部分叫函数声明,把它单独写在文件开头就可以避免隐式函数声明;这种声明函数的方式叫显式声明;
把函数声明单独写一条语句时可以省略参数的名称;

/*
 * 函数隐式声明
 */
#include <stdio.h>
/* 显式函数声明,可以只保留参数类型省略参数 */
double add(double, double);

int main() {
	printf("add(4,7) is %d\n", (int)add(4, 7));
	/*
	 * 编译器会对未声明的函数进行类型猜测,
	 * 默认为int add(),这种格式即函数的隐式声明;
	 */
	return 0;
}

/*
 * //如果函数的返回值类型是int型,就可以采用函数隐式类型声明
 * int add(int x,int y) {
 *     return x + y ;
 * }
 */

double add(double x, double y) {
	return x + y;
}


文件操作函数

文件操作的相关标准函数
	fopen()标准函数用来打开一个标准文件,返回FILE*类型的指针;
	fclose()标准函数用来关闭文件;成功返回0;
	fread()/fwrite()标准函数用来向文件中读写数据;返回成功读/写的个数;
计算机中的文件分为两种
	一种是文本文件,是以ASCII码或定长的字符集编码的,可以用编辑器显示出来;
	另一种是二进制文件,记录的数据是自定义格式的二进制内容;
补充
	从文件的编码方式来看,可分为字符编码和自定义编码;
	文本文件基本上是基于字符的定长编码(也有非定长的UTF-8),每个字符在具体编码中是确定的;ASCII码是一个字符占8个bit,UNICODE一般占16个bit;
	二进制文件可以看成是变长编码的,多少bit代表一个值,完全有你自定义;比如C语言中定义的数据结构,只有你清楚每个部分占多少空间,数据如何解读等;
	以文本的方式解析二进制文件就可能会出现乱码;
	比如int型的数字12,在以二进制存储时占4个字节,以文本存储是可能只占2字节,1和2分别以ASCII码的形式存储;

	如果我们要操作一个二进制文件,那么我们就以二进制方式打开,同时读写的时候用fread()/fwrite()函数;
	如果我们要操作一个文本文件,那么我们就以文本方式打开,同时读写的时候用读写字符的那些函数fprintf()/fscanf()/fgetc()/fputc()/putw()/getw()/fputs()/fgets();

/*
 * 文件程序框架
 */
#include <stdio.h>
int main() {
	FILE *p_file = fopen("test.bin", "w");
	/*
	 * 打开文件test.bin放在p_file
	 * fopen的第一个实参是文件路径,
	 * test.bin表示当前目录下文件名为test.bin
	 * 第二个实参描述如何使用该文件,代表文件的打开模式
	 */

	/* fopen有可能是失败的,要经常检查之 */
	/*
	 * if (p_file) {
	 *     检查文件是否打开成功
	 *     fclose(p_file); // fclose必须要以fopen的结果作为实参
	 *     p_file = NULL;两条语句次序固定
	 * }
	 */

	/* 以下是文件操作的另一种写法 */
	if (!p_file) {
		return 0;
	}

	/*
	 * 对文件相关的读写操作等
	 */

	fclose(p_file);
	p_file = NULL;

	return 0;
}


FILE *p_file = fopen("a", "w"); //打开文件a放在p_file指向的缓冲区
fopen()的
第一个实参是文件路径,a表示当前目录下文件名为a;
第二个实参描述如何使用该文件,代表文件的打开模式:
	r	表示只能读文件内容,读从文件头开始,文件必须事先已经存在;
	r+	表示在前一个模式的基础上增加修改能力;为读写打开一个文件
	w	只能修改文件内容,修改操作从文件头开始;如果文件事先不存在则创建新文件,如果文件事先已经存在,则删除文件中原有内容;
	w+	在前一种模式的基础上增加读能力;为读写创建一个文件;
	a	模式只能修改文件内容,如果文件事先不存在则创建新文件,如果文件事先存在则在原文件内容后面追加新内容;
	b	也是一种打开模式,这种模式可以和前面任何一种模式混合使用;表示以二进制方式对文件进行操作;

	二进制方式很简单,读文件的时候会原封不动的读出文件的内容,写的时候也会把内存缓冲区中的内容原封不动的写入到文件中;
	文本方式就不一样;在读文件的时候会将换行符(CRLF,0X0D 0X0A)全部替换成单个0X0A,并且当遇到结束符(CTRLZ,0X1A)时,就认为文件已经结束;相应的写文件时,会将所有的0X0A替换成0X0D 0X0A;
	若用文本方式打开二进制文件就很容易出现文件读不完整或内容不对的错误;即使是用文本方式打开文件文件也要小心谨慎,比如复制文件就不应该使用文本方式;
	要特别注意的是,上面这样的说法仅适用于DOS和windows系统,在Unix和其他一些系统中没有文本方式和二进制方式的区分,用不用"b"标志都是一样的;

fopen()标准函数在返回值变量中记录一个文件指针,指向代表文件的缓冲区;
fopen()标准函数有可能失败,如果失败返回值变量作为布尔值使用时是假;

每当结束对一个文件的所有操作后必须使用fclose()标准函数关闭这个文件;


fread()/fwrite()
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

	第一个参数:数组(存储空间的首地址)(fread()会把从文件中得到的内容放在数组的存储位置中/fwrite()会把数组存储位置中的内容写入到文件中);一个指向一段有效内存空间的指针也可以;
	第二个参数:数组中单个存储位置的大小;
	第三个参数:我们希望操作的存储位置的个数;
	第四个参数:表示要操作的文件指针;
fread()/fwrite()返回值表示实际读/写的存储位置的个数;
size_t类型是可移植的无符号整型;
	在32位系统被定义为unsigned int;
	在64位系统被定义为unsigned long long;
举例
	size_t size = fwrite(arr, sizeof(int), 4, p_file);
	printf("实际存储了%d个整数\n", size);
	size_t size = fread(arr, sizeof(int), 6, p_file);
	printf("实际共读取%d个整数\n", size);
/*
 * fwrite()演示
 */
#include <stdio.h>
int main() {
	int arr[] = { 1, 2, 3, 4, 5, 6 }, size = 0;
	char str[12] = "hello world";
	FILE *p_file = fopen("filetest.bin", "wb");
	if (p_file) {
		size = fwrite(arr, sizeof(int), 6, p_file);
		printf("存储了%d个int\n", size);
		size = fwrite(str, sizeof(char), 12, p_file);
		printf("存储了%d个char\n", size);
		fclose(p_file);
		p_file = NULL;
	}
	return 0;
}

/*
 * fread()演示
 */
#include <stdio.h>
int main() {
	int arr[6] = { }, size = 0, num = 0;
	char str[12] = {};
	FILE *p_file = fopen("filetest.bin", "rb");
	if (p_file) {
		size = fread(arr, sizeof(int), 6, p_file);
		printf("实际共读取%d个int\n", size);
		for (num = 0; num <= size - 1; num++) {
			printf("%d ", arr[num]);
		}
		printf("\n");

		size = fread(str, sizeof(char), 12, p_file);
		printf("实际共读取%d个char\n", size);
		printf("%s\n", str);

		fclose(p_file);
		p_file = NULL;
	}
	return 0;
}

练习
	将下列5组数据存入一个二维数组,然后存入一个文件中;
	然后从文件中读取后,反行序存入一个数组并打印出来:
1	2	3	4	5
6	7	8	9	10
...
21	22	23	24	25

21	22	23	24	25
16	17	18	19	20
11	12	13	14	15
6	7	8	9	10
1	2	3	4	5

/*
 * fwrite()练习
 */
#include <stdio.h>
int main() {
	int arr[5][5] = { }, row = 0, col = 0, size = 0;
	/* 对数组循环赋值 */
	for (row = 0; row <= 4; row++) {	
		for (col = 0; col <= 4; col++) {
			arr[row][col] = row * 5 + col + 1;
		}
	}
	int num = 0;
	FILE *p_file = fopen("filetest.bin", "wb");
	if (p_file) {
		for (num = 0; num <= 4; num++) {
			/* 将数组内容写入文件 */
			fwrite(arr[num], sizeof(int), 5, p_file);
		}
		fclose(p_file);
		p_file = NULL;
	}
	return 0;
}

/*
 * fread()练习
 */
#include <stdio.h>
int main() {
	int arr[5][5] = { }, num = 0;
	int row = 0, col = 0, size = 0;
	FILE *p_file = fopen("filetest.bin", "rb");
	if (p_file) {
		/* 循环读取内容 */
		for (num = 4; num >= 0; num--) {	
			fread(arr[num], sizeof(int), 5, p_file);
		}
		/* 循环打印 */
		for (row = 0; row <= 4; row++) {	
			for (col = 0; col <= 4; col++) {
				printf("%2d ", arr[row][col]);
			}
			printf("\n");
		}
		fclose(p_file);
		p_file = NULL;
	}

	return 0;
}

练习
	编写人员信息管理系统;
	每个人员信息包含三部分,(id,姓名,工资)(int,char[20],float);
	从键盘得到多个人员信息并记录到文件中;
	如果多次运行程序文件中的人员信息会越来越多,可以出现重复id,每次得到一个人员信息后提示是否还需要输入下一个人员信息;
	可以使用scanf()从键盘得到多个字符数据并记录在字符数组中(应该使用%s做占位符)姓名中不应该出现空格,不能有中文,长度不能超过20个字符;和%s配对的数据是数组名称;

/*
 * 编写人员信息管理系统
 * infowrite.c
 */
#include <stdio.h>
int main() {
	int id = 0, flag = 0;
	char name[20] = { };
	float salary = 0.0f;
	FILE *p_file = fopen("info.db", "ab"); // 追加的方式
	if (p_file) {
		do {
			printf("请输入id: ");
			scanf("%d", &id);
			printf("请输入name: ");
			scanf("%s", name);
			printf("请输入salary: ");
			scanf("%f", &salary);

			fwrite(&id, sizeof(int), 1, p_file);
			fwrite(name, sizeof(char), 20, p_file);
			fwrite(&salary, sizeof(float), 1, p_file);
			printf("是否需要输入下一个人员信息<1/0>? ");
			scanf("%d", &flag);
		} while (flag);
		fclose(p_file);
		p_file = NULL;
	}
	return 0;
}

/*
 * 编写人员信息管理系统
 * inforead.c
 */
#include <stdio.h>
int main() {
	int id = 0, flag = 0;
	char name[20] = { };
	float salary = 0.0f;
	FILE *p_file = fopen("info.db", "rb");
	if (p_file) {
		fread(&id, sizeof(int), 1, p_file);
		fread(name, sizeof(char), 20, p_file);
		fread(&salary, sizeof(float), 1, p_file);
		printf("id:%d\n", id);
		printf("name:%s\n", name);
		printf("salary:%f\n", salary);

		fread(&id, sizeof(int), 1, p_file);
		fread(name, sizeof(char), 20, p_file);
		fread(&salary, sizeof(float), 1, p_file);
		printf("id:%d\n", id);
		printf("name:%s\n", name);
		printf("salary:%f\n", salary);

		fclose(p_file);
		p_file = NULL;
	}
	return 0;
}

##################################################

其他常用的文件操作相关函数
int fseek(FILE *stream, long offset, int whence);
	用来实现文件指针位置偏移,whence是参考位置,offset是移动距离;
	成功返回0;
long ftell(FILE *stream);
	用来获取文件当前位置的偏移量;
int feof(FILE *stream);
	返回文件位置指针是否在文件结尾;
int fprintf(FILE *stream, const char *format, ...);
	按给定的格式输出字符串到文件;

作业
	1.编写函数把一个数组中所有存储的内容从前到后颠倒数据
/*
 * 编写函数把一个数组中所有存储的内容从前到后颠倒数据
 */
#include <stdio.h>
void reverse(int arr[], int size);
void print(int arr[], int size);

int main() {
	int arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	printf("原数据:\n");
	print(arr, 10);
	reverse(arr, 10);
	printf("交换后:\n");
	print(arr, 10);
	return 0;
}

void reverse(int arr[], int size)
{
	int i = 0, tmp = 0;
	for (i = 0; i <= size / 2 - 1; i++) {
		tmp = arr[i];
		arr[i] = arr[size - 1 - i];
		arr[size - 1 - i] = tmp;
	}
}
void print(int arr[], int size) {
	int i = 0;
	for (i = 0; i <= size - 1; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

	2.编写函数交换主函数中两个变量的内容
/*
 * 编写函数交换主函数中两个变量的内容
 */
#include <stdio.h>
void swap(int *, int *);
int main()
{
	int num = 3, num1 = 7;
	printf("num is %d, num1 is %d\n", num, num1);
	swap(&num, &num1);
	printf("num is %d, num1 is %d\n", num, num1);
	return 0;
}

void swap(int *arr, int *arr1) {
	int tmp = *arr;
	*arr = *arr1;
	*arr1 = tmp;
}

	3.编写程序把b.out文件复制一份并命名为c.out
/*
 * 编写程序把b.out文件复制一份并命名为c.out
 */
#include <stdio.h>
int main() {
	char buf[100] = { };
	int size = 0;
	FILE *p_src = fopen("b.out", "rb");
	/* 每次要以字节为单位读取 */
	if (!p_src) {
		return 0;
	}
	FILE *p_dest = fopen("c.out", "wb");
	if (!p_dest) {
		fclose(p_src);
		/* 如果文件c打开失败,直接关闭b */
		p_src = NULL;
		return 0;
	}

	/* 以下循环语句为本程序核心代码 */
	while (size = fread(buf, sizeof(char), 100, p_src)) {	
		/* 以字节为单位读取 */
		fwrite(buf, sizeof(char), size, p_dest);
	}			
	/* fread()第一次读文件开头,以后会顺序往下读文件的内容 */
	
	fclose(p_dest);
	p_dest = NULL;
	fclose(p_src);
	p_src = NULL;
	return 0;
}

	4.编写程序把我们课堂上生成的人员信息文件中的所有内容打印在屏幕上;
	如果读取的id为空则表示读取循环要结束;
/*
 * 编写程序
 * 把我们在课堂上生成的人员信息文件中
 * 所有内容打印到屏幕上
 * 如果读取id为空,则表示读取循环结束;
 */
#include <stdio.h>
int main()
{
	int id = 0, n = 0;
	char name[20] = { };
	float salary = 0.0f;
	FILE *p_file = fopen("info.db", "rb");
	if (p_file) {
		while (fread(&id, sizeof(int), 1, p_file)) {
			printf("文件第%d次读取\n", n++);
			fread(name, sizeof(char), 20, p_file);
			fread(&salary, sizeof(float), 1, p_file);

			printf("id is %d\n", id);
			printf("name is %s\n", name);
			printf("salary is %g\n", salary);
		}
		fclose(p_file);
		p_file = NULL;
	}
	return 0;
}

/*
 * standard C
 * std_bintxt.c
 * 使用标准C语言分别实现以二进制方式和
 * 文本方式读写文件
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

/*
 * UNIX C
 * uc_bintxt.c
 * 使用Unix系统库函数,分别实现二进制方式和
 * 文本方式读写文件
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
		   emp.name, emp.age, emp.salary);	//防止数据溢出
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

