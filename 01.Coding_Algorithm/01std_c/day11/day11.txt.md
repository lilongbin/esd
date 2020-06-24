递归函数
变量的生命周期和作用域
全局变量,局部变量,块变量
声明变量的关键字

递归函数

C语言允许嵌套地调用函数,也就是说,在调用一个函数的过程中,又去调用另外的函数;
函数的嵌套调用有个特例,即递归调用,也就是说,在调用一个函数的过程中,又出现了直接或间接地调用该函数本身;

自己调用自己的函数叫递归函数;
递归函数调用会在计算机里面同时存在多个,其中最后一个是当前正在工作的那个;
一个非常复杂的问题如果可以拆分成多个小问题,其中至少一个小问题和原来的问题本质上一样,只是规模小一些;这样的问题适合采用递归方式解决;
类似于任务的层层下放,每次找对人分配正确的任务即可;然后将计算机自动会将底层的工作逐级回收;

从前有座山,山上有座庙,庙里有一个老和尚和一个小和尚,老和尚在给小和尚讲故事;讲的是,从前有座山,...
/*
 * 递归函数演示
 */
#include <stdio.h>
int old_monk = 50, young_monk = 3;
void tell_story() {
	old_monk += 1;
	young_monk += 1;
	printf("从前有座山,山上有座庙,庙里老和尚(%d岁)在给小和尚(%d岁)讲故事...\n", old_monk, young_monk);
	if (old_monk < 60) {
		/* 递归形式 */
		tell_story();
	} else {
		printf("老和尚退休了,不讲了\n");
		/* 递归边界 */
	}
}
int main() {
	tell_story();
	return 1;
}

问题:
	求一个数的前n项和
/*
 * 求从0到用户给定整数之间的所有整数之和;类似阶乘;
 */
#include <stdio.h>
int sum(int);
int main() {
	int n = 0;
	printf("请输入一个整数:");
	scanf("%d", &n);
	printf("sum is: %d\n", sum(n));
	return 0;
}

int sum(int num) {
	if (num <= 1) {
		return 1;
	}
	return num + sum(num - 1);
}

递归调用的时候,调用的是跟自己同名的子函数,参数已经发生变化,虽然函数中的参数名字相同,却不是同一个变量,代表不同的值;
在使用递归的时候,如果后面的函数没有返回结果,前面的函数就一直处于等待状态,变量也没有释放;直到最底层的递归结束,才会逐级回收;

某些问题既可以采用递归函数解决也可以采用循环解决,这个时候采用递归函数解决问题的思路叫递归,采用循环解决问题的思路叫递推;
要花一些时间好好研究递归,数据结构和算法,以及函数传参,文件操作等;

如何编写递归程序
	在语法上简单,递归即为普通的函数调用;
	在算法上较难,如何找递归形式,如何找到递归边界;
递归算法可以分为两种类型
	基于分治策略的递归算法;
	基于回溯策略的递归算法;
基于分治策略的递归算法
	分而治之(divide-and-conquer)的算法设计思想;
	1.Divide 把问题划分为若干个子问题;
	2.Conquer 以同样的方式分别去处理各个子问题;
	3.combine 把各个子问题的处理结果综合起来,形成最终的处理结果;
如何建立分治递归的思维方式
	基本原则:目标驱动;
	计算n!: n! = n * (n-1)! /* 递归形式 */ 且1! = 1; /*递归边界*/
/*
 * 求n!
 */
#include <stdio.h>
int factorial(int); //阶乘
int main() {
	int num = 5;
	printf("factorial(%d) = %d\n", num, factorial(num));
	return 0;
}

int factorial(int num) {
	/* 递归边界 */
	if (1 == num) return 1;
	/* 分治递归 */
	return num * factorial(num - 1);
	//可以用num=num-1,或--num,但不可以用num--;
}

函数的递归调用就相当于普通的函数调用,每调用一级,虽然函数代码相同,但执行的不是相同的代码,访问的也不是相同的数据;而是各自都有自己的一套;

问题描述
	给定一个整型数组a,找出其中的最大值;
如何设计相应的递归算法
	目标: max{a[0], a[1], ..., a[n-1]}
	可分解为: max{a[0], max{a[1], ..., a[n-1]}}
	另外已知max{x} = x;
	这就是递归算法的递归形式和递归边界,据此可以编写出相应的递归函数;
#include <stdio.h>
int Max(int a[], int first, int n) {
	int max;
	if (first == n - 1) return a[first];
	max = Max(a, first+1, n);
	if (max < a[first]) {
		return a[first];
	} else {
		return max;
	}
}
int main() {
	int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	printf("max = %d\n", Max(arr, 1, 10));
	return 0;
}

