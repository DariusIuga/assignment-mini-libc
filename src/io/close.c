// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <unistd.h>

int close(int fd)
{
    // Invoke the close syscall.
    int ret = syscall(__NR_close, fd);

    // Error checking.
    if (ret < 0) {
        errno = -ret;
        ret = -1;
    }

    return ret;
}
