CC = gcc
CPP = g++
CFLAGS = -W -Wall -Werror -g
CPPFLAGS = -W -Wall -Werror -g

objects = log.o dlist.o tree.o

all: queue

queue: $(objects) queue.c
	gcc $(CFLAGS) -o queue queue.c $(objects)

.PHONY: clean
clean:
	-rm -f queue $(objects)

distclean: clean
	rm -f *~

# just for checkinstall
install: queue
	install -d ${DESTDIR}/usr/bin/
	install -g staff -o root ${<} ${DESTDIR}/usr/bin/
