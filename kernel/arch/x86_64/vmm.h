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


#ifndef KERNEL_x86_64_VMM
#define KERNEL_x86_64_VMM

#include <stddef.h>
#include <stdint.h>
#include <forbia/kernel.h>

void vmm_map_page(uint64_t virt_addr, uint64_t phys_addr, uint64_t flags);

void vmm_alloc_space(uint64_t virt_from, uint64_t virt_to, uint64_t flags);

#endif
