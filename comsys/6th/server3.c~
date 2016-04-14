//-----------------------------------------------------------
// 2010311484
// KWON YOUNGDAE
// SSE2030: Introduction to Computer Systems (Fall 2013)
//
// Skeleton code for PA#4
//
// October 18, 2013.
// Author : Dong Hyun, Song (songdh418@gmail.com)
// Sungkyunkwan University
//
//-----------------------------------------------------------

#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "http.h"

#include <pthread.h>

#define MAXLINE (80)
#define MAXDATA 2048

void *network(void *args);
int port=1234;

char *mystrcat(char *a, const char *b){	//return (arrA+arrB)
	int i, j;
	for(i=0; i<1024; i++){
		if( *(a+i) == 0)
			break;
	}
	for(j=0; j<1024; j++){
		*(a+i+j) = *(b+j);
		if( *(b+j) == 0)
			break;
	}
	return a;
}

char *mystrcpy(char *a, const char *b){	//return (arrB)
	int j;
	for(j=0; j<1024; j++){
		*(a+j) = *(b+j);
		if( *(b+j) == 0)
			break;
	}
	return a;
}
char *mystrncpy(char *a, const char *b, size_t n){	//return (arrB) with length n
	int j;
	for(j=0; j<n; j++){
		*(a+j) = *(b+j);
	}
	*(a+j) = '\0';
	return a;
}

//find one char position from startpoint n
int myfindchar(const char* a, int n, const char b){	//if you can find 'b' in (arrA)
	int i;									//from n, return point i;
	for( i=(n+1); i<MAXDATA ; i++){				//if fail, return MAXDATA or
		if( *(a+i) == b)						//sizeof(arrA)
			return i;
	}
	return i;
}
int myfindchar2(const char* a, int n, const char b){	//if you can find 'b' reversely
	int i;							//(back to front) from n in (arrA), return point
	for( i=(n-1); i>0; i--){				//if fail, return 0;
		if( *(a+i) == b)
			return i;
	}
	return i;
}
int myfindtype(const char *b){		//check type, then return integer for the type
	if( (*(b)=='h')&&(*(b+1)=='t')&&(*(b+2)=='m')&&(*(b+3)=='l')&&(*(b+4)=='\0') ){
		return TYPE_HTML;
	}
	else if( (*(b)=='j')&&(*(b+1)=='p')&&(*(b+2)=='g')&&(*(b+3)=='\0') ){
		return TYPE_JPEG;
	}
	else if( (*(b)=='p')&&(*(b+1)=='n')&&(*(b+2)=='g')&&(*(b+3)=='\0') ){
		return TYPE_PNG;
	}
	else if( (*(b)=='g')&&(*(b+1)=='i')&&(*(b+2)=='f')&&(*(b+3)=='\0') ){
		return TYPE_GIF;
	}
	else{
		return TYPE_UNKNOWN;
	}
}

