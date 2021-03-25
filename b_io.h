/**************************************************************
* Class:  CSC-415-0# Summer 2020
* Name:
* Student ID:
* Project: Assignment 2 – Buffered I/O
*
* File: b_io.h
*
* Description:
*
**************************************************************/

#ifndef _B_IO_H
#define _B_IO_H
#include <fcntl.h>

int b_open (char * filename, int flags);
int b_read (int fd, char * buffer, int count);
int b_write (int fd, char * buffer, int count);
void b_close (int fd);

#endif

