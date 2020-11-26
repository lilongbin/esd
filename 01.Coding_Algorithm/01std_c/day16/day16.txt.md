动态内存分配;
二级指针做形参;
函数指针;
常用标准函数

# 动态内存分配

动态内存分配可以在程序运行时随时分配存储位置;
+ 动态分配的存储位置来自于堆区;
+ 堆中的所有存储位置需要使用语句来完成分配和回收;

C语言中提供几个标准函数用来分配和回收堆中的存储位置;为了使用这些标准函数需要包含stdlib.h头文件;
1. malloc()标准函数用来动态分配多个连续的字节存储位置;
    + malloc()把分配后的第一个字节的地址赋值给返回值变量;这个地址是使用该存储位置的唯一依据;
    + malloc()返回值是void*指针,需要使用强制类型转换转换成所需要的类型的指针,然后赋值给相应类型的指针变量;
2. malloc()在失败的时候会把NULL赋值给返回值变量;
    其实NULL就是#define NULL (void *)0 定义的;
3. free()标准函数用来回收不再使用的动态分配的存储位置;
    不回收会导致内存泄漏,即已分配的这段内存一直被系统保护,无法再次利用直到进程结束或系统最终回收;
4. 所有动态分配的内存在使用完成后都必须立即释放;释放内存时需要使用第一个字节的地址作为参数;一次分配得到的所有存储位置必须统一释放;
5. 一段动态分配的内存只能释放一次,释放后记录它的地址指针将变成野指针;所谓野指针就是指针变量记录了一个未知空间的地址,将会导致无法预知的结果;

```
/*
 * 动态内存分配
 */
#include <stdio.h>
#include <stdlib.h>
int main() {
    int num = 0;
    /* 将返回值转换为整数类型的指针变量后赋值给一个整形指针变量; */
    int *p_num = (int *)malloc(3 * sizeof(int));
    if (NULL != p_num) {
        //动作内容
        for (num = 0; num <= 2; num++) {
            *(p_num + num) = num + 1;
        }
        for (num = 2; num >= 0; num--) {
            printf("%d ", *(p_num + num));
        }
        printf("\n");
        free(p_num);    //释放动态分配的内存;
        /* free(p_num + 1); //部分释放,段错误; */
        p_num = NULL;    //使野指针变为空指针;
    }
    return 0;
}
```

# 二级指针做形参

二级指针做形参可以把被调函数动态分配的存储位置交给调用函数使用;这个二级指针形参对应的一级指针存储位置必须由调用函数提供;

```
/*
 * 动态内存分配
 */
#include <stdio.h>
#include <stdlib.h>
typedef struct pt {
    int x, y;
} pt;

/* 采用动态分配内存实现计算中点位置的函数 */
pt *midpt(const pt *p_start, const pt *p_end) {
    pt *p_ret = (pt *) malloc(sizeof(pt));
    if (p_ret) {
        p_ret->x = (p_start->x + p_end->x) / 2;
        p_ret->y = (p_start->y + p_end->y) / 2;
    }
    return p_ret;
}

/* 二级指针做形参 */
int midpt1(const pt *p_start, const pt *p_end, pt **pp_pt) {
    /* 二级指针通常把被调函数动态分配的内存交给调用函数使用 */
    *pp_pt = (pt *) malloc(sizeof(int));
    /* pp_pt是pt类型的二级指针, *pp_pt是pt类型的指针; */
    if (*pp_pt) {
        (*pp_pt)->x = (p_start->x + p_end->x) / 2;
        (*pp_pt)->y = (p_start->y + p_end->y) / 2;
        return 1;    //返回动态分配是否成功;
    }
    return 0;
}

int main() {
    pt start = {}, end = {}, *p_pt = NULL;
    printf("请输入点: ");
    scanf("%d%d", &start.x, &start.y);
    printf("请输入点: ");
    scanf("%d%d", &end.x, &end.y);
    //p_pt = midpt(&start, &end);
    //if (p_pt) {
    if (midpt1(&start, &end, &p_pt)) {
        /* 要在被调函数中改变p_pt,必须使用更高一级的指针做参数; */
        printf("中点位置在(%d, %d)\n", p_pt->x, p_pt->y);
        free(p_pt);    //得到数据后再释放被调函数动态分配内存
        p_pt = NULL;
    }
    return 0;
}
```