int main(int argc, char ** argv)
{
	struct hostent;
	struct sockaddr_in saddr, caddr;
	int listenfd, *connfdp, caddrlen;
	//pthread
	pthread_t tid;

	if (argc == 2 && argv[1] != NULL)
	{
		port = atoi(argv[1]);
	}

	if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		return 1;
	}

	bzero((char*)&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(port);

	if (bind(listenfd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0)
	{
		return 2;
	}
	
	if (listen(listenfd, 5) < 0)
	{
		return 3;
	}
	caddrlen = sizeof(caddr);
	while(1){
		connfdp = (int *)malloc(sizeof(int));
		if ((*connfdp = accept(listenfd, (struct sockaddr*)&caddr, (socklen_t *)&caddrlen)) < 0)
		{
			return 4;
		}
		pthread_create(&tid, NULL, network, connfdp);
	}
	close(listenfd);
	return 0;
}

void *network(void *args){
	int len=-1, send=0, n;
	char buffer[BUF_SIZE] = {0,};
	char* http_header; 
	//my new variable
	int point_url1=0, point_url2=0,pathname_len=-1,pathname_type_point1=0,pathname_type_point2=0;
	int status_code=0,content_type=0, content_length=0, out_fd=-1;
	struct stat st;
	char input_url[MAXLINE], pathname[MAXLINE];
	char pathname_type[5];
	char default_msg[] = "loading failed", default_pathname[]="index.html";

	int connfd = *( (int *)args );
	pthread_detach(pthread_self());
	free(args);
	
	char *home_dir=getenv("HOME_DIR");
	// read client request into buffer until there is '\r\n\r\n'
	do {
		n = read(connfd, buffer + send, 1024);
		send += n;
		if (buffer[send-4] == '\r' && buffer[send-3] == '\n' &&
		buffer[send-2] == '\r' && buffer[send-1] == '\n')
			break;
	} while (send <= 1024);
/////////////////////////////doing client request below///////////////////////////
	//separate path from request
	if( (point_url1 = myfindchar(buffer, 0, ' ')) ){
		point_url2 = myfindchar(buffer, point_url1, ' ');
		mystrncpy(input_url, (buffer+point_url1+1), (point_url2-point_url1-1));
	}
	if (!home_dir)
	{
		mystrcpy(pathname, input_url);
	}
	else{
		mystrcpy(pathname, home_dir);
		mystrcat(pathname, input_url);
	}
	//find content_type of pathname
	if( (input_url[0]=='/') && (input_url[1]=='\0') ){
		mystrcat(pathname, default_pathname);
	}
	
//	pathname_len = mystrlen(pathname);
	while(pathname[++pathname_len]);
	pathname_type_point1 = (myfindchar2(pathname, pathname_len, '.'));
	pathname_type_point2 = (myfindchar2(pathname, pathname_len, '/'));
	if( pathname_type_point1 > pathname_type_point2) {	//Normal position
		mystrcpy(pathname_type, (pathname + pathname_type_point1 + 1) );
		content_type = myfindtype(pathname_type);
		if( content_type == TYPE_UNKNOWN){
			status_code = ERR_NOT_ALLOWED;
			content_length = 14;	
		}	
		else{
		//find status_code of pathname
		if( (out_fd = open(pathname, O_RDONLY) ) < 0){		//error status
			//if(errno == ENOENT){
				status_code = (ERR_NO_FILE);
			//}
			if(errno == EACCES){
				status_code = (ERR_NOT_ALLOWED);
			}
			content_type = TYPE_UNKNOWN;
			content_length = 14;	//content_length of pathname in error status
							
		}
		//find content_length of pathname in normal status
		else{		//normal status
			status_code = (NO_ERR);
			stat(pathname, &st);	
			content_length = st.st_size;
			if( content_type == TYPE_UNKNOWN){
				status_code = ERR_NOT_ALLOWED;
				content_length = 14;
			}
		}
		
		}
	}
	else{
		content_type = TYPE_UNKNOWN;
		status_code = ERR_NOT_ALLOWED;
		content_length = 14;	
	}		

///////////////////////////////// sending <HTTP body>:////////////////////////
/////////////////////////////////////NORMAL///////////////////////////////
		http_header = make_http_header(status_code, content_type, content_length);	
		while(http_header[++len]); // length of http_header	
		send = 0;
		do {
			send += write(connfd, http_header + send, len - send);
		} while (send < len); // until write is done
		if((status_code == NO_ERR) && (content_type != TYPE_UNKNOWN ) ){	//"Normal"
			while( (n= read(out_fd, buffer, BUF_SIZE) ) >0){
				send =0;
				do{
					send += write(connfd, buffer+send, n-send);
				}while(send<n);
			}
		}
//////////////////////////////////////loading failed/////////////////////////
		else{		// "loading failed"
			send = 0;
			do {
				send += write(connfd, default_msg + send, content_length - send);
			} while (send < content_length);
		}
/////////////////////////////update_data/////////////////////////////////
	free(http_header);
	close(out_fd);
	close(connfd);
	return 0;
}
