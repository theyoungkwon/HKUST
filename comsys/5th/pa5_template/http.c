//-----------------------------------------------------------
// 
// SSE2030: Introduction to Computer Systems (Fall 2013)
//
// Skeleton code for PA #5
//
// Nov. 18, 2013
//
// Authors : Dong Hyun, Song (songdh418@gmail.com)
// 				   Woo-Yeong Jeong
//
// Computer Systems Laboratory
// Sungkyunkwan University
//
//-----------------------------------------------------------

#include <sys/socket.h>
#include <sys/types.h>
#include <strings.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "http.h"

char*
make_http_header(int http_status, int content_type, int content_length)
{
	const char* str_status = NULL;
	const char* str_type = NULL;
	char http_header[BUF_SIZE] = {0,}; // enoughly long string for header

	switch (http_status)
	{
		case NO_ERR: // file is existed
		{
			str_status = STATUS_200;
			break;
		}
		case ERR_NO_FILE: // file is not existed
		{
			str_status = STATUS_404;
			break;
		}
		case ERR_NOT_ALLOWED: // access fail
		{
			str_status = STATUS_403;
			break;
		}
		default:
		{
			return NULL;
		}
	}

    switch (content_type)
    {
        case TYPE_HTML:
            {
                str_type = "text/html";
                break;
            }
        case TYPE_JPEG:
            {
                str_type = "image/jpeg";
                break;
            }
        case TYPE_PNG:
            {
                str_type = "image/png";
                break;
            }
        case TYPE_GIF:
            {
                str_type = "image/gif";
                break;
            }
        case TYPE_UNKNOWN:
            {
                str_type = "text/plain";
                break;
            }
        default:
            return NULL;
    }

    snprintf(http_header, sizeof(http_header), "HTTP/1.0 %s\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n", str_status, str_type, content_length);

	return strdup(http_header);	
}

char *
make_report (int connections, long long int sent_bytes,
						 int html, int jpeg, int png, int gif, int unknown)
{
	char report[1000];

	snprintf(report, sizeof report,
					"<html><body><h2>Status Report for webserver2</h2><p>\n"
					"%d connections / %lld bytes sent</p>\n"
					"<p><table border=1 cellspacing=1><tr>\n"
					"<th>html</th> <th>jpeg</th> <th>png</th>"
					"<th>gif</th> <th>unknown</th></tr>\n<tr>"
					"<td>%d</td> <td>%d</td> <td>%d</td> <td>%d</td> <td>%d</td>\n"
					"</tr></table></p></body></html>\n",
					connections, sent_bytes, html, jpeg, png, gif, unknown);
	
	return strdup(report);
}
