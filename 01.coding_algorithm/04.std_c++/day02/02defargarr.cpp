/*
 * 函数默认参数
 */
#include <iostream>
using namespace std;
void printArr(int *parr, unsigned int size = 5, char dis = ',');
int main() {
	int arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	printArr(arr, 3);
	printArr(arr);
	printArr(arr, 10);
	printArr(arr, 10, '$');
}
void printArr(int *parr, unsigned int size, char dis) {
	for (int i = 0; i <= size - 1; i++) {
		cout << parr[i];
		if (i == size - 1) {
			break;
		} else {
			cout << dis;
		}
	}
	cout << endl;;
}
