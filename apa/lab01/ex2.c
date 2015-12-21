#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define BUF_SIZ 100
#define MAX_STR 20


FILE * openFile (char * filename, char * mode);
void readFile (FILE *finn, FILE *fout, char* str1, char* str2);

int 
main (int argc, char *argv[])
{
	FILE *finn, *fout;
	char str1 [MAX_STR+1], str2[MAX_STR+1];
	
	if (argc != 5)
	{
		fprintf (stderr, "Wrong number of arguments.\n");
		fprintf (stderr, "Usage: %s <string1> <file1> <string2> <file2>\n", argv[0]);
		exit(1);
	}
	
	strcpy(str1, argv[1]);
	strcpy(str2, argv[3]);
	
	finn = openFile (argv[2], "r");
	fout = openFile (argv[4], "w");
	
	readFile (finn, fout, str1, str2);

	fclose (finn);
	fclose (fout);	
	
	return 0;
}

// open file with error check
FILE * openFile (char * filename, char * mode)
{
	FILE *fd;
	
	fd = fopen (filename, mode);
	if (fd == NULL)
	{
		if (strcmp(mode, "r") == 0)
		{
			fprintf (stderr, "Input file error\n");
			exit(1);
		} else if (strcmp(mode, "w") == 0)
		{
			fprintf (stderr, "Output file error\n");
			exit(1);
		}
	}
	return fd;
}

void readFile (FILE * finn, FILE * fout, char *str1, char *str2)
{
	char buffer[BUF_SIZ+1];
	
	while ( fgets(buffer, BUF_SIZ, finn) != NULL)
	{
		printf ("%s", buffer);
		
	}
}

void substituteString (char *original, char *old, char *new)
{
	int i, len;
	char new[BUF_SIZ]
	
	for (i = 0; i < BUF_SIZ; i += 1)
	{
		if (original[i] == old[i])
		{
								
		}	
	}
	
}

int substitute (char *original, char *old, char *new, int start)
{
	int i,j;
	
	char new_str[BUF_SIZ];
	for (i = 0; i < count; i += 1)
	{
		new_str[i]=original[i]
		if (i = start)
		{	
			for (j = 0; j < strlen(old); j += 1)
			{
				new_str[j+i] = new[j];
			}
			
		}
	}
