
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <termios.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


int set_com_config(int fd,int baud_rate,\
				int data_bits, char parity, int stop_bits)
{
	struct termios new_cfg, old_cfg;
	int speed;

	if(tcgetattr(fd,&old_cfg)!=0)
	{
		perror("tcgetattr");
		return -1;
	}

	new_cfg = old_cfg;

	cfmakeraw(&new_cfg);

	new_cfg.c_cflag &= ~CSIZE;

	switch(baud_rate)
	{
		case 9600:
				speed = B9600;
				break;
		case 19200:
				speed = B19200;
				break;
		case 115200:
				speed = B115200;
				break;
		default: 
				speed = B115200;
				break;
	}
	
	cfsetispeed(&new_cfg,speed);
	cfsetospeed(&new_cfg,speed);

	switch(data_bits)
	{
		case 7:
				new_cfg.c_cflag |=CS7;
				break;
		case 8:
				new_cfg.c_cflag |= CS8;
				break;
		default:
				new_cfg.c_cflag |= CS8;
				break;

	}

	switch(parity)
	{
		default:
		case 'n':
		case 'N':
			new_cfg.c_cflag &= ~PARENB;
			new_cfg.c_cflag &= ~INPCK;
			break;
		case 'o':
		case 'O':
			new_cfg.c_cflag |= (PARODD|PARENB);
			new_cfg.c_cflag |= INPCK;
			break;
		case 'e':
		case 'E':
			new_cfg.c_cflag |= PARENB;
			new_cfg.c_cflag &= ~PARODD;
			new_cfg.c_cflag |= INPCK;
			break;
	}

	switch(stop_bits)
	{
		default:
		case 1:
				new_cfg.c_cflag &= ~CSTOPB;
				break;
		case 2:
				new_cfg.c_cflag |= CSTOPB;
				break;
	}

	new_cfg.c_cc[VTIME] = 0;
    new_cfg.c_cc[VMIN] =1;

	tcflush(fd, TCIFLUSH);	

	if((tcsetattr(fd,TCSANOW,&new_cfg))!=0)
	{
		perror("tcsetattr");
		return -1;
	}
	
	return 0;
}















