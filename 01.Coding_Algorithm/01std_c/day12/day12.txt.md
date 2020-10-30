指针




# 指针
    指针变量是一种特殊的变量,指针变量也对应一个存储位置,这个存储位置记录了另外一个存储位置的地址;
    指针变量又根据级别划分成一级指针,二级指针等;
```
图中左边的指针变量可以表示右边的任何一个存储位置;
=================================================
     地址c            地址b            地址a
    +--------+       +--------+       +--------+
    |   &b   |       |   &a   |       |        |
    +--------+       +--------+       +--------+
   二级指针变量ppi   一级指针变量pi   普通变量i
=================================================
地址b中存放的数据是地址a(即&i,普通变量的地址),即一级指针变量pi的值为a;
    pi == &i; //*pi == i;
地址c中存放的数据是地址b(即&b,一级指针变量的地址),即二级指针变量ppi的值为b;
    ppi == &pi; //*ppi == pi == *i; **ppi == *pi == i;
```

指针变量也是分类型的,一种类型的指针变量为一种类型的普通变量服务;
    + 指针变量的类型是人为规定的;这个类型可以根据需要随时改变;
    + 指针变量的类型可以决定关联的存储位置的类型;
    + 指针变量只有和一个普通存储位置关联以后才可以使用;
    + 既没有记录有效地址也没有记录空地址的指针叫野指针,也叫悬空指针;

要避免程序中出现野指针;
    + 约定,没有记录普通存储位置地址的指针变量中必须记录NULL(空地址,数值为0);
    + 避免野指针的办法是在它刚出现的时候立刻把它的内容设置成空;
    + 所有的指针变量都应当初始化;
    + 指针变量前加*可以表示对应的普通存储位置;

野指针不是和没有赋值的变量一样吗?感觉不到什么威胁啊;
    野指针是和没有赋值的变量一样,里边的内容不确定;普通变量相当于是一个花盆,里边是什么样的植物都不会出大事,但指针变量相当于是一把手枪,它里边是子弹,是很危险的;
    定义指针时如果不赋初值,系统会随机赋值给他,如果这个地址在程序的代码区,在地址变量被引用时会操作运行的程序代码,会出错;
    把NULL指针用%d打印出来就会段错误;
    NULL指针没有和普通变量关联所以还不能用;

为什么定义的时候*号不参加运算;
    定义的时候*号是用来标识它是指针变量的;

在使用一个指针的时候,应该首先把它指向一个有效的存储空间;
    不能声明一个指针变量之后就直接当数组一样使用;
    虽然数组的本质是指针,但数组(指针)已经关联了对应的存储空间了;
    如果指针已经指向了一段有效的连续存储空间,那么指针就可以像使用数组一样使用;
    ```
    p[i] <==> *(p + i);
    ```

练习
    从键盘得到三个数字,使用指针变量找出其中的最大数字
    普通变量的内容可以改变,但不能丢失数据,不能使用新的普通变量;
/*
 * 从键盘得到三个数字,用指针变量找出其中的最大值
 */
#include <stdio.h>
int main() {
    int num = 0, num1 = 0, num2 = 0;
    printf("请输入三个数字:");
    scanf("%d%d%d", &num, &num1, &num2);
    int *p_num = &num;    //建立指针与普通变量的关联并初始化
    //以上可以表示为int *p_num = NULL;p_num=&num;两个动作
    //可以声明为int *p_num=&num,*p_num=&num1,*p_num2=&num2;
    int *p_num1 = &num1;
    int *p_num2 = &num2;

    if (*p_num <= *p_num1) { //交换数据
        *p_num ^= *p_num1;
        *p_num1 ^= *p_num;
        *p_num ^= *p_num1;
    }
    if (*p_num <= *p_num2) {
        *p_num ^= *p_num2;
        *p_num2 ^= *p_num;
        *p_num ^= *p_num2;
    }
    printf("最大数据是: %d\n", *p_num);
    printf("%d, %d, %d\n", num, num1, num2);
    return 0;
}

/*
 * 从键盘得到三个数字,用指针变量找出其中的最大值
 * 保留原来普通变量的值
 */
#include <stdio.h>
int main() {
    int a = 0, b = 0, c = 0;
    int *p_max = &a;
    int *p_mid = &b;
    int *p_min = &c;
    printf("请输入三个数字:");
    scanf("%d%d%d", p_max, p_mid, p_min);
    if (*p_max <= *p_mid) {
        // 交换指针的值,即交换指针的指向
        int *p_tmp = p_max;
        p_max = p_mid;
        p_mid = p_tmp;
    }
    if (*p_max <= *p_min) {
        int *p_tmp = p_max;
        p_max = p_min;
        p_min = p_tmp;
    }
    if (*p_mid <= *p_min) {
        int *p_tmp = p_mid;
        p_mid = p_min;
        p_min = p_tmp;
    }
    printf("最大数据是: %d\n", *p_max);
    printf("%d, %d, %d\n", *p_max, *p_mid, *p_min);
    printf("%d, %d, %d\n", a, b, c);
    return 0;
}

    可以在一条语句中声明多个同类型的指针变量,每个指针变量名称前都应该有*符号;

=================================================
                     _______
                    | 地址1 |
                    |_______|
                        ^
                        |
                    普通变量num1
     _______         _______
    |  地址 |       | 地址2 |
    |_______|       |_______|
        ^               ^
        |               |
    指针变量        普通变量num2
=================================================
指针变量可以在程序运行时随时改变关联的普通存储位置;
    指针变量可以看作普通存储位置的一个身份;

    所有类型的指针在内存中都占用4个字节(32位系统);64位系统占8字节;
    指针变量的类型在转换过程中不会导致地址数据受影响;
    指针变量在类型转换过程中影响的是和指针关联的普通变量的解析;
    计算机中对数据的解析是按类型的;
/*
 * 指针类型转换演示
 */
#include <stdio.h>
int main() {
    int num = 0x04030201;
    int *p_num = &num;
    printf("p_num is %p, *p_num is 0x%x\n",
            p_num, *p_num); // 0x7ffdb8808d04, 0x4030201
    printf("(char*)p_num is %p, *(char*)p_num is 0x%x\n",
            (char *)p_num, *(char *)p_num); //0x7ffdb8808d04, 0x01
    printf("(short *)p_num is %p, *(short *)p_num is 0x%x\n",
            (short *)p_num, (*(short *)p_num)); //0x7ffdb8808d04, 0x0201
    /* p_num指向的地址都一样,但由于类型不同, */
    /* 计算机对这个地址所对应的存储内容解析方式不同; */
    return 0;
}
/*
 * 指针与类型
 */
