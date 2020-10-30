排序算法
查找算法



算法
    广义的说,为解决一个问题而采取的操作方法和操作步骤,就称为算法;
计算机算法可分为两大类别
    1->    数据运算算法
    2->    非数值运算算法;
在写程序之前,必须想清楚做什么和怎么做;
    做什么是任务;
    怎么做包括两方面的内容
        一是要做哪些事情才能达到解决问题的目的;
        二是要决定做这些事情的先后次序;
想好一个算法后可以选择不同的方式表示;
为了设计算法时的方便,常采用一种称为伪代码(pseudo code)的工具;
伪代码是介于自然语言和计算机语言之间的文字和符号来描述算法;即将计算机语言中的关键字用英文表示,其他的可用汉字;总之,以便于书写和阅读为原则,无固定的严格的语法规则;

算法是解决某些通用问题的方法
同一个问题可以有多种不同的解决办法,分别适合使用在不同的场合下;

排序算法
排序算法负责把一组数据按照固定的顺序排列好;
所有排序算法都是不停的调整某两个数字间的顺序直到把所有数字的顺序都调整好,不同排序算法的区别是在什么时候处理哪两个数字;

1. 冒泡排序(鱼吐泡)
    最简单,最基本,最慢;
    冒泡排序在任何时候只处理相邻两个数字,将相邻的两个数比较,冒泡排序采用双层循环实现;
    外循环的循环变量从最后一个下标变化到第二个下标,内循环的循环变量从第二个下标变化到外循环的循环变量;
    冒泡排序中任何一个数字从开始位置移动到结束位置的过程中会在所有位置中间位置上停留;
    就像鱼吐出的气泡一样是逐渐露出水面的,而不是吐出后直接就跳到水面;
/*
 * 冒泡排序演示
 */
#include <stdio.h>
void print(int *arr, int num) {
    int pos = 0;
    for (pos = 0; pos <= num - 1; pos++) {
        printf("%d ", arr[pos]);
    }
    printf("\n");
}
int main() {
    int arr[6] = { 2, 4, 3, 6, 5, 1 }, pos = 0, num = 0;

    print(arr, 6);
    for (num = 5; num >= 1; num--) {    //从最后到第二个位置循环
        for (pos = 1; pos <= num; pos++) {    //把最大的靠后放
            if (arr[pos - 1] > arr[pos]) {
                int tmp = arr[pos - 1];
                arr[pos - 1] = arr[pos];
                arr[pos] = tmp;
            }
        }
        print(arr, 6);
    }
    return 0;
}

2 4 3 6 5 1
2 3 4 5 1 6 
2 3 4 1 5 6 
2 3 1 4 5 6 
2 1 3 4 5 6 
1 2 3 4 5 6

2. 选择排序(按个子高低排座位)
    模拟人的思维方式;
    每次选定一个位置,用这个位置上的数字和所有其他位置上的数字比较并调整顺序;
    然后换一个位置重复上面的操作直到所有数字的顺序都调整好;
    采用双重循环实现;
    外层循环的循环变量从第一个位置到倒数第二个位置,内层循环的循环变量从外循环的变量+1到最后一个位置;内循环内部对两个循环变量对应位置的数字进行处理; 
    就好比体育老师按高低个给同学们排队;
/*
 * 选择排序演示
 */
#include <stdio.h>
void print(int *arr, int num) {
    int pos = 0;
    for (pos = 0; pos <= num - 1; pos++) {
        printf("%d ", arr[pos]);
    }
    printf("\n");
}
int main() {
    int arr[6] = { 2, 4, 3, 6, 5, 1 }, pos = 0, num = 0;
    print(arr, 6);
    for (num = 0; num <= 4; num++) {
        /* 一次排好一个位置 */
        for (pos = num + 1; pos <= 5; pos++) {
            if (arr[num] > arr[pos]) {
                int tmp = arr[num];
                arr[num] = arr[pos];
                arr[pos] = tmp;
            }
        }
        print(arr, 6);
    }
    return 0;
}
2 4 3 6 5 1
1 4 3 6 5 2 
1 2 4 6 5 3 
1 2 3 6 5 4 
1 2 3 4 6 5 
1 2 3 4 5 6

3. 插入排序(打麻将起牌时把后来的放到合适位置)
    每次把一个位置上的数据插入到前边已排好的数字中某个合适的位置上形成一个新的已排序的数字序列;
    重复这个操作直到所有数字都插入进去为止; 
    采用双重循环实现;
    外循环的循环变量从第二个位置开始到最后一个位置为止,内循环的循环变量从外循环变量-1开始到0为止;在内循环中对内循环变量和它后面的变量中的数字进行顺序调整; 
