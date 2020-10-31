数组



# 数组
在C语言中使用数组来表示多个连续的同类型的存储位置;

使用数组表示多个连续存储位置的时候只需要一个名字,这个名字就代表所有这些存储位置的整体;
每一个存储位置有一个自己的编号,最前边的存储位置的编号是0,向后依次递增,最后一个存储位置的编号是个数-1;这个编号叫数组的下标;

使用 名称[下标] 就可以表示这组存储位置中的某一个;

绝不可以使用超过范围的下标;如果使用了越界的存储位置结果是未知的,不能保证安全性;
在声明数组的时候,除了要有名称之外,还要指定连续存储位置的个数;

```
/*
 * 数组演示
 */
#include <stdio.h>
int main() {
    int arr[6];
    arr[2] = 6;
    printf("arr[2] is %d\n", arr[2]);
    return 0;
}
```

使用循环操作数组可以最大限度发挥数组的优势
```
/*
 * 数组练习
 */
#include <stdio.h>
int main() {
    int arr[5];        //声明
    int num = 0;
    for (num = 0; num <= 4; num++) {
        //循环赋值
        arr[num] = num + 1;
    }
    for (num = 4; num >= 0; num--) {
        //循环打印
        printf("%d ", arr[num]);
    }
    printf("\n");
    return 0;
}
```

数组也需要初始化,数组初始化方法如下

```
int arr[3] = {1, 2, 3};
或
int arr[3] = {};
```

>其中1,2,3这三个数字用来对数组中的三个存储位置分别进行初始化;
>
>注意: 可以采用上述方法对数组进行初始化,不可以采用上述方法对数组进行赋值;
>>如:
>>    int arr[3];
>>    arr[3] = {1, 2, 3}; //赋值操作不合法

赋值的时候可以采用循环依次对每个数组元素赋值.

```
/*
 * 数组练习数字拆分
 */
#include <stdio.h>
int main() {
    int arr[5], num = 0, num1 = 0;
    printf("请输入一个数字: ");
    scanf("%d", &num1);
    //数组初始化
    for (num = 0; num <= 4; num++) {
        arr[num] = -1;
    }
    //数组循环赋值
    for (num = 4; num >= 0; num--) {
        arr[num] = num1 % 10;
        num1 /= 10;
        if (!num1) {
            break;
        }
    }
    //循环打印数组
    for (num = 0; num <= 4; num++) {
        if (arr[num] >= 0) {
            printf("%d ", arr[num]);
        }
    }
    printf("\n");
    return 0;
}
```

* 如果数组初始化的时候有些存储位置没有对应的初始化数据则它们被初始化成0;
* 如果初始化数据比存储位置的个数多则多余的数据自动被忽略;

```
/*
 * 奇偶校验练习
 */
#include <stdio.h>
int main() {
    int arr[8] = { }, num = 0;
    for (num = 0; num <= 6; num++) {
        printf("请输入一个数字(0或1): ");
        scanf("%d", &arr[num]);
        arr[num] &= 1;
    }
    for (num = 0; num <= 6; num++) {
        if (arr[num]) {
            arr[7] ^= 1;
            //每当遇到数组中有一个1最高位状态变化一次;
        }
    }
    for (num = 0; num <= 7; num++) {
        printf("%d", arr[num]);
    }
    printf("\n");
    return 0;
}
```

* 如果初始化的时候为每个存储位置提供了数据则可以省略存储位置的个数;
> 例如 int arr[] = {1, 2, 3};

数组名称在计算机中采用一个临时计算出来的数字表示,这个数字是第一个存储位置的地址;
数组的本质就是指针;
> 数组名称不可以被赋值;数组名称代表一个地址,也是第一个元素的地址;

一维数组中下标为n的存储位置的地址可以使用数组名称加n的方式表示;
> arr+i == &arr[i];//&和最后一个[]抵消;

对数组名称进行sizeof计算可以得到整个数组的大小;


