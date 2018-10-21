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

#include <stdlib.h>
#include "log.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#pragma once

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