折半查找
	前提是数据有序;
基本思路
	将目标值与数组的中间元素进行比较;
	若相等,查找成功;否则根据比较的结果将查找范围缩小一半,然后重复此过程;
/*
 * 折半查找
 */
#include <stdio.h>
void print(int b[], int size) {
	int i = 0;
	for (i = 0; i < size; i++) {
		printf("%d ", b[i]);
	}
	printf("\n");
}
int bsearch(int b[], int num, int L, int R) {
	int mid;
	if (L > R) return -1;
	mid = (L + R) / 2;
	if (b[mid] == num) {
		return mid + 1;
	} else if (b[mid] > num) {
		/* 不断变化左右边界,缩小查找范围 */
		/* R = mid - 1; */
		return bsearch(b, num, L, mid - 1);
	} else {
		/* L = mid + 1; */
		return bsearch(b, num, mid + 1, R);
	}
}

int main() {
	int b[11] = {1, 2, 2, 3, 4, 5, 5, 6, 7, 8, 9};
	print(b, 11);
	int x = 8;
	printf("8位于数组的第%d个元素\n", bsearch(b, x, 0, 10));
	return 0;
}

汉诺塔
相传在古印度Bramah庙中,有位僧人整天把三根柱子上的金盘倒来倒去,原来他是想把64个一个比一个小的金盘从一根柱子上移到另一根柱子上去;
移动过程中遵守以下规则:每次只允许移动一只盘,且大盘不得落在小盘上;
简单吗?若每秒移动一只盘子,需5800亿年;
怎样编写这样的程序,思路还是先从最简单的情况分析,慢慢理出思路;
1->在A柱子上只有1个盘子,假定盘号为1,这时只需将该盘直接从A搬至C,记为
	move A -> C;
2->在A柱子上有2个盘子,1号小2号大,分三步;
	move A -> B;
	move A -> C;
	move B -> C;
3->在A柱子上有3个盘子,从小到大分别为1,2,3号;分7步移动;
	分3步进行;
	move A(1,2) -> B;
	move A(3) -> C;
	move B(1,2) -> C;
4->在A柱子上有n个盘子,从小到大分别为1,2,...n号;
	move A(1..n-1) -> B;
	move A(n) -> C;
	move B(1..n-1) -> C;
定义函数move(int n, char L, char M, char R);
	表示move n discs L(n) -> R using M;
	如果n=1,表示move L -> R;
/*
 * 汉诺塔挪移
 */
#include <stdio.h>

/* 打印移动的步骤 */
void move(char x, char y) {
	printf("%c -> %c\n", x, y);
}

void hanoit(int level, char a, char b, char c) {
	/*
	 * 假如我只移动最后一个;其他的都让别人来完成;
	 * 至于别人有多少任务让他们再找人吧,我只需要他们打包的结果;
	 * 
	 * 最后一个一定是我把它从A -> C,
	 * 即函数参数的第一个代表位置的地方,
	 * 到最后一个代表位置的地方
	 */
	if (level == 1) {
		/* 最简单的情况,只有最后一个 */
		move(a, c);
	} else {
		/* 总共分为两大块,一个是别人的,一个是我的 */

		/* 让别人从a搬走level-1个到b */
		hanoit(level - 1, a, c, b);

		/* 我完成最后一个从a搬到c */
		move(a, c);

		/* 再让别人从b搬回level-1到c */
		hanoit(level - 1, b, a, c);
	}
}

int main() {
	int level = 0;
	printf("please type your level: ");
	scanf("%d", &level);

	/* 调用函数 */
	hanoit(level, 'A', 'B', 'C');
	/* 共需要2的n次幂 - 1次操作 */
	return 0;
}

递归函数的编写规则;
	1.首先要在递归函数中编写语句描述问题拆分方式;
	2.在递归函数的开始编写分支解决不再拆分的情况,这种情况必须保证函数可以结束;(代表着最后的任务,最底层的工作,必须得有人做,否则没办法回收工作);

练习
	编程计算两个整数的最大公约数;
/*
 * 递归练习
 * 计算两个数字的最大公约数
 * */
#include <stdio.h>
int yue(int num, int num1) {
	if (!(num % num1)) {
		return num1;
	}
	return yue(num1, num % num1);
}

int main() {
	int num = 0, num1 = 0;
	printf("请输入两个数字:");
	scanf("%d%d", &num, &num1);
	printf("最大公约数为:%d\n", yue(num, num1));
	return 0;
}

得到一个递归函数后可以采用设计几套参数的办法了解它的工作原理;
第一套参数应该让函数做尽可能少的事情,以后的每套参数都在前一套参数的基础上变得复杂一些;

