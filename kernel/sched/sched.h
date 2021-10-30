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

#pragma once

#include <sched/task.h>
#include <stddef.h>

/**
 * fire
 *   brief: fire a task
 */
void fire(struct task *task);

/**
 * halt
 *   brief: halt a task
 */
void halt(struct task *task);

/**
 * kill
 *   brief: kill a task
 */
void kill(struct task *task);

/**
 * switch_to
 *   brief: switch tasks
 */
void switch_to(struct task *tasks, size_t n);