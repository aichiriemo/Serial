
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <termios.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "open_port.c"
#include "set_com_config.c"



//
#define BUFF_SIZE 1024

int main(void)
{
	int fd;
	char buff[BUFF_SIZE];

	if( (fd = open_port(0) )<0)
	{
		perror("open_port");
		return -1;
	}

	if(set_com_config(fd,115200,8,'N',1)<0)
	{
		perror("set_com_config");
		return -1;
	}

	do
	{
		printf("input some world(enter 'quit' to exit)");
		memset(buff,0,BUFF_SIZE);
		
		if(fgets(buff,BUFF_SIZE,stdin)==NULL)
		{
			perror("fgets");
			break;
		}
		write(fd,buff,strlen(buff));
	}
	while(strncmp(buff,"quit",4));
	close(fd);
	return 0;
}