练习
	0 1 2 3 4 5 6  7
	1 1 2 3 5 8 13 21...
/*
 * 递归函数练习
 * 1 2 3 5 8 13 21 34 ...
 */
#include <stdio.h>
int i;
/* 递归函数 */
int fei0(int num) {
	/* 每递归一层就重新申请一部分空间 */
	if (num <= 1) {
		return 1;
	} else if (num == 2) {
		return 2;
	} else if (num >= 40) {
		/* num > 40 已经会有很深的递归 */
		return 0;
	}
	return fei0(num - 1) + fei0(num - 2);
}

int arr[100];	//声明arr为全局数组,没有初始化语句时被自动初始化为0
/* 优化1的递归函数 */
int fei1(int num) {
	if (num <= 1) {
		return 1;
	} else if (num == 2) {
		return 2;
	}

	/* 添加一个记录中间变量的过程
	 * 减少递归调用的层次 */
	if (!arr[num - 1]) {
		arr[num - 1] = fei1(num - 1);
	}
	if (!arr[num - 2]) {
		arr[num - 2] = fei1(num - 2);
	}
	return arr[num - 1] + arr[num - 2];
}

int arr2[100];
/* 优化2的递归函数 */
int fei2(int num) {
	int ret = 0;
	//int arr[50]={};//声明arr为局部变量,每调用一次重新分配一次
	if (num <= 1) {
		/* num<=1时递归结束 */
		return 1;
	}
	if (arr2[num - 2]) {
		ret += arr2[num - 2];	//如果arr[num-2]已经算出不再计算
	} else {
		arr2[num - 2] = fei2(num - 2);
		ret += arr2[num - 2];
	}
	if (arr2[num - 1]) {
		ret += arr2[num - 1];
	} else {
		arr2[num - 1] = fei2(num - 1);
		ret += arr2[num - 1];
	}
	return ret;
}

int main() {
	int num = 0;
	printf("请用户输入一个编号:");
	scanf("%d", &num);
	printf("编号为%d的数字是%d\n", num, fei1(num));
	printf("编号为%d的数字是%d\n", num, fei2(num));
	printf("编号为%d的数字是%d\n", num, fei0(num));
	return 0;
}

青蛙过河
	一条小溪尺寸不大,青蛙可以从左岸跳到右岸,在左岸有一石柱L,面积只容得下一只青蛙落脚,同样右岸也有一石柱R,面积也只容得下一只青蛙落脚;
	有一队青蛙从尺寸上一个比一个小;我们将青蛙从小到大,用1,2,…,n编号;规定初始时这队青蛙只能趴在左岸的石头L上,按编号一个摞一个,小的落在大的上面;不允许大的在小的上面;
	在小溪中有S根石柱,有y片荷叶,规定溪中的柱子上允许一只青蛙落脚,如有多只同样要求按编号一个落一个,大的在下,小的在上,而且必须编号相邻;对于荷叶只允许一只青蛙落脚,不允许多只在其上;对于右岸的石柱R,与左岸的石柱L一样允许多个青蛙落脚,但须一个落一个,小的在上,大的在下,且编号相邻;
	当青蛙从左岸的L上跳走后就不允许再跳回来;同样,从左岸L上跳至右岸R,或从溪中荷叶或溪中石柱跳至右岸R上的青蛙也不允许再离开;
	问在已知溪中有S根石柱和y片荷叶的情况下,最多能跳过多少只青蛙?

这题看起来较难,但是如果我们认真分析,理出思路,就可化难为易;
思路
1简化问题,探索规律
	先从个别到一般,要善于对多个因素作分解,孤立出一个一个因素来分析,化难为易;
2定义函数
    Jump(S, y) 最多可跳过河的青蛙数
    其中	S 河中柱子数
			y 荷叶数
3先看最简单情况,河中无柱子,S=0;Jump(0, y);
	当y=0时,Jump(0, 0) = 1;
	当y=1时,Jump(0, 1) = 2;
	当y=2时,Jump(0, 2) = 3;
	Jump(0, y) = y + 1;当河中没有任何柱子的情况下,过河的青蛙数仅取决于荷叶的数+1;
4再看Jump(S, y),先看最简单情况,S=1,y=0;
	Jump(1, 0) = 2; Jump(0, 0) = 1;
	Jump(1, 1) = 4; Jump(0, 1) = 2;
	Jump(1, 2) = 6; Jump(0, 2) = 3;
	Jump(1, y) = 2 * Jump(0, y);