/*
 * 插入排序
 */
#include <stdio.h>
void print(int *arr, int num) {
    int pos1 = 0;
    for (pos1 = 0; pos1 <= 5; pos1++) {
        printf("%d ", arr[pos1]);
    }
    printf("\n");
}
int main() {
    int arr[6] = { 3, 6, 4, 2, 7, 1 }, pos = 0, pos1 = 0;
    print(arr, 6);
    for (pos = 1; pos <= 5; pos++) {
        /* 类似于纸牌起牌,把后来的每一张放到合适位置 */
        for (pos1 = pos; pos1 > 0; pos1--) {
        /* 从当前位置往前比较后插入 */
            if (arr[pos1] < arr[pos1 - 1]) {
            /* 当前位置与前一个位置比较 */
                int tmp = arr[pos1 - 1];
                arr[pos1 - 1] = arr[pos1];
                arr[pos1] = tmp;
            } else {
                break;
            }
        }
        print(arr, 6);
    }
    return 0;
}
3 6 4 2 7 1
3 6 4 2 7 1 
3 4 6 2 7 1 
2 3 4 6 7 1 
2 3 4 6 7 1 
1 2 3 4 6 7 

4. 快速排序
    重点+难点
    每次选一个基准数字放在合适的位置上同时把所有数字分成两组,其中一组中的数字都比基准数字小,另一组中的数字都比基准数字大;
    基准数字通常选未处理数字中的第一个数字,一趟排序后得到基准数字和左右两边的两组数字,其中一组都比基准数字小,另一组都比基准数字大,然后使用递归处理这两组数字;
    每次要保证把所有未处理过的数字包括在基准数字和下一个要处理的数字中间;
    快速排序应该采用递归方式实现; 
如
#######################################
     2 5 6 9 3 1
     [> 首先选择两端未处理的数字调整 <]
     [> 首先选择2作为基准数字base <]
     [> 拿2(base)和1调整;从两端开始处理; 交换了 <]
     1 5 6 9 3 2
     [> 拿2(base)和5调整;从两边向中间压缩; 交换了 <]
     1 2 6 9 3 5
     [> 拿2(base)和3调整; 不用交换; <]
     1 2 6 9 3 5
     [> 拿2(base)和9调整; 不用交换; <]
     1 2 6 9 3 5
     [> 拿2(base)和6调整; 不用交换; <]
     一轮结束,2已经处理好了,2左边的都比他小,2右边的都比他大;

     然后再采用相同的方式处理基准数字两边的数字;使用递归实现; 
     下面是分别处理上次的基准数字2左边和右边未处理的数字

     2左边的数字1无需再调整
     处理2右边的数字 6 9 3 5
     6 9 3 5
     [> 选择6作为新的基准数字base; <]
     [> 拿6(base)和5调整, 交换; <]
     5 9 3 6
     [> 拿6(base)和9调整, 交换; <]
     5 6 3 9
     [> 拿6(base)和3调整, 交换; <]
     5 3 6 9
     [> 这次结束时,6也被处理好了; <]

     再处理6左边的数字 5 3 和右边未处理的数字
     5 3
     [> 选择5作为基准数字 <]
     [> 拿5(base)和3调整, 交换 <]
     3 5

     整个过程结束
     1 2 3 5 6 9
#######################################

/*
 * 快速排序演示
 */
#include <stdio.h>
#include <stdlib.h>
void print(int *arr, int size) {
    int num = 0;
    for (num = 0; num <= size -1; num++) {
        printf("%d ", arr[num]);
    }
    printf("\n");
}

