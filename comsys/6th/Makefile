#-----------------------------------------------------------
# 
# SSE2030: Introduction to Computer Systems (Fall 2013)
#
# Skeleton code for PA #6
#
# Dec. 2, 2013
#
# Woo-Yeong Jeong
# Computer Systems Laboratory
# Sungkyunkwan University
#
#-----------------------------------------------------------


CC		= gcc
CFLAGS		= -O2 -g -Wall -Werror
LDFLAGS		= -lpthread
RM		= rm
TAR		= tar

CSRCS		= server3.c http.c
SUBCSRCS	= Makefile
TARGET		= server3
OBJECTS		= $(CSRCS:.c=.o)

ifeq (tar,$(firstword $(MAKECMDGOALS)))
  TAR_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(TAR_ARGS):;@:)
endif

all: $(TARGET)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

tar:
	$(TAR) zcvf $(TAR_ARGS).tar.gz $(CSRCS) $(SUBCSRCS)

clean:
	$(RM) -f $(OBJECTS) $(TARGET) *~