```
/*
 * 数组演示
 */
#include <stdio.h>
int main() {
    int arr[] = { 1, 2, 3 };
    /* arr = 0;   数组名称不可以被赋值,代表第一个元素的地址 */
    printf("arr:%p, &arr:%p, &arr[0]:%p\n", arr, &arr, &arr[0]);
    //arr:0x7ffea0f5dc5c, &arr:0x7ffea0f5dc5c, &arr[0]:0x7ffea0f5dc5c
    //arr, &arr, &arr[0] 值相等

    printf("arr+1:%p, &arr[1]:%p, &arr[0]+1:%p, &arr+1:%p\n", arr+1, &arr[1], &arr[0]+1, &arr+1);
    //arr+1:0x7ffea0f5dc60, &arr[1]:0x7ffea0f5dc60, &arr[0]+1:0x7ffea0f5dc60, &arr+1:0x7ffea0f5dc68
    //arr, &arr, &arr[0] 意义不同

    printf("sizeof(arr):%ld, sizeof(arr[0]):%ld\n", sizeof(arr), sizeof(arr[0]));
    //sizeof(arr):12, sizeof(arr[0]):4
    return 0;
}
```

>C99规范中允许使用变量作为个数声明数组,这种数组叫变长数组;
>因为只有在运行时才能知道其中的存储位置个数;
>变长数组不可以初始化;

数组一旦存在,其存储位置及存储位置的个数就不可改变了,数组的大小是不可调的;

# 柔性数组
柔性数组即数组大小待定的数组;
>C语言中结构体的最后一个元素可以是大小未知的数组;
>C语言可以由结构体产生柔性数组;

```
struct soft_array {
    int len;
    int array[];
};
```
sizeof(soft_array)可以发现,柔性数组是不占空间的;
在使用的时候需要现申请一段内存空间,返回给这个结构体类型的指针;
这样这个数组就可以不用指定大小,自由使用下标访问这段内存空间;
本质是把申请的这段空间给这个结构体指针,然后数组处于最后一段区域,就可以用指针(数组+下标)访问;

```
/*
 * 柔性数组创建与使用
 */
#include <stdio.h>
#include <stdlib.h>
typedef struct soft_array {
    int len;
    int arr[];
} dat;
int main() {
    int num = 0;
    int len = 10;
    printf("sizeof(struct soft_array) = %ld\n", sizeof(struct soft_array));

    dat *pdat = (dat *)malloc(sizeof(dat) + (sizeof(int))* len);
    //柔性数组的本质就是把申请的内存空间中最后一段都分配给了数组的首地址
    //以后就可以用这个数组的首地址来访问剩下的这段空间;
    //因为是用malloc()分配的,这段内存也是受保护的;
    if (pdat) {
        pdat->len = len;
        for (num = 0; num < pdat->len; num++) {
            pdat->arr[num] = num + 1;
        }
        for (num = 0; num < pdat->len; num++) {
            printf("pdat->arr[%d] = %d\n", num, pdat->arr[num]);
        }
        free(pdat);
        pdat = NULL;
    }
    return 0;
}
```

> 随机数
>
> rand()标准函数用来获得随机数,把这个函数的调用语句当数字使用就是得到的随机数;
> 为了使用这个函数需要包含stdlib.h文件;
>
> srand()标准函数用来设置随机数种子,这个函数把一个整数作为种子使用,
> 为了使用这个函数也需要包含stdlib.h文件;
>
> time()标准函数可以用来获得当前的时间,得到的时间是一个整数;
> 为了使用这个标准函数需要包含time.h文件

```
    time_t time(time_t *t);

    time()  returns  the  time  since  the  Epoch (00:00:00 UTC, January 1, 1970), measured in seconds.
    If t is non-NULL, the return value is also stored in the memory pointed to by t.
```

> time(0);或time(NULL);
> 只以返回值的形式获得当前时间的秒数;


```
/*
 * 随机数演示
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    time_t t1, t2;
    t2 = time(&t1); //time()将时间值保存到t1中并返回给t2;
    printf("t1 = %ld, t2 = %ld\n", (long)t1, (long)t2);

    struct tm *mytime = localtime(&t1); //localtime()转换为本地时间
    printf("%04d-%02d-%02d %02d:%02d:%02d\n", 
            mytime->tm_year + 1900, mytime->tm_mon + 1, mytime->tm_mday,
            mytime->tm_hour, mytime->tm_min, mytime->tm_sec);
    printf("%s\n", ctime(&t1)); //转换为本地时间,并转换成日历的字符串
    
    srand(time(0)); //种下一棵随机种子树
    /*
     * srand(time(NULL));
     * time(0)即time(NULL);
     * time(0)获取当前时间对应的一个秒数(距1970-01-01 00:00:00)
     * srand(time(0))以该整数为种子种下一个随机树
     */
    printf("%d\n", rand());
    printf("%d\n", rand());
    printf("%d\n", rand());
    return 0;
}
```

