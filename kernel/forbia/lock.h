/*
 * Copyright (C) 2020 synthels <synthels.me@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef LOCK_H
#define LOCK_H

typedef volatile int mutex_t;

#define declare_lock(name) static mutex_t name = 0

/* Acquire lock */
void lock(mutex_t *mutex);

/* Release lock */
void unlock(mutex_t *mutex);

#endif