5再看S=2的情况;
	Jump(2, 0) = 4; Jump(1, 0) = 2;
	Jump(2, 1) = 8; Jump(1, 1) = 4;
	Jump(S, y) = 2 * Jump(S - 1, y);可以把最后一根柱子看作是上一步的R河岸;
Jump(S, y)可以将S根柱子分为第S根和前面的所有(S-1根柱子和y荷叶);第S根柱子上可以放上一次过河的数量的青蛙Jump(S-1, y),并且其他S-1根柱子和y荷叶也是上次过河的数量的青蛙Jump(S-1, y);因此S根柱子和y荷叶共可以过2*Jump(S-1, y);依次递推,直到S=0时,Jump(0, y) = y+1;
因此得到
	递归形式Jump(S, y) = 2 * Jump(S - 1, y);
	递归边界Jump(0, y) = y + 1;
/*
 * 青蛙过河
 */
#include <stdio.h>
int Jump(int S, int y) {
	if (S == 0) return y + 1;
	return 2 * Jump(S - 1, y);
}
int main() {
	int S = 0, y = 0;
	printf("Please input the number of pillar and frog: ");
	scanf("%d%d", &S, &y);
	printf("can jump frogs: %d\n", Jump(S, y));
	return 0;
}

快速排序
快速排序的基本思路
	1在数组a中有一段待排序的数据,下标从l到r;
	2取a[l]放在变量value中,通过由右/左两边对value的取值的比较,为value选择应该排定的位置;
	这时要将比value大的数放右边,比它小的数放左边;
	当value到达最终位置后(如下标m),由它划分了左右两个集合[l..m-1],[m+1..r];然后转第1步,再用相同的思路分别去处理左集合和右集合;
快速排序是一种不稳定排序,而冒泡排序则是稳定排序;
稳定排序是指如果排序前有两个相同的数,比如对[a=10, b=10, c=2]排序,a和b相等,排序前a在b的前面,稳定排序后结果为[c, a, b],a仍然在b的前面,而不稳定排序则不保证相等的两个数位置不会交换,排序结果可能变为[c, b, a];

/*
 * quick sort
 */
#include <stdio.h>
void print(int *arr, int size) {
	int i = 0;
	for (i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	} 
	printf("\n");
}
void quick_sort_v2(int *p_num, int L, int R)
{
	/* 不需要再拆分的情况 */
	if (L >= R) {
		return;
	}   

	int base = *(p_num + L); //选择最前面的那个作为基准数字;
	int start = L, end = R;
	/* 把基准数字放到适当位置 */
	while (L < R) {
		while (*(p_num + R) >= base && L < R) R--;
		if (*(p_num + R) < base && L < R) {
			*(p_num + L) = *(p_num + R); 
			L++;
		}   
		while (*(p_num + L) <= base && L < R) L++;
		if (*(p_num + L) > base && L < R) {
			*(p_num + R) = *(p_num + L); 
			R--;
		}   
	}   
	*(p_num + L) = base; //把基准数字归位

	/*  
	 * 循环结束后,一个基准数字就会被处理完毕;
	 * 循环结束时,L/R应该是相等的;
	 * 接下来需要递归处理基准数字两边的数字
	 */

	/* 递归处理基准数字左边的数字 */
	quick_sort_v2(p_num, start, R - 1); 
	/*  
	 * 递归处理基准数字右边的数字;
	 * 起始位置是p_num + start + 1;
	 * 个数是size - start - 1;
	 */
	quick_sort_v2(p_num, L + 1, end);
}

int main() {
	int arr[6] = {2, 5, 6, 9, 3, 1};
	quick_sort_v2(arr, 0, 5);
	print(arr, 6);
	return 0;
}

基于回溯策略的递归
back tracking
	在程序设计中,有一类问题如求一组解/全部解或求最优解,不是根据某种确定的计算法则,而是利用试探和回溯(Backtracking)的搜索技术求解;
	回溯法也是设计递归算法的一种重要方法,它的求解过程实质上是先序遍历一棵"状态树"的过程;
	只不过这棵树不是预先建立的,而是隐含在遍历的过程当中;

分书问题
	有五本书,它们的编号分别为1,2,3,4,5现准备分给A, B, C, D, E五个人,每个的阅读兴趣用一个二维数组来加以描述
	like[i][j]; //1表示i喜欢j书,0表示i不喜欢j书;
	希望编写一个程序,输出所有的分书方案,让人人皆大欢喜;
假如这5个人对这5本书的阅读兴趣如下表
人 书1 2 3 4 5
A    0 0 1 1 0
B    1 1 0 0 1
C    0 1 1 0 1
D    0 0 0 1 0
E    0 1 0 0 1
解题思路
1定义一个整型的二维数组,将上表中的阅读喜好用初始化的方法赋值给这个二维数组;
2定义一个整型一维数组BookFlag[6]用来记录书是否已被选用,用后5个下标作为5本书的标号,被选用的元素值为1,未被选用的值为0,初始化皆为0;
	int BookFlag[6] = {0};
