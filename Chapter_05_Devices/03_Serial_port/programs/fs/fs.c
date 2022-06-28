#include <kernel/errno.h>
#include <kernel/features.h>
#include <arch/interrupt.h>
#include <arch/processor.h>
#include <api/stdio.h>
#include <lib/string.h>
#include <stdio.h>
#include <api/prog_info.h>
int fs(){


	int fd = open("file:disk1", O_CREAT | O_WRONLY, 0);
	kprintf("fd=%d\n", fd);
	int retval1 = write(fd, "xxxxxxxxxxxaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaX", 53);
	kprintf("retval=%d\n", retval1);
	retval1 = close(fd);
	/*int fd2 = open("file:disk2", O_CREAT | O_RDWR, 0);
	kprintf("fd=%d\n", fd2);
	int retval2 = write(fd2, "aaa", 3);
	kprintf("retval=%d\n", retval2);
	retval1 = close(fd);

	kprintf("closed retval=%d\n", retval1);

	kprintf("fd=%d\n", fd2);
	char buff2[12];
	retval2 = read(fd2, buff2, 12);
	kprintf("retval=%d\n", retval2);
	printf("\n");
	kprintf("disk 2 buff=%s\n", buff2);*/

	fd = open("file:disk1", O_RDONLY, 0);
	kprintf("fd=%d\n", fd);
	char buff[54];
	retval1 = read(fd, buff, 54);
	kprintf("retval=%d\n", retval1);
	printf("\n");
	kprintf("disk 1 buff=%s\n", buff);
	
	retval1 = close(fd);
	//retval2 = close(fd2);

	return 0;

}