//quick_sort接收两个参数
void quick_sort(int *p_num, int size) {
    /* 不需要再拆分的情况 */
    if (size <= 1) {
        return;
    }

    int base = *p_num; //选择最前面的那个作为基准数字;
    /* start记录要处理的数字中前面那个的下标,end为后一个; */
    int num = 0, start = 0, end = size - 1;
    print(p_num, size); //处理前
    for (num = 1; num <= size -1; num++) {
        /* 如果我们要处理的前一个比后一个大,交换 */
        if (*(p_num + start) > *(p_num + end)) {
            int tmp = *(p_num + start);
            *(p_num + start) = *(p_num + end);
            *(p_num + end) = tmp;
        }
        /* 找到下次循环需要使用的下标 */
        /* 分基准数字在前和基准数字在后面两种情况 */
        if (*(p_num + start) == base) {
            /* 基准数字在前,下一个要处理的数字就应该是end--; */
            end--;
        } else {
            /* 基准数字在后,下一个要处理的数字就应该是start++; */
            start++;
        }
        print(p_num, size); //打印处理后的结果
    }
    printf("\n");
    /*
     * 循环结束后,一个基准数字就会被处理完毕;
     * 循环结束时,start和end应该是相等的;
     * 接下来需要递归处理基准数字两边的数字
     */

    /* 循环结束时,start和end相等;就是基准数字; */
    /* 递归处理基准数字左边的数字 */
    quick_sort(p_num, start);

    /*
     * 递归处理基准数字右边的数字;
     * 起始位置是p_num + start + 1;
     * 个数是size - start - 1;
     */
    quick_sort(p_num + start + 1, size - start - 1);
}

void quick_sort_v2(int *p_num, int L, int R) {
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
    int arr[6] = {2, 5, 6, 9, 3, 1}, num = 0;
    print(arr, 6);
    /* quick_sort(arr, 6); */
    /*
     * 在上面这个算法里面,我们经常会用基准数字和其他数字交换;
     * 影响效率,可以对该方法进行改进;
     * 如果我们把基准数字记录下来,
     * 当找到最后一个数字的时候再写入可能会提高效率;
     * 请参考下面的算法
     */
    quick_sort_v2(arr, 0, 5);
    print(arr, 6);
    return 0;
}
递归函数一定要注意描述递归边界,否则无法正常退出;


C语言提供了qsort()标准函数可以实现快速排序;
为了使用这个标准函数,需要包含stdlib.h头文件;
void qsort(void *base, size_t nmemb, size_t size,
    int (*compar)(const void *, const void *));
这个函数有4个参数;
    第1个参数是所有要进行排序的数字中第1个数字的地址;
    第2个是要排序的数字的个数;
    第3个是要排序的单个数字的大小;
    第4个是一个函数指针;我们需要提供一个函数来完成两个数字的比较;

/*
 * 快速排序qsort()标准函数的使用
 * 以后在使用快速排序时编写比较函数后直接调用qsort()标准函数即可;
 */
#include <stdio.h>
#include <stdlib.h>
void print(int *arr, int size) {
    int num = 0;
    for (num = 0; num <= size -1; num++) {
        printf("%d ", arr[num]);
    }
    printf("\n");
}

//编写供qsort()标准函数使用的回调函数
//注意形参类型的形式,而且要加const关键字;
int compare(const void *p_num, const void *p_num1) {
    /*
     * 如果前面的数比较大,返回1;将被排在后面;
     * 如果两个数相等,返回0
     * 如果后面的数比较大,返回-1;将被排在前面;
     * 这样的排序结果就是升序的;
     */
    if (*(const int *)(p_num) > *(const int *)(p_num1)) {
        //如果希望从小到大排列,就返回1;
        return 1;
        // 如果像把一个数排在另一个前面,就在比较时返回-1;
    } else if (*(const int *)(p_num) < *(const int *)(p_num1)) {
        return -1;
    } else {
        return 0;
    }
    //这是一个升序排列;
    //如果希望降序排列,返回值时1和-1颠倒一下就可以了;
}

int main() {
    int arr[6] = {2, 5, 6, 9, 3, 1}, num = 0;
    print(arr, 6);

    /* 直接调用该标准函数即可完成快速排序; */
    qsort(arr, 6, sizeof(int), compare);

    print(arr, 6);
    return 0;
}


5. 归并排序
    假设所有数字分成前后两组,每组都是已经排好序的;则归并排序可以把他们合并成一个新的数字序列; 
思路
    使用递归调用对前后两组分别进行排序;
    将两个有序的序列合并为一组有序的序列;
    首先考虑下如何将将二个有序数列合并;这个非常简单,只要从比较二个数列的第一个数,谁小就先取谁,取了后就在对应数列中删除这个数;然后再进行比较,如果有数列为空,那直接将另一个数列的数据依次取出即可;
    再来看归并排序,其的基本思路就是将数组分成二组A,B,如果这二组组内的数据都是有序的,那么就可以很方便的将这二组数据进行排序;\
    如何让这二组组内数据有序了?
    可以将A,B组各自再分成二组;依次类推,当分出来的小组只有一个数据时,可以认为这个小组组内已经达到了有序,然后再合并相邻的二个小组就可以了;这样通过先递归的分解数列,再合并数列就完成了归并排序;

