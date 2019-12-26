线程的状态
线程的同步技术
综合案例基于TCP的多人聊天室



回顾
	多线程编程;由于多进程过于耗费资源,因此网络应用使用多进程会严重影响效率,多线程是网络应用中不可缺少的技术;
	线程原理;使用CPU时间片技术实现的伪并行;针对时间点来说线程是串行,针对时间段来说线程是并行;
	什么时候使用线程技术;在一个进程内部需要同时执行两个以上任务时;
	线程的编程API(函数);
		pthread_create()//创建线程,线程执行第三个参数对应的函数,并把第四个参数传给函数;
		pthread_join()//可以让一个线程等待另外一个线程,并获取结束线程的返回值;
		pthread_exit()//结束线程
		pthread_self()//获取当前线程的ID;
	
	程序员笔试题中经常出现一些边边角角的东西,但开发时又严禁使用这些;
//数组做参数,按指针来处理;

今天

线程执行轨迹
	同步方式(非分离状态)
		等待新创建线程结束;
		只有当pthread_join()函数返回时,创建的线程才终止,才可释放自己占用的系统资源;
	异步方式(分离状态)
		未被其他线程等待,自己运行结束即可终止线程并释放系统资源(自爆);
		返回值是无法被pthread_join()拿到的;
	还有一种既不pthread_join()也不分离的,没人回收;

线程的状态:分离和非分离
线程同步技术:互斥量/互斥锁/信号量;

线程虽然共享了资源,但还是有自己的栈区内存;
线程资源的回收有以下三种可能
	1.非分离的线程:调用了pthread_join(),资源在pthread_join()函数结束时立即回收;(有人监护);
	2.分离的线程;线程一结束立即回收资源;(不设监护人,自觉型的);
	3.非分离的线程,也没有被pthread_join();资源不一定何时回收;应尽量避免;(没人看护,也不够自觉);

	因此,线程最好处于分离状态或被pthread_join(),资源才会正常回收;
	如果把线程设置为join状态,只需在创建线程以后调用pthread_join()即可;
	如果把线程设置为分离状态,只需在创建线程以后调用pthread_detach(id)即可;处于detach状态的线程pthread_join()函数无效;
/*
 * pthread_detach()函数演示
 */
#include <stdio.h>
#include <pthread.h>
void *task(void *p) {
	int i;
	for (i = 0; i < 10; i++) {
		printf("task:%d\t", i);
		usleep(10000);
	}
}
int main() {
	pthread_t id;
	pthread_create(&id, 0, task, 0);
	pthread_detach(id);
	//分离状态join无效;
	/* pthread_join(id, 0); */
	/* 主线程不会等待id线程结束; */
	int i;
	for (i = 0; i < 10; i++) {
		printf("main:%d\n", i);
		usleep(10000);
	}
	printf("The program over\n");
	return 0;
}
	如果先pthread_join()再pthread_detach()的话,detach是无效的废代码,因为pthread_join()会等待线程结束,这是pthread_join()已经没有意义了;


线程同步技术
	由于同一个进程内部的多进程共享进程的资源,因此可能出现共享数据的冲突;解决方案就是把有可能出现冲突的代码改成排队串行(部分串行);
	这种技术叫线程同步技术,线程同步技术有很多种,Uc主要有三种
	1.互斥量
	2.信号量
	3.条件变量
	注意线程同步技术会大幅降低效率,因此要尽可能少用,但是如果有共享数据冲突的代码,一定要使用;尽量并行,会引起冲突的地方串行;

互斥量又叫互斥锁(mutex);
	POSIX规范中已经解决了多线程共享数据冲突的问题,方案就是互斥量
	互斥量有固定的使用套路,步骤
	1.声明互斥量
		pthread_mutex_t lock;
	2.初始化互斥量
		pthread_mutex_init(&lock, NULL);
	或在声明的同时用宏初始化:
		pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
		这个宏只能在声明时使用,不能单独赋值;
		pthread_mutex_t lock;
	    lock = PTHREAD_MUTEX_INITIALIZER;//错误;
		先声明再赋值,错误;
	3.给共享数据冲突的代码加锁(串行代码的开始);
		pthread_mutex_lock(&lock);
	4.访问共享数据(的代码);
	5.解锁(串行代码的结束);
		pthread_mutex_unlock(&lock);
	6.释放互斥量的资源
		pthread_mutex_destroy(&lock);
