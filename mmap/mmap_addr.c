#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h> 
#include <sys/types.h>
#include <sys/stat.h>

#define PAGE_SIZE 4096
#define   FILE_MODE   (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

unsigned char *p_map;

unsigned char* getMappedAddr(){

	int fd = open("tmp",O_RDWR|O_CREAT,FILE_MODE);
	if(fd<0){
		perror("open error");
		exit(1);
	}

	p_map = (unsigned char*)mmap(0,PAGE_SIZE,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(p_map == MAP_FAILED){
		perror("mmap");
		exit(1);
	}
	
	return p_map;
}

int main(void){

	int pid;

	pid = fork();
	if(pid<0){
		perror("fork");
		exit(1);
	}else if(pid == 0){
	// child
		unsigned char* addr = getMappedAddr();
		char *data = "123456789";
		memcpy(addr,data,strlen(data));
		munmap(p_map,PAGE_SIZE);
		printf("child process:%d write data end\n",getpid());
	}else{
	// parent
		sleep(2);
		unsigned char* addr2 = getMappedAddr();
		printf("addr2:%s in Process:%d\n",addr2,getpid());
		munmap(p_map,PAGE_SIZE);
	}

here:
	return 0;
}
