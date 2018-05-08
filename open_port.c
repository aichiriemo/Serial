#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <termios.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_COM_NUM 3

int open_port(int com_port)
{
	int fd;//串口终端文件描述符
	char *dev[]={"/dev/ttyUSB0","/dev/ttyUSB1","/dev/ttyUSB2"};

	if( (com_port<0) || (com_port>MAX_COM_NUM))
	{
		printf("端口号错误");
		return -1;
	}
	
	fd =open(dev[com_port],O_RDWR|O_NOCTTY|O_NDELAY);

	if(fd<0)
	{
			perror("open serial port");
			return -1;
	}
	
	if(fcntl(fd,F_SETFL,0)<0)
	{
			perror("fcntl F_SETF\n");
			return -1;
	}
	if(isatty(STDIN_FILENO)==0)
	{
		perror("standard input is not a terminal device\n");
		return -1;
	}

	return fd;
}
