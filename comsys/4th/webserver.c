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

#define MAXLINE (80)
#define MAXDATA 2048
int mystrlen(char *a){		// ex) when "123", return value is 3
	int i;
	for(i=0; i<2048; i++){
		if( *(a+i) == '\0')
			break;
	}
	return i;
}

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
		if( *(b+j) == 0)
			break;
	}
	*(a+j) = '\0';
	return a;
}

void arrclear(char *a){	//make all element NULL
	int i;
	for(i =0; i<2048; i++){
		*(a+i) = 0;
	}
}

int mystrncmp(const char* a, const char* b, size_t n){ //if arrA and arrB are identical
	int i;								//for length n, return 0		
	for( i=0; i<n ; i++){
		if( *(a+i) > *(b+i) )
			return 1;
		if( *(a+i) < *(b+i) )
			return -1;
	}
	return 0;	
}
//find one char position from startpoint n
int myfindchar(const char* a, int n, const char b){	//if you can find 'b' in (arrA)
	int i;									//from n, return point i;
	for( i=(n+1); i<MAXDATA ; i++){				//if fail, return MAXDATA or
		if( *(a+i) == b)						//sizeof(arrA)
			return i;
		if(*(a+i) == '\0')
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
	char *html = "html", *jpeg = "jpg", *png = "png", *gif = "gif";
	if( mystrncmp(b, html, 5) == 0){
		return TYPE_HTML;
	}
	else if( mystrncmp(b, jpeg, 4) == 0){
		return TYPE_JPEG;
	}
	else if( mystrncmp(b, png, 4) == 0){
		return TYPE_PNG;
	}
	else if( mystrncmp(b, gif, 4) == 0){
		return TYPE_GIF;
	}
	else{
		return TYPE_UNKNOWN;
	}
}
void handler2 (int sig){		//handler 
	int child_status;
	pid_t pid;
	while( (pid = waitpid(-1, &child_status, WNOHANG) ) >0 ){
		print_pid(pid);
	}
}

int main(int argc, char ** argv)
{
	struct hostent;
	struct sockaddr_in saddr, caddr;
 
	int len = -1;
	int send = 0;
	int listenfd, connfd, caddrlen, n;
	int port = 1234;
	char default_msg[] = "loading fail";
	char buffer[BUF_SIZE] = {0,};
	char* http_header; 
	char* home_dir = getenv("HOME_DIR");
	//my new variable
	pid_t pid;
	int point_url1=0, point_url2=0, pathname_len=0, pathname_type_point1=0,pathname_type_point2=0;
	int status_code=0,content_type=0, content_length=0, type_check=0;
	int out_fd;
	struct stat st;
	char input_url[MAXLINE], pathname[MAXLINE];
	char pathname_type[5], default_path[]="/", default_pathname[]="index.html";
	signal (SIGCHLD, handler2);
	
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
	while(1){
		caddrlen = sizeof(caddr);
		if ((connfd = accept(listenfd, (struct sockaddr*)&caddr, (socklen_t *)&caddrlen)) < 0)
		{
			write(1, "accept fail\n", 12);
			return 4;
		}
		if( (pid=fork() ) == 0){		//child process
			close(listenfd);	
			// do nothing:
			// ignore client's request
			// read client request into buffer until there is '\r\n\r\n'
			do {
				n = read(connfd, buffer + send, 10);
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
				point_url1 = 0, point_url2 =0;
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
			if( mystrncmp(input_url, default_path, 2) == 0){		// input_url is "/"
				mystrcat(pathname, default_pathname);
			}
			pathname_len = mystrlen(pathname);
			pathname_type_point1 = (myfindchar2(pathname, pathname_len, '.'));
			pathname_type_point2 = (myfindchar2(pathname, pathname_len, '/'));
			if( pathname_type_point1 > pathname_type_point2) {	//Normal position
				mystrcpy(pathname_type, (pathname + pathname_type_point1 + 1) );
				content_type = myfindtype(pathname_type);
				if( content_type == TYPE_UNKNOWN){
					type_check=1;
				}	
				//find status_code of pathname
				if( (out_fd = open(pathname, O_RDONLY) ) < 0){		//error status
					if(errno == ENOENT){
						status_code = (ERR_NO_FILE);
					}
					if(errno == EACCES){
						status_code = (ERR_NOT_ALLOWED);
					}
					content_type = TYPE_UNKNOWN;
					content_length = 12;	//content_length of pathname in error status
										
				}
				//find content_length of pathname in normal status
				else{		//normal status
					status_code = (NO_ERR);
					stat(pathname, &st);	
					content_length = st.st_size;
					if( content_type == TYPE_UNKNOWN){
						status_code = ERR_NOT_ALLOWED;
						content_length = 12;
					}
				}
				if( type_check == 1){
					content_type = TYPE_UNKNOWN;
					status_code = ERR_NOT_ALLOWED;
					content_length = 12;
				}
			}
			else{
				content_type = TYPE_UNKNOWN;
				status_code = ERR_NOT_ALLOWED;
				content_length = 12;
				
			}		
////////////////make <HTTP header> status_code, content_type, content_length////////////////
			http_header = make_http_header(status_code, content_type, content_length);	
			while(http_header[++len]); // length of http_header
			if (http_header == NULL)
			{
				write(1, "make_http_header returns NULL\n", 30);
				return 5;
			}
//////////////////////// sending <HTTP header> and <EMPTY LINE> ////////////////////////
			send = 0;
			do {
				send += write(connfd, http_header + send, len - send);
			} while (send < len); // until write is done
			
/////////////////////// sending <HTTP body>:////////////////////////
			if((status_code == NO_ERR) && (content_type != TYPE_UNKNOWN ) ){	//"Normal"
				while( (n= read(out_fd, buffer, BUF_SIZE) ) >0){
					send =0;
					do{
						send += write(connfd, buffer+send, n-send);
					}while(send<n);
				}
			}
			else{		// "loading fail"
				send = 0;
				do {
					send += write(connfd, default_msg + send, content_length - send);
				} while (send < content_length);
			}
			free(http_header);
			close(out_fd);
			close(connfd);
			exit(0);
		}
		//parent process
		close(connfd);		//disconnect
	}
	return 0;
}
