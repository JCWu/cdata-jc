#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "cdata_ioctl.h"

int main(void)
{
	int fd;

	fd = open("/dev/cdata", O_RDWR);
	ioctl(fd, IOCTL_EMPTY, 0);
	ioctl(fd, IOCTL_SYNC, 0);
	close(fd);
}
