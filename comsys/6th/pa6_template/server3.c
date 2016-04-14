//-----------------------------------------------------------
// 
// SSE2030: Introduction to Computer Systems (Fall 2013)
//
// Skeleton code for PA #6
//
// Dec. 2, 2013.
// Author : JYHa
// Sungkyunkwan University
//
//-----------------------------------------------------------

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <strings.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>

#include "http.h"

#define MAXLINE (80)

int
main(int argc, char ** argv)
{
	struct hostent;
	struct sockaddr_in saddr, caddr;
	struct stat statbuf;	
	
	int len = -1;
	int send = 0;
	int retval = 0;
	int i;
	int sent_bytes =0;
	int filefd;
	int read_bytes;
	int listenfd, connfd, caddrlen, n;
	int port = 1234;
	char path[1024]={0,};
	char buffer[BUF_SIZE] = {0,};
	char* http_header; 
	char* home_dir = getenv("HOME_DIR");
	
	if (!home_dir)
	{
		home_dir = getenv("PWD");
	}


	if (argc == 2 && argv[1] != NULL)
	{
		port = atoi(argv[1]);
	}

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		retval = write(1, "socket fail\n", 12);
		return 1;
	}

	bzero((char*)&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(port);

	if (bind(listenfd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0)
	{
		retval = write(1, "bind fail\n", 10);
		return 2;
	}

	if (listen(listenfd, 5) < 0)
	{
		retval = write(1, "listen fail\n", 12);
		return 3;
	}
	caddrlen = sizeof(caddr);
	while(1){
		if ((connfd = accept(listenfd, (struct sockaddr*)&caddr, (socklen_t *)&caddrlen)) < 0)
		{
			retval = write(1, "accept fail\n", 12);
			return 4;
		}
		
	for (i = 0 ; i < 1024 ; i++)
	{
		path[i] = home_dir[i];
		if (path[i] == '\0')
		{
			path[i] = '/';
			i++;
			path[i + 1] = '\n';
			break;
		}
	}
		send =0;

		do {
			n = read(connfd, buffer + send, 10);
			send += n;
			if (buffer[send-4] == '\r' && buffer[send-3] == '\n' &&
					buffer[send-2] == '\r' && buffer[send-1] == '\n')
				break;
		} while (send <= 1024);
	
	
		int j = 4;
		for ( ; i < 1024 ; i++,  j++)
		{
			path [i] = buffer[j];
			if ((buffer[j] == ' ') && (buffer[j + 1] == 'H'))
			{
				path[i] = '\0';
				break;
			}
		}

		filefd = open(path, O_RDONLY);
		if (filefd == -1)
		{
			printf("%d\n",errno);
			statbuf.st_size = 0;
		}
		else
			fstat(filefd, &statbuf);
		http_header = make_http_header(200, TYPE_UNKNOWN, statbuf.st_size);

		len = -1;
		while(http_header[++len]);
		if (http_header == NULL)
		{
			retval = write(1, "make_http_header returns NULL\n", 30);
			return retval;
		}


		send = 0;
		do {

			send += write(connfd, http_header + send, len - send);
		} while (send < len);

		sent_bytes = 0;
		if (filefd != -1)
		{
			do
			{
				read_bytes = read(filefd, buffer, 100);
				send = 0;	
				do {
					send += write(connfd, buffer + send, read_bytes - send);
				} while (send < read_bytes);
				sent_bytes += read_bytes;
			}while (sent_bytes < statbuf.st_size);

			free(http_header);
			close(connfd);
		}
	}
	return 0;
}

