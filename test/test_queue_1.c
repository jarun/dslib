/*
 * Test cases for queue
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

#include <common.h>
#include <queue.h>

int current_log_level = DEBUG;

/* Test queue */
int main(void)
{
	int count = 5;
	int arr[5] = {0, 1, 2, 3, 4};
	int *val;

	queue_p queue = get_queue();

	while (count) {
		if (enqueue(queue, &arr[--count]) == FALSE) {
			log(ERROR, "enqueue failed!\n");
			destroy_queue(queue);
			return -1;
		}

		log(DEBUG, "enqueued: arr[%d] = %d\n", count, arr[count]);
	}

	count = 5;

	while (count) {
		val = dequeue(queue);
		if (val)
			log(DEBUG, "dequeued: arr[%d] = %d\n", --count, (int)*val);
		else
			log(ERROR, "dequeue failed!\n");
	}

	destroy_queue(queue);

	return 0;
}
