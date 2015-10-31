CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fPIC

TARGET = libds.so.1.0
DESTDIR = /usr/lib

objects = log.o dlist.o tree.o queue.o stack.o bfs.o dfs.o

all: $(TARGET)

$(TARGET): $(objects)
	gcc -shared -Wl,-soname,libds.so.1 -o $(TARGET) $(objects)

.PHONY: clean
clean:
	-rm -f $(objects) $(TARGET)

distclean: clean
	rm -f *~

install:
	install -o root -m 644 $(TARGET) $(DESTDIR)/
	ln -sf $(DESTDIR)/$(TARGET) $(DESTDIR)/libds.so.1
	ln -sf $(DESTDIR)/libds.so.1 $(DESTDIR)/libds.so

uninstall:
	rm -f $(DESTDIR)/libds.so $(DESTDIR)/libds.so.1 $(DESTDIR)/libds.so.1.0
