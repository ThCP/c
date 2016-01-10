/**
	This program writes on the device created in the kernel the string contained by the buffer.
	The device being written upon is called "my_device" and is set in the "/dev/ folder of the file system.
	
	Riccardo Cappuzzo
	
	Sysprog 04
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>		/* open */
#include <unistd.h>		/* exit */
#include <string.h>

#define DEVICE_NAME "/dev/my_device"
#define BUFLEN 1024

int 
main (int argc, char *argv[])
{
	int fd;
	char *buffer = "This is the message I want to write on the device.\n" ;
	
	fd = open (DEVICE_NAME, O_WRONLY); // open the device in write mode, the device is already present
	
	// error check
	if (fd < 0)
	{
		printf ("ERROR: It was not possible to open the device file %s\n", DEVICE_NAME);
		return -1;
	}
	
	write(fd, buffer, strlen(buffer)); // write on the device

	close (fd);	
	
	return 0;
}
