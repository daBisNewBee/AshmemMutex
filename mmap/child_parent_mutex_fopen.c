#include    <stdio.h>  
#include    <stdlib.h>  
#include    <unistd.h>  
#include    <fcntl.h>  
#include    <sys/mman.h>  
#include    <pthread.h>  
#include <sys/types.h>
#include <sys/stat.h>

#define   FILE_MODE   (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

pthread_mutex_t* g_mutex;  
//创建共享的mutex  
void init_mutex(void)  
{  
    int ret;  
    //g_mutex一定要是进程间可以共享的，否则无法达到进程间互斥  
	int fd = open("tmp",O_RDWR|O_CREAT,FILE_MODE);
    g_mutex=(pthread_mutex_t*)mmap(NULL, sizeof(pthread_mutex_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);  
    if( MAP_FAILED==g_mutex )  
    {  
        perror("mmap");  
        exit(1);  
    }  
      
    //设置attr的属性  
    pthread_mutexattr_t attr;  
    pthread_mutexattr_init(&attr);  
    //一定要设置为PTHREAD_PROCESS_SHARED  
    //具体可以参考http://blog.chinaunix.net/u/22935/showart_340408.html  
    ret=pthread_mutexattr_setpshared(&attr,PTHREAD_PROCESS_SHARED);  
    if( ret!=0 )  
    {  
        perror("init_mutex pthread_mutexattr_setpshared");  
        exit(1);  
    }  
    pthread_mutex_init(g_mutex, &attr);  
}  
int main(int argc, char *argv[])  
{  
    init_mutex();  
    int ret;      
    pid_t pid;  
    pid=fork();  
    if( pid<0 )  
    {  
        perror("fork");  
        exit(1);  
    }  
    else if( 0==pid )  
    {  
        ret=pthread_mutex_lock(g_mutex);  
        if( ret!=0 )  
        {  
            perror("child pthread_mutex_lock");  
        }  
        //测试是否能够阻止父进程的写入  
		printf("this is child process.doing AAAAAAAA\n");
		sleep(1);
		printf("this is child process.doing BBBBBBBB\n");
		sleep(1);
		printf("this is child process.doing CCCCCCCC\n");
		sleep(1);
		printf("this is child process.doing DDDDDDDD\n");
		
        ret=pthread_mutex_unlock(g_mutex);    
        if( ret!=0 )  
        {  
            perror("child pthread_mutex_unlock");  
        }     
    }  
    else  
    {  
        sleep(2);//保证子进程先执行   
        ret=pthread_mutex_lock(g_mutex);  
        if( ret!=0 )  
        {  
            perror("father pthread_mutex_lock");  
        }  
		printf("this is parent process.doing AAAAAAAA\n");
		sleep(1);
		printf("this is parent process.doing BBBBBBBB\n");
		sleep(1);
		printf("this is parent process.doing CCCCCCCC\n");
		sleep(1);
		printf("this is parent process.doing DDDDDDDD\n");
        ret=pthread_mutex_unlock(g_mutex);    
        if( ret!=0 )  
        {  
            perror("father pthread_mutex_unlock");  
        }                 
    }  
    wait(NULL);  
    munmap(g_mutex, sizeof(pthread_mutex_t));  
}  