3定义一个整型一维数组BookTaken[6]用来记录每一个人选用了哪本书;用数组元素的下标来作为人的标号,用数组元素的值来表示书号;如果某个人还没有选好书,则相应的元素值为0;初始化时,所有的元素值均为0;
	int BookTaken[6] = {0};
4循环变量i表示人,j表示书;
如果用枚举法,计算量太大;
/*
 * 分书问题
 */
#include <stdio.h>
void person(int i);
int Like[6][6] = {{0},{0, 0,0,1,1,0},
					{0, 1,1,0,0,1},
					{0, 0,1,1,0,1},
					{0, 0,0,0,1,0},
					{0, 0,1,0,0,1}};
int BookFlag[6] = {0};
int BookTaken[6] = {0};

int main() {
	person(1);
	return 0;
}
void person(int i) {
	/* 尝试给第i个人分书 */
	int j = 0, k = 0;
	/* 尝试把每本书分给第i个人 */
	for (j = 1; j <= 5; j++) {
		if (BookFlag[j] != 0 || Like[i][j] == 0)
		   continue; //失败
		BookTaken[i] = j; //第j本书分给第i个人;
		BookFlag[j] = 1; //第j本书已被分走;
		if (i == 5) {
			/* 已找到一种分书方案 */
			for (k = 1; k <= 5; k++) {
				printf("person[%d] taken book: %d\n", k, BookTaken[k]);
			}
			printf("\n");
		} else {
			person(i + 1); //给第i+1个人分书
		}

		/* 回溯,把这一次分成功的书退回,继续找其他方案 */
		BookTaken[i] = 0;
		BookFlag[j] = 0;
	}
}

下楼问题
	从楼上走到楼下共有h个台阶,每一步有3种走法,走1阶,走2阶,走3阶;
	问可以走出多少种方案,希望用递归思想来编程;
数据定义
	j=1,2,3 表示每一步可以试走的台阶数;
	s		表示步数
	pace[s]	保存第s步走过的台阶数
基本思路
	1让i先取h值,然后在下楼时,试着一步一步地走,从高到低;每走一步i的值就会减去这一步的台阶数j(步数s也加1),当i=0时说明走到楼下;
	2每一步都要试j的三种不同的取值,可以用for循环;
	3每一步走法都用相同的策略,故可以用递归算法;

定义TryStep(i, s)
	站在第i级台阶上往下试走第s步的过程
	如果i-j<0,表明这一步不可能走j级台阶,函数返回;否则继续;
	如果这一步走j级台阶,即space[s]=j;如果i-j=0,说明已经到达地面,也就是找到了一种方案了,把它显示书来;否则,接着走下一步,TryStep(i - j, s + 1);
/*
 * 下楼问题
 */
#include <stdio.h>
int pace[100] = {};
void TryStep(int i, int s) {
	int j = 0, k = 0;
	/* 每一步都有1,2,3三种可能 */
	for (j = 1; j <= 3; j++) {
		if (i - j < 0) continue; //不符合要求
		pace[s] = j; //记录每一步是如何走的
		if (i - j == 0) {
			/* 找到一种成功方案 */
			for (k = 0; k <= s; k++) {
				printf("%d ", pace[k]);
			}
			printf("\n");
		} else {
			/* 走下一步 */
			TryStep(i - j, s + 1); //台阶高度-j,步数+1;
		}
	}
}
int main() {
	int h = 20;
	TryStep(h 0); //共20个台阶,还没有走一步;
	return 0;
}

8皇后问题
在8x8的棋盘上,放置8个皇后,使其两两之间互不攻击;所谓互不攻击是说任何两个皇后都要满足;
	不在棋盘的同一行;
	不在棋盘的同一列;
	不在棋盘的同一对角线上;
因此可以推论出,棋盘共有8行,故最多有8个皇后,即每一行有且仅有一个皇后;这8个皇后中的每一个应该摆放在那一列上是解决该题的任务;
数据定义
	i,j 第i行(第i个皇后),第j列;
	Queen[i]  记录第i行皇后所在的列;
	Column[j]  记录第j列是否安全;
	Rfall[i-j+7]  记录每一条right falling方向上的对角线是否安全;
	Lfall[i+j-2]  记录每一条left falling方向上的对角线是否安全;
