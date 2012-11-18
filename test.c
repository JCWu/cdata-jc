#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "cdata_ioctl.h"

int main(void)
{
	int fd;
	pid_t child;

	child=fork();

	fd = open("/dev/cdata", O_RDWR);

	if(child != 0) { // Parent
	  write(fd,"ABCDE", 14);
	} else {	 // Child
	  write(fd,"12345", 14);
	}
	//ioctl(fd, IOCTL_EMPTY, 0);
	ioctl(fd, IOCTL_SYNC, 0);
	close(fd);
}
