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
 * Main function
 */

#include "kmain.h"

/* Kernel main function */
void kmain(multiboot_info_t *info)
{
	/* Init tty */
	tty_init();

	printk("phiOS %s", KERNEL_VERSION_STRING);

	/* Set kernel mode */
	set_kernel_mode(TTY_MODE);

	/* Check if grub can give us a memory map */
	/* TODO: Detect manually */
	if (!(info->flags & (1<<6))) {
		panic("couldn't get memory map!");
	}

	/* Init mm */
	printk("\nMemory map:");
	kmem_init(info);

	/* Init page directory */
	init_paging();

	/* Init IDT */
	printk("\nIRQ info:");
	init_idt();

	/* Init all drivers */
	init_drivers();

	printk("\nWelcome! %uiMiB of RAM detected in total!",  (kmem_get_installed_memory() / 1048576) + 2);

	#ifdef BUILD_TESTS
		/* Start tests */
		/* TODO: Malloc tests do not work due to
		   the kernel memory space being too short */
		do_tests();
	#endif

	for(;;);
}
