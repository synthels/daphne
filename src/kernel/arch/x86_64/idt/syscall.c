/*
 * Copyright (C) 2022 synthels <synthels.me@gmail.com>
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
 * Interrupt handlers
 */

#include <arch/x86_64/ports.h>
#include <stdint.h>
#include <arch/x86_64/x64.h>

#include <lib/log.h>

#ifdef ARCH_x86_64
    #include <arch/x86_64/x64.h>
#endif

/* syscall handler */
void syscall_handler(regs_t *r)
{
    pr_warn("not implemented - syscall(%i)", r->rax);
}
