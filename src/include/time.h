/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef __STDIO_H__
#define __STDIO_H__ 1

typedef long unsigned int time_t;

struct timespec {
    time_t tv_sec;
    long tv_nsec;
};

int nanosleep(const struct timespec *req, struct timespec *rem);

#endif
