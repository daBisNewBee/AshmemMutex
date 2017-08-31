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
//���������mutex  
void init_mutex(void)  
{  
    int ret,pshared=0;  
    //g_mutexһ��Ҫ�ǽ��̼���Թ���ģ������޷��ﵽ���̼以��  
	int fd = open("tmp",O_RDWR|O_CREAT,FILE_MODE);
	//int fd = open("/root/test/mmap/data2",O_RDWR|O_CREAT,FILE_MODE);
    g_mutex=(pthread_mutex_t*)mmap(NULL, sizeof(pthread_mutex_t), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);  
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
	int ret=pthread_mutex_lock(g_mutex);  
	if( ret!=0 )  
	{  
		perror("child pthread_mutex_lock");  
	}  
	//�����Ƿ��ܹ���ֹ�����̵�д��  
	printf("this is process a.doing AAAAAAAA\n");
	sleep(1);
	printf("this is process a.doing BBBBBBBB\n");
	sleep(1);
	printf("this is process a.doing CCCCCCCC\n");
	sleep(1);
	printf("this is process a.doing DDDDDDDD\n");

	ret=pthread_mutex_unlock(g_mutex);    
	if( ret!=0 )  
	{  
		perror("child pthread_mutex_unlock");  
	}     
      
    munmap(g_mutex, sizeof(pthread_mutex_t));  
	return 0;
}
