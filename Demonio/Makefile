CC=gcc
CFLAGS=-Wall -g
SRCS=inotify_test.c inotify_utils.c event_queue.c copia.c
OBJS=inotify_test.o inotify_utils.o event_queue.o copia.o

.c.o:
	$(CC) $(CFLAGS) -c $<

all: inotify_test

inotify_test: $(OBJS)
	$(CC) $(CFLAGS) inotify_utils.o inotify_test.o event_queue.o copia.o -o inotify_test

clean:
	rm -f $(OBJS) *.bak inotify_test
