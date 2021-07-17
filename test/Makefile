CC = gcc
CFLAGS = -Wall -Wextra -g -fsanitize=address,undefined $(INCLUDE)

#INCLUDE = -I/usr/include/dslib
#LIBS = -lds
#SRCDIR =

INCLUDE = -I../include
LIBS =
SRCDIR = ../src/*.c

all:
	$(CC) $(CFLAGS) $(INCLUDE) $(SRCDIR) -o test_avl_1 test_avl_1.c $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRCDIR) -o test_bst_1 test_bst_1.c $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRCDIR) -o test_dlist_1 test_dlist_1.c $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRCDIR) -o test_queue_1 test_queue_1.c $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRCDIR) -o test_stack_1 test_stack_1.c $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDE) $(SRCDIR) -o avl_Thread_Safe_Test avl_Thread_Safe_Test.c $(LIBS) -lpthread

.PHONY: clean
clean:
	rm -f test_avl_1 test_bst_1 test_dlist_1 test_queue_1 test_stack_1 avl_Thread_Safe_Test
