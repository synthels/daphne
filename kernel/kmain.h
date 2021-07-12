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

#ifndef KERNEL_INIT
#define KERNEL_INIT

#include <stdint.h>
#include <forbia/kernel.h>
#include <io/io.h>
#include <mem/mem.h>
#include <mem/malloc.h>
#include <dev/dev.h>
#include <vid/lfb.h>
#include <shrimp/shrimp.h>
#include <libk/printk.h>

#define STACK_SIZE 65536 /* 64KiB */

#ifdef ARCH_x86_64
    #include <arch/x86_64/gdt.h>
    #include <arch/x86_64/idt/idt.h>
#endif

#endif
