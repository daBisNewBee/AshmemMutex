#include    <stdio.h>  
#include    <stdlib.h>  
#include    <unistd.h>  
#include    <fcntl.h>  
#include    <sys/mman.h>  
#include    <pthread.h>  
pthread_mutex_t* g_mutex;  
//���������mutex  
void init_mutex(void)  
{  
    int ret;  
    //g_mutexһ��Ҫ�ǽ��̼���Թ���ģ������޷��ﵽ���̼以��  
    g_mutex=(pthread_mutex_t*)mmap(NULL, sizeof(pthread_mutex_t), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);  
    if( MAP_FAILED==g_mutex )  
    {  
        perror("mmap");  
        exit(1);  
    }  
      
    //����attr������  
    pthread_mutexattr_t attr;  
    pthread_mutexattr_init(&attr);  
    //һ��Ҫ����ΪPTHREAD_PROCESS_SHARED  
    //������Բο�http://blog.chinaunix.net/u/22935/showart_340408.html  
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
        //�����Ƿ��ܹ���ֹ�����̵�д��  
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
        sleep(2);//��֤�ӽ�����ִ��   
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