/*
 * 归并排序演示
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MaxSize 1000
void print(int a[], int n) {
    int i = 0;
    for (i = 0; i <= n - 1; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
/* 将有二个有序数列a[first...mid]和a[mid...last]合并; */
void mergearray(int a[], int first, int mid, int last, int temp[]) {
    int i = first, j = mid + 1;
    int m = mid, n = last;
    int k = 0;
    while (i <= m && j <= n) {
        if (a[i] <= a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }
    while (i <= m)
        temp[k++] = a[i++];
    while (j <= n)
        temp[k++] = a[j++];
    for (i = 0; i < k; i++)
        a[first + i] = temp[i];
}
void mergesort(int a[], int first, int last, int temp[]) {
    if (first < last) {
        int mid = (first + last) / 2;
        /* 先递归分解数列 */
        mergesort(a, first, mid, temp);    //左边有序
        mergesort(a, mid + 1, last, temp);    //右边有序
        /* 再合并数列 */
        mergearray(a, first, mid, last, temp);    //再将二个有序数列合并
        /* print(a, last - first + 1); */
    }
}
int MergeSort(int a[], int n) {
    /* 分配辅助空间 */
    int *p = (int *)malloc(sizeof(int) * n);
    if (p == NULL)
        return -1;
    /* print(a, n); */
    mergesort(a, 0, n - 1, p);
    free(p);
    p = NULL;
    return 0;
}
int main() {
    int arr[1000] = {};
    int i = 0;
    srand(time(0));
    for (i = 0; i <= MaxSize - 1; i++) {
        arr[i] = rand() % (MaxSize * 10);
    }
    print(arr, MaxSize);
    MergeSort(arr, sizeof(arr) / sizeof(arr[0]));
    print(arr, MaxSize);
    return 0;
}

查找算法
    可以从一组数字中找到一个特定的数字; 
    1-> 顺序查找; 从前向后一个一个匹配;
    2-> 折半查找; 要求所有数字是排序好的,每次匹配可以排除一半的数;

/*
 * 折半查找
 */
#include <stdio.h>
void print(int *arr, int size) {
    int num = 0;
    for (num = 0; num <= size - 1; num++) {
        printf("%d ", arr[num]);
    }
    printf("\n");
}

/* 循环方式 */
int *search_loop(int *p_num, int size, int num) {
    int low = 0, mid = (size - 1) / 2, high = size - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (*(p_num + mid) == num) {
            /* 中间的数字和要找的数字相等 */
            return p_num + mid;
        } else if (*(p_num + mid) > num) {
            /* 中间的数字大于要找的,将目标范围缩小到前半部 */
            high = mid - 1;
        } else {
            /* 中间的数字小于要找的,将目标范围缩小到后半部; */
            low = mid + 1;
        }
    }
    return NULL;
}

/* 递归方式 */
int *search_recursion(int *p_num, int size, int num) {
#define MID ((size - 1) / 2)
    if (*(p_num + MID) == num) {
        /* 不再递归拆分的情况 */
        /* 中间的数字和要找的数字相等 */
        return p_num + MID;
    } else if (*(p_num + MID) > num) {
        /* 中间的数字大于要找的,将目标范围缩小到前半部 */
        /* p_num不变;size = size/2; */
    } else {
        /* 中间的数字小于要找的,将目标范围缩小到后半部; */
        /* p_num移动到后半部的开头;p_num += (size + 1)/2; */
        /* size = size/2; */
        p_num += (size + 1)/2;
    }
    printf("*p_num = %d, size = %d, MID = %d\n", *p_num, size, MID);

    /* 递归处理; */
    return search_recursion(p_num, size/2, num);
#undef MID
}
int bsearch(int *p_num, int num, int L, int R) {
    int mid;
    if (L > R) return -1;
    mid = (L + R) / 2;
    if (p_num[mid] == num) {
        return mid + 1;
    } else if (p_num[mid] > num) {
        /* R = mid - 1; */
        return bsearch(p_num, num, L, mid - 1);
    } else {
        /* L = mid + 1; */
        return bsearch(p_num, num, mid + 1, R);
    }
}

int main() {
    int arr[11] = { 0, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9 };
    print(arr, 11);

    /* int *p_num = search_loop(arr, 11, 8); */
    int *p_num = search_recursion(arr, 11, 8);
    if (p_num) {
        printf("找到的数字是%d\n", *p_num);
    }
    int num = bsearch(arr, 8, 0, 10);
    if (num != -1) {
        printf("找到的数字是数组的第%d个元素\n", num);
    }
    return 0;
}

