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
 *
 * Malloc
 */

/* NOTE: Free bytes don't do much as of now and kfree is useless. They might get removed soon */

#include "malloc.h"

/* Offset for each mmap entry */
static size_t mmap_offs[256];

/* __new mutex lock */
static mutex_t __new_mutex = 0;

static uint32_t *__new(size_t n)
{
	acquire_mutex(&__new_mutex);
	int entry_found = 0;
	size_t i = 0;
	mmap_entry_t *mmap = mm_get_kernel_mmap();
	for (; i < mm_get_kmmap_size(); i++) {
		if (mmap[i].type == MEMORY_AVAILABLE) {
			/* 
			 * Check how much of this entry we
			 * have already used
			 */
			if (mmap->length_low - mmap_offs[i] >= n) {
				entry_found = 1;
				mmap_offs[i] += n;
				break;
			}
		}
	}

	if (!entry_found)
		panic("__new: Ran out of memory!");

	release_mutex(&__new_mutex);
	return (uint32_t *) mmap[i].base_addr_low + mmap_offs[i];
}

void *kmalloc(size_t n)
{	
	/* Align n to 32 bits */
	if (n % 32 != 0) {
		if (n <= 32) {
			n = 32;
		} else {
			n = 32 * ((n / 32) + 1);
		}
	}

	return (void *) __new(n);
}