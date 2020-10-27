# 变量,赋值,数据类型


# 变量
计算机的内存可以用来记录数据;
计算机的内存可以分成很多存储位置,每个存储位置可以用来记录一个数字;
在C语言程序中可以使用这些存储位置,前提是计算机把某个位置分配给了我们的程序;

在C语言程序中通过变量可以使用一个存储位置;
存储位置是分类型的,一个存储位置只能用来记录某种类型的数据; 
变量也是分类型的,变量必须使用声明语句声明过后才可以使用,计算机会为我们的程序分配一个存储位置然后把它和我们的变量绑定;

变量声明语句包含变量的类型和变量的名称,例如: int num;
变量的定义不同于变量的声明,如: int num = 10;

使用变量实际上是使用变量所在的存储位置,变量是我们使用存储位置的便捷途径. 
我们代码中所使用的数值尽量存储在变量里,方便代码的维护;


# 赋值
一个存储位置有两种使用方法(放数据和取数据),赋值语句可以向存储位置中放数据;

赋值操作符(=)是赋值语句的核心,赋值操作符左边写一个变量,右边写一个可以当数字使用的内容就构成一条赋值语句,这条赋值语句就可以把右边的数值放在左边变量代表的存储位置里. 
```
int num;
num = 2 + 5; //变量赋值
```

赋值操作符左边必须是一个左值,左值代表一个变量,变量代表一个存储位置. 

在C语言程序中把代表存储位置的东西当数字使用就是从存储位置取数据. 
变量有时代表存储位置,有时代表存储位置里的数据. 
可以使用0替换变量看该语句是否仍然成立以验证变量是代表存储位置还是存储位置的数据. 

同类型的变量可以在一条变量声明语句中声明. 
存储位置是一直存在的,但里面的内容是我们所无法控制的;

可以在声明变量时立刻赋值,这叫做变量初始化initial.所有变量最好都进行初始化,这是一种编程的好习惯.

初始化的实现方法和普通的赋值的实现方法很可能是不同的.
* 一个初值为0的全局变量会存储在BSS段
* 初值不为0的全局变量会被存储在全局区

可以用一个存储位置存储多个相关数据.前提是任何时候我们只使用这组数据中的一个,最好是这组数据之间可以通过某种方式求得;

```
/*
 * 变量练习
 */
#include <stdio.h>
int main() {
    int num = 0, num1 = 0;    //多个同类型的变量可以在一条语句中声明
    /* 变量的初始化是个编程好习惯 */
    num = 2 + 5;
    num + 3;
    printf("num = %d\n", num);

    num = num;
    //第一个num代表一个存储位置,第二个num代表存储位置里面的数
    //用一个数字代替,看语句是否还成立来判断代表一个存储位置还是数
    return 0;
}
```

```
/* 
 * 变量练习
 * 把60 * 2 = 120打印在屏幕
 * 要求使用变量和赋值语句
 * */

#include <stdio.h>
int main() {
    int num0 = 60, num1 = 2, res = 0;
    printf("%d * %d = %d\n", num0, num1, num0 * num1);

    res = num0 * num1;
    printf("%d * %d = %d\n", num0, num1, res);

    return 0;
}
```

练习
在屏幕打印如下信息
1 * 9 = 9
2 * 8 = 16
3 * 7 = 21
4 * 6 = 24
5 * 5 = 25

```
/*
 * 变量练习
 * 在屏幕打印1 * 9 = 9, 2 * 8 = 16, ...5 * 5 = 25
 * */
#include <stdio.h>
int main() {
    int num = 1, num1 = 9;
    printf("%d * %d = %d\n", num, num1, num * num1);
    num = num + 1;
    num1 = num1 - 1;
    printf("%d * %d = %d\n", num, num1, num * num1);
    num = num + 1;
    num1 = num1 - 1;
    printf("%d * %d = %d\n", num, num1, num * num1);
    num = num + 1;
    num1 = num1 - 1;
    printf("%d * %d = %d\n", num, num1, num * num1);
    num = num + 1;
    num1 = num1 - 1;
    printf("%d * %d = %d\n", num, num1, num * num1);
    return 0;
}
```

在程序中使用变量时,不要把注意力放在这个变量代表哪个数,而应该是这个变量起什么作用,应该怎么用;
在对一个变量进行调整的时候,应该描述它的调整规律而不是直接把调整结果赋值给变量;

# 操作符
* /表示除,结果为整数;15 / 6 = 2
* %表示取余;15 % 6 = 3

