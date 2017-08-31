#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h> 
#include <errno.h> 

#define PAGE_SIZE 4096

int main(int argc , char *argv[])
{
	int fd;
	int i;
	unsigned char *p_map;

	//���豸
	fd = open("/root/test/mmap/data2",O_RDWR|O_CREAT|O_TRUNC);
	if(fd < 0)
	{
		printf("open fail:%s\n",strerror(errno));
		exit(1);
	}

	char *msg="Hello World\n";
	write(fd,msg,strlen(msg));

	//�ڴ�ӳ��
	p_map = (unsigned char *)mmap(0, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED,fd, 0);
	if(p_map == MAP_FAILED)
	{
		printf("mmap fail\n");
		goto here;
	}  

	//��ӡӳ�����ڴ��е�����
	printf("mapped msg:%s\n",p_map);

here:
	munmap(p_map, PAGE_SIZE);
	return 0;
}
