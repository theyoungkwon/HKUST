#-----------------------------------------------------------
# 
# SSE2030: Introduction to Computer Systems (Fall 2013)
#
# Skeleton code for PA #4
#
# October 23, 2013.
# Jinyong Ha
# Sungkyunkwan University
#
#-----------------------------------------------------------


CC		= gcc
CFLAGS	= -g -Wall
LDFLAGS	=
RM		= rm

CSRCS	= webserver.c http.c
SUBCSRCS	= Makefile
TARGET	= webserver
OBJECTS	= $(CSRCS:.c=.o)

ifeq (tar,$(firstword $(MAKECMDGOALS)))
ifneq (2, $(words $(MAKECMDGOALS)))
  $(error ERROR: No studentID given. usage: "$$ make tar 2012310000")
endif
  TAR_ARGS := $(wordlist 2, 2, $(MAKECMDGOALS))
  $(eval $(TAR_ARGS):;@:)
endif


all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@
tar:
	tar zcvf $(TAR_ARGS).tar.gz $(CSRCS) $(SUBCSRCS)
clean:
	$(RM) -f $(OBJECTS) $(TARGET) *~

