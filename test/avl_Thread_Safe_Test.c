/*
 * Test cases for AVL-ThreadSafe tree
 *
 * Author: Emanuele Alfano <alfystar1701@gmail.com>
 * Copyright (C) 2015 by Arun Prakash Jana <engineerarun@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dslib.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * This demo works in posix, it create "nSearch" thread and him call forEver
 * "search_BFS_avl_S", with ctrl+c you send a lockWrite,
 * with ctrl+z you send unlockWrite
 *
 * The function must send in order:
 * 1° Lock-write
 * 2° Unlock-write
 *
 * Is also possible send different configuratio:
 * 1° Lock-write
 *      2° Lock-write
 *          3° Lock-write
 *          4° Unlock-write
 *      5° Unlock-write
 *  6° Unlock-write
 *  ...
 *
 * To end script type ctrl+\ (sigKill)
 *
 *
 * Is important to see that, when first writeLock arrive, search thread just at work
 * finish his work and finaly the write lock arrive
 */

#define nSearch 50

#include <common.h>
#include "avl.h"

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int current_log_level = DEBUG;
avl_pp_S head;

int n_nodeInsert;
int searchRange;
int writePending;

void *searchTh(void *info)
{
	int id = *(int *)info;
	int keySearch;
	int found;

	while (1) {
		keySearch = (int) random() % searchRange;

		found = search_BFS_avl_S(head, keySearch, TRUE);

		printf("TH-Search %d Search key %d and ret %d\n", id, keySearch, found);

		usleep(1000000*random()%100);   //random wait between 1 and 100 ms
	}
	free(info);

	return NULL;
}

void lockWriteSem_sig(int sig)
{
	writePending++;
	printf("\n\t****sigINT receive sig = %d; n°writePending = %d\n\n", sig, writePending);
	lockWriteSem(head.semId);
	printf("\n\t####sigInt lock Write TAKE\n");
}

void unlockWriteSem_sig(int sig)
{
	//note, if writePending = 0, this signal stay in wait until arrive one lockWriteSem_sig,
	//but the library wasn't design tu solve this!!! It work only if every Writer, on the Start lock the tree, and at the End unlock then.
	printf("\n\t#(sigTSTP) receive sig = %d\n\n", sig);
	unlockWriteSem(head.semId);
	writePending--;
	printf("\n\t#(sigTSTP) unlock Write; n°writePending = %d\n", writePending);
}

int main(void)
{

	signal(SIGINT, lockWriteSem_sig);
	signal(SIGTSTP, unlockWriteSem_sig);
	head = init_avl_S();

	n_nodeInsert = nSearch * 10;
	searchRange = n_nodeInsert * 2;


	for (int count = 0; count < n_nodeInsert; count++) {
		if (insert_avl_node_S(head, count, (int)random() % searchRange) == FALSE) {
			log(ERROR, "Insertion failed.\n");
			destroy_avl(head.avlRoot);
			return 0;
		}
	}
	print_avl_S(head);
	//sleep(20);  //to give time to see tree print

	pthread_t tid;

	printf("Start search Thread\n");
	for (int count = 0; count < nSearch; count++) {
		int *i = malloc(sizeof(int));
		*i =  count;
		pthread_create(&tid, NULL, searchTh, i);
	}
	while (1)
		pause();
	return 0;
}