```
/*
 * 操作符练习
 * */
#include <stdio.h>
int main() {
    printf("15 / 6 is %d\n", 15 / 6);    //2
    printf("15 %% 6 is %d\n", 15 % 6);    //3
    /* 注意如果在双引号里打印出一个%,还需要在%之间再加一个% */
    return 0;
}
```

练习
在屏幕打印
54321
5432
543
54
5

```
/*
 * 练习,在屏幕打印54321到5
 * */
#include <stdio.h>
int main() {
    int num = 54321;
    printf("%d\n", num);
    num = num / 10;
    printf("%d\n", num);
    num = num / 10;
    printf("%d\n", num);
    num = num / 10;
    printf("%d\n", num);
    num = num / 10;
    printf("%d\n", num);
    int num1 = 54321;
    printf("%d\n", num1);
    return 0;
}
```

在屏幕打印
54321
4321
321
21
1

```
/*
 * 变量练习
 * */
#include <stdio.h>
int main() {
    int num = 54321, num1 = 10000, num2 = 10;
    printf("%d\n", num);
    num = num % num1;
    num1 = num1 / num2;
    printf("%d\n", num);
    num = num % num1;
    num1 = num1 / num2;
    printf("%d\n", num);
    num = num % num1;
    num1 = num1 / num2;
    printf("%d\n", num);
    num = num % num1;
    num1 = num1 / num2;
    printf("%d\n", num);
    return 0;
}
```

# 变量的交换
* 方式1,借助中间变量备份其他变量的值;
    + int a = 1; b = 2;
    + int c;
    + c = a; //先将a中保存的值备份一下
    + a = b; //a中存放b的值;
    + b = c; //将备份的a的值赋值给b;
* 方式2,使用数学运算方式实现两个变量值的交换;
    + int a = 1, b = 2;
    + a ^= b;
    + b ^= a;
    + a ^= b;

在屏幕打印
12345
12435
14235

```
/*
 * 变量练习
 * */
#include <stdio.h>
int main() {
    int num = 1, num1 = 2, num2 = 3, num3 = 4, num4 = 5, temp;
    printf("%d%d%d%d%d\n", num, num1, num2, num3, num4);
    temp = num2;
    num2 = num3;
    num3 = temp;
    printf("%d%d%d%d%d\n", num, num1, num2, num3, num4);
    temp = num1;
    num1 = num2;
    num2 = temp;
    printf("%d%d%d%d%d\n", num, num1, num2, num3, num4);
    return 0;
}
```

```
/*
 * 变量内容交换练习
 * */
#include <stdio.h>
int main() {
    int num = 3, num1 = 7;
    int num2 = 0;
    printf("交换前:\n");
    printf("num 是 %d\n", num);
    printf("num1 是 %d\n", num1);
    num2 = num; //借助中间变量num2
    num  = num1;
    num1 = num2;
#if 0
    num = num + num1; //注意有可能会溢出
    num1 = num - num1;
    num = num - num1;
#endif
    printf("交换后:\n");
    printf("num 是 %d\n", num);
    printf("num1 是 %d\n", num1);

    //最高效的方式如下 位操作
    num ^= num1;        //num变为与原来的num和num1都有关系的中间变量
    num1 ^= num;        //num1实现交换
    num ^= num1;        //num实现交换
    printf("交换后:\n");
    printf("num 是 %d\n", num);
    printf("num1 是 %d\n", num1);
    return 0;
}
```

我们在编程的时候一定要注意,计算机的实现方式可能跟我们看到的完全不是一回事;
我们要学会剖析和分解问题,先把问题抽象再具体化;
抽象成过程和方法论,具体化为每一个实现方式和细节;

# scanf()标准函数
scanf()标准函数可以把用户在键盘上输入的一个数字直接记录在某个存储位置中. 

用变量表示存储位置只是一种方式,每个存储位置有一个专门的编号,不同存储位置的编号不同,这个编号叫做变量存储空间的地址. 
地址是另外一种表示存储位置的方法.
在变量前面加上&可以获得变量的存储空间的地址,获得地址的方法不止此一种. 

scanf()使用注意事项
* 为了使用scanf()标准函数需要把stdio.h合并到当前文件中. 
* 在scanf()标准函数中,必须使用地址表示存储位置,不可以直接使用变量.
* 不要在scanf()标准函数中使用"\n";
* scanf()双引号中除了占位符以外的内容,用户必须在键盘上原样输入. 
* scanf()可以一次读入多个数据,用户输入不同数据时要使用空格或换行符隔开. 

