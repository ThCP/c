/**
	This program reads from the device created in the kernel until it reaches the end of the file.
	The device being read is called "my_device" and is set in the "/dev/ folder of the file system.
	
	Riccardo Cappuzzo
	
	Sysprog 04
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>		/* open */
#include <unistd.h>		/* close */

#define DEVICE_NAME "/dev/my_device" //path of the device
#define BUFLEN 1024 // buffer used to read from the device

int 
main (int argc, char *argv[])
{
	int fd; 
	int count = 0; // read bytes
	char buffer [BUFLEN + 1];
	
	fd = open (DEVICE_NAME, O_RDONLY); // open the file in read mode
	
	// error check
	if (fd < 0)
	{
		printf ("ERROR: It was not possible to open the device file %s\n", DEVICE_NAME);
		return -1;
	}
	
	// read from the device and print on stdout
	while ((count = read(fd, buffer, BUFLEN) ) > 0)
	{
		fputs(buffer, stdout);
	}
	
	// close the file
	close (fd); 
	
	return 0;
}