int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);
	第1个参数是互斥量的指针;
	第2个参数是互斥量的属性;
	成功返回0,失败返回错误码;
int pthread_mutex_destroy(pthread_mutex_t *mutex);
	成功返回0,失败返回错误码;
/*
 * 互斥量代码演示
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
char *data[5];			//字符串数组//BSS段,全0,0是空指针
int num = 0;			//现在存了几个名字
//1声明互斥量
pthread_mutex_t lock;
void *task(void *p) {
	//3上锁
	pthread_mutex_lock(&lock);
	printf("task running\n");
	//4访问共享数据
	data[num] = (char *)p;	//存入人名
	usleep(10000);	
	//如果不加锁,线程1/2会同时访问,造成数据冲突
	num++;			//人数+1
	//5解锁
	pthread_mutex_unlock(&lock);
}
int main() {
	//2初始化互斥量
	pthread_mutex_init(&lock, NULL);
	data[num] = "liubei";
	num++;
	//创建2个线程
	pthread_t id1, id2;
	pthread_create(&id1, 0, task, "zhangfei");
	pthread_create(&id2, 0, task, "guanyu");
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	//6销毁互斥量的资源;
	pthread_mutex_destroy(&lock);
	int i;
	for (i = 0; i < num; i++) {
		printf("%s\n", data[i]);
	}
	return 0;
}

信号量
	信号量也能解决共享数据的冲突问题
	信号量自身就是一个计数器,可以控制访问共享资源的最大的进程/线程总数;
	信号量的计数如果是1,效果等价于互斥量;
	信号量不属于POSIX,需要使用semaphore.h;使用步骤和互斥量非常相似,但函数不同;
信号量的使用步骤
	1.声明信号量	sem_t sem;
	2.初始化		sem_init(&sem, 0, 1);
		第1个参数是信号量的地址;
		第2个参数表示用于进程还是线程,0表示线程;
		第3个参数就是计数的最大值;1等价于互斥量;
	3.计数-1操作	sem_wait(&sem);
	4.访问共享资源;
	5.计数+1操作	sem_post(&sem);
	6.释放信号量的资源 sem_destroy(&sem);

练习
	把互斥量的代码改成信号量,看看效果;
/*
 * 信号量代码演示
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h> //添加新的头文件
char *data[5];			//字符串数组//BSS段,全0,0是空指针
int num = 0;			//现在存了几个名字
//1声明信号量
sem_t sem;
void *task(void *p) {
	//3上锁
	sem_wait(&sem);
	printf("task running\n");
	//4访问共享数据
	data[num] = (char *)p;	//存入人名
	usleep(10000);	
	//如果不加锁,线程1/2会同时访问,造成数据冲突
	num++;			//人数+1
	//5解锁
	sem_post(&sem);
}
int main() {
	//2初始化信号量
	sem_init(&sem, 0, 1); //最大计数为1,即互斥;
	data[num] = "liubei";
	num++;
	//创建2个线程
	pthread_t id1, id2;
	pthread_create(&id1, 0, task, "zhangfei");
	pthread_create(&id2, 0, task, "guanyu");
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	//6销毁互斥量的资源;
	sem_destroy(&sem);
	int i;
	for (i = 0; i < num; i++) {
		printf("%s\n", data[i]);
	}
	return 0;
}

	如果遇到共享冲突,尽量使用互斥量;
	因为信号量主要是用于控制访问共享数据的线程总数;
	互斥量和条件变量还可以结合使用;而且互斥量是官方支持的;
/*
 * 数据库连接池计数控制模拟
 */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