> 任何程序中只使用一次srand()标准函数就可以了;

练习
    编写程序自动生成一张彩票(允许出现重复数字)7个数字
```
/*
 * 彩票练习
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    int arr[7] = { };
    int num = 0;
    srand(time(0)); //种下一棵随机种子树

    for (num = 0; num <= 6; num++) {
        /* 产生随机种子并保存到数组 */
        arr[num] = rand() % 36 + 1;
    }
    for (num = 0; num <= 6; num++) {
        printf("%d ", arr[num]);
    }
    printf("\n");
    return 0;
}
```

> 一维数组可以和一级指针混用;

```
/*
 * 一维数组与指针使用
 */
#include <stdio.h>
int main() {
    int arr[10] = { };
    int num = 0;
    int *p_num = arr;
    for (num = 0; num < 10; num++) {
        /* arr[num] = num + 1; */
        *(arr + num) = num + 1;
    }
    /* arr[i] <==> *(arr + i) <==> *(p_num + i) */
    for (num = 0; num < 10; num++) {
        printf("arr[%d] = %d, *(arr + %d) = %d,    *(p_num + %d) = %d\n",
               num, arr[num], num, *(arr + num), num, *(p_num + num));
    }
    return 0;
}
```

# 二维数组
只使用一个下标就可以表示一些连续存储空间的数组叫一维数组;
使用两个下标表示某些连续存储空间的数组叫二维数组;

二维数组也是对一串连续存储位置的表示方式;数组一旦存在,其存储位置及存储位置的个数就不可改变了,数组的大小是不可调的;

二维数组在声明的时候需要提供两个数字,第一个数字表示分了多少组,第二个数字表示每组中包含多少个存储位置;
使用二维数组时需要提供两个下标才能表示某个存储位置;第一个下标表示某个分组,第二个下标表示分组中的某个存储位置;这两个下标都是从0开始的;
在使用二维数组时下标也不可以超过范围;

通常使用循环嵌套处理二维数组;
```
/*
 * 二维数组演示
 */
#include <stdio.h>
int main() {
    int matrix[12] = { };
    int row = 0, col = 0;
    int matrix1[3][4];        //声明二维数组
    matrix1[1][2] = 0;        //二维数组单个元素赋值

    //循环嵌套处理二维数组
    for (row = 0; row <= 2; row++) {
        for (col = 0; col <= 3; col++) {
            matrix1[row][col] = row + col;
        }
    }

    for (row = 0; row <= 2; row++) {
        for (col = 0; col <= 3; col++) {
            printf("%d ", matrix1[row][col]);
        }
        printf("\n");
    }
    return 0;
}
```

二维数组既可以当成一个一维数组来初始化,也可以当成多个一维数组进行初始化;
如果可以根据初始化数据的个数确定组的个数则可以省略组的个数;

对二维数组名称进行 sizeof 计算可以得到二维数组中所有存储位置大小的总和;

二维数组只使用一个下标时可以表示某一组中所有存储位置;
> 如matrix[0]代表的是一个地址即&matrix[0][0];

