//-----------------------------------------------------------
// 
// SSE2030: Introduction to Computer Systems (Fall 2013)
//
// Skeleton code for PA#4
//
// October 18, 2013.
// Author : Dong Hyun, Song (songdh418@gmail.com)
// Sungkyunkwan University
//
//-----------------------------------------------------------

#ifndef _HTTP_H
#define _HTTP_H

enum
{
	TYPE_HTML,
	TYPE_JPEG,
	TYPE_PNG,
	TYPE_GIF,
	TYPE_UNKNOWN
};

#define STATUS_200 "200 OK"
#define STATUS_404 "404 Not Found"
#define STATUS_403 "403 Forbidden"

#define NO_ERR (0)
#define ERR_NO_FILE (-1)
#define ERR_NOT_ALLOWED (-2)

#define BUF_SIZE (1024*4)
#define DEFAULT_WEB_PAGE "index.html"

char*
make_http_header(int http_status, int content_type, int content_length);
void print_pid(int pid);

#endif /* _HTTP_H */

