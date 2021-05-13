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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Module interface
 */

#ifndef MODULE
#define MODULE

#include <stdint.h>
#include <kernel.h>
#include <memory/init_module/init_module.h>

#define MODULES 3

#define MODULE_EXPECTING_NEXT_WRITE 1
#define MODULE_WRITE_OK 0
#define MODULE_NO_WRITE -1
#define MODULE_NO_READ -2
#define MODULE_TOO_MANY_WRITES -3
#define MODULE_TOO_LITTLE_WRITES -4
#define MODULE_DISABLED -5

/* --- */
#define MODULE_WRITE_END return 0

/* --- */
#define MODULE_WRITE 0
#define MODULE_COMMIT 1

#include <modules/keyboard/keyboard.h>
#include <modules/sound/speaker/speaker.h>
#include <modules/time/PIT.h>

struct module_interface {
	/*
	 * Param 1: data
	 * Param 2: commit: 1 for commit, anything else for just write
	 *
	 * Passing data to the driver requires that you set
	 * the second parameter to the be anything other than 1 every time you
	 * write to the driver and want to pass extra data again later
	 * and 1 when you want to commit the data and start a new
	 * session with the driver. Will return MODULE_EXPECTING_NEXT_WRITE if it expects another write
	 * (will return MODULE_TOO_MANY_WRITES if you write more times than the driver supports before committing)
	 * (will return MODULE_TOO_LITTLE_WRITES if you don't write enough times before committing)
	 */
	int (*write) (uint32_t, int);
	/* Param 1: data */
	void (*read) (uint32_t *);
	int enabled;
	int event; /* Set if an event is raised (SHOULD ONLY BE SET BY THE DRIVER & CLEARED BY THE KERNEL) */
};

/* Init drivers */
void init_modules(void);

#endif