```
/*
 * 二维数组初始化演示
 */
#include <stdio.h>
int main() {
    //int matrix[2][3] = {1, 2, 3, 4, 5, 6}; //当成1个一维数组初始化
    //int matrix[2][3] = {1, 2, 3, 4}; 
    //int matrix[2][3] = {{1, 2}, {3, 4}}; //当成2个一维数组
    //int matrix[][3] = {1, 2, 3, 4}; //可以在适当情况下省略大小数字
    int matrix[][3] = { {1, 2}, {3, 4} };
    int row = 0, col = 0;

    for (row = 0; row <= 1; row++) {
        for (col = 0; col <= 2; col++) {
            printf("%d ", matrix[row][col]);
        }
        printf("\n");
    }

    //matrix == &matrix[0]; matrix[0] == &matrix[0][0];
    printf("matrix:%p, matrix[0]:%p, &matrix[0]:%p, &matrix[0][0]:%p\n", matrix, matrix[0], &matrix[0], &matrix[0][0]);
    //matrix:0x7ffe76828d40, matrix[0]:0x7ffe76828d40, &matrix[0]:0x7ffe76828d40, &matrix[0][0]:0x7ffe76828d40

    //&matrix[0] == matrix; &matrix[0][0] == matrix[0];
    //&matrix[0]+1 == matrix+1; &matrix[0][0]+1 = matrix[0]+1;
    //matrix == &matrix[0]; matrix[0] == &matrix[0][0];
    //matrix+1 == (int)&matrix+(int)sizeof(matrix[0]); matrix[0]+1 == (int)&matix[0]+sizeof(matrix[0][0]);
    printf("matrix+1:%p, matrix[0]+1:%p, &matrix[0]+1:%p, &matrix[0][0]+1:%p\n", matrix+1, matrix[0]+1, &matrix[0]+1, &matrix[0][0]+1);
    //matrix+1:0x7ffe76828d4c, matrix[0]+1:0x7ffe76828d44, &matrix[0]+1:0x7ffe76828d4c, &matrix[0][0]+1:0x7ffe76828d44

    printf("sizeof(matrix):%ld, sizeof(matrix[0]):%ld\n", sizeof(matrix), sizeof(matrix[0]));
    //sizeof(matrix):24, sizeof(matrix[0]):12
    return 0;
}
```

练习,将以下图案打印在屏幕,要求使用二维数组,不能使用这些数据初始化
11111
22222
33333
44444
55555
```
/*
 * 二维数组练习
 */
#include <stdio.h>
int main() {
    int matrix[5][5] = { };
    int row = 0, col = 0;
    for (row = 0; row <= 4; row++) {
        for (col = 0; col <= 4; col++) {
            matrix[row][col] = row + 1;
        }
    }

    for (row = 0; row <= 4; row++) {
        for (col = 0; col <= 4; col++) {
            printf("%d", matrix[row][col]);
        }
        printf("\n");
    }
    return 0;
}
```

10002
01020
00200
02010
20001
```
/*
 * 二维数组练习
 */
#include <stdio.h>
int main() {
    int matrix[5][5] = { };
    int row = 0, col = 0;

    for (row = 0; row <= 4; row++) {
        //循环赋值
        for (col = 0; col <= 4; col++) {
            matrix[row][col] = 0;
            if (row == col) {
                matrix[row][col] = 1;
            }
            if (row + col == 4) {
                matrix[row][col] = 2;
            }
        }
    }

    for (row = 0; row <= 4; row++) {
        //打印
        for (col = 0; col <= 4; col++) {
            printf("%d", matrix[row][col]);
        }
        printf("\n");
    }

    return 0;
}
```

# 深入理解数组
## ndarray
```
0维为标量; int x;
1维为向量; array[n]     [1,2,3,4,5,6,...];
2维为矩阵; matrix[n][m] [[1,2,3],[4,5,6],[7,8,9]];
n维为张量; tensor 即ndarray,为n维矩阵;
```

## 一维数组
```
地址:  &arr[0]  &arr[1]  &arr[2]  &arr[3]
地址:   arr+0    arr+1    arr+2    arr+3
     +--------+--------+--------+--------+
arr  |        |        |        |        |
     +--------+--------+--------+--------+
值:    arr[0]   arr[1]   arr[2]   arr[3]
值:   *(arr+0) *(arr+1) *(arr+2) *(arr+3)
```

## 二维数组
```
mtx;
      +----------+----------+----------+----------+
mtx[0]|          |          |          |          |
      +----------+----------+----------+----------+
mtx[1]|          |          |          |          |
      +----------+----------+----------+----------+
mtx[2]|          |          |          |          |
      +----------+----------+----------+----------+
mtx[3]|          |          |          |          |
      +----------+----------+----------+----------+
mtx[4]|          |          |          |          |
      +----------+----------+----------+----------+

从第一维来看
mtx value
      +----------+
mtx[0]|          |
      +----------+
mtx[1]|          |
      +----------+
mtx[2]|          |
      +----------+
mtx[3]|          |
      +----------+
mtx[4]|          |
      +----------+

进行转置

地址:  &mtx[0]  &mtx[1]  &mtx[2]  &mtx[3]  &mtx[4]
地址:   mtx+0    mtx+1    mtx+2    mtx+3    mtx+4
     +--------+--------+--------+--------+--------+
mtx  |        |        |        |        |        |
     +--------+--------+--------+--------+--------+
值:    mtx[0]   mtx[1]   mtx[2]   mtx[3]   mtx[4]
值:   *(mtx+0) *(mtx+1) *(mtx+2) *(mtx+3) *(mtx+4)

再看第二维
以第一维的某个元素展开为例
mtx[0]分布如下

地址:  &mtx[0][0]  &mtx[0][1]  &mtx[0][2]  &mtx[0][3]
地址:   mtx[0]+0    mtx[0]+1    mtx[0]+2    mtx[0]+3
      +----------+----------+----------+----------+
mtx[0]|          |          |          |          |
      +----------+----------+----------+----------+
值:     mtx[0][0]   mtx[0][1]   mtx[0][2]   mtx[0][3]
值:   *(mtx[0]+0) *(mtx[0]+1) *(mtx[0]+2) *(mtx[0]+3)
```


