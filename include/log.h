/*
 * A modular, level based log file implementation
 *
 * Author: Arun Prakash Jana <engineerarun@gmail.com>
 * Copyright (C) 2014 by Arun Prakash Jana <engineerarun@gmail.com>
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

#pragma once

#include <stdio.h>
#include <stdarg.h>

#define ERROR 0
#define INFO 1
#define DEBUG 2

#define log(level, format, ...) \
	debug_log(__FILE__, __func__, __LINE__, \
			level, format, ##__VA_ARGS__)

void debug_log(const char *file,
		const char *func,
		int line,
		int level,
		const char *format,
		...) __attribute__((__format__(printf, 5, 6)));
