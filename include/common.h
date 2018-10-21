/*
 * Common header file for dslib
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

#include "log.h"

#pragma once

#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

/* Introduce boolean type */
#define TRUE 1
#define FALSE !TRUE

#define LEFT  0
#define RIGHT 1

typedef unsigned char bool;

/*=======================================================*/
/*      Syncronize for ThreadSafe APIs start here        */
/*=======================================================*/

enum semName {wantWrite=0,readWorking=1,writeWorking=2};

int semInit();

/*#######################################*/
/*   Lock/unlock for writers function    */
/*#######################################*/
int lockWriteSem(int semId);

int unlockWriteSem(int semId);

/*#######################################*/
/*   Lock/unlock for readers function    */
/*#######################################*/
int lockReadSem(int semId);

int unlockReadSem(int semId);

//semInfo print
void semInfo(int semId);


/*
The scheme of synchronization is easy: (i use system 5)
There are 3 semaphore: wantWrite,readWorking and writeWorking (last like mutex, and the first two are counter in fact)

READER:
If more than one read-funx(like search) need to read data it  will be wait until wantWrite!=0.
ATOMICALLY it add at readWorking +1, to start only if no one write are current at working.
After, ALL READER-funx can be work and finally decrease readWorking counter (this in concurrency).

WRITER:
to start it  add wantWrite +1, (to signal at new reader, it si necessary to waiting)
after the writers WAIT until all reader just at work finish.
then, writer-funx can lock writeWorking to write one at time (is a mutex),
enter in critic section, and at the end unlock writeWorking.
Finally decrement wantWrite -1, and finish.

*/
