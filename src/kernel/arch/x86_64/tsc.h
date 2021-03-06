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

#include <stdint.h>
#include <generic/time/sleep.h>

/**
 * tsc_init
 *   brief: calibrate tsc
 */
void tsc_init(void);

/**
 * rdtsc
 *   brief: rdtsc (what, don't you get it??)
 */
uint64_t rdtsc(void);

/**
 * tsc_delay
 *   brief: tsc_delay (what, you still don't get it??)
 */
void tsc_delay(uint64_t amount);

/**
 * tsc_get_mhz
 *   brief: get tsc timing
 */
uint64_t tsc_get_mhz(void);
