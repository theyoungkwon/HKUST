//-----------------------------------------------------------
// 
// SSE2030: Introduction to Computer Systems (Fall 2013)
//
// Skeleton code for PA #4 and #5
//
// October 18, 2013.
// Author : Dong Hyun, Song (songdh418@gmail.com)
// Sungkyunkwan University
//
//-----------------------------------------------------------

#include <sys/socket.h>
#include <sys/types.h>
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

	int len = -1;
	int send = 0;
	int listenfd, connfd, caddrlen, n;
	int port = 1234;
	char default_msg[] = "DEFAULT";
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
		write(1, "socket fail\n", 12);
		return 1;
	}

	bzero((char*)&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(port);

	if (bind(listenfd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0)
	{
		write(1, "bind fail\n", 10);
		return 2;
	}

	if (listen(listenfd, 5) < 0)
	{
		write(1, "listen fail\n", 12);
		return 3;
	}
	caddrlen = sizeof(caddr);

	if ((connfd = accept(listenfd, (struct sockaddr*)&caddr, (socklen_t *)&caddrlen)) < 0)
	{
		write(1, "accept fail\n", 12);
		return 4;
	}

	http_header = make_http_header(-1, TYPE_UNKNOWN, 7);
	while(http_header[++len]); // length of http_header

	if (http_header == NULL)
	{
		write(1, "make_http_header returns NULL\n", 30);
		return 5;
	}

	// do nothing:
	// ignore client's request
	do {
		n = read(connfd, buffer + send, 10);
		send += n;
		if (buffer[send-4] == '\r' && buffer[send-3] == '\n' &&
				buffer[send-2] == '\r' && buffer[send-1] == '\n')
			break;
	} while (send <= 1024);

	// sending <HTTP header> and <EMPTY LINE>
	send = 0;
	do {
		send += write(connfd, http_header + send, len - send);
	} while (send < len); // until write is done

	// sending <HTTP body>:
	// "default"
	send = 0;
	do {
		send += write(connfd, default_msg + send, 7 - send);
	} while (send < 7);

	free(http_header);
	close(connfd);

	return 0;
}