#include <stdio.h>
int main() {
    char arr[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    void *p = NULL;
    p = arr;
    /* 对指针的强制类型转换会影响程序对数据的读取和解析方式 */
    printf("%hhd, %hd, %d\n", *(char *)p, *(short *)p, *(int *)p);

    /* 强制类型转换的实现方式是临时生成一个新数据, */
    printf("%hhd, %hd, %d\n", (char)arr[0], (short)arr[0], (int)arr[0]);
    /* 使用旧数据对新书据进行赋值;以后的操作采用的都是新数据; */
    return 0;
}

void *也是一种指针类型;
    这种类型的指针只表示其中记录了一个地址数据但没有告诉我们它关联什么类型的存储空间;
    这种类型的指针不可以直接加*使用,必须首先进行强制类型转换;
    这种指针通常用来记录来源不明的地址数据;如malloc()申请的内存空间;
/*
 * void*指针演示
 */
#include <stdio.h>
int main() {
    char ch = 'a';
    int num = 10;
    float fnum = 7.4f;
    void *p_val = &ch;    //在使用时必须首先进行强制类型转换
    *(char *)p_val = 'f';
    printf("*(char *)p_val is %c\n", *(char *)p_val);
    p_val = &num;
    printf("*(int *)p_val is %d\n", *(int *)p_val);
    p_val = &fnum;
    printf("*(float *)p_val is %g\n", *(float *)p_val);
    return 0;
}

指针变量也可以作为函数的形参使用;
    图中任何一列中的指针变量作为函数形参使用时,它右边所有存储位置都可以在两个函数之间共享;
    指针形参可以实现双向数据传递,因此他们都是输入输出参数;
    函数的参数传递始终都是值传递,被调函数是拿到了被操作数据的地址才实现了在函数中的改变,影响函数外部的值;
    因此如果想通过函数传参改变某个变量的值时,要把该变量的地址给函数;因为函数中的形参都是实参的一个拷贝,形参的改变不会影响实参本身;
    数组做形参只是一种假象,其实是指针在做形参;
/*
 * 指针形参演示
 */
#include <stdio.h>
void swap(int *p_num, int *p_num1) {
    /* p_num和p_num1是局部变量,分别接受实参的值(地址) */
    /* 获得了变量的地址,也就可以间接的操作这个变量; */
    int tmp = *p_num;
    *p_num = *p_num1;
    *p_num1 = tmp;
}
int main() {
    int num = 3, num1 = 7;
    printf("num is %d, num1 is %d\n", num, num1);
    swap(&num, &num1); // 把num和num1的地址传递给函数
    printf("num is %d, num1 is %d\n", num, num1);
    return 0;
}

void*类型的指针经常会作为函数的形参使用,扩展函数的通用性;
/*
 * void*指针做形参演示
 */
#include <stdio.h>
void print(void *p_val, int type) {
    if (type == 1) {
        printf("%c\n", *(char *)p_val);    //使用时做强制类型转换
    } else if (type == 2) {
        printf("%d\n", *(int *)p_val);
    } else {
        printf("%g\n", *(float *)p_val);
    }
}
int main() {
    char ch = 'g';
    int num = 10;
    float fnum = 4.6f;
    print(&ch, 1);
    print(&num, 2);
    print(&fnum, 3);
    return 0;
}

指针类型变量也可以作为函数的返回值使用;
    指针类型的返回值可以用来表示一个存储位置;
    不可以把局部变量的位置赋值给指针类型的返回值(局部变量的生命周期决定的);
/*
 * 指针类型返回值演示
 */
#include <stdio.h>
int max(int num, int num1) {
    return num > num1 ? num : num1;
}
//int *max1(int num, int num1) {
//    return num > num1 ? *num : *num1;
//    /* 错误,不能返回局部变量的地址; */
//}
int *max2(int *p_num, int *p_num1) {
    return *p_num > *p_num1 ? p_num : p_num1;
       //返回的是地址
    //返回的是局部变量(指针)的值,是从实参传过来的一个有效的地址;
}
int main() {
    int num = 3, num1 = 7;
    /* 将最大值变量的地址赋值给p_num指针; */
    int *p_num = max2(&num, &num1);
    printf("*p_num is %d\n", *p_num);
    return 0;
}


指针的算术运算

地址数据所能参与的四则运算有如下
    地址 + 整数
    地址 - 整数
    地址 - 地址
地址数据仅有以上运算

以上计算中的整数都是有单位的,单位由地址数据的类型决定;
地址数据相减的结果是整数,这个整数也是有单位的,单位由地址数据的类型决定;
/*
 * 地址数据算术运算演示
 */
#include <stdio.h>
int main() {
    int num = 0, num1 = 0;
    int *p_num = &num, *p_num1 = &num1;
    printf("p_num  is %p, p_num+3 is %p\n", p_num, p_num + 3);
    printf("p_num1 is %p, (char*)p_num1+3 is %p\n",
            p_num1, (char *)p_num1 + 3);
    printf("p_num1 - p_num is 0x%lx\n", (long)(p_num1 - p_num));
    return 0;
}

数组名称和指针变量的差异
    1.数组名称不可以被赋值(相当于int * const array, 指向不能改变),指针变量可以被赋值(改变指向);
    2.进行sizeof计算结果不同,数组是整个存储空间大小;指针是4字节;
    3.对他们分别取地址结果不同;对数组名称取地址数值不变但级别变成二维数组;
可以利用指针变量作为循环变量处理数组中的每个存储位置;
/*
 * 数组与指针对比
 */
#include <stdio.h>
int main() {
    int arr[] = { 1, 2, 3, 4, 5 };
    int *p_num = arr;
    printf("sizeof(arr) = %lu, sizeof(p_num) = %lu\n",
            (unsigned long)sizeof(arr), (unsigned long)sizeof(p_num));
    printf("p_num = %p, &p_num = %p\n", p_num, &p_num);
    printf("arr = %p, &arr = %p\n", arr, &arr);

    for (p_num = arr; p_num <= arr + 4; p_num++) {
        printf("%d ", *p_num);
        /* 数组的存储空间是连续的,可以用指针顺序访问; */
    }
    printf("\n");

    p_num = arr;
    int i = 0;
    for (i = 0; i <= 4; i++) {
        printf("%d ", p_num[i]); 
        /* 当指针指向一段有效的连续存储空间后,可以当数组使用; */
    }
    printf("\n");

    return 0;
}

指针变量声明时也可以使用const关键字
    const int *p_num; //const修饰int,p_num指向的普通变量只读
上面的指针自己可以被赋值(改变指向),但关联的普通存储位置不可以被赋值;
    int * const p_num;//const修饰int *,p_num指针只读
上面的指针自己不可以被赋值(不可以改变指向),但关联的普通存储位置可以被赋值;
/*
 * const指针演示
 */
#include <stdio.h>
int main() {
    int num = 5;
    int const *p_num = NULL;    //指针变量可以被修改
    int *const p_num1 = &num;    //指针指向的普通变量可以被修改
    p_num = &num;        //可以
//  *p_num = 10;        //错误,普通变量num不可以被赋值;
    *p_num1 = 10;        //可以
//  p_num1 = NULL;        //错误,本身不可以被赋值
}

const实际是声明所修饰的变量为只读变量,实质还是变量;
const实际上修饰的是它左边的东西,const的位置可以适当的移动,但不能越过*操作符;
    int const a1;
    const int a2; /* 与int const a2等价 */
    int * const a3; /* 指针指向不可更改 */
    int const * a4; /* 指针指向的普通变量的为只读 */
    const int * a5 /* 与int const *a5等价 */

作业
    1.编写程序颠倒一个数组里面的数字,要求使用指针;
/*
 * 编写程序把一个数组中的所有内容颠倒,要求使用指针完成;
 */
#include <stdio.h>
int main() {
    int arr[] = { 1, 2, 3, 4, 5, 6, 7 }, size = 7;
    int *p_pre = arr, *p_post = arr + 6;
    while (p_pre < p_post) {
        *p_pre ^= *p_post;    //对数组中的内容交换
        *p_post ^= *p_pre;
        *p_pre ^= *p_post;
        p_pre++;    //为下一步循环做准备
        p_post--;
    }
    for (p_pre = arr; p_pre <= arr + size - 1; p_pre++) {
        printf("%d ", *p_pre);
    }
    printf("\n");
    return 0;
}

    2.编程从一个大数组中查找小数组,
    把查到的所有起点打印在屏幕上,要求使用指针完成;
/*
 * 编程从一个大数组中查找小数组,
 * 把查到的所有起点打印在屏幕上,要求使用指针完成;
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    srand(time(0));
    int arr[] = { 1, 2, 3, 4, 5, 6, 7, 3, 4, 6, 7, 3, 4, 5 };
    int arr1[] = { 3, 4, 5 };
    int *p_cur = NULL, *p_arr1 = NULL;
    for (p_cur = arr; p_cur <= arr + 11; p_cur++) {
        for (p_arr1 = arr1; p_arr1 <= arr1 + 2; p_arr1++) {
            if (*(p_arr1 - arr1 + p_cur) != *p_arr1) {
                break;
            }
        }
        if (!(p_arr1 <= arr1 + 2)) {
            printf("检测到地址起点%p,第%d位\n", p_cur,
                   p_cur - arr);
            printf("检测到数组数据%d %d %d\n", *p_cur,
                   *(p_cur + 1), *(p_cur + 2));
        }
    }
    return 0;
}