## 动态内存练习
采用动态分配内存实现字符串拷贝功能;
新字符串的存储位置由被调函数提供,采用返回值和形参两个版本;
```
/*
 * 采用动态分配内存方式实现字符串拷贝功能;
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *mystrcpy(const char *p_src) {
    char *p_ret = (char *)malloc((strlen(p_src) + 1) * sizeof(char));
    if (p_ret) {
        /* strcpy(p_ret, p_src); */
        char *p_dest = p_ret;
        while ((*p_dest++ = *p_src++) != '\0') ;
    }
    return p_ret;
}

void mystrcpy1(const char *p_str, char **pp_dest) {
    *pp_dest = (char *)malloc((strlen(p_str) + 1) * sizeof(char));
    if (*pp_dest) {
        /* strcpy(*pp_dest, p_str); */
        char *p_tmp = *pp_dest;
        while ((*p_tmp++ = *p_str++) != '\0');
    }
}

int main() {
    char *p_str = mystrcpy("abc");
    if (p_str) {
        printf("新字符串是: %s\n", p_str);
        free(p_str);
        p_str = NULL;
    }
    mystrcpy1("abcdef", &p_str);
    if (p_str) {
        printf("新字符串是: %s\n", p_str);
        free(p_str);
        p_str = NULL;
    }
    return 0;
}
```

calloc()同样可以动态分配连续的存储位置;
+ calloc()会把分配好的所有存储位置清零;
+ calloc()分配时需要考虑存储位置的类型;

realloc()函数可以调整动态分配内存的大小;


# 函数指针
1. 函数指针可以用来记录函数的地址(函数第一条语句的地址);
2. 函数指针可以用来调用函数;
3. 函数名称可以用来表示函数的地址;
4. 函数指针可以用来代表未来可以扩展的函数;

## 声明函数指针的方法
将函数声明语句中的函数名用(* p)替换即可得到函数的指针;
其中p就是函数的指针;p可以用来指向一个函数;
```
int (*p_func)(int, int) = NULL; //声明函数指针p_func并初始化
p_func = add; //为函数指针赋值
```

+ 函数的名字(不加圆括号)其实就是这个函数的地址;
+ 对函数名称取地址得到的也是这个函数的地址;
+ 对函数名称取*得到的也是这个函数的地址;


使用函数指针可以编写出更加灵活,更有扩展性的程序;
```
/*
 * 函数指针
 */
#include <stdio.h>
int add(int x, int y) {
    return x + y;
}

int main() {
    int (*p_func) (int, int) = NULL; //声明函数指针并初始化
    //%p就是将数据按16进制打印出来,即按地址格式打印;
    printf("add is %p\n", add); //add代表函数地址;
    printf("add is 0x%x\n", add); //add是这个函数的地址;
    printf("&add is 0x%x\n", &add);//&add也是这个函数的地址;
    printf("*add is 0x%x\n", *add);//*add也是这个函数的地址;
    printf("**add is 0x%x\n", **add);//**add也是这个函数的地址;
    //对一个函数名字取&或*结果仍旧是这个函数的地址;
    //结果仍然等价于对函数名没有做任何操作,仍旧是函数的地址;
    p_func = add;
    printf("result is: %u\n", p_func(3, 6));
    printf("result is: %u\n", (*p_func)(3, 6));
    printf("result is: %u\n", (**p_func)(3, 6));
    printf("p_func is %p\n", p_func);
    printf("*p_func is %p\n", *p_func);
    printf("**p_func is %p\n", **p_func);
    printf("&p_func is a variable: &p_func =  %p\n", &p_func);
    return 0;
}
```

```
/*
 * 函数指针演示
 */
#include <stdio.h>
int add(int x, int y) {
    return x + y;
}
int sub(int x, int y) {
    return x - y;
}
int mul(int x, int y) {
    return x * y;
}
int div(int x, int y) {
    return x / y;
}

int main() {
    int num = 0, num1 = 0, ret = 0;
    char opr = 0;
    int (* p_func) (int, int) = NULL;
    printf("请输入一个表达式\n");
    scanf("%d%c%d", &num, &opr, &num1);
    // 采用函数指针的形式
    if (opr == '+') {
        p_func = add;
    } else if (opr == '-') {
        p_func = sub;
    } else if (opr == '*') {
        p_func = mul;
    } else if (opr == '/') {
        p_func = div;
    } else {
        printf("error\n");
        return 1;
    }
    printf("计算结果是: %d\n", p_func(num, num1));
    return 0;
}
```