当我们需要在棋盘的(i,j)位置摆放一个皇后的时候,可以通过Column[]数组,Rfall[]数组和Lfall[]数组的相应元素,来判断该位置是否安全;
当我们已经在棋盘的(i,j)位置摆放了一个皇后以后,就应该区修改Column[]数组,Rfall[]数组和Lfall[]数组的相应元素,把相应的列和对角线设置为不安全;

/*
 * 8皇后问题
 */
#include <stdio.h>
int Queen[9] = {}; //存放皇后摆放的位置,下标代表行号
int Column[9] = {}; //记录每一列是否可用
int Lfall[15] = {}; //15条/方向的对角线
int Rfall[15] = {}; //15条\方向的对角线

/* 摆放第i行的皇后 */
void TryQueen(int i) {
	int j = 0, k = 0;
	/* 尝试把皇后放在每一列 */
	for (j = 1; j <= 8; j++) {
		if (Column[j] || Rfall[i-j+7] || Lfall[i+j-2]) {
			continue; //不符合要求
		}
		Queen[i] = j; //把第i个皇后放在j列上;
		/* 设置标记 */
		Column[j] = 1; Rfall[i-j+7] = 1; Lfall[i+j-2] = 1;
		if (i == 8) {
			/* 找到一种解决方案 */
			for (k = 1; k <= 8; k++) {
				printf("%d ", Queen[k]);
			}
			printf("\n");
		} else {
			TryQueen(i + 1); //摆放第i+1行皇后
		}
		Queen[i] = 0;
		/* 回溯,把该皇后从第j列拿起; */
		/* 以便继续尝试其他可能 */
		Column[j] = 0; Rfall[i-j+7] = 0; Lfall[i+j-2] = 0;
	}
}
int main() {
	TryQueen(1);
	return 0;
}

过河问题
	有M条狼和N条狗(N>=M)渡船过河,从河西到河东;在每次航行中,该船最多能容纳2只动物,且最少需搭载1只动物;
安全限制
	无论是在河东,河西还是在船上,如果有狗,那么狗的数量不能小于狼的数量;
能否找到一种方案,是所有动物都能顺利过河,并打印移动步骤;
/*
 * 过河问题
 * 回溯递归
 */
#include <stdio.h>
#define MAX_M 20
#define MAX_N 20

int M, N;
struct Status {
	int W, D, B;
} steps[1000]; //用来记录每一步的状态
int s = 0; //步数
int num = 0; //找到的方案编号
int flags[MAX_M][MAX_N][2] = {};

int IsValid(int w, int d, int b) {
	if (w < 0 || w > M) return 0;
	if (d < 0 || d > N) return 0;
	if (flags[w][d][b] == 1) {
		//记录该结点已经走过了,防止反复倒退
		return 0;
	}
	if (d > 0 && w > d) {
		/* 如果有狗剩下的Dog数量要不小于Wolf数量 */
		return 0;
	}
	if ((N - d > 0) && (M - w > N - d)) {
		/* 如果对岸有狗,Dog的数量也要不小于Wolf的数量 */
		return 0;
	}
	return 1; //合法的一步操作
}

void CrossRiver(int W, int D, int B) {
	int i, j, num_f;
	int w, d, b; //重新定义一套变量是为了步破坏原有的数据
	/* b,B代表运送方向{0,1} */
	/* b/B == 0 表示正向 -> */
	/* b/B == 1 表示反向 <- */
	num_f = ((B == 0) ? -1 : 1); //运送的数量标志{-1,1}

	for (j = 1; j <= 5; j++) {
		switch (j) {
			case 1:  //运送1条Wolf
				w = W + num_f * 1; d = D; 
				break;
			case 2:  //运送2条Wolf
				w = W + num_f * 2; d = D; 
				break;
			case 3:  //运送1条Dog
				d = D + num_f * 1; w = W; 
				break;
			case 4:  //运送2条Dog
				d = D + num_f * 2; w = W; 
				break;
			case 5:  //运送1条Wolf,1条Dog
				w = W + num_f * 1; d = D + num_f * 1; 
				break;
		}
		b = 1 - B; //方向反转
		/* 判断是否合法 */
		if (IsValid(w, d, b)) {
			flags[w][d][b] = 1;
			steps[s].W = w;
			steps[s].D = d;
			steps[s].B = b;
			s++;
			if (w == 0 && d == 0 && b == 1) {
				num ++;
				printf("Solution %d:\n", num);
				for (i = 0; i < s; i++) {
					printf("%d %d %s\n",
						steps[i].W, steps[i].D,
					   	((steps[i].B == 0) ? "->": "<-"));
				}
			} else {
				CrossRiver(w, d, b);
			}
			flags[w][d][b] = 0;
			s--;
		}
	}
}