```
/*
 * scanf标准函数演示
 * */
#include <stdio.h>
int main() {
    int num = 0, num1 = 0;
    printf("please input 2 integer:");
    scanf("%d%d", &num, &num1);    //scanf里面不可以加\n
    // 用户需输入:
    // num 空格或回车 num1再回车
    printf("num = %d, num1 = %d\n", num, num1);
    return 0;
}
```

键盘缓冲区,输入缓冲区

```
/*
 scanf演示
  */
#include <stdio.h>
int main() {
    int num = 0, num1 = 0;

    printf("请输入一个数:\n");
    scanf("%d", &num);
    printf("输入的数据是:%d\n", num);

    scanf("%*[^\n]");    /* 清除缓存中的垃圾 */
    scanf("%*c");

    printf("请输入一个数:\n");
    scanf("%d", &num1);
    printf("输入的数据是:%d\n", num1);
    return 0;
}
```

使用scanf读取用户输入时,一次错误的输入可能导致后面的所有读取工作失败,使用下面两条语句可以把输入缓冲区中下一个\n之前的所有内容(包括这个\n)都清除: 
* scanf("%*[^\n]");//读取所有不是换行符的字符(丢弃),然后返回;
* scanf("%*c");//读入一个字符(上一条语句没有读的\n),但不保存在变量中;

注意上两条语句的顺序,可以清空输入缓冲区的内容;

```
/*
 * scanf函数练习
 * */
#include <stdio.h>
int main() {
    int price0 = 0, num = 0, num1 = 0;

    printf("请输入单价:");
    scanf("%d", &price0);
    scanf("%*[^\n]");
    scanf("%*c");
    printf("单价是:%d\n", price0);

    printf("请输入数量:");
    scanf("%d", &num);
    printf("数量是:%d\n", num);
    num1 = price0 * num;
    printf("总价是:%d * %d = %d\n", price0, num, num1);
    return 0;
}
```

```
/*
 * 输入缓冲区练习
 */
#include <stdio.h>
int main() {
    int num = 0, flag = 0;
    do {
        if (flag) {
            scanf("%*[\n]");
            scanf("%*c");
        }
        flag = 1;
        printf("请输入一个数字:");
    } while (!scanf("%d", &num));

    printf("while is end\n");
    /*
     * scanf()出错时返回0(成功接收到的个数);
     * scanf("%d", &num);
     */
    scanf("%*[^\n]");
    scanf("%*c");

    printf("num是%d\n", num);
    printf("请输入一个数字:");
    scanf("%d", &num);
    printf("num是%d\n", num);
    return 0;
}
```

# 数据类型
## 字符型
字符型是一种数据类型,用 char 表示;

字符型包含256个不同的字符,例如'a','+','?'等,其实所有字符数据在计算机中都是采用整数表示的. 

字符数据有字符和数据两种身份. 
ASCII码表中已经列出字符数据两种身份之间的对应关系;
字符身份和数据身份两个一一对应, 如: 
* 'a' ---110 0001-----(0x61)------97
* 'A' ---100 0001-----(0x41)------65
* '0' ----------------------------48

所有字符数据分成两组,每组128个不同字符. 
* 其中一组两个身份之间的对应关系在所有计算机环境下都一样,这组数据身份是从0到127;
* 另外一组两个身份之间的对应关系在不同计算机环境下有区别,这组数据的数字身份可能是从128到255,也可能是从-1到-128;因此最好不要用字符的数据身份. 

不可打印字符printf出来是看不见的;
在ASCII码表中所有的英文字母连续排列,但大写与小写之间不连续;
* 字母a的数字身份最小,字母z的数字身份最大.
* 所有阿拉伯数字字符之间也是连续排列的,并且'0'的数字身份最小,'9'的数字身份最大. 
    + 't'-'a' 等于 'T'-'A'
    + '3'-'0' 等于 'd'-'a'
    + 'D'-'d' 等于 'A'-'a'
* 字符常量是用单引号括起来的单个字符(如'a'表示一个ASCII值为97的一个字符常量);
* 字符串常量是用双引号扩起来任意个字符(如"a"表示一个字符串常量a),
* 不加任何修饰的可以表示一个变量(特殊字符除外)(如 char a; int b;);

```
ASCII值   字符
0         NULL//不可见
48        '0' //字符0
65        'A' //字符A
97        'a' //字符a
```

无符号字符类型也是一种数据类型,用 unsigned char 表示;
无符号字符类型同样包含了字符类型中的256个不同字符,
这种类型中所有字符的数字身份固定从0到255;

