/*
 * Test cases for AVL tree
 *
 * Author: Arun Prakash Jana <engineerarun@gmail.com>
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

#define nSearch 20

#include <common.h>
#include <avl.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void searchTh(void *info);

void sigInt (int sig);

void sigTSTP(int sig);


int current_log_level = INFO;
avl_pp_S head;

int main(int argc, char **argv)
{

	signal(SIGINT, sigInt);
	signal(SIGTSTP,sigTSTP);
	bool stop = TRUE;
	head = init_avl_S();


	int len = 100000;
	//int arr[len];

	for (int count = 0; count < len; count++) {

		if (insert_avl_node_S(head, (int)random()%10000) == FALSE) {
			log(ERROR, "Insertion failed.\n");
			destroy_avl(head.avlRoot);
			return 0;
		}
	}

	pthread_t tid;
	printf("iniziano i search \n");

	for (int count = 0; count < nSearch; count++) {
		int *i=malloc(sizeof(int));
		*i=count;
		pthread_create(&tid,NULL,searchTh,i);
	}
	while (1) pause();
	return 0;
}

void searchTh(void *info)
{
	int id=*(int *)info;
	while (1) {
		search_BFS_avl_S(head, (int) random() % 10000, TRUE);
		printf("Search %d finish tree Search\n", id);
		usleep(1000000*random()%100);   //attesa casuale tra 1 e 100 ms
	}
	free(info);

}

void sigInt (int sig)
{
	printf("\n\t####sigInt recive\n\n");
	lockWriteSem(head.semId);
	printf("\n\t####sigInt lock Write preso\n");

	return;

}

void sigTSTP(int sig)
{
	printf("\n\t****sigTSTP recive\n\n");
	unlockWriteSem(head.semId);
	printf("\n\t****sigTSTP unlock Write libero\n");

	return;
}