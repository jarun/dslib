CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3 -fPIC $(INCLUDE)

SRC = $(wildcard src/*.c)
OBJS = $(SRC:%.c=%.o)
INCLUDE = -I$(PWD)/include
TARGET = bin/libds.so.1.0

BINDIR = ./bin
DESTDIR = /usr/lib

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir $(BINDIR)
	gcc -shared -Wl,-soname,libds.so.1 -o $(TARGET) $(OBJS)
	strip $(TARGET)

.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(BINDIR)

distclean: clean
	rm -f *~

install:
	install -o root -m 644 $(TARGET) $(DESTDIR)/
	ln -sf $(DESTDIR)/$(TARGET) $(DESTDIR)/libds.so.1
	ln -sf $(DESTDIR)/libds.so.1 $(DESTDIR)/libds.so

uninstall:
	rm -f $(DESTDIR)/libds.so $(DESTDIR)/libds.so.1 $(DESTDIR)/libds.so.1.0