## 输出控制字符
```
'\n'   换行字符 /* 不会覆盖原来的内容,指示切换到下一行 */
'\r'   回车字符,让输出位置回到行首,如printf("abc\rde");的输出结果是dec
'\t'   制表符
'\\'   代表\,以避免与\n混淆
'\''   代表'
'\"'   代表"
```

```
/*
 * 输出控制字符
 * */
#include <stdio.h>
int main() {
    printf("abcde\n");    //abcde
    printf("abc\rde\n");    //dec
    printf("ab\tcd\n");    //ab    cd
    printf("abc\td\n");    //abc   t
    printf("\\\n\'\n\"\n");
    //       \
    //       '
    //       "
    return 0;
}
```

## 短整型
* 短整数数据类型可以记录65536个不同的整数,范围是从-32768到+32767; 短整数类型用 short 表示;
* 无符号短整数数据类型也包括65536个不同的整数,范围是从0到65535; 无符号短整数类型用 unsigned short 表示;

## 长整型
* 长整数类型包括2的32次方个不同的整数,范围从负的2的31次方到正的2的31次方减1; 用 long 或 long int 表示;
* 无符号长整数类型也包括2的32次方个不同的整数,范围是从0到2的32次方减1; 用 unsigned long 或 unsigned long int 表示;

一个字节(byte)有8个二进制位(bit)
* 2的10次方叫1Kb(1024个字节byte);
* 2的20次方叫1Mb;
* 2的30次方叫1Gb;
* 2的40次方叫1Tb;
* 2的50次方叫1Pb;

在我们的计算机环境里整数类型和长整数类型一样,整数类型用int表示;
无符号整数类型和无符号长整数类型一样,用 unsigned int 表示;
在整数数字后面加u表示这个数字是无符号类型的数字, 例如8u;

## 小数类型
C语言中可以使用两种数据类型表示小数点数据
* 单精度浮点类型用 float 表示
* 双精度浮点类型用 double 表示

单精度浮点类型所能记录的小数点后面的位数少;

程序中带小数点的数字默认是 double 类型的数据,在数字后面加一个小写f表示 float 类型的数据,如1.6f;

# 练习
1. 在屏幕上打印如下内容: 
    1
    21
    321
    4321
    54321
```
/*
 * 在屏幕上打印如下内容:
 *     1
 *     21
 *     321
 *     4321
 *     54321
 */
#include <stdio.h>
int main() {
    int num = 54321, num1 = 0, num2 = 10;
    num1 = num % num2;
    num2 = num2 * 10;
    printf("%d\n", num1);
    num1 = num % num2;
    num2 = num2 * 10;
    printf("%d\n", num1);
    num1 = num % num2;
    num2 = num2 * 10;
    printf("%d\n", num1);
    num1 = num % num2;
    num2 = num2 * 10;
    printf("%d\n", num1);
    num1 = num % num2;
    printf("%d\n", num1);
    return 0;
}
```
2. 编程计算用户给定数字的相反数

```
/*
 * 编程计算用户给定的相反数
 */
#include <stdio.h>
int main() {
    long int num, num1 = 0;
    printf("请输入一个数字:");
    scanf("%d", &num);
    scanf("%*[^\n]");
    scanf("%*c");
    num1 = num;
    num = 0 - num;
    printf("%d的相反数是:%d\n", num1, num);
    return 0;
}
```

3. 编程计算用户给定矩形的面积(用户指定长和宽)
```
/*
 * 作业要求
 * 编程计算用户给定的矩形的面积(用户指定长和宽)
 */
#include <stdio.h>
int main() {
    int length = 0, width = 0, area = 0;
    printf("请输入矩形的长和宽:");
    scanf("%d%d", &length, &width);
    printf("矩形的长为:%d\n", length);
    printf("矩形的宽为:%d\n", width);
    area = length * width;
    printf("矩形的面积为:%d\n", area);
    return 0;
}
```

4. 编程完成温度转换
华氏温度=2*摄氏度+32

```
/*
 * 作业要求
 * 编程完成温度转换
 * 华氏温度=2*摄氏度+32
 */
#include <stdio.h>
int main() {
    int sheshi = 0;
    float huashi = 0.0;
    printf("请输入摄氏温度:");
    scanf("%d", &sheshi);
    printf("输入的摄氏温度为:%d\n", sheshi);
    huashi = sheshi * 1.8 + 32;
    printf("华氏温度为:%lg\n", huashi);
    return 0;
}
```