//1 声明信号量
sem_t sem;
void *task(void *p) {
	int i = (int)p;
	printf("第%2d个线程申请数据库连接\n", i);
	//3 计数-1
	sem_wait(&sem);		//计数-1
	//4 使用数据库
	printf(">>第%2d个线程成功连接\n", i);
	srand(time(0));
	int r = rand() % 8;	//0-7s
	sleep(r);
	printf("第%2d个线程释放连接<<\n", i);
	//5 计数+1
	sem_post(&sem);		//计数+1
}
void f_exit() {
	//6 释放信号量
	sem_destroy(&sem);
	signal(SIGINT, SIG_DFL);
	printf("system going down ...\n");
	pthread_exit(NULL); //退出主线程;
}
int main() {
	printf("<Ctrl+C> to exit");
	signal(SIGINT, f_exit);
	//2 初始化信号量
	sem_init(&sem, 0, 10);
	int i = 0;
	for (i = 0; i < 15; i++) {
		pthread_t id;
		pthread_create(&id, 0, task, (void *)(i + 1));
	}
	while (1) ;
	return 0;
}

	使用线程同步技术一定要避免死锁现象;
		pthread_mutex_t lock1,lock2;
		线程a:
			lock(&lock1);
			...
				lock(&lock2); //阻塞
				...
				unlock(&lock2);
			unlock(&lock1);
		线程b:
			lock(&lock2);
			...
				lock(&lock1); //阻塞
				...
				unlock(&lock1);
			unlock(&lock2);
		如果在这种情况下线程a和线程b并行了;将会导致死锁;
	
	死锁在复杂应用中,不能绝对避免,但有避免死锁的基本原则
		正向上锁,反向解锁,不要回调;
		A -> B -> C -> D -> E; //不要回调;
		A -> B -> C -> D -> A; //回调就会死锁;
面试题
	写一个死锁,然后解锁;
思路:
	先使用两个信号量,形成死锁;然后对任意信号量使用计数+1使其解锁;
/*
 * 写一个死锁,然后解锁;
 */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
sem_t sem1, sem2;
void *task1(void *p) {
	sem_wait(&sem1);
	sleep(1);
	printf("task1 running ...\n");
	sem_wait(&sem2);
	printf("sem1 operating sem2 ...\n");
	sleep(3);
	sem_post(&sem2);
	sem_post(&sem1);
	printf("task1 over\n");
	/*
	 * lock sem1
	 * ...... 
	 *     lock sem2
	 *     ...... 
	 *     unlock sem2
	 * unlock sem1
	 */
}
void *task2(void *p) {
	sem_wait(&sem2);
	sleep(1);
	printf("task2 running ...\n");
	sem_wait(&sem1);
	printf("sem2 operating sem1 ...\n");
	sleep(3);
	sem_post(&sem1);
	sem_post(&sem2);
	printf("task2 over\n");
	/*
	 * lock sem2
	 * ...... 
	 *     lock sem1
	 *     ...... 
	 *     unlock sem1
	 * unlock sem2
	 */
}
void func_unlock() {
	//解锁
	sem_post(&sem2);
	/* 或sem_post(&sem1); */
	printf("\nhas been unlocked\n");
}
int main() {
	signal(SIGINT, func_unlock);
	printf("<Ctrl+C> to unlock\n");
	sem_init(&sem1, 0, 1);
	sem_init(&sem2, 0, 1);
	pthread_t id1, id2;
	pthread_create(&id1, 0, task1, NULL);
	pthread_create(&id2, 0, task2, NULL);
	pthread_join(id1, NULL);
	pthread_join(id2, NULL);
	sem_destroy(&sem1);
	sem_destroy(&sem2);
	return 0;
}
	
	

综合案例
	基于TCP的聊天室,支持多个用户同时登录服务器进行聊天;
socket编程,可以做一对一的通信也可以做一对多的通信;
做一对多的通信,必然要用到多线程,保证多个客户端同时登录服务器进行聊天;

具体实现
客户端:
	1.用户需要先登录,登录时需要输入一个昵称,昵称不需要判断是否重复;
	2.用户登录后要连接服务器,进入聊天室;
	3.用户可以输入聊天信息,也可以接收别人的聊天信息;
	4.用户可以输入一个特殊的单词,代表退出聊天室;
服务器端:
	1.启动服务器开放网络端口;
	2.等待客户端的连接,每连接上一个客户端就启动一个线程;
	3.在线程中与客户端进行交互,交互的过程:
	如果有客户端登录/退出/提交聊天,服务器都要把这些信息发给所有的客户端;
---------------------------------
TCP通信步骤:
服务器端:
	1.创建socket;
	2.准备网络通信地址;struct sockaddr_in
	3.绑定socket和网络通信地址;bind()
	4.设置监听;listen();
	5.等待客户端连接;accept();
	6.读写;
	7.
客户端:
	1.创建socket;
	2.准备网络通信地址;服务器的IP和端口;
	3.连接服务器connect();
	4.读写;
	5.
----------------------------------
TCP通信相关函数:
send()/recv()
int_send(sockfd,buf,len,flags);
参数flags表示发送的方式,如果flags置零和write一样;
recv函数的返回值:
	>0	//返回接收到的字节数;
	<0	//接收出错;
	=0	//表示TCP的另一端主动断开连接;


