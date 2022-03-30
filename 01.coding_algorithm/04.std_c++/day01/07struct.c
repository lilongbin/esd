/*
 * struct.c
 */
#include <stdio.h>
struct Emp {
};
int main() {
	printf("%d\n", sizeof(struct Emp)); //0
	struct Emp emp;
	printf("%d\n", sizeof emp); //0 //变量可以省略小括号
}