int main() {
	printf("please input the number of Wolves and Dogs: ");
	scanf("%d%d", &M, &N);
	if (M >= 15 || N >= 15) {
		printf("too large\n");
		return 0;
	}
	flags[M][N][0] = 1;
	steps[0].W = M;
	steps[0].D = N;
	steps[0].B = 0;
	s = 1;
	CrossRiver(M, N, 0);
	return 0;
}

排列问题
	n个对象的一个排列就是把这n个不同的对象放在同一行上的一种安排;
	例如对于三个对象a,b,c,总共有6个排列;
	n个对象的排列个数就是n!;
基于回溯策略的递归算法;
基本思路
	每一个排列的长度为N,对这N个不同的位置,按照顺序逐一枚举所有可能出现的数字;
	定义一维数组NumFlag[N+1]用来记录1~N之间的每一个数字是否已被使用{0,1};
	定义一维数组NumTaken[N+1]用来记录每一个位置上使用的是哪一个数字;如果在某个位置上还没有选好数字,则相应的数组元素值为0;初始化时所有元素值均为0;
循环变量i表示第i个位置,j表示整数j;
/*
 * 排列组合
 */
#include <stdio.h>
#define N 3
int NumFlag[N+1] = {};
int NumTaken[N+1] = {};

void TryNumber(int i) {
	int j = 0, k = 0;
	for (j = 1; j <= N; j++) {
		if (NumFlag[j] != 0) continue;
		NumTaken[i] = j; //记录第i个数字是j
		NumFlag[j] = 1;  //标记j已经使用
		if (i == N) {
			/* 找到一种方案 */
			for (k = 1; k <= N; k++) {
				printf("%d ", NumTaken[k]);
			}
			printf("\n");
		} else {
			TryNumber(i + 1);
		}
		/* 回溯,继续尝试其他方案 */
		NumTaken[i] = 0;
		NumFlag[j] = 0;
	}
}
int main() {
	TryNumber(1);
	return 0;
}

编写一个程序,它接受用户输入的一个英文单词(长度不超过20个字符),然后输出有这个单词的每个字母所组成的所有排列;
有两个条件
	这个单词的各个字母允许有相同;
	不能输出重复的排列;
/*
 * 单词重组
 */
#include <stdio.h>
#include <string.h>
#define MAXSIZE 20
int CharFlag[MAXSIZE] = {};
int CharTaken[MAXSIZE] = {};
void TryChar(char *word, int i, size_t length) {
	int j = 0, k = 0;
	for (j = 1; j <= length; j++) {
		if (CharFlag[j] == 1) continue;
		/* 排除重复的情况 */
		for (k = 1; k < j; k++) {
			/* 如果word(aXbXc)中有重复字母X,当后面的X排在前时将跳过 */
			/* 因为在j比较小的时候已经排过一种情况了 */
			/* 允许..x..X.,排除..X..x. */
			if (CharFlag[k] == 0) {
				if (word[k-1] == word[j-1]) break;
			}
		}
		if (k < j) continue;
		CharTaken[i] = j; //记录第i个位置放的是word中的第j个字符
		CharFlag[j] = 1; //标记word中第j个字符已经使用过
		if (i == length) {
			/* 找到一种情况 */
			for (k = 1; k <= length; k++) {
				printf("%c", word[CharTaken[k] - 1]);
			}
			printf("\n");
		} else {
			/* 继续找下一个字符 */
			TryChar(word, i + 1, length);
		}
		/* 回溯,尝试其他可能的情况 */
		CharTaken[i] = 0;
		CharFlag[j] = 0;
	}
}
int main() {
	char word[MAXSIZE];
	size_t length;
	printf("please input a word: ");
	scanf("%s", word);
	length = strlen(word);
	TryChar(word, 1, length);
	return 0;
}


变量的两个重要属性:生命周期和作用域
这两个属性决定什么时候以及在什么地方可以使用某个变量;
作用域是可以使用变量名称的所有语句的总和;

根据变量的作用域可以把变量分成三种类型
	全局变量,局部变量和块变量;
声明在所有函数之外的变量叫全局变量;
全局变量的作用域是由程序中的所有语句构成的;任何一个函数都可以使用全局变量;
没有初始化的变量自动被初始化为0;
声明在函数内部的变量叫局部变量;
局部变量的作用域包含函数内部的所有语句,该函数可以使用该局部变量;
主函数与被调函数的变量可以同名,不会产生干涉,他们都是局部变量,仅对所在函数产生影响;
/*
 * 局部变量生命周期演示
 */
