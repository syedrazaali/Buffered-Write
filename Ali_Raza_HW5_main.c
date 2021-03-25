/**************************************************************
* Class:  CSC-415-02 Fall 2020
* Name: Raza Ali
* Student ID: 917648503
* Project: Assignment 5 – Buffered I/O
*
* File: Bierman_Robert_HW5_main.c
*
* Description: Driver file to demo b_io - b_write
*
**************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "b_io.h"

#define LENBUF 75

int main (int argc, char * argv[])
	{
	int fd, ofd;
	char * buf;
	int readCount;
	int lineCount = 1;
	
	//Need a command line argument
	if (argc != 3)
		{
		printf("Usage: driver input_filename output_filename\n");
		return (-1);
		}
		
	// open the file specified - abort if failed	
	fd = b_open (argv[1], O_RDONLY);
	if (fd < 0)
		{
		printf ("Error opening file %s\n", argv[1]);
		return (-2);
		}
	
	// open the file specified - abort if failed	
	ofd = b_open (argv[2], O_WRONLY | O_CREAT | O_TRUNC);
	if (ofd < 0)
		{
		printf ("Error opening file %s\n", argv[2]);
		b_close(fd);
		return (-5);
		}
	
	// Allocate our read buffer - abort if fails
	// Adding 2 to allow for addition of null terminator	
	buf = malloc (LENBUF + 2);
	
	if (buf == NULL) 
		{
		printf ("Failed to malloc the buffer needed\n");
		b_close (fd);
		b_close (ofd);
		return (-3);
		}
	
	int index = 0;
	int hasHardBreak;
	do
		{
		// Read LENBUF characters
		readCount = b_read(fd, buf + index, LENBUF - index);
		readCount = readCount + index;
		
		buf[readCount] = '\0';		//Add null terminator to buffer
		hasHardBreak = 0;			//No Hardbreak
		if (readCount < LENBUF)
			{
			b_write (ofd, buf, readCount);	//write remaining buffer
			break;
			}
		
		for ( int n = readCount - 1; n > 0; n--)
			{
			if (buf[n] == '\n') // found hard break
				{
				b_write (ofd, buf, n+1);		//Write out that lineCount
				
				index = readCount - (n+1);
				memcpy (buf, buf+n+1,index);
				hasHardBreak = 1;			// Hardbreak
				break;
				}
			}
		if (hasHardBreak == 0)
			{
			for ( int n = readCount - 1; n > 0; n--)
				{
				//line has no hard breaks - soft break it	
				if (buf[n] == ' ')  // found break
					{
					// force the break to be a new line
					buf[n] = '\n';
					b_write (ofd, buf, n+1);		//Write out that lineCount
				
					index = readCount - (n+1);
					memcpy (buf, buf+n+1,index);
					break;
					}
				}
			}
		
		// print the line number and line
	//	printf ("%03d: %s\n", lineCount, buf);
		++lineCount;
		}	while (readCount == LENBUF); // when not equal we must be done
	b_close (ofd);	
	b_close (fd);
	free (buf);
	buf = NULL;
	return 0;
	}
