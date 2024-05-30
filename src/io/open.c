// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>

int open(const char *filename, int flags, ...)
{
    // Invoke the open syscall.
    int ret = syscall(__NR_open, filename, flags, 0);

    // Error checking.
    if (ret < 0) {
        errno = -ret;
        ret = -1;
    }

    return ret;
}