作业
    1.修改彩票程序,避免出现重复数字
```
/*
 * 彩票练习
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    int lottery[7] = { };
    int num = 0;
    int num1 = 0;

    srand(time(0));
    do {
        lottery[num] = rand() % 36 + 1;
        for (num1 = 0; num1 <= num - 1; num1++) {
            if (lottery[num1] == lottery[num]) {
                break;    //排除重复
            }
        }
        /* 如果for是正常结束的,说明没有出现重复的 */
        if (!(num1 <= num - 1)) {
            num++;
        }
    } while (num < 7);

    for (num = 0; num <= 6; num++) {
        printf("%d ", lottery[num]);
    }
    printf("\n");

    return 0;
}
```

    2.编写程序检查一个身份证号码是否真实把身份证前17个数字依次和下面17个数字做乘法
    (7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2),然后把所有乘法结果求和;最后使用求和结果除以11得到余数,根据余数从下面11个数字中找到身份证号码中的最后一个数
    (1, 0, X, 9, 8, 7, 6, 5, 4, 3, 2)
```
/*
 * 身份证号码验证
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_num_str(char *arr, int num) {
    printf("please input the front 17bit number of your id: ");
    fgets(arr, num, stdin);
    /* printf("you typed: %s\n", arr); */
}

char get_last_bit(char *arr, int num) {
    int id[] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 };
    char res[] = { '1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2' };
    int i, sum = 0;
    char idx[4] = { };

    for (i = 0; i <= 16; i++) {
        /* strncpy(idx, &arr[i], 1); */
        idx[0] = arr[i];
        /* printf("%c, %d, %d\n", arr[i], id[i], atoi(idx)); */
        id[i] *= atoi(idx);
        sum += id[i];
        /* printf("%c, %d, %d\n", arr[i], id[i], atoi(idx)); */
    }

    switch (sum % 11) {
    case 0:
        idx[0] = res[0];
        break;
    case 1:
        idx[0] = res[1];
        break;
    case 2:
        idx[0] = res[2];
        break;
    case 3:
        idx[0] = res[3];
        break;
    case 4:
        idx[0] = res[4];
        break;
    case 5:
        idx[0] = res[5];
        break;
    case 6:
        idx[0] = res[6];
        break;
    case 7:
        idx[0] = res[7];
        break;
    case 8:
        idx[0] = res[8];
        break;
    case 9:
        idx[0] = res[9];
        break;
    case 10:
        idx[0] = res[10];
        break;
    }

    return *idx;
}

int main() {
    char arr[20];
    get_num_str(arr, 18);
    sprintf(arr, "%s%c\n", arr, get_last_bit(arr, 18));
    printf("your complete id number is: %s\n", arr);

    return 0;
}
```

    3.编程在一个10行10列的棋盘上随机布置10个地雷;布雷完成后把整个棋盘打印在屏幕上;(不是雷的位置打印空格,是雷的位置打印X);

```
/*
 * 随机布雷
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MINE    'X'
#define SPACE    ' '
int main() {
    int mine[10][10] = {};
    srand(time(0));
    int i = 0, j = 0, num = 0;
    for (num = 0; num < 10;) {
        i = rand() % 10;
        j = rand() % 10;
        if (mine[i][j] != MINE) {
            mine[i][j] = MINE;
            num++;
        }
    }
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (mine[i][j] != MINE) {
                printf("%c", SPACE);
            } else {
                printf("%c", MINE);
            }
        }
        printf("\n");
    }
    return 0;
}
```

