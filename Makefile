CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3 -fPIC $(INCLUDE)

SRC = $(wildcard src/*.c)
OBJS = $(SRC:%.c=%.o)
INCLUDE = -I$(PWD)/include
TARGET = libds.so.1.0

BINDIR = ./bin
DESTDIR = /usr/lib

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir $(BINDIR)
	gcc -shared -Wl,-soname,libds.so.1 -o $(BINDIR)/$(TARGET) $(OBJS)
	strip $(BINDIR)/$(TARGET)

test:
	cd test && $(MAKE)

.PHONY: clean
clean:
	rm -f $(OBJS) $(BINDIR)/$(TARGET)
	rm -rf $(BINDIR)
	# clean test files too
	cd test && $(MAKE) clean

distclean: clean
	rm -f *~

install:
	install -o root -m 644 $(BINDIR)/$(TARGET) $(DESTDIR)/
	ln -sf $(DESTDIR)/$(TARGET) $(DESTDIR)/libds.so.1
	ln -sf $(DESTDIR)/libds.so.1 $(DESTDIR)/libds.so

uninstall:
	rm -f $(DESTDIR)/libds.so $(DESTDIR)/libds.so.1 $(DESTDIR)/$(TARGET)