```
/*
 * 函数指针演示
 */
#include <stdio.h>
typedef struct expr {
    int num, num1;
    int (* p_func) (int, int);
    /* 声明一个函数指针,结构体声明中不可以有函数 */
} expr;
int add(int x, int y) {
    return x + y;
}
int sub(int x, int y) {
    return x - y;
}
int mul(int x, int y) {
    return x * y;
}
int div(int x, int y) {
    return x / y;
}

int main() {
    expr exprs[3] = { };
    char opr = 0;
    int i = 0;
    for (i = 0; i <= 2; i++) {
        printf("请输入一个表达式: ");
        scanf("%d%c%d", &exprs[i].num, &opr, &exprs[i].num1);
        if (opr == '+') {
            exprs[i].p_func = add;
        } else if (opr == '-') {
            exprs[i].p_func = sub;
        } else if (opr == '*') {
            exprs[i].p_func = mul;
        } else if (opr == '/') {
            exprs[i].p_func = div;
        } else {
            printf("error\n");
            return 1;
        }
    }
    for (i = 0; i <= 2; i++) {
        printf("结果是: %d\n",
               exprs[i].p_func(exprs[i].num, exprs[i].num1));
    }
    return 0;
}
```

## 函数指针使用的特殊场景
```
/*
 * 函数指针使用的特殊场景
 */

#include <stdio.h>
typedef struct sdata {
    int num;
    int *p_num;
} sdata;
int arr[] = { 4, 9, 6, 2, 7 };

int print(int *p_num, void *p_val) {
    printf("%d ", *p_num);
    return 0;
}

int clear(int *p_num, void *p_val) {
    *p_num = 0;
    return 0;
}

int sum(int *p_num, void *p_data) {
    *(int *)p_data += *p_num;
    return 0;
}

//为回调函数添加返回值,供调用函数使用;
int search(int *p_num, void *p_data) {
    if (((sdata *)p_data)->num == *p_num) {
        ((sdata *)p_data)->p_num = p_num;
        return 1;
    }
    return 0;
}

//for_each()就叫遍历函数
//具有极强的扩展性
void for_each(int (*p_func)(int *, void *), void *p_val) {
    int *p_num = NULL;
    for (p_num = arr; p_num <= arr + 4; p_num++) {
        if (p_func(p_num, p_val)) {
            break; // if search OK, break;
        }
    }
    printf("\n");
}

int main() {
    //int num = 0;
    //for_each(print, 0);
    //for_each(print, 0);
    //for_each(sum, &num);
    //printf("num = %d\n", num);
    sdata sd = {9, NULL};
    for_each(search, &sd);
    printf("search OK: %d\n", *(sd.p_num));
    return 0;
}
```

# 其他常用标准函数

atoi()函数  可以把字符串中的整数提取出来得到整数数值(ascii to  int);

atof()函数  可以把字符串中带小数点的数字提取出来得到double类型数值(ascii to double float);

> 为了使用这两个标准函数,需要包含 stdlib.h 文件;

字符串版的printf()和scanf();
```
sprintf()标准函数  可以把数据按照格式输出(存储)到字符串中;
    可以按照某种格式合并字符串;
    sprintf(buf, "hello %d", num);

sscanf()标准函数  可以按照格式从字符串中把数字读出来并存储在存储位置里;
    可以提取某种格式的字符串并分别存储到对应类型的变量中;
    sscanf("a 36", "%c%d", &ch, &num);
fprintf()/fscanf()标准函数是对文件进行格式化操作的标准函数;
```

```
/*
 * 标准函数演示
 */
#include <stdio.h>
#include <stdlib.h>
int main() {
    char buf[20] = { }, ch = 0;
    int num = atoi("123");
    double dnum = atof("4.56");
    printf("num is %d\n", num);
    printf("dnum is %lg\n", dnum);

    /* printf()格式前面加一个数组,打印到前面的数组中 */
    sprintf(buf, "%d %g %c", 34, 5.7f, 't');
    printf("buf is %s\n", buf);

    sscanf("y 36 5.8", "%c%d%lg", &ch, &num, &dnum); //从前面读取
    printf("%lg %c %d\n", dnum, ch, num);
    return 0;
}
```

sleep()函数可以让进程等待一定时间,时间单位为秒;
等待时间不是十分精确;需要包含unistd.h文件;

```
/*
 * sleep演示
 */
#include <stdio.h>
#include <time.h>
#include <unistd.h>
int main() {
    printf("开始时间为%ld\n", time(0)); //time(0)与time(NULL)等价;
    sleep(4);
    printf("结束时间为%ld\n", time(NULL));
    return 0;
}
```

输出缓冲区内容显示在屏幕上的条件
1. 输出缓冲区中遇到'\n';
2. 执行打印任务的函数结束了;
3. 输出缓冲区已满;
4. 使用fflush(stdout)强制刷新缓冲区;fflush是函数,stdout是参数;

数据结构和算法中大量的使用了指针,请对指针和数组深入研究,多加练习;

