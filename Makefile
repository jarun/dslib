CC = gcc
CPP = g++
CFLAGS = -Wall -Wextra -Werror -g
CPPFLAGS = -Wall -Wextra -Werror -g

objects = log.o dlist.o tree.o queue.o stack.o bfs.o

all: ds

ds: $(objects)
	gcc $(CFLAGS) -o ds main.c $(objects)

.PHONY: clean
clean:
	-rm -f ds $(objects)

distclean: clean
	rm -f *~

# just for checkinstall
install: stack
	install -d ${DESTDIR}/usr/bin/
	install -g staff -o root ${<} ${DESTDIR}/usr/bin/