#include <stdio.h>
void func(void) {
	static int num = 10;
	//程序运行期间存储位置不被释放,初始化工作只进行一次;
	printf("%d\n", num);
	num = 3;
}

void func1() {
	int num1 = 10;
	int num = 11; // 与f()的num无关
	int num2 = num + num1;
}

int main() {
	func();
	func1();
	func();
	return 0;
}

块变量是声明在语句块{}内的变量;
块变量的作用域包含语句块内部的所有语句,不可以被语句块外边的函数使用;

作用域是指空间范围;
生命周期是时间范围;

生命周期指变量的存储位置被使用的时间范围;
程序中的所有存储位置都是在某个时刻被分配,又在另一个时刻被回收的;
变量的生命周期是从变量的存储位置被分配到被回收;

全局变量,局部变量和块变量的生命周期也不一样;

全局变量的存储位置在程序开始时被分配,在程序结束时被回收;
全局变量的生命周期包含整个程序运行期间;
局部变量的存储位置在函数开始运行时被分配又在函数结束时被回收,局部变量的生命周期包含整个函数的运行周期;
形式参数的生命周期和局部变量一样;

块变量的存储位置在语句块开始运行时被分配,在语句块结束时被回收,它的生命周期包括整个语句块运行期间;

尽量减少全局变量的使用,局部变量是第一选择;
局部变量只在函数运行期间有效;

三种类型的变量可以重名;
一条语句中使用的变量一定是作用域包含这条语句的所有同名变量中声明语句离他最近的那个,这个原则叫做就近原则;
/*
 * 变量重名演示,就近原则
 */
#include <stdio.h>
int num;
int main() {
	printf("num is %d\n", num);	//0
	int num = 1;
	printf("num is %d\n", num);	//1
	{
		/* 块语句 */
		printf("num is %d\n", num);	//1
		int num = 2; //声明块变量
		printf("num is %d\n", num);	//2
	}
	printf("num is %d\n", num);	//1
	return 0;
}

声明变量时可以使用的关键字
	auto 关键字用来声明自动变量,所有局部变量缺省都是自动变量,几乎不使用这个关键字;
	static 关键字用来声明静态变量,静态变量的生命周期和作用域是和不同东西相关的,他们不一致;
	静态全局变量的作用域包括声明它的那个文件中的所有语句,生命周期不变;
	静态局部变量的作用域没变,生命周期被拉长;
	静态局部变量和静态块变量的生命周期包括整个程序运行期间;
	没有初始化的局部变量自动被初始化成0,
	静态局部变量和静态块变量的初始化只在程序的开始时执行一次;
	静态变量存储在静态区,全局区包括静态区;

静态全局变量的作用域被限制在本文件中;
静态局部变量的作用域在本文件中,生命周期被拉长;
static 修饰函数,函数的作用于将被限制在本文件中使用;

	const 关键字用来声明只读变量,这种变量应该在初始化的时候初始化一个值,其他时候不可以直接赋值;这种变量的内容可以通过其他方式(如指针)间接修改,如scanf("%d", &num);
	volatile 关键字用来声明多变(易挥发的)的变量;这种变量的内容随时可能被改变,而且这种改变的原因不是我们的语句造成的;如硬件寄存器中的某个值,如果用volatile关键字修饰,程序运行时将在每次需要用到这个变量时直接去寄存器读取,而不是读缓存数据;
/*
 * const演示
 */
#include <stdio.h>
int main() {
	const int num = 7; //只能在初始化的时候初始化一个值,不可以被赋值
	printf("num is %d\n", num);
	/* num = 7; //不可以被直接赋值 */
	printf("请输入一个数字:");
	scanf("%d", &num);	//可以改变
	printf("num is %d\n", num);
	return 0;
}

作业
	1.编写递归函数,打印一个数组中所有数字;
/*
 * 编写递归函数,打印一个数组中的所有数字;
 */
#include <stdio.h>
void print(int arr[], int size, int curr) {
	if (curr == size - 1) {
		printf("%d\n", arr[curr]);
		return;
	}
	printf("%d ", arr[curr]);
	print(arr, size, curr + 1);
}

int main() {
	int arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }, i = 0;
	print(arr, 10, 0);
	printf("\n");
	return 0;
}

	2.编写函数生成一张彩票,不使用数组形参;
/*
 * 编写函数生成一张彩票,不使用数组形参;
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int lottery[10];
void create() {
	int num = 0;
	for (num = 0; num <= 9; num++) {
		lottery[num] = rand() % 36 + 1;
	}
}
int main() {
	int i = 0;
	srand(time(0));
	create();
	for (i = 0; i <= 9; i++) {
		printf("%d ", lottery[i]);
	}
	printf("\n");
	return 0;
}

