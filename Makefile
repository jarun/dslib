CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3 -fPIC -I$(INCLUDE)

SRC = $(wildcard src/*.c)
OBJS = $(SRC:%.c=%.o)
INCLUDE = $(PWD)/include
TARGET = libds.so.1.0

BINDIR = ./bin
HEADERDIR = /usr/include/dslib
DESTDIR = /usr/lib

all: $(TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BINDIR)
	gcc -shared -Wl,-soname,libds.so.1 -o $(BINDIR)/$(TARGET) $(OBJS)
	strip $(BINDIR)/$(TARGET)

.PHONY: test clean
test:
	cd test && $(MAKE)

clean:
	rm -f $(OBJS) $(BINDIR)/$(TARGET)
	rm -rf $(BINDIR)
	# clean test files too
	cd test && $(MAKE) clean

distclean: clean
	rm -f *~

install:
	install -m755 -d $(HEADERDIR)
	install -m644 -t $(HEADERDIR) include/*.h
	install -o root -m 644 $(BINDIR)/$(TARGET) $(DESTDIR)/
	ln -sf $(DESTDIR)/$(TARGET) $(DESTDIR)/libds.so.1
	ln -sf $(DESTDIR)/libds.so.1 $(DESTDIR)/libds.so

uninstall:
	rm -rf $(HEADERDIR)
	rm -f $(DESTDIR)/libds.so $(DESTDIR)/libds.so.1 $(DESTDIR)/$(TARGET)
