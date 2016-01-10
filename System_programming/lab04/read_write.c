/**
	This program asks the user whether to write on the device or to read from it.
	The device being written upon is called "my_device" and is set in the "/dev/ folder of the file system.
	
	I used two functions in order to make the code more readable.
	
	Riccardo Cappuzzo
	
	Sysprog 04
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>		/* open */
#include <unistd.h>		/* close */
#include <string.h>

#define DEVICE_NAME "/dev/my_device"
#define BUFLEN 1024

void reading (void);
void writing (void);

int 
main (int argc, char *argv[])
{
	int choice;
	
	printf("Welcome! Choose the operation you want to perform:\n1: Read\n2: Write\n");
	scanf("%d", &choice);
	
	switch (choice)	{
		case 1:
			printf("Reading.\n");
			reading();
			break;
		case 2:
			printf("Writing.\n");
			writing();
			break;
		default:
			printf("Wrong choice, exiting.\n");
			break;
	}
	
	return 0;
}

void reading (void)	{
	int fd;
	int count = 0;
	char buffer [BUFLEN + 1];
	
	fd = open (DEVICE_NAME, O_RDONLY);
	
	if (fd < 0)
	{
		printf ("ERROR: It was not possible to open the device file %s\n", DEVICE_NAME);
		exit(EXIT_FAILURE);			
	}
	
	while ((count = read(fd, buffer, BUFLEN) ) > 0)
	{
		fputs(buffer, stdout);
	}
	
	close (fd);
	
}

void writing (void) {
	int fd;
	char buffer[BUFLEN];
	
	fd = open (DEVICE_NAME, O_WRONLY);
	
	if (fd < 0)
	{
		printf ("ERROR: It was not possible to open the device file %s\n", DEVICE_NAME);
		exit(EXIT_FAILURE);
	}
	
	printf("Insert the line you want to write on the device.\n");
	scanf("%s", buffer);
	
	write(fd, buffer, strlen(buffer));

	close (fd);		
}
