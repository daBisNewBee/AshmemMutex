#include "com_example_ashmem_JNIInterface.h"
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), creat() */
#include <linux/ashmem.h>
#include <sys/mman.h>
#include <android/log.h>
#include <stdio.h>
#include    <stdlib.h>
#include    <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <errno.h>

#define LOGD(...) 	\
	{				\
	__android_log_print(ANDROID_LOG_DEBUG, "JNI", __VA_ARGS__);	\
	}

int g_fd2ashmem;
pthread_mutex_t* g_mutex;

JNIEXPORT jint JNICALL Java_com_example_ashmem_JNIInterface_initAndGetFd2Ashmem
  (JNIEnv *env, jclass thiz){

    jint fd = open("/dev/ashmem",O_RDWR);
    ioctl(fd,ASHMEM_SET_NAME,"MyAshmemName");
    ioctl(fd,ASHMEM_SET_SIZE,4096);
    g_fd2ashmem = fd;
    LOGD("initAndGetFd2Ashmem open fd:%d",g_fd2ashmem);
    return fd;
}


//创建共享的mutex
void init_mutex(int fd)
{
	int ret,zero=0;

	g_mutex=(pthread_mutex_t*)mmap(NULL, sizeof(pthread_mutex_t), PROT_READ|PROT_WRITE, MAP_SHARED,fd==0?g_fd2ashmem:fd,0);

	if( MAP_FAILED==g_mutex )
	{
		LOGD("mmap:%d",errno);
		LOGD("strerror:%s",strerror(errno));
		return;
	}

	if(fd!=0){
		// 与Linux下表现一样，二次初始化会导致共享锁失败
		LOGD("RemoteService don`t init_mutex ");
		return;
	}

	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	ret=pthread_mutexattr_setpshared(&attr,PTHREAD_PROCESS_SHARED);
	if( ret!=0 )
	{
		LOGD("init_mutex pthread_mutexattr_setpshared");
		return;
	}
	pthread_mutex_init(g_mutex, &attr);
}

JNIEXPORT void JNICALL Java_com_example_ashmem_JNIInterface_doOperaNow
  (JNIEnv *env, jclass thiz){
	init_mutex(0);
	int ret=pthread_mutex_lock(g_mutex);
	if( ret!=0 )
	{
		LOGD("child pthread_mutex_lock");
		return;
	}
	//测试是否能够阻止父进程的写入
	sleep(2);
	LOGD("this is process a.doing AAAAAAAA");
	sleep(1);
	LOGD("this is process a.doing BBBBBBBB");
	sleep(1);
	LOGD("this is process a.doing CCCCCCCC");
	sleep(1);
	LOGD("this is process a.doing DDDDDDDD");

	ret=pthread_mutex_unlock(g_mutex);
	if( ret!=0 )
	{
		LOGD("child pthread_mutex_unlock");
	}

    munmap(g_mutex, sizeof(pthread_mutex_t));
}


JNIEXPORT void JNICALL Java_com_example_ashmem_JNIInterface_doOperaLater
  (JNIEnv *env, jclass thiz, jint fd){

	init_mutex(fd);
	sleep(2);// 保证process a先行
	int ret=pthread_mutex_lock(g_mutex);
	if( ret!=0 )
	{
		LOGD("child pthread_mutex_lock");
	}
	LOGD("this is process b.doing AAAAAAAA");
	sleep(1);
	LOGD("this is process b.doing BBBBBBBB");
	sleep(1);
	LOGD("this is process b.doing CCCCCCCC");
	sleep(1);
	LOGD("this is process b.doing DDDDDDDD");

	ret=pthread_mutex_unlock(g_mutex);
	if( ret!=0 )
	{
		LOGD("child pthread_mutex_unlock");
	}

	munmap(g_mutex, sizeof(pthread_mutex_t));

}


