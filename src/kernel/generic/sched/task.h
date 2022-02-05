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
 */

#pragma once

#include <lib/printk.h>
#include <lib/string.h>
#include <lib/vec.h>

#include <generic/malloc/malloc.h>

#ifdef ARCH_x86_64
    #include <arch/x86_64/x64.h>
    #include <arch/x86_64/pmm.h>
    #include <arch/x86_64/vmm.h>
#endif

#include <generic/malloc/mmu.h>

typedef uint16_t pid_t;
enum task_state_t {
    DEAD,
    ASLEEP,
    RUNNING
};

struct task {
    pid_t pid;
    context_t *context;
    enum task_state_t state;
    vec_t *children;
};

/**
 * init_sched
 *   brief: init sched
 */
void init_sched(void);
