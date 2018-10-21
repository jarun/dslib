CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3 $(INCLUDE)

INCLUDE = -I/usr/include/dslib
LIBS = -lds

all:
	$(CC) $(CFLAGS) $(INCLUDE) -o test_avl_1 test_avl_1.c $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDE) -o test_bst_1 test_bst_1.c $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDE) -o test_dlist_1 test_dlist_1.c $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDE) -o test_queue_1 test_queue_1.c $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDE) -o test_stack_1 test_stack_1.c $(LIBS)
	$(CC) $(CFLAGS) $(INCLUDE) -o avl_Thread_Safe_Test avl_Thread_Safe_Test.c $(LIBS)

.PHONY: clean
clean:
	rm -f test_avl_1 test_bst_1 test_dlist_1 test_queue_1 test_stack_1